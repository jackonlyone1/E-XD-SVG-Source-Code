// ProgressWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString	g_strCancel = _T("Cancel");
CString	g_strProgress = _T("Progress");

/////////////////////////////////////////////////////////////////////////////
// CProgressWnd

CProgressWnd::CProgressWnd()
{
	m_bCanCancel = FALSE ;
	m_dwFillColour = PW_FILLCOLOUR_DEFAULT ;
	m_hCur = NULL ;
	m_pAnimation = NULL ;
	m_pBtnCancel = NULL ;
	m_rctBar.SetRect(0, 0, 0, 0);
	m_rctMessage.SetRect(0, 0, 0, 0);
	m_sizScreen.cx = ::GetSystemMetrics(SM_CXSCREEN);
	m_sizScreen.cy = ::GetSystemMetrics(SM_CYSCREEN);
	m_strAnimationAVI = _T("");
	m_strMessage = _T("");
	m_strTitle = g_strProgress;
	m_uBarStyle = PW_BARSTYLE_SUNKEN ;
	m_uCancelMessage = 0 ;
	m_uCurrentValue = 0 ;
	m_uFullScale = 100 ;
	m_uWidth = m_sizScreen.cx / 4 ;
	if (m_uWidth < 200)
		m_uWidth = 200 ;
}

CProgressWnd::~CProgressWnd()
{
	if (m_hWnd != NULL)
		Hide();
}

BEGIN_MESSAGE_MAP(CProgressWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CProgressWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CProgressWnd message handlers

void CProgressWnd::SetTitle(CString strTitle)
{
// Can be changed whether showing or not.
	m_strTitle = strTitle;
	if (m_hWnd != NULL)
		SetWindowText(m_strTitle);
}

void CProgressWnd::SetMessage(CString strMessage, BOOL bResizeToFit)
{
// Can be changed whether showing or not.
	m_strMessage = strMessage;
	if (m_hWnd != NULL)
	{
		if (bResizeToFit)
			CalculateSizes();
		InvalidateRect(NULL);
		if (m_pAnimation != NULL)
			m_pAnimation->Play(0,(UINT)-1,(UINT)-1);
	}
}

void CProgressWnd::CalculateSizes(void)
{
	CClientDC	*pDC ;
	CFont		*pFntOld ;
	CRect		rctClient, rctButton, rctAnimation, rctWindow ;
	CSize		sizFont, sizFrame ;
	int			iLeft, iTop, iIndent ;
	UINT		uMessageBase, uBarBase, uHeight, uCaptionHeight ;

	uCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);
	sizFrame.cx = ::GetSystemMetrics(SM_CXFRAME);
	sizFrame.cy = ::GetSystemMetrics(SM_CYFRAME);

// We can only do this if we have created the window already.
	if (m_hWnd != NULL)
	{
		pDC = new CClientDC(this);
// Select the correct font and find out how big the word "Cancel" is.
		pFntOld = (CFont *)pDC->SelectObject(&m_fntMessage);
		sizFont = pDC->GetTextExtent(g_strCancel);

// Set an initial message rectangle which covers the full width, for now.
		m_rctMessage.SetRect(PW_SIZE_BORDER, PW_SIZE_BORDER, 
							m_uWidth - PW_SIZE_BORDER - (2 * sizFrame.cx), 
							PW_SIZE_BORDER);

// If an AVI has been specified...
		if (m_strAnimationAVI != _T("") )
		{
			if (m_pAnimation == NULL)
			{
// Doesn't exist. Create it.
				m_pAnimation = new CAnimateCtrl ;
				rctAnimation.SetRect(PW_SIZE_BORDER, PW_SIZE_BORDER, 
										PW_SIZE_BORDER + 16, PW_SIZE_BORDER + 16);
				m_pAnimation->Create(WS_CHILD|WS_VISIBLE|ACS_TRANSPARENT, 
										rctAnimation, this, 9999);
			}
			else
			{
// Remove the previous AVI and open the new one.
				m_pAnimation->Close();
			}

// Open the specified AVI, if possible, and get the new control size.
			if (m_pAnimation->Open(m_strAnimationAVI) )
			{
				m_pAnimation->GetWindowRect(&rctAnimation);
				ScreenToClient(&rctAnimation);
			}

// Adjust the message left-hand side to leave space for the AVI.
			m_rctMessage.left += (rctAnimation.Width() + PW_SIZE_BORDER);
		}
		else
		{
// No animation specified. If it exists, delete the control.
			if (m_pAnimation != NULL)
			{
				delete m_pAnimation ;
				m_pAnimation = NULL ;
			}
		}

// Calculate how much height is need to fit the message in the given width.
		pDC->DrawText(m_strMessage, &m_rctMessage, DT_WORDBREAK|DT_CALCRECT);
// If the animation exists and is taller than the message rectangle, adjust the 
// message height.
		if (m_pAnimation != NULL && m_rctMessage.bottom < rctAnimation.bottom)
			m_rctMessage.bottom = rctAnimation.bottom ;
// Set the baseline of the message and animation.
		uMessageBase = (2 * PW_SIZE_BORDER) + m_rctMessage.Height();
// Set the baseline of the progress bar.
		uBarBase = uMessageBase + sizFont.cy ;
// Set the total height of the progress window.
		uHeight = uBarBase + PW_SIZE_BORDER ;
		uHeight += (uCaptionHeight + (2 * sizFrame.cy) );
		if (m_bCanCancel)
			uHeight += (sizFont.cy + (2 * PW_SIZE_BORDER) );
// Set the rectangle to be used for the progress bar.
		m_rctBar.SetRect(PW_SIZE_BORDER, uMessageBase, 
							m_uWidth - PW_SIZE_BORDER - (2 * sizFrame.cx), 
							 uBarBase);
// Set the rectangle to be used for the cancel button.
		iIndent = (m_uWidth - (2 * sizFrame.cx) - sizFont.cx 
					- (2 * PW_SIZE_BORDER) ) / 2 ;
		rctButton.SetRect(iIndent, uBarBase + PW_SIZE_BORDER, 
							m_uWidth - (2 * sizFrame.cx) - iIndent, 
							uBarBase + (2 * PW_SIZE_BORDER) + sizFont.cy);

		pDC->SelectObject(pFntOld);

		delete pDC ;

// Establish the window position, based on the owner or the screen. If the 
// window is already visible, we should just adjust the size about the centre 
// point (so that the window's centre stays in the same position - in case it 
// has been moved by the user, in which case we don't want it to snap back to 
// the centre of the owner window / screen).
		if (IsWindowVisible() )
		{
			GetWindowRect(&rctWindow);
			rctWindow.InflateRect( (int)(m_uWidth - rctWindow.Width() ) / 2, 
									(int)(uHeight - rctWindow.Height() ) / 2);

			MoveWindow(&rctWindow);
		}
		else
		{
			if (m_pWndOwner == NULL)
			{
				iLeft = (m_sizScreen.cx - m_uWidth) / 2 ;
				iTop = (m_sizScreen.cy - uHeight) / 2 ;
			}
			else
			{
				m_pWndOwner->GetClientRect(&rctClient);
				m_pWndOwner->ClientToScreen(&rctClient);
				iLeft = (rctClient.Width() - m_uWidth) / 2 ;
				iLeft += rctClient.left ;
				iTop = (rctClient.Height() - uHeight) / 2 ;
				iTop += rctClient.top ;
			}
// Position the window ready.
			MoveWindow(iLeft, iTop, m_uWidth, uHeight);
		}

// If we need a cancel button...
		if (m_bCanCancel)
		{
			if (m_pBtnCancel == NULL)
			{
// Button does not exist. Create it.
				m_pBtnCancel = new CButton ;
				m_pBtnCancel->Create(g_strCancel, 
										WS_CHILD|WS_VISIBLE|BS_DEFPUSHBUTTON, 
										rctButton, this, IDCANCEL);
			}
			else
			{
// Button already exists. Position it and change its text, if necessary.
				m_pBtnCancel->SetWindowText(g_strCancel);
				m_pBtnCancel->MoveWindow(&rctButton);
			}

// Make sure it has the same font as the window.
			m_pBtnCancel->SetFont(&m_fntMessage);
		}
		else
		{
// No cancel button needed. If it exists, delete it.
			if (m_pBtnCancel != NULL)
			{
				delete m_pBtnCancel ;
				m_pBtnCancel = NULL ;
			}
		}

	}
}

