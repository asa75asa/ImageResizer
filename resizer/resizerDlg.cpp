
// resizerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resizer.h"
#include "resizerDlg.h"

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CresizerDlg dialog


inline int round(double x)
{
  return int(x > 0.0 ? x + 0.5 : x - 0.5);
}

CresizerDlg::CresizerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CresizerDlg::IDD, pParent)
  , m_iResolution(4)
  , m_lWidth(1600)
  , m_lHeight(1200)
  , m_bKeepRatio(TRUE)
  , m_lQuality(80)
  , m_sPrefix(_T("Resize of "))
  , m_sSuffix(_T(""))
  , m_fRatio((float)m_lWidth / m_lHeight)
  , m_lNewWidth(0)
  , m_lNewHeight(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CresizerDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_SLIDER1, m_sliderQuality);
  DDX_Radio(pDX, IDC_RADIO1, m_iResolution);
  DDX_Text(pDX, IDC_EDIT_WIDTH, m_lWidth);
  DDX_Text(pDX, IDC_EDIT_HEIGHT, m_lHeight);
  DDX_Check(pDX, IDC_CHECK1, m_bKeepRatio);
  DDX_Text(pDX, IDC_EDIT_QUALITY, m_lQuality);
  DDX_Text(pDX, IDC_EDIT_PREFIX, m_sPrefix);
  DDX_Text(pDX, IDC_EDIT_SUFFIX, m_sSuffix);
  DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CresizerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDC_RADIO1, &CresizerDlg::OnBnClickedRadio1)
  ON_BN_CLICKED(IDC_RADIO6, &CresizerDlg::OnBnClickedRadio6)
  ON_BN_CLICKED(IDC_RADIO2, &CresizerDlg::OnBnClickedRadio2)
  ON_BN_CLICKED(IDC_RADIO3, &CresizerDlg::OnBnClickedRadio3)
  ON_BN_CLICKED(IDC_RADIO4, &CresizerDlg::OnBnClickedRadio4)
  ON_BN_CLICKED(IDC_RADIO5, &CresizerDlg::OnBnClickedRadio5)
  ON_EN_CHANGE(IDC_EDIT_QUALITY, &CresizerDlg::OnEnChangeEditQuality)
//  ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CresizerDlg::OnNMCustomdrawSlider1)
ON_WM_HSCROLL()
ON_WM_VSCROLL()
ON_BN_CLICKED(IDC_CHECK1, &CresizerDlg::OnBnClickedCheck1)
ON_EN_CHANGE(IDC_EDIT_WIDTH, &CresizerDlg::OnEnChangeEditWidth)
//ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CresizerDlg::OnNMCustomdrawProgress1)
ON_BN_CLICKED(IDOK, &CresizerDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CresizerDlg message handlers

BOOL CresizerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

  LoadSettings();
  UpdateData(FALSE);
  EnableControls();
  m_sliderQuality.SetRange(0, 100);
  m_sliderQuality.SetPos(m_lQuality);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CresizerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CresizerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CresizerDlg::OnBnClickedRadio1()
{
  EnableControls();
}

void CresizerDlg::OnBnClickedRadio6()
{
  EnableControls();
}

void CresizerDlg::EnableControls(void)
{
  UpdateData();
  CWnd *pWnd = NULL;
  
  BOOL bEnable = (m_iResolution == 5);
  int controls[] = {
      IDC_EDIT_WIDTH
    , IDC_EDIT_HEIGHT
    , IDC_CHECK1
  };

  for (int i = 0; i < sizeof(controls) / sizeof(int); i++)
  {
    pWnd = GetDlgItem(controls[i]);
    if (pWnd)
    {
      pWnd->EnableWindow(bEnable);
    }
  }

  pWnd = GetDlgItem(IDC_EDIT_HEIGHT);
  if (pWnd)
  {
    pWnd->EnableWindow(!m_bKeepRatio);
  }

  pWnd = GetDlgItem(IDC_PROGRESS1);
  if (pWnd)
  {
    pWnd->ShowWindow(SW_HIDE);
  }
}

void CresizerDlg::OnBnClickedRadio2()
{
  EnableControls();
}

void CresizerDlg::OnBnClickedRadio3()
{
  EnableControls();
}

void CresizerDlg::OnBnClickedRadio4()
{
  EnableControls();
}

void CresizerDlg::OnBnClickedRadio5()
{
  EnableControls();
}

void CresizerDlg::OnEnChangeEditQuality()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CDialog::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  long lQuality = m_lQuality;
  UpdateData();
  if (m_lQuality < 0) m_lQuality = 0;
  if (m_lQuality > 100) m_lQuality = 100;
  if (lQuality != m_lQuality)
  {
    m_sliderQuality.SetPos(m_lQuality);
  }

  UpdateData(FALSE);
}

