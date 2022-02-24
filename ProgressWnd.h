// ProgressWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressWnd window

#define PW_SIZE_BORDER	8

#define PW_WIDTH_DEFAULT	(UINT)-1

// Bar styles.
#define PW_BARSTYLE_FIRST	0

#define PW_BARSTYLE_FLAT	0
#define PW_BARSTYLE_SUNKEN	1
#define PW_BARSTYLE_RAISED	2

#define PW_BARSTYLE_LAST	2

// Fill colour.
#define PW_FILLCOLOUR_DEFAULT	(COLORREF)-1

 
//===========================================================================
// Summary:
//     The CProgressWnd class derived from CFrameWnd
//      Progress Window
//===========================================================================

class CProgressWnd : public CFrameWnd
{
// Construction
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Showing, Determines if the given value is correct or exist.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		void---void
	BOOL IsShowing(void);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Current Percent Scale, Returns the specified value.
	//		Returns a UINT type value.  
	// Parameters:
	//		void---void
	UINT GetCurrentPercentScale(void);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Cancel Text, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		strText---strText, Specifies A CString type value.
	void SetCancelText(CString strText);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Fill Colour, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		dwColour---dwColour, Specifies A 32-bit value used as a color value.
	void SetFillColour(COLORREF dwColour);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Width, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		uWidth---uWidth, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetWidth(UINT uWidth);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Animation File, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		strAVI---A V I, Specifies A CString type value.
	void SetAnimationFile(CString strAVI);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Bar Style, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		uStyle---uStyle, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetBarStyle(UINT uStyle);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Cancel Message, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		uMessage---uMessage, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetCancelMessage(UINT uMessage);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Was Cancelled, None Description.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		void---void
	BOOL WasCancelled(void);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Can Cancel Flag, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		bCanCancel---Can Cancel, Specifies A Boolean value.
	void SetCanCancelFlag(BOOL bCanCancel);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Update Progress, Call this member function to update the object.
	// Parameters:
	//		uCount---uCount, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void UpdateProgress(UINT uCount = 1);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Reset Progress, Called this function to empty a previously initialized CProgressWnd object.
	// Parameters:
	//		void---void
	void ResetProgress(void);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Full Scale, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		uFullScale---Full Scale, Specifies A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.
	void SetFullScale(UINT uFullScale);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Hide, Hides the objects by removing it from the display screen. 
	// Parameters:
	//		void---void
	void Hide(void);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Show, Call this function to show the specify object.
	// Parameters:
	//		*pWndOwner---Window Owner, A pointer to the CWnd  or NULL if the call failed.
	void Show(CWnd *pWndOwner = NULL);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Message, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		strMessage---strMessage, Specifies A CString type value.  
	//		bResizeToFit---Resize To Fit, Specifies A Boolean value.
	void SetMessage(CString strMessage, BOOL bResizeToFit = TRUE);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Title, Sets a specify value to current class CProgressWnd
	// Parameters:
	//		strTitle---strTitle, Specifies A CString type value.
	void SetTitle(CString strTitle);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Progress Window, Constructs a CProgressWnd object.
	//		Returns A  value.
	CProgressWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressWnd)
	public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Do Before Translate Message, None Description.
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		pMsg---pMsg, A pointer to the MSG or NULL if the call failed.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Post Nc Destroy, None Description.
	// This member function is also a virtual function, you can Override it if you need,
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// C Progress Window, Destructor of class CProgressWnd
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CProgressWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgressWnd)
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Paint, Called to repaint a portion of the window.

	afx_msg void OnPaint();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Create, Called as a part of window creation.
	//		Returns a int type value.  
	// Parameters:
	//		lpCreateStruct---Create Struct, Specifies a LPCREATESTRUCT lpCreateStruct object.
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Destroy, Called when CWnd is being destroyed.

	afx_msg void OnDestroy();
	
	//-----------------------------------------------------------------------
	// Summary:
	// On Cancel, This member function is called by the framework to allow your application to handle a Windows message.
	// Parameters:
	//		void---void
	afx_msg void OnCancel(void);
	//}}AFX_MSG
	
	//-----------------------------------------------------------------------
	// Summary:
	// E C L A R E_ M E S S A G E_ M A P, None Description.
	//		Returns A  value.
	DECLARE_MESSAGE_MAP()
private:
 
	// Fill Colour, This member sets A 32-bit value used as a color value.  
	COLORREF m_dwFillColour;
 
	// m_pAnimation, This member maintains a pointer to the object CAnimateCtrl.  
	CAnimateCtrl * m_pAnimation;
 
	// Animation A V I, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strAnimationAVI;
 
	// m_fntMessage, The CFont class encapsulates a Windows graphics device interface (GDI) font and provides member functions for manipulating the font.  
	CFont m_fntMessage;
 
	// Was Cancelled, This member sets TRUE if it is right.  
	BOOL m_bWasCancelled;
 
	// Cancel Message, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uCancelMessage;
 
	// Button Cancel, The CButton class provides the functionality of Windows button controls.  
	CButton * m_pBtnCancel;
 
	// Can Cancel, This member sets TRUE if it is right.  
	BOOL m_bCanCancel;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Clear Bar, Remove the specify data from the list.
	// Parameters:
	//		void---void
	void ClearBar(void);
 
	// Last Position, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uLastPosition;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Draw Bar, Draws current object to the specify device.
	// Parameters:
	//		bForce---bForce, Specifies A Boolean value.
	void DrawBar(BOOL bForce = FALSE);
 
	// Bar Style, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uBarStyle;
 
	// Current Value, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uCurrentValue;
 
	// Full Scale, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uFullScale;
 
	// Window Owner, The CWnd class provides the base functionality of all window classes in the Microsoft Foundation Class Library.  
	CWnd * m_pWndOwner;
 
	// m_hCur, This member specify HCURSOR object.  
	HCURSOR m_hCur;
 
	// Window Class, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strWndClass;
 
	// m_sizScreen, This member sets a CSize value.  
	CSize m_sizScreen;
 
	// m_uWidth, This member can be sets with A 16-bit unsigned integer on Windows versions 3.0 and 3.1; a 32-bit unsigned integer on Win32.  
	UINT m_uWidth;
 
	// m_rctMessage, This member sets a CRect value.  
	CRect m_rctMessage;
 
	// m_rctBar, This member sets a CRect value.  
	CRect m_rctBar;
	
	//-----------------------------------------------------------------------
	// Summary:
	// Calculate Sizes, None Description.
	// Parameters:
	//		void---void
	void CalculateSizes(void);
 
	// m_strMessage, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strMessage;
 
	// m_strTitle, You can freely substitute CString objects for const char* and LPCTSTR function arguments.  
	CString m_strTitle;
};

/////////////////////////////////////////////////////////////////////////////