void CProgressWnd::OnPaint() 
{
	CFont		*pFntOld ;
	CPaintDC	dc(this);
	CPen		penShadow, penHighlight ;
	DWORD		dwClrShadow, dwClrHighlight ;

	dwClrShadow = ::GetSysColor(COLOR_3DDKSHADOW);
	dwClrHighlight = ::GetSysColor(COLOR_3DLIGHT);
	penShadow.CreatePen(PS_SOLID, 1, dwClrShadow);
	penHighlight.CreatePen(PS_SOLID, 1, dwClrHighlight);

// Message.
	pFntOld = (CFont *)dc.SelectObject(&m_fntMessage);
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_strMessage, &m_rctMessage, DT_WORDBREAK);
	dc.SelectObject(pFntOld);

// Bar border.
	m_rctBar.InflateRect(2, 2);
	dc.SelectStockObject(WHITE_BRUSH);
	switch (m_uBarStyle)
	{
		case PW_BARSTYLE_FLAT :
			m_rctBar.InflateRect(-1, -1);
			m_rctBar.right++ ;
			m_rctBar.bottom++ ;
			dc.SelectStockObject(BLACK_PEN);
			dc.Rectangle(m_rctBar);

			m_rctBar.right-- ;
			m_rctBar.bottom-- ;
			break ;

		case PW_BARSTYLE_SUNKEN :
			dc.SelectObject(&penShadow);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.left, m_rctBar.top);
			dc.LineTo(m_rctBar.right + 1, m_rctBar.top);

			dc.SelectObject(&penHighlight);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.top - 1);

			dc.SelectObject(&penShadow);
			m_rctBar.InflateRect(-1, -1);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.left, m_rctBar.top);
			dc.LineTo(m_rctBar.right + 1, m_rctBar.top);

			dc.SelectObject(&penHighlight);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.top - 1);

			dc.SelectStockObject(WHITE_PEN);
			m_rctBar.InflateRect(-1, -1);
			m_rctBar.right++ ;
			m_rctBar.bottom++ ;
			dc.Rectangle(m_rctBar);

			m_rctBar.right-- ;	// Back to nominal size.
			m_rctBar.bottom-- ;
			break ;

		case PW_BARSTYLE_RAISED :
			dc.SelectObject(&penHighlight);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.left, m_rctBar.top);
			dc.LineTo(m_rctBar.right + 1, m_rctBar.top);

			dc.SelectObject(&penShadow);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.top - 1);

			dc.SelectObject(&penHighlight);
			m_rctBar.InflateRect(-1, -1);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.left, m_rctBar.top);
			dc.LineTo(m_rctBar.right + 1, m_rctBar.top);

			dc.SelectObject(&penShadow);
			dc.MoveTo(m_rctBar.left, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.bottom);
			dc.LineTo(m_rctBar.right, m_rctBar.top - 1);

			dc.SelectStockObject(WHITE_PEN);
			m_rctBar.InflateRect(-1, -1);
			m_rctBar.right++ ;
			m_rctBar.bottom++ ;
			dc.Rectangle(m_rctBar);

			m_rctBar.right-- ;
			m_rctBar.bottom-- ;
			break ;
	}

// Bar itself.
	DrawBar(TRUE);	// Force it.

	penHighlight.DeleteObject();
	penShadow.DeleteObject();
}

void CProgressWnd::Show(CWnd *pWndOwner)
{
	CDC		*pDC ;
	CFont	*pFont ;
	CRect	rctWindow(0, 0, 100, 100);
	CWinApp	*pApp ;
	DWORD	dwStyle = WS_OVERLAPPED|WS_CAPTION ;
	HBRUSH	hBrGrey ;
	LOGFONT	sLF ;

	if (m_hWnd == NULL)
	{
		pApp = AfxGetApp();
		if (pApp != NULL)
			m_hCur = pApp->LoadStandardCursor(IDC_ARROW);
		hBrGrey = ::GetSysColorBrush(COLOR_3DFACE);
		m_strWndClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW, m_hCur, hBrGrey);

		m_pWndOwner = pWndOwner ;
		m_bWasCancelled = FALSE ;

		CFrameWnd::Create(m_strWndClass, m_strTitle, dwStyle, rctWindow);
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		pDC = GetDC();
		pFont = (CFont *)pDC->SelectStockObject(ANSI_VAR_FONT);
		pFont = (CFont *)pDC->SelectStockObject(ANSI_VAR_FONT);
		pFont->GetLogFont(&sLF);
		m_fntMessage.CreateFontIndirect(&sLF);
		ReleaseDC(pDC);

		CalculateSizes();	// Cancel button, if required, is created here.
		ResetProgress();
		ShowWindow(SW_SHOWNORMAL);
		if (m_pAnimation != NULL)
			m_pAnimation->Play(0,(UINT)-1,(UINT)-1);
		if (m_bCanCancel)
			m_pBtnCancel->SetFocus();
	}
}

void CProgressWnd::Hide(void)
{
	if (m_hWnd != NULL)
		DestroyWindow();
}

int CProgressWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	LONG	lExStyle ;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

// Remove the sunken edge.	
	lExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
	lExStyle &= ~WS_EX_CLIENTEDGE ;
	SetWindowLong(m_hWnd, GWL_EXSTYLE, lExStyle);
	
	return 0;
}

void CProgressWnd::OnDestroy() 
{
	m_fntMessage.DeleteObject();

	CFrameWnd::OnDestroy();
	
	if (m_pBtnCancel != NULL)
	{
		delete m_pBtnCancel ;
		m_pBtnCancel = NULL ;
	}

	if (m_pAnimation != NULL)
	{
		m_pAnimation->Close();
		delete m_pAnimation ;
		m_pAnimation = NULL ;
	}
}

void CProgressWnd::PostNcDestroy() 
{
// Do nothing. Specifically don't delete this!
}

void CProgressWnd::DrawBar(BOOL bForce)
{
	CBrush		brFill, *pBrOld ;
	CClientDC	*pDC ;
	CPen		penFill, *pPenOld ;
	CRect		rctFill ;
	DWORD		dwClrHighlight ;
	UINT		uPosition ;

	if (m_hWnd != NULL)
	{
		pDC = new CClientDC(this);

		if (m_dwFillColour == PW_FILLCOLOUR_DEFAULT)
			dwClrHighlight = ::GetSysColor(COLOR_HIGHLIGHT);
		else
			dwClrHighlight = m_dwFillColour ;
		penFill.CreatePen(PS_SOLID, 1, dwClrHighlight);
		brFill.CreateSolidBrush(dwClrHighlight);

		m_rctBar.right++ ;
		m_rctBar.bottom++ ;

		if (m_uCurrentValue == 0)
		{
			pDC->SelectStockObject(WHITE_PEN);
			pDC->SelectStockObject(WHITE_BRUSH);
			pDC->Rectangle(m_rctBar);
		}
		else
		{
			if (m_uFullScale == 0)
				uPosition = m_rctBar.Width();
			else
				uPosition = m_uCurrentValue * m_rctBar.Width() / m_uFullScale ;
			if (uPosition > 0 && (uPosition != m_uLastPosition || bForce) )
			{
				m_uLastPosition = uPosition ;
				rctFill.SetRect(m_rctBar.left, m_rctBar.top, 
								m_rctBar.left + uPosition, m_rctBar.bottom);
				pPenOld = (CPen *)pDC->SelectObject(&penFill);
				pBrOld = (CBrush *)pDC->SelectObject(&brFill);
				pDC->Rectangle(rctFill);
				pDC->SelectObject(pBrOld);
				pDC->SelectObject(pPenOld);
			}
		}

		m_rctBar.bottom-- ;
		m_rctBar.right-- ;

		brFill.DeleteObject();
		penFill.DeleteObject();

		delete pDC ;
	}
}

void CProgressWnd::SetFullScale(UINT uFullScale)
{
// Can be changed whether showing or not.
	ASSERT(uFullScale != 0);

// 0 in release mode will be handled in DrawBar().
	m_uFullScale = uFullScale ;
	if (m_hWnd != NULL)
	{
		ClearBar();
		DrawBar(TRUE);	// Force it.
	}
}

void CProgressWnd::ClearBar(void)
{
	CClientDC	*pDC ;

	if (m_hWnd != NULL)
	{
		pDC = new CClientDC(this);

		pDC->SelectStockObject(WHITE_PEN);
		pDC->SelectStockObject(WHITE_BRUSH);

		m_rctBar.right++ ;
		m_rctBar.bottom++ ;

		pDC->Rectangle(m_rctBar);

		m_rctBar.bottom-- ;
		m_rctBar.right-- ;

		m_uLastPosition = 0 ;

		delete pDC ;
	}
}

void CProgressWnd::ResetProgress(void)
{
// This can be changed whether it is showing or not.
	m_uCurrentValue = 0 ;
	if (m_hWnd != NULL)
		ClearBar();
}

void CProgressWnd::UpdateProgress(UINT uCount)
{
	m_uCurrentValue += uCount ;
	if (m_uCurrentValue > m_uFullScale)
		m_uCurrentValue = m_uFullScale ;
	DrawBar();
}

void CProgressWnd::SetCanCancelFlag(BOOL bCanCancel)
{
// Can't change this while showing.
	if (m_hWnd == NULL)
		m_bCanCancel = bCanCancel ;
}

void CProgressWnd::OnCancel(void)
{
// We must check that we can cancel, because the <Esc> key could dismiss it 
// otherwise, even if there is no cancel button.
	if (m_bCanCancel)
	{
		m_bWasCancelled = TRUE ;

		if (m_pWndOwner != NULL && m_uCancelMessage > 0)
			m_pWndOwner->PostMessage(m_uCancelMessage);
	}
}

BOOL CProgressWnd::WasCancelled(void)
{
	BOOL	bWasCancelled = m_bWasCancelled ;

	if (m_hWnd == NULL)
		m_bWasCancelled = FALSE ;

	return bWasCancelled ;
}

void CProgressWnd::SetCancelMessage(UINT uMessage)
{
	m_uCancelMessage = uMessage ;
}

void CProgressWnd::SetBarStyle(UINT uStyle)
{
// Can't change this while showing.
	if (m_hWnd == NULL)
	{
		if (uStyle >= PW_BARSTYLE_FIRST && uStyle <= PW_BARSTYLE_LAST)
			m_uBarStyle = uStyle ;
	}
}

BOOL CProgressWnd::PreTranslateMessage(MSG* pMsg) 
{
	BOOL	bProcessed ;

	if (IsDialogMessage(pMsg) )
		bProcessed = TRUE ;
	else
		bProcessed = CFrameWnd::PreTranslateMessage(pMsg);

	return bProcessed ;
}

void CProgressWnd::SetAnimationFile(CString strAVI)
{
// Can't change this while showing.
	if (m_hWnd == NULL)
		m_strAnimationAVI = strAVI;
}

void CProgressWnd::SetWidth(UINT uWidth)
{
// Can be changed whether it is showing or not.
	if (uWidth == PW_WIDTH_DEFAULT)
	{
		m_uWidth = m_sizScreen.cx / 4 ;
		if (m_uWidth < 200)
			m_uWidth = 200 ;
	}
	else
		m_uWidth = uWidth ;

	if (m_hWnd != NULL)
	{
		CalculateSizes();
		ClearBar();
		DrawBar(TRUE);	// Force it.
		if (m_pAnimation != NULL)
			m_pAnimation->Play(0,(UINT)-1,(UINT)-1);
	}
}

void CProgressWnd::SetFillColour(COLORREF dwColour)
{
// This can be changed whether it is showing or not.
	m_dwFillColour = dwColour ;
	if (m_hWnd != NULL)
		DrawBar(TRUE);	// Force it.
}

void CProgressWnd::SetCancelText(CString strText)
{
// This can be changed whether it is showing or not.
	g_strCancel = strText;
	if (m_hWnd != NULL)
	{
		CalculateSizes();
		ClearBar();
		DrawBar(TRUE);	// Force it.
		if (m_pAnimation != NULL)
			m_pAnimation->Play(0,(UINT)-1,(UINT)-1);
	}
}

UINT CProgressWnd::GetCurrentPercentScale(void)
{
	UINT	uPercent = (UINT)-1 ;

	if (m_hWnd != NULL && m_uFullScale > 0)
		uPercent = (m_uCurrentValue * 100) / m_uFullScale ;

	return uPercent ;
}

BOOL CProgressWnd::IsShowing(void)
{
	BOOL	bShowing = FALSE ;

	if (m_hWnd != NULL)
		bShowing = TRUE ;

	return bShowing ;
}
