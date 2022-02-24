// SVGDemoDoc.h : interface of the CSVGDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGDEMODOC_H__751835A5_0A3A_4643_84BA_4A4C28DE7A0E__INCLUDED_)
#define AFX_SVGDEMODOC_H__751835A5_0A3A_4643_84BA_4A4C28DE7A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//E-XD++ Library add lines.
#include "ExtDataModel.h"	

class CSVGDemoDoc : public CDocument
{
protected: // create from serialization only
	CSVGDemoDoc();
	DECLARE_DYNCREATE(CSVGDemoDoc)

// Attributes
public:

	//E-XD++ Library add lines.
	CExtDataModel *m_pDataModel;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSVGDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//E-XD++ Library add lines.
	virtual void DeleteContents();
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	virtual BOOL IsModified();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void SetTitle(LPCTSTR lpszTitle);			
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSVGDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSVGDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SVGDEMODOC_H__751835A5_0A3A_4643_84BA_4A4C28DE7A0E__INCLUDED_)
