#include "StdAfx.h"
#include "MyCommandLineInfo.h"

CMyCommandLineInfo::CMyCommandLineInfo(void)
{
}

CMyCommandLineInfo::~CMyCommandLineInfo(void)
{
}

void CMyCommandLineInfo::ParseParam(const TCHAR* pszParam,  BOOL bFlag, BOOL bLast)
{
  m_arrayFiles.Add(pszParam);
  CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
}