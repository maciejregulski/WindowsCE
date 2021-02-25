// Registry.h: interface for the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRY_H__B7E34BE8_1C6B_47EC_ABC1_B6D2157574C8__INCLUDED_)
#define AFX_REGISTRY_H__B7E34BE8_1C6B_47EC_ABC1_B6D2157574C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRegistry  
{
public:
	CRegistry();
	virtual ~CRegistry();

	bool IsRegKey(HKEY hKeyRoot, LPCTSTR pszSubKey);
	bool IsRegValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
	bool CreateRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey);
	bool DeleteRegistryKey(HKEY hKeyRoot, LPCTSTR pszSubKey);
	bool DeleteRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
	bool Get_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pBuffer, DWORD& rdwSize);
	bool Get_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue);
	bool Get_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned long &ulBuff);
	bool Get_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned __int64 &u64Buff);
	bool Get_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPTSTR pszBuffer, DWORD& rdwSize);
	bool Set_MultiStringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString);
	bool Set_BinaryRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, PVOID pData, DWORD dwSize);
	bool Set_BOOLRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, bool bVal);
	bool Set_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned long ulValue);
	bool Set_DWORDRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, unsigned __int64 u64Buff);
	bool Set_StringRegistryValue(HKEY hKeyRoot, LPCTSTR pszSubKey, LPCTSTR pszValue, LPCTSTR pszString);

};

#endif // !defined(AFX_REGISTRY_H__B7E34BE8_1C6B_47EC_ABC1_B6D2157574C8__INCLUDED_)
