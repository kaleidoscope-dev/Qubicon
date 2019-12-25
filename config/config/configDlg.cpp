// configDlg.cpp : implementation file
//

#include "stdafx.h"
#include "config.h"
#include "configDlg.h"
#include "include\I_cSettings.h"
#include ".\configdlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;

//#define DEBUG_OFF

string toString(int c)
{
 char *ch = new char[32];

 sprintf(ch,"%d",c);
 string s(ch);
 delete []ch;
 return s;
 
}





string toStringf(float c)
{
 char *ch = new char[32];


 sprintf(ch,"%f",c);
 string s(ch);
 delete []ch;
 return s;
}

int toInt(string s)
{

    int r = atoi(s.c_str());
 return r;
}

float toFloat(string s)
{
    float f = (float)atof(s.c_str());
    return (float)f;
}





// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
 afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
 ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CconfigDlg dialog



CconfigDlg::CconfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CconfigDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CconfigDlg::DoDataExchange(CDataExchange* pDX)
{
 CDialog::DoDataExchange(pDX);
 DDX_Control(pDX, IDC_EDIT1, EDIT_Rows);
 DDX_Control(pDX, IDC_EDIT2, EDIT_Cols);
 DDX_Control(pDX, IDC_EDIT3, EDIT_Speed);
 DDX_Control(pDX, IDC_EDIT4, EDIT_Startx);
 DDX_Control(pDX, IDC_EDIT5, EDIT_Starty);
 DDX_Control(pDX, IDC_EDIT6, EDIT_Startz);
 DDX_Control(pDX, IDC_EDIT7, EDIT_Distance);
}

BEGIN_MESSAGE_MAP(CconfigDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CconfigDlg message handlers

bool ret(string x)
{
 int c = 0;
 return x.length()==c;
}

BOOL CconfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	int r = ret("oa");


	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CconfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CconfigDlg::OnPaint() 
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
HCURSOR CconfigDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
 CDialog::OnShowWindow(bShow, nStatus);
 

 


 // TODO: Add your message handler code here
}

void CconfigDlg::OnBnClickedOk()
{
 CString scol,srow,srot,sx,sy,sz,sdist;
 
 EDIT_Rows.GetWindowText(srow);
 EDIT_Cols.GetWindowText(scol);;
 EDIT_Speed.GetWindowText(srot);
 EDIT_Startx.GetWindowText(sx);
 EDIT_Starty.GetWindowText(sy);
 EDIT_Startz.GetWindowText(sz);
 EDIT_Distance.GetWindowText(sdist);
 
 gSettings->SetRowsCols(toInt(srow.GetBuffer()),toInt(scol.GetBuffer()));
 gSettings->SetRotSpeed(toFloat(srot.GetBuffer()));
 gSettings->SetStartxy(toFloat(sx.GetBuffer()),toFloat(sy.GetBuffer()));
 gSettings->SetStartz(toFloat(sz.GetBuffer()));
 gSettings->SetDistance(toFloat(sdist.GetBuffer()));
 
 gSettings->SaveSettings();
 
 OnOK();
}

void CconfigDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
 CDialog::OnShowWindow(bShow, nStatus);
 gSettings = new I_cSettings();
 gSettings->LoadSettings();
 
 this->EDIT_Cols.SetWindowText(toString(gSettings->GetCols()).c_str());
 this->EDIT_Rows.SetWindowText(toString(gSettings->GetRows()).c_str());
 this->EDIT_Speed.SetWindowText(toStringf(gSettings->GetRotSpeed()).c_str());
 this->EDIT_Startx.SetWindowText(toStringf(gSettings->GetStartx()).c_str());
 this->EDIT_Starty.SetWindowText(toStringf(gSettings->GetStarty()).c_str());
 this->EDIT_Startz.SetWindowText(toStringf(gSettings->GetStartz()).c_str());
 this->EDIT_Distance.SetWindowText(toStringf(gSettings->GetDistance()).c_str());
 
}
