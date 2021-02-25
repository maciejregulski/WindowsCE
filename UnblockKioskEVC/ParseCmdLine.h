// ParseCmdLine.h: interface for the CParseCmdLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARSECMDLINE_H__20B5B057_7D5D_4A64_BBDE_CD703F1B3D4E__INCLUDED_)
#define AFX_PARSECMDLINE_H__20B5B057_7D5D_4A64_BBDE_CD703F1B3D4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CParseCmdLine  
{	
public:
	CParseCmdLine(TCHAR *lpCmdLine);
	virtual ~CParseCmdLine();
private:
	TCHAR **m_lpszArgList;
	int m_nArgCount;
public:
	TCHAR **GetArgList();
	int GetArgCount();
	bool HasSwitch(TCHAR *lpParamName);
	TCHAR *GetArgument(TCHAR *lpParamName, int nIdx);
protected:
	bool IsSwitch(TCHAR *lpParam);
};

#endif // !defined(AFX_PARSECMDLINE_H__20B5B057_7D5D_4A64_BBDE_CD703F1B3D4E__INCLUDED_)
