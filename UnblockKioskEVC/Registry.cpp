// Registry.cpp: implementation of the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Registry.h"

#include <windows.h>
#include <tchar.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistry::CRegistry()
{

}

CRegistry::~CRegistry()
{

}

//////////////////////////////////////////////////////////////////////

// Checks if key exists
bool CRegistry::IsRegKey(HKEY hKeyRoot, LPCTSTR pszSubKey)
{
    HKEY hKey;
    LONG lRes;

	lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, NULL, KEY_READ, &hKey);

    if(lRes == ERROR_SUCCESS)
    {
		RegCloseKey(hKey);
		return true;
    }


    SetLastError((DWORD)lRes);
    return false;
}

//////////////////////////////////////////////////////////////////////

// Checks if value exists
bool CRegistry::IsRegValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue)
{
    HKEY hKey;
    LONG lRes;

	lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, NULL, KEY_READ, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError((DWORD)lRes);
        return false;
    }

    lRes = RegQueryValueEx(hKey, pszValue, NULL, NULL, NULL, NULL);

    if(lRes == ERROR_SUCCESS)
    {
		RegCloseKey(hKey);
		return true;
    }


    SetLastError((DWORD)lRes);
    return false;
}

//////////////////////////////////////////////////////////////////////

// Deletes a value from a given subkey and root
bool CRegistry::DeleteRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue)
{
    HKEY hKey;
    LONG lRes;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_SET_VALUE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError((DWORD)lRes);
        return false;
    }

    lRes = RegDeleteValue(hKey, pszValue);

    RegCloseKey(hKey);

    if(lRes == ERROR_SUCCESS)
        return true;

    SetLastError(lRes);
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Creates a key specified by pszSubKey - you can't create
// keys directly under HKEY_LOCAL_MACHINE in Windows NT or 2000
// just for an extra bit of info.
bool CRegistry::CreateRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey)
{
    HKEY hKey;
    DWORD dwFunc;
    LONG  lRet;

    lRet = RegCreateKeyEx(
        hKeyRoot,
        pszSubKey,
        0,
        (LPTSTR)NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &hKey,
        &dwFunc
    );

    if(lRet == ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        hKey = (HKEY)NULL;
        return true;
    }

    SetLastError((DWORD)lRet);
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRegistry::DeleteRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey)
{
    DWORD dwRet = ERROR_SUCCESS;

	dwRet = RegDeleteKey(hKeyRoot, pszSubKey);
    if(dwRet == ERROR_SUCCESS)
        return true;

    SetLastError(dwRet);
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fetch a binary value. If the size specified by rdwSize is too small, rdwSize will
// be set to the correct size.
bool CRegistry::Get_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pBuffer, DWORD& rdwSize)
{
    HKEY  hKey;
    DWORD dwType = REG_BINARY;
    DWORD dwSize = rdwSize;
    LONG lRes   = 0;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError((DWORD)lRes);
        return false;
    }

    lRes = RegQueryValueEx(hKey, pszValue, 0, &dwType, (LPBYTE)pBuffer, &dwSize);

    rdwSize = dwSize;
    RegCloseKey(hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    if(dwType != REG_BINARY)
    {
        //throw ERROR_WRONG_TYPE;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fetch a little endian DWORD from the registry
//(see platform SDK "Registry Value Types")
bool CRegistry::Get_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned __int64 &u64Buff)
{
    HKEY hKey;
    DWORD dwType = REG_QWORD;
    DWORD dwSize = sizeof(u64Buff);
    LONG  lRes;

    u64Buff = 0;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegQueryValueEx(hKey, pszValue, 0, &dwType, (LPBYTE)&u64Buff, &dwSize);

    RegCloseKey(hKey);

    if(dwType != REG_QWORD)
        //throw ERROR_WRONG_TYPE;

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fetch a little endian DWORD from the registry
//(see platform SDK "Registry Value Types")
bool CRegistry::Get_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned long &ulBuff)
{
    HKEY hKey;
    DWORD dwType = REG_DWORD;
    DWORD dwSize = sizeof(ulBuff);
    LONG  lRes;

    ulBuff = 0;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_READ, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegQueryValueEx(hKey, pszValue, 0, &dwType, (LPBYTE)&ulBuff, &dwSize);

    RegCloseKey(hKey);

    if(dwType!=REG_DWORD)
        //throw ERROR_WRONG_TYPE;

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Retrieve a string value. If the given buffer for the string is too small (specified
// by rdwSize), rdwSize is increased to the correct value. If the buffer is bigger than
// the retrieved string, rdwSize is set to the length of the string (in bytes) including
// the terminating null.
bool CRegistry::Get_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPTSTR pszBuffer, DWORD& rdwSize)
{
    HKEY  hKey;
    LONG  lRes;
    DWORD dwType = KEY_ALL_ACCESS;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, NULL, KEY_READ, &hKey);
    if(lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        SetLastError(lRes);
        return false;
    }

    lRes = RegQueryValueEx(hKey, pszValue, NULL, NULL, (unsigned char*)pszBuffer, &rdwSize);


	ASSERT(dwType==REG_SZ);

	if (dwType==REG_MULTI_SZ)


    if(lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        SetLastError(lRes);
        return false;
    }

    lRes = RegCloseKey(hKey);
    if(lRes != ERROR_SUCCESS)
    {
        RegCloseKey(hKey);
        SetLastError(lRes);
        return false;
    }


    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes a binary value to the registry
bool CRegistry::Set_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pData, DWORD dwSize)
{
    HKEY hKey;
    LONG lRes = 0;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegSetValueEx(hKey, pszValue, 0, REG_BINARY, (unsigned char*)pData, dwSize);

	RegFlushKey(hKey);
    RegCloseKey(hKey);

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes a DWORD value to the registry
bool CRegistry::Set_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned long ulValue)
{
    HKEY hKey;
    LONG lRes;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegSetValueEx(hKey, pszValue, 0, REG_DWORD, (unsigned char*)&ulValue, sizeof(ulValue));

	RegFlushKey(hKey);
    RegCloseKey(hKey);

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes a DWORD_PTR value to the registry
bool CRegistry::Set_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned __int64 u64Value)
{
    HKEY hKey;
    LONG lRes;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegSetValueEx(hKey, pszValue, 0, REG_QWORD, (LPBYTE)&u64Value, sizeof(u64Value));

	RegFlushKey(hKey);
    RegCloseKey(hKey);

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes a string to the registry.
bool CRegistry::Set_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString)
{
    HKEY  hKey;
    LONG  lRes;
    DWORD dwSize = lstrlen(pszString) * sizeof(TCHAR);

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegSetValueEx(hKey, pszValue, 0, REG_SZ, (unsigned char*)pszString, dwSize);

	RegFlushKey(hKey);
    RegCloseKey(hKey);

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Writes a string to the registry.
bool CRegistry::Set_MultiStringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString)
{
    HKEY  hKey;
    LONG  lRes;
    DWORD dwSize = lstrlen(pszString) * sizeof(TCHAR)+1;

    lRes = RegOpenKeyEx(hKeyRoot, pszSubKey, 0, KEY_WRITE, &hKey);

    if(lRes != ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    lRes = RegSetValueEx(hKey, pszValue, 0, REG_MULTI_SZ, (unsigned char*)pszString, dwSize);

	RegFlushKey(hKey);
    RegCloseKey(hKey);

    if(lRes!=ERROR_SUCCESS)
    {
        SetLastError(lRes);
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRegistry::Set_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, bool bVal)
{
	DWORD dwVal = 0;

	if(bVal)
	{
		dwVal = 1;
	}

	return Set_DWORDRegistryValue(hKeyRoot, pszSubKey, pszValue, dwVal);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CRegistry::Get_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue)
{
	DWORD dwVal = 0;

	if(Get_DWORDRegistryValue(hKeyRoot, pszSubKey, pszValue, dwVal))
	{
		return (dwVal > 0);
	}
	return false;
}


