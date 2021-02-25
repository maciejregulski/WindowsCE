// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// Local Header Files

// TODO: reference additional headers your program requires here

const LPCTSTR initKey = L"init";
const LPCTSTR kioskKey = _T( "Launch50" );

const LPCTSTR lanAX88796C1Key = L"Comm\\AX88796C1\\Parms\\TcpIp";
const LPCTSTR lanAX887961Key = L"Comm\\AX887961\\Parms\\TcpIp";
const LPCTSTR lanAX88772B1Key = L"Comm\\AX88772B1\\Parms\\TcpIp";

const LPCTSTR ipKey = TEXT( "IPAddress" );
const LPCTSTR maskKey = TEXT( "SubnetMask" );
const LPCTSTR dhcpKey = TEXT( "EnableDHCP" );

void WINAPI ShowHelp();
void WINAPI SetKiosk(bool kiosk);
void WINAPI SetLan(LPCTSTR ipValue, LPCTSTR maskValue);
bool WINAPI CheckIP(TCHAR *lpAddress);


//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
