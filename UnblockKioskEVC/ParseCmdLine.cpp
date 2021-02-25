// ParseCmdLine.cpp: implementation of the CParseCmdLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ParseCmdLine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParseCmdLine::CParseCmdLine(TCHAR *lpCmdLine1)
		: m_lpszArgList(NULL)
		, m_nArgCount(0)
{
	static TCHAR seps[] = _T(" ");
    TCHAR *lpCmdLine = GetCommandLine();
	TCHAR *token;
//_tprintf(_T("Command line: %s\n\n"), lpCmdLine);
	// Establish m_lpCmdLine and get the first token
	token = _tcstok( lpCmdLine, seps );
	while( token != NULL )
	{
		// While there are tokens in "lpCmdLine" 

		// increment m_nArgCount
		++m_nArgCount;

                    // Get next token:
		token = _tcstok( NULL, seps );
	}

	// if any arguements
	if( m_nArgCount )
	{
		m_lpszArgList = new TCHAR *[m_nArgCount];

		// loop again and store the pointers
		for( int nIndex = 0; nIndex < m_nArgCount; nIndex++ )
		{
			m_lpszArgList[nIndex] = _tcstok( lpCmdLine, seps );
			lpCmdLine += (_tcslen(lpCmdLine) + 1);
		}
	}
}

CParseCmdLine::~CParseCmdLine()
{
	if( NULL != m_lpszArgList )
	{
		delete [] m_lpszArgList;
		m_lpszArgList = NULL;
	}
}

TCHAR ** CParseCmdLine::GetArgList()
{
	return m_lpszArgList;
}

int CParseCmdLine::GetArgCount()
{
	return m_nArgCount;
}

/*
   was the switch found on the command line ?

   ex. if the command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

   call                          return
   ----                          ------
   cmdLine.HasSwitch("-a")       true
   cmdLine.HasSwitch("-z")       false
*/
bool CParseCmdLine::HasSwitch(TCHAR *lpSwitch)
{
	if (lpSwitch == NULL)
		return false;

	for( int i = 0; i < m_nArgCount; i++ )
	{
		if (_tcscmp(m_lpszArgList[i], lpSwitch) == 0)
			return true;

	}
	return false;
}

/*
   fetch a argument associated with a switch. throws an exception 
   of (int)0, if the parameter at index iIdx is not found.

   example :
  
   command line is : app.exe -a p1 p2 p3 -b p4 -c -d p5

   call                             return
   ----                             ------
   cmdLine.GetArgument("-a", 1)     p1
   cmdLine.GetArgument("-b", 2)     returns an NULL

*/
TCHAR * CParseCmdLine::GetArgument(TCHAR *lpSwitch, int nIdx)
{
	if (lpSwitch == NULL)
		return NULL;

	for( int i = 0; i < m_nArgCount; i++ )
	{
		if ((_tcscmp(m_lpszArgList[i], lpSwitch) == 0) && (i+nIdx < m_nArgCount))
			if (!IsSwitch(m_lpszArgList[i+nIdx]))
				return m_lpszArgList[i+nIdx];

	}
	return NULL;
}

/*
   test a parameter to see if it's a switch :

   switches are of the form : -x
   where 'x' is one or more characters.
   the first character of a switch must be non-numeric!
*/
bool CParseCmdLine::IsSwitch(TCHAR *lpParam)
{
	if (lpParam == NULL)
		return false;

	// switches must have at least one character after the '-'
	int len = lstrlen(lpParam);
	if (len <= 1)
		return false;

	// switches always start with '-'
	if (lpParam[0] == '-') {
		// allow negative numbers as arguments.
		// ie., don't count them as switches
		return (!isdigit(lpParam[1]));
	}

	return false;
}