#pragma once
#include "afxwin.h"

class CMyCommandLineInfo :
  public CCommandLineInfo
{
public:
  void ParseParam(const TCHAR* pszParam,  BOOL bFlag, BOOL bLast);
  CMyCommandLineInfo(void);
  ~CMyCommandLineInfo(void);
  CArray<CString> m_arrayFiles;
};
