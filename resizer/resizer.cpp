
// resizer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "resizer.h"
#include "resizerDlg.h"
#include "MyCommandLineInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CresizerApp

BEGIN_MESSAGE_MAP(CresizerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CresizerApp construction

CresizerApp::CresizerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CresizerApp object

CresizerApp theApp;


// CresizerApp initialization

BOOL CresizerApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("ImageResizer"));

  CMyCommandLineInfo cmdLine;
  ParseCommandLine(cmdLine);

	CresizerDlg dlg;
  dlg.SetFileNames(cmdLine.m_arrayFiles);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