//void CresizerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//  LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//  // TODO: Add your control notification handler code here
//  *pResult = 0;
//}

void CresizerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  long lQuality = m_sliderQuality.GetPos();
  UpdateData();
  if (m_lQuality != lQuality)
  {
    m_lQuality = lQuality;
    UpdateData(FALSE);
  }

  CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CresizerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
  long lQuality = m_sliderQuality.GetPos();
  UpdateData();
  if (m_lQuality != lQuality)
  {
    m_lQuality = lQuality;
    UpdateData(FALSE);
  }

  CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CresizerDlg::OnBnClickedCheck1()
{
  EnableControls();
  if (m_bKeepRatio)
  {
    m_fRatio = (float)m_lWidth / m_lHeight;
  }
}

void CresizerDlg::OnEnChangeEditWidth()
{
  // TODO:  If this is a RICHEDIT control, the control will not
  // send this notification unless you override the CDialog::OnInitDialog()
  // function and call CRichEditCtrl().SetEventMask()
  // with the ENM_CHANGE flag ORed into the mask.

  if (m_bKeepRatio)
  {
    long lWidth = m_lWidth;
    UpdateData();
    if ((m_lWidth != lWidth) && (m_fRatio > 0.000001))
    {
      m_lHeight = (long)(round((float)m_lWidth / m_fRatio));
      UpdateData(FALSE);
    }
  }
}

void CresizerDlg::SetFileNames(const CString & sFiles)
{
  CString sToken = _T(" ");
  int iPos = 0;
  CString sRes;

  sRes = sFiles.Tokenize(sToken, iPos);
  while (sRes != _T(""))
  {
    m_arrayFiles.Add(sRes);
    sRes = sFiles.Tokenize(sToken, iPos);
  };   
}

void CresizerDlg::SetFileNames(const CArray<CString> & arrayFiles)
{
  for (int i = 0; i < arrayFiles.GetCount(); i++)
  {
    m_arrayFiles.Add(arrayFiles[i]);
  }
}
//void CresizerDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//  LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//  // TODO: Add your control notification handler code here
//  *pResult = 0;
//}

void CresizerDlg::OnBnClickedOk()
{
  // OK button is pressed
  // check for files in array
  if (m_arrayFiles.GetCount() > 0)
  {
    UpdateData();
    SaveSettings();
    ProcessFiles();
  }
  else
  {
    OnOK();
  }
}

void CresizerDlg::ProcessFiles(void)
{
  m_progress.SetRange(0, m_arrayFiles.GetCount() * 100);
  m_progress.SetPos(0);
  m_progress.ShowWindow(SW_SHOW);

  UpdateData();
  switch (m_iResolution)
  {
  case 0:
    m_lNewHeight = 480;
    m_lNewWidth = 640;
    break;
  case 1:
    m_lNewHeight = 600;
    m_lNewWidth = 800;
    break;
  case 2:
    m_lNewHeight = 768;
    m_lNewWidth = 1024;
    break;
  case 3:
    m_lNewHeight = 900;
    m_lNewWidth = 1200;
    break;
  case 4:
    m_lNewHeight = 1200;
    m_lNewWidth = 1600;
    break;
  case 5:
    m_lNewHeight = m_lHeight;
    m_lNewWidth = m_lWidth;
    break;
  default:
    m_lNewHeight = 1200;
    m_lNewWidth = 1600;
  }

  AfxBeginThread(CompressFunction, (LPVOID)this);
}

UINT CresizerDlg::CompressFunction(LPVOID pParam)
{
  if (pParam)
  {
    CresizerDlg *pThis = (CresizerDlg*)pParam;
    UINT rv = pThis->CompressFunction();
    ::PostMessage(pThis->GetSafeHwnd(), WM_CLOSE, 0, 0);
    return rv;
  }
  return -1;
}

