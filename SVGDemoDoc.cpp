// SVGDemoDoc.cpp : implementation of the CSVGDemoDoc class
//

#include "stdafx.h"
#include "SVGDemo.h"

#include "SVGDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoDoc

IMPLEMENT_DYNCREATE(CSVGDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSVGDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSVGDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoDoc construction/destruction

CSVGDemoDoc::CSVGDemoDoc()
{
	// TODO: add one-time construction code here
	//E-XD++ Library add lines.
	m_pDataModel = new CExtDataModel;
}

CSVGDemoDoc::~CSVGDemoDoc()
{
	//E-XD++ Library add lines.
	if(m_pDataModel != NULL)
	{
		delete m_pDataModel;
		m_pDataModel = NULL;
	}
}

BOOL CSVGDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSVGDemoDoc serialization

void CSVGDemoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		//E-XD++ Library add lines.	
		m_pDataModel->Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		//E-XD++ Library add lines.	
		m_pDataModel->Serialize(ar);
	}
}


//E-XD++ Library add lines.
void CSVGDemoDoc::SetTitle(LPCTSTR lpszTitle)
{
	m_pDataModel->SetDocTitle(lpszTitle);
	CDocument::SetTitle(lpszTitle);
}

void CSVGDemoDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
	m_pDataModel->ResetContent();
}

//added override
BOOL CSVGDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnSaveDocument(lpszPathName))
	{
		return FALSE;
	}
	m_pDataModel->SetClean();		// Tells the command history that the document is "clean" at this point
	SetModifiedFlag(FALSE);
	return TRUE;
}

//added override (optional as long as you never call this member)
void CSVGDemoDoc::SetModifiedFlag(BOOL b)
{
	// Do nothing
	m_pDataModel->SetModifiedFlag(b);
}

//added override
BOOL CSVGDemoDoc::IsModified()
{
	return m_pDataModel->IsModified();
}

BOOL CSVGDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if(!CDocument::OnOpenDocument(lpszPathName))
	{
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoDoc diagnostics

#ifdef _DEBUG
void CSVGDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSVGDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoDoc commands
