// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__546D8EAD_7A6B_4D5E_AD09_FC2510D27C30__INCLUDED_)
#define AFX_MAINFRM_H__546D8EAD_7A6B_4D5E_AD09_FC2510D27C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMainFrame : public CFOPMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes

// Operations
public:

	CFOMultiToolBoxBar m_FileBar;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CFOPStatusBar		m_wndStatusBar;
	CFOPToolBar		m_wndToolBar;
	// Draw Tool Bar, This member specify E-XD++ CFOPToolBar object.  
	CFOPToolBar			m_wndDrawToolBar;

	// Align Tool Bar, This member specify E-XD++ CFOPToolBar object.  
	CFOPToolBar			m_wndAlignToolBar;

	// Layout Tool Bar, This member specify E-XD++ CFOPToolBar object.  
	CFOPToolBar			m_wndLayoutToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnViewToolbox();
	afx_msg void OnUpdateViewToolbox(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT LPCREATESTRUCT);
	afx_msg void OnViewFullscreen();
	afx_msg void OnUpdateViewFullscreen(CCmdUI* pCmdUI);
	afx_msg void OnAppDrawing();
	afx_msg void OnUpdateAppDrawing(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__546D8EAD_7A6B_4D5E_AD09_FC2510D27C30__INCLUDED_)
