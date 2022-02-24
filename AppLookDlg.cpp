// AppLookDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SVGDemo.h"
#include "AppLookDlg.h"
#include "MainFrm.h"
#include "NewVisualProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog


CAppLookDlg::CAppLookDlg(BOOL bStartup, CWnd* pParent /*=NULL*/)
	: CDialog(CAppLookDlg::IDD, pParent),
	m_bStartup (bStartup)
{
	//{{AFX_DATA_INIT(CAppLookDlg)
	m_nAppLook = 1;
	m_bShowAtStartup = FALSE;
	//}}AFX_DATA_INIT

	m_nAppLook = theApp.GetProfileInt(_T("UCanCode Software"), _T("AppLook"), 1);
	m_bShowAtStartup = theApp.GetProfileInt(_T("UCanCode Software"), _T("ShowAppLookAtStartup"), TRUE);
}


void CAppLookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppLookDlg)
	DDX_Control(pDX, IDOK, m_wndOK);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Radio(pDX, IDC_APP_LOOK1, m_nAppLook);
	DDX_Check(pDX, IDC_SHOW_AT_STARTUP, m_bShowAtStartup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppLookDlg, CDialog)
	//{{AFX_MSG_MAP(CAppLookDlg)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_APP_LOOK1, OnAppLook)
	ON_BN_CLICKED(IDC_APP_LOOK2, OnAppLook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg message handlers

BOOL CAppLookDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetLook ();

	if (m_bStartup)
	{
		if (!m_bShowAtStartup)
		{
			EndDialog (IDCANCEL);
			return TRUE;
		}

		CRect rectBtn;

		// Hide "Cancel" button:
		m_wndCancel.GetWindowRect (rectBtn);
		ScreenToClient (rectBtn);

		m_wndOK.MoveWindow (rectBtn);

		m_wndCancel.EnableWindow (FALSE);
		m_wndCancel.ShowWindow (SW_HIDE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAppLookDlg::OnOK() 
{
	CDialog::OnOK();
	SetLook ();
}

void CAppLookDlg::OnApply() 
{
	SetLook ();

	if (!m_bStartup)
	{
		m_wndCancel.SetWindowText (_T("Close"));
	}
}

void CAppLookDlg::SetLook ()
{
	UpdateData ();
	OnAppLook();

	switch (m_nAppLook)
	{
	case 0:
		CFOPVisualProxy::ChangeVisualProxy(RUNTIME_CLASS(CNewVisualProxy));
		break;

	case 1:
		CFOPVisualProxy::ChangeVisualProxy(RUNTIME_CLASS(CNewVisualProxy2));
		break;
	}

	theApp.WriteProfileInt(_T("UCanCode Software"),_T("AppLook"), m_nAppLook);
	theApp.WriteProfileInt(_T("UCanCode Software"),_T("ShowAppLookAtStartup"), m_bShowAtStartup);

}

void CAppLookDlg::OnAppLook() 
{
	UpdateData ();
}
