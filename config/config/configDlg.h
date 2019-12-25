// configDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CconfigDlg dialog
class CconfigDlg : public CDialog
{
// Construction
public:
	CconfigDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFIG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
 CEdit EDIT_Rows;
 CEdit EDIT_Cols;
 CEdit EDIT_Speed;
 CEdit EDIT_Startx;
 CEdit EDIT_Starty;
 CEdit EDIT_Startz;
 afx_msg void OnBnClickedOk();
 afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
 CEdit EDIT_Distance;
};
