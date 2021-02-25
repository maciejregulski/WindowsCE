// UnblockKioskEVC.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ParseCmdLine.h"
#include "Registry.h"

#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#include <winsock2.h>

// need link with Ws2_32.lib
#pragma comment(lib, "Ws2.lib")

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	LPTSTR lpBuffer = NULL;
	LPTSTR lpValue = NULL;
	DWORD dwBufferSize = 0;

	static TCHAR seps[] = _T(" ");
	TCHAR **argv;
	int argc = 0;


	dwBufferSize = lstrlen(lpCmdLine) * sizeof(TCHAR);
	lpBuffer = new TCHAR[dwBufferSize];
	lstrcpy(lpBuffer, lpCmdLine);


	CParseCmdLine oParseCmdLine(lpBuffer); 
	argc = oParseCmdLine.GetArgCount();
	argv = oParseCmdLine.GetArgList();

	//_tprintf(_T("Command line: %s\n\n"), lpBuffer);
	//_tprintf(_T("->argv[%d]: %s\n"), i, argv[i]);

	_tprintf(_T("argc: %d\n\n"), argc);	


	if (argc == 0) {
		_tprintf(_T("default action: unblock\n"));
		SetKiosk(false);
	} 
	else {

		if (oParseCmdLine.HasSwitch(L"-help")) {
			ShowHelp();
		} 
		else {

			if (oParseCmdLine.HasSwitch(L"-unblock")) {
				SetKiosk(false);
				_tprintf(_T("action: unblock\n"));
			} else if (oParseCmdLine.HasSwitch(L"-kiosk")) {
				SetKiosk(true);
				_tprintf(_T("action: return kiosk mode\n"));
			} 
			
			if (oParseCmdLine.HasSwitch(L"-lan")) {

				SetLan(oParseCmdLine.GetArgument(L"-lan", 1), 				
					oParseCmdLine.GetArgument(L"-lan", 2));				

			}
		}
	}


	delete[] lpBuffer; // DO NOT FORGET THIS!


	return 0;
}

void WINAPI ShowHelp()
{
	TCHAR exePath[MAX_PATH];

	if(GetModuleFileName(0, exePath, MAX_PATH) == 0)
		return;

	_tprintf(_T("command line is: %s [-unblock] [-kiosk] [-lan ip mask]\n"), exePath);
	_tprintf(_T("default action: unblock (if called without any parameters)\n"));
	_tprintf(_T("example return to kiosk mode: %s -kiosk\n"), exePath);
	_tprintf(_T("example setup lan ip and mask: %s -lan 192.168.1.1 255.255.255.0\n"), exePath);

}

void WINAPI SetKiosk(bool kiosk)
{

	CRegistry oRegistry;
	// Declare buffer to read actual value
	DWORD dwBufferSize = 100;
	LPTSTR lpszValue = new TCHAR[dwBufferSize];

	if (oRegistry.Get_StringRegistryValue(HKEY_LOCAL_MACHINE, initKey, kioskKey, lpszValue, dwBufferSize)) {
		_tprintf( TEXT(" Init: %s\n\n"), lpszValue );
	}

	delete[] lpszValue; // DO NOT FORGET THIS!

	// Set explorer value
	if (kiosk)
		oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, initKey, kioskKey, L"_explorer.exe\0");
	else oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, initKey, kioskKey, L"explorer.exe\0");

}

// while setting multi string
// LPCTSTR ipValue = TEXT( "192.168.10.99\0\0" );
// LPCTSTR maskValue = TEXT( "255.255.0.0\0\0" );

void WINAPI SetLan(LPCTSTR ipValue, LPCTSTR maskValue)
{
	CRegistry oRegistry;

	// First check AX88796C1
	if (oRegistry.IsRegKey(HKEY_LOCAL_MACHINE, lanAX88796C1Key)) {
		// Set ip
		if (CheckIP(LPTSTR(ipValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX88796C1Key, ipKey, ipValue))
				_tprintf( TEXT( " setting ip for AX88796C1 %s\n", ), ipValue);
		// Set mask  
		if (CheckIP(LPTSTR(maskValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX88796C1Key, maskKey, maskValue))
				_tprintf( TEXT( " setting mask for AX88796C1 %s\n", ), maskValue);
		// Set DHCP
		oRegistry.Set_DWORDRegistryValue(HKEY_LOCAL_MACHINE, lanAX88796C1Key, dhcpKey, (DWORD)0);
	}
	// Second check AX887961
	else if (oRegistry.IsRegKey(HKEY_LOCAL_MACHINE, lanAX887961Key)) {
		// Set ip
		if (CheckIP(LPTSTR(ipValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX887961Key, ipKey, ipValue))
				_tprintf( TEXT( " setting ip for AX887961 %s\n", ), ipValue);
		// Set mask  
		if (CheckIP(LPTSTR(maskValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX887961Key, maskKey, maskValue))
				_tprintf( TEXT( " setting mask for AX887961 %s\n", ), maskValue);
		// Set DHCP
		oRegistry.Set_DWORDRegistryValue(HKEY_LOCAL_MACHINE, lanAX887961Key, dhcpKey, (DWORD)0);
	}
	// Third check AX88772B1 (Dual Core)
	else if (oRegistry.IsRegKey(HKEY_LOCAL_MACHINE, lanAX88772B1Key)) {
		// Set ip
		if (CheckIP(LPTSTR(ipValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX88772B1Key, ipKey, ipValue))
				_tprintf( TEXT( " setting ip for AX88772B1 %s\n", ), ipValue);
		// Set mask  
		if (CheckIP(LPTSTR(maskValue))) 
			if (oRegistry.Set_StringRegistryValue(HKEY_LOCAL_MACHINE, lanAX88772B1Key, maskKey, maskValue))
				_tprintf( TEXT( " setting mask for AX88772B1 %s\n", ), maskValue);
		// Set DHCP
		oRegistry.Set_DWORDRegistryValue(HKEY_LOCAL_MACHINE, lanAX88772B1Key, dhcpKey, (DWORD)0);
	}
}

bool WINAPI CheckIP(TCHAR *lpAddress)
{
	unsigned long ulAddr = INADDR_NONE;
	struct in_addr addr;

	if (lpAddress == NULL)
		return false;
	
	char *buff = new char[100];
	wcstombs(buff, lpAddress, 100);

	// Call inet_addr(). If the call succeeds,
	// the result variable will hold a IN_ADDR
	ulAddr = inet_addr(buff);

    if ( ulAddr == INADDR_NONE ) {
        printf("inet_addr failed and returned INADDR_NONE\n");
        return false;
    }   
    
    if (ulAddr == INADDR_ANY) {
        printf("inet_addr failed and returned INADDR_ANY\n");
        return false;  
    }

    if (ulAddr == INADDR_LOOPBACK) {
        printf("inet_addr failed and returned INADDR_LOOPBACK\n");
        return false;  
    }

    if (ulAddr == INADDR_BROADCAST) {
        printf("inet_addr failed and returned INADDR_BROADCAST\n");
        return false;  
    }

	addr.S_un.S_addr = ulAddr;

	if (strcmp(inet_ntoa(addr), buff) == 0) {
		printf("inet_addr returned success on: %s == %s\n", buff, inet_ntoa(addr));
		return true;
	} else {
		printf("inet_addr failed and returned %s\n", inet_ntoa(addr));
	}

	return false;
}