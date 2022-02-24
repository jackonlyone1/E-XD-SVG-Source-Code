// SVGDemoView.h : interface of the CSVGDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGDEMOVIEW_H__E663E5A9_5FA3_47AE_8020_A2DBB0BD4ABB__INCLUDED_)
#define AFX_SVGDEMOVIEW_H__E663E5A9_5FA3_47AE_8020_A2DBB0BD4ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSVGDemoView : public CFODrawView
{
protected: // create from serialization only
	CSVGDemoView();
	DECLARE_DYNCREATE(CSVGDemoView)

// Attributes
public:
	CSVGDemoDoc* GetDocument();

public:

	// Do model change.
	virtual void	DoChangeModel(
		// Pointer of model.
		CFODataModel *pModel);

// Operations
public:

	// End print preview mode.
	void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,POINT pt, CPreviewView* pView);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVGDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//E-XD++ Library add lines.
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSVGDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
public:
	//{{AFX_MSG(CSVGDemoView)
	afx_msg void OnFilePrintPreview();
	afx_msg void OnConvertSvgShapes();
	afx_msg void OnUpdateConvertSvgShapes(CCmdUI* pCmdUI);
	afx_msg void OnExportSvg();
	afx_msg void OnUpdateExportSvg(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SVGDemoView.cpp
inline CSVGDemoDoc* CSVGDemoView::GetDocument()
   { return (CSVGDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVGDEMOVIEW_H__E663E5A9_5FA3_47AE_8020_A2DBB0BD4ABB__INCLUDED_)
