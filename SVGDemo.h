// SVGDemo.h : main header file for the SVGDEMO application
//

#if !defined(AFX_SVGDEMO_H__57ECC244_040B_4D56_A103_D110249C622E__INCLUDED_)
#define AFX_SVGDEMO_H__57ECC244_040B_4D56_A103_D110249C622E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoApp:
// See SVGDemo.cpp for the implementation of this class
//

class CSVGDemoApp : public CWinApp
{
public:
	CSVGDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVGDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	// Drawing Scale, This member specify double object.  
	double dDrawingScale;
	
	// Load Text, This member sets TRUE if it is right.  
	BOOL m_bLoadText;
	
	// Application Path, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strAppPath;
 
	// Default Hatch, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_nDefHatch;
	
	// Default Texture, This variable specifies a 32-bit signed integer on 32-bit platforms.  
	int		m_DefTexture;
	//-----------------------------------------------------------------------
	// Summary:
	// Create Temp X M L, You construct a CSVGDemoApp object in two steps. First call the constructor, then call Create, which creates the object.
	//		Returns a CString type value.  
	// Parameters:
	//		strSVG---S V G, Specifies A CString type value.
	CString CreateTempXML(CString strSVG);

	// Conversion, This member specify double object.  
	double Conversion;
 
// Implementation
	//{{AFX_MSG(CSVGDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
extern CSVGDemoApp theApp;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVGDEMO_H__57ECC244_040B_4D56_A103_D110249C622E__INCLUDED_)
