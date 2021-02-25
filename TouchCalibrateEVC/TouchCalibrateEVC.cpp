// TouchCalibrateEVC.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "pwinuser.h"
#include <windows.h>

typedef BOOL (WINAPI* PTouchCalibrate)(void);

int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
 	// TODO: Place code here.

/*
	HINSTANCE hDll = LoadLibrary(L"CoreDll.dll");
	reinterpret_cast<BOOL (*)(void)>(GetProcAddress(hDll, MAKEINTRESOURCE(0x36D)))();
	FreeLibrary(hDll);
*/

/*
	HMODULE hCoreDLL = LoadLibrary(_T("coredll.dll"));
	PTouchCalibrate pTouchCalibrate = (PTouchCalibrate)GetProcAddress(hCoreDLL, _T("TouchCalibrate"));

	if (pTouchCalibrate)
		pTouchCalibrate();
*/

	TouchCalibrate();

	// Declare a key to store the result
	HKEY hKey; 

	// Open the Registry Key
	DWORD lRv = RegOpenKeyEx (HKEY_LOCAL_MACHINE, L"", NULL, KEY_READ, &hKey);

	if (lRv == ERROR_SUCCESS)
	{
		RegFlushKey(hKey);
	}

	return 0;
}

