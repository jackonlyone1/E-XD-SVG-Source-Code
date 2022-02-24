#if !defined(AFX_APPLOOKDLG_H__958C6FBF_2889_458B_98CC_BF74B77C2F9F__INCLUDED_)
#define AFX_APPLOOKDLG_H__958C6FBF_2889_458B_98CC_BF74B77C2F9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppLookDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppLookDlg dialog

 
//===========================================================================
// Summary:
//     The CAppLookDlg class derived from CDialog
//      Application Look Dialog
//===========================================================================

class CAppLookDlg : public CDialog
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Application Look Dialog, Constructs a CAppLookDlg object.
	//		Returns A  value.  
	// Parameters:
	//		bStartup---bStartup, Specifies A Boolean value.  
	//		pParent---pParent, A pointer to the CWnd or NULL if the call failed.
	CAppLookDlg(BOOL bStartup, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppLookDlg)
	enum { IDD = IDD_APP_LOOK };
 
	// O K, The CButton class provides the functionality of Windows button controls.  
	CButton	m_wndOK;
 
	// m_wndCancel, The CButton class provides the functionality of Windows button controls.  
	CButton	m_wndCancel;
 
	// Application Look, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nAppLook;
 
	// Show At Startup, This member sets TRUE if it is right.  
	BOOL	m_bShowAtStartup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppLookDlg)
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Data Exchange, Do a event. 
	// This member function is also a virtual function, you can Override it if you need,  
	// Parameters:
	//		pDX---D X, A pointer to the CDataExchange or NULL if the call failed.
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppLookDlg)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Initial Dialog, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.
	virtual BOOL OnInitDialog();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On O K, This member function is called by the framework to allow your application to handle a Windows message.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void OnOK();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Apply, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnApply();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Application Look, This member function is called by the framework to allow your application to handle a Windows message.

	afx_msg void OnAppLook();
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()

 
	// m_bStartup, This member sets TRUE if it is right.  
	const BOOL	m_bStartup;

	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Look, Sets a specify value to current class CAppLookDlg

	void SetLook ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPLOOKDLG_H__958C6FBF_2889_458B_98CC_BF74B77C2F9F__INCLUDED_)
