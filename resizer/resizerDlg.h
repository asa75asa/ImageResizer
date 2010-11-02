
// resizerDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CresizerDlg dialog
class CresizerDlg : public CDialog
{
// Construction
public:
	CresizerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RESIZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnBnClickedRadio1();
  CSliderCtrl m_sliderQuality;
  int m_iResolution;
  long m_lWidth;
  long m_lHeight;
  BOOL m_bKeepRatio;
  long m_lQuality;
  CString m_sPrefix;
  CString m_sSuffix;
  afx_msg void OnBnClickedRadio6();
  void EnableControls(void);
  afx_msg void OnBnClickedRadio2();
  afx_msg void OnBnClickedRadio3();
  afx_msg void OnBnClickedRadio4();
  afx_msg void OnBnClickedRadio5();
  afx_msg void OnEnChangeEditQuality();
//  afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnBnClickedCheck1();
  afx_msg void OnEnChangeEditWidth();
  float m_fRatio;
  void SetFileNames(const CString & sFiles);
  void SetFileNames(const CArray<CString> & arrayFiles);
protected:
  CArray<CString> m_arrayFiles;
public:
  afx_msg void OnBnClickedOk();
  void ProcessFiles(void);
  static UINT __cdecl CompressFunction(LPVOID pParam);
  UINT CompressFunction(void);
  CProgressCtrl m_progress;
protected:
  UINT m_lNewWidth;
  UINT m_lNewHeight;
public:
  void LoadSettings(void);
  void SaveSettings(void);
};