UINT CresizerDlg::CompressFunction(void)
{
  DWORD dwStart = GetTickCount();
  DWORD tick1, tick2;
  for (int i = 0; i < m_arrayFiles.GetCount(); i++)
  {
    UINT width, height;
    m_progress.SetPos(i * 100 + 0);
    using namespace cv;
    {
      char fileName[MAX_PATH];
      WideCharToMultiByte(CP_ACP, 0, m_arrayFiles[i], -1, fileName, MAX_PATH, NULL, NULL);
      Mat srcImageMat;
      try
      {
        srcImageMat = imread(fileName);
      }
      catch (CException* e)
      {
        continue;
      }
      
      width = srcImageMat.size().width ;
      height = srcImageMat.size().height;
      if ((width == 0) || (height == 0)) continue;

      m_progress.SetPos(i * 100 + 30);


      double ratio = (double)width / (double)height;
      double newRatio = (double)m_lNewWidth / (double)m_lNewHeight;
      if ((m_iResolution == 5) && (!m_bKeepRatio))
      {
        if (width < height)
        {
          long tmp = m_lNewHeight;
          m_lNewHeight = m_lNewWidth;
          m_lNewWidth = tmp;
        }
      }
      else
      {
        if (width > height)
        {
          m_lNewHeight = round((double)m_lNewWidth / ratio);
        }
        else
        {
          m_lNewWidth = m_lNewHeight;
          m_lNewHeight = round((double)m_lNewWidth / ratio);
        }
      }

      Mat newImageMat;
      cv::Size newSize(m_lNewWidth, m_lNewHeight);
      try
      {
        resize(srcImageMat, newImageMat, newSize, 0, 0, INTER_CUBIC);
      }
      catch (CException* e)
      {
        continue;
      }

      m_progress.SetPos(i * 100 + 90);

      TCHAR newFileNameW[MAX_PATH];
      if (m_sSuffix.GetLength() > 0)
      {
        CString tmp = m_arrayFiles[i].Left(m_arrayFiles[i].ReverseFind(_T('.')));
        CString ext = m_arrayFiles[i].Right(m_arrayFiles[i].GetLength() - m_arrayFiles[i].ReverseFind(_T('.')));
        wsprintf(newFileNameW, _T("%s%s%s%s"), m_sPrefix, tmp, m_sSuffix, ext);
      }
      else
      {
        wsprintf(newFileNameW, _T("%s%s%s"), m_sPrefix, m_arrayFiles[i], m_sSuffix);
      }
      char newFileName[MAX_PATH];
      WideCharToMultiByte(CP_ACP, 0, newFileNameW, -1, newFileName, MAX_PATH, NULL, NULL);

      vector<int> p;
      // set quality
      p.push_back(CV_IMWRITE_JPEG_QUALITY);
      p.push_back(m_lQuality);
      p.push_back(0);

      try
      {
        imwrite(newFileName, newImageMat, p);
      }
      catch (Exception* e)
      {
        e->formatMessage();
      	
      }

      // restore EXIF from original file
      Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(fileName);
      assert(image.get() != 0);
      image->readMetadata();

      Exiv2::ExifData &exifData = image->exifData();
      if (!exifData.empty()) 
      {
        Exiv2::Image::AutoPtr imageNew = Exiv2::ImageFactory::open(newFileName);
        assert(imageNew.get() != 0);

        imageNew->setExifData(exifData);
        imageNew->writeMetadata();
      }

    }  
  }
  return 0;
}

void CresizerDlg::LoadSettings(void)
{
  CString section = _T("Settings");
  
  m_iResolution = AfxGetApp()->GetProfileInt(section, _T("Resolution"), 4);
  if (m_iResolution < 0) m_iResolution = 0;
  if (m_iResolution > 5) m_iResolution = 5;
  
  m_lWidth = AfxGetApp()->GetProfileInt(section, _T("Width"), 1600);
  if (m_lWidth < 0) m_lWidth = 1600;
  if (m_lWidth > 10000) m_lWidth = 1600;

  m_lHeight = AfxGetApp()->GetProfileInt(section, _T("Height"), 1200);
  if (m_lHeight < 0) m_lHeight = 1200;
  if (m_lHeight > 10000) m_lHeight = 1200;

  m_bKeepRatio = AfxGetApp()->GetProfileInt(section, _T("KeepRatio"), TRUE);
  if (m_bKeepRatio < 0) m_bKeepRatio = TRUE;
  if (m_bKeepRatio > 1) m_bKeepRatio = TRUE;

  m_lQuality = AfxGetApp()->GetProfileInt(section, _T("Quality"), 80);
  if (m_lQuality > 100) m_lQuality = 100;
  if (m_lQuality < 0) m_lQuality = 10;

  m_sPrefix = AfxGetApp()->GetProfileString(section, _T("Prefix"), _T("Resize of "));
  m_sSuffix = AfxGetApp()->GetProfileString(section, _T("Suffix"), _T(""));
}

void CresizerDlg::SaveSettings(void)
{
  CString section = _T("Settings");
  AfxGetApp()->WriteProfileInt(section, _T("Resolution"), m_iResolution);
  AfxGetApp()->WriteProfileInt(section, _T("Width"), m_lWidth);
  AfxGetApp()->WriteProfileInt(section, _T("Height"), m_lHeight);
  AfxGetApp()->WriteProfileInt(section, _T("KeepRatio"), m_bKeepRatio);
  AfxGetApp()->WriteProfileInt(section, _T("Quality"), m_lQuality);
  AfxGetApp()->WriteProfileString(section, _T("Prefix"), m_sPrefix);
  AfxGetApp()->WriteProfileString(section, _T("Suffix"), m_sSuffix);
}

