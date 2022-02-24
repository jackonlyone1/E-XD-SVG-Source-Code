// SVGDemoView.cpp : implementation of the CSVGDemoView class
//

#include "stdafx.h"
#include "SVGDemo.h"

#include "SVGDemoDoc.h"
#include "SVGDemoView.h"
#include "ChildFrm.h"
#include "FOPVisioStencilConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView

IMPLEMENT_DYNCREATE(CSVGDemoView, CFODrawView)
BEGIN_MESSAGE_MAP(CSVGDemoView,CFODrawView)
	//{{AFX_MSG_MAP(CSVGDemoView)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_CONVERT_SVG_SHAPES, OnConvertSvgShapes)
	ON_UPDATE_COMMAND_UI(ID_CONVERT_SVG_SHAPES, OnUpdateConvertSvgShapes)
	ON_COMMAND(ID_EXPORT_SVG, OnExportSvg)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_SVG, OnUpdateExportSvg)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CFODrawView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFODrawView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView construction/destruction

CSVGDemoView::CSVGDemoView()
{
	// TODO: add construction code here
}

CSVGDemoView::~CSVGDemoView()
{
}

BOOL CSVGDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREAFOAPPWIZARDRUCT cs
	return CFODrawView::PreCreateWindow(cs);

}

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView drawing

void CSVGDemoView::OnDraw(CDC* pDC)
{
	CSVGDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	Draw(pDC);
	// TODO: add draw code for native data here
}

void CSVGDemoView::DoChangeModel(CFODataModel * pModel)
{
	CFODrawView::DoChangeModel(pModel);
	// Adding your data model init codes here..

}

void CSVGDemoView::OnInitialUpdate()
{
	SetCurrentModel(GetDocument()->m_pDataModel);
	CFODrawView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView printing

BOOL CSVGDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{

	// default preparation
	return CFODrawView::OnPreparePrinting(pInfo);

}

void CSVGDemoView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	// E-XD++ Library Add line.
	CFODrawView::OnBeginPrinting(pDC,pInfo);
}

void CSVGDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSVGDemoView::OnFilePrintPreview() 
{
	FOPrintPreview(this);
}

void CSVGDemoView::OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo,
							  POINT pt, CPreviewView* pView) 
{
	CScrollView::OnEndPrintPreview(pDC, pInfo,pt, pView); 

}

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView diagnostics

#ifdef _DEBUG
void CSVGDemoView::AssertValid() const
{
//E-XD++ Library add lines.
	CFODrawView::AssertValid();


	//CView::AssertValid();
}

void CSVGDemoView::Dump(CDumpContext& dc) const
{
//E-XD++ Library add lines.
	CFODrawView::Dump(dc);


	//CView::Dump(dc);
}

CSVGDemoDoc* CSVGDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSVGDemoDoc)));
	return (CSVGDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoView message handlers
//E-XD++ Library add line.
void CSVGDemoView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	//CView::OnPrint(pDC, pInfo);
	//E-XD++ Library Add line.
	CFODrawView::OnPrint(pDC,pInfo);
}


void xxFOUpdateComp(CFOCompositeShape *pComp)
{
	FOPRect rcTemp = pComp->GetTotalSnapRect();
	//	pComp->ResetCurrentShape();
	pComp->SetPointAt(0, CPoint(rcTemp.left,  rcTemp.top));
	pComp->SetPointAt(1, CPoint(rcTemp.right, rcTemp.top));
	pComp->SetPointAt(2, CPoint(rcTemp.right, rcTemp.bottom));
	pComp->SetPointAt(3, CPoint(rcTemp.left,  rcTemp.bottom));
	
	pComp->UpdateDataManager();
	
	POSITION pos = pComp->GetCompList()->GetHeadPosition();
	while(pos != NULL)
	{
		CFODrawShape *pNewShape = (CFODrawShape *)pComp->GetCompList()->GetNext(pos);
		if(HAS_BASE(pNewShape, CFOCompositeShape))
		{
			CFOCompositeShape *pNew = static_cast<CFOCompositeShape *>(pNewShape);
			xxFOUpdateComp(pNew);
		}
		
	}
}

void CSVGDemoView::OnConvertSvgShapes() 
{
	// TODO: Add your command handler code here
	BOOL bSave = gfxData.m_bAllFullGeometry;
	gfxData.m_bAllFullGeometry = TRUE;

	CString strType = _T("Import SVG Files (*.svg)|*.svg||");
	CFileDialog fileDlg(TRUE, _T("SVG Shapes"), _T("*.svg"), OFN_FILEMUSTEXIST|OFN_HIDEREADONLY, strType, NULL);
	if (IDOK != fileDlg.DoModal())
		return;
	
	CString strFileName = fileDlg.GetPathName();
	CFOPSVGStencilConverter converter(GetCurrentModel(), strFileName);
	converter.Convert();
	converter.Dispose();
	
	BOOL bNotChanged = FALSE;
// 	if(GetCurrentModel()->GetCompsCount() == 1)
// 	{
// 		CFODrawShape *pShape = (CFODrawShape *)GetCurrentModel()->GetShapes()->GetObject(0);
// 		if(pShape->IsKindOf(RUNTIME_CLASS(CFOGroupShape)))
// 		{
// 			CFOGroupShape *pGroup = static_cast<CFOGroupShape *>(pShape);
// 			if(pGroup->GetCompCount() < 40)
// 			{
// 				GetCurrentModel()->Ungroup(pGroup);
// 				bNotChanged = TRUE;
// 			}
// 			
// 		}
// 	}
// 	else
	{
		m_listSelectComp.RemoveAll();
	}
	
	if(GetCurrentModel()->GetCompsCount() < 40 && bNotChanged)
	{
		CRect rcTotal = GetCurrentModel()->GetTotalSnapRect(*GetCurrentModel()->GetShapes());
		CFODrawShape *pShape = NULL;
		int xy = 0;
		for(xy = 0; xy < GetCurrentModel()->GetShapes()->Count(); xy ++)
		{
			pShape = (CFODrawShape *)GetCurrentModel()->GetShapes()->GetObject(xy);
			if(HAS_BASE(pShape, CFOCompositeShape))
			{
				CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShape);
				xxFOUpdateComp(pComp);
				
			}
			pShape->OffsetAllPoints(-rcTotal.left, -rcTotal.top);
			
			if(theApp.dDrawingScale != 1.0)
			{
				pShape->ScaleShape(1.0/ theApp.dDrawingScale, 1.0 / theApp.dDrawingScale, 0, 0);
			}
			
			pShape->OffsetAllPoints(100, 100);
		}
	}
	else if(theApp.dDrawingScale != 1.0 && GetCurrentModel()->GetCompsCount() < 200)
	{
		CRect rcTotal = GetCurrentModel()->GetTotalSnapRect(*GetCurrentModel()->GetShapes());
		CFODrawShape *pShape = NULL;
		int xy = 0;
		for(xy = 0; xy < GetCurrentModel()->GetShapes()->Count(); xy ++)
		{
			pShape = (CFODrawShape *)GetCurrentModel()->GetShapes()->GetObject(xy);
			if(HAS_BASE(pShape, CFOCompositeShape))
			{
				CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShape);
				xxFOUpdateComp(pComp);
				
			}
			pShape->OffsetAllPoints(-rcTotal.left, -rcTotal.top);
			
			if(theApp.dDrawingScale != 1.0)
			{
				pShape->ScaleShape(1.0/ theApp.dDrawingScale, 1.0 / theApp.dDrawingScale, 0, 0);
			}
			
			pShape->OffsetAllPoints(100, 100);
		}
	}
	else
	{
		CFODrawShape *pShape = NULL;
		int xy = 0;
		for(xy = 0; xy < GetCurrentModel()->GetShapes()->Count(); xy ++)
		{
			pShape = (CFODrawShape *)GetCurrentModel()->GetShapes()->GetObject(xy);
			if(HAS_BASE(pShape, CFOCompositeShape))
			{
				CFOCompositeShape *pComp = static_cast<CFOCompositeShape *>(pShape);
				xxFOUpdateComp(pComp);
				
			}
			pShape->OffsetAllPoints(100, 100);
		}
	}

	if(GetCurrentModel()->GetCompsCount() == 1)
	{
		CFODrawShape *pShape = (CFODrawShape *)GetCurrentModel()->GetShapes()->GetObject(0);
		if(pShape->IsKindOf(RUNTIME_CLASS(CFOGroupShape)))
		{
			CFOGroupShape *pGroup = static_cast<CFOGroupShape *>(pShape);
			if(pGroup->GetCompCount() < 40)
			{
				GetCurrentModel()->Ungroup(pGroup);
				bNotChanged = TRUE;
			}
			
		}
	}
	gfxData.m_bAllFullGeometry = bSave;
	FOPInvalidate();
}

void CSVGDemoView::OnUpdateConvertSvgShapes(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CSVGDemoView::OnExportSvg() 
{
	// TODO: Add your command handler code here
	static CString lasttime = _T("SVG Export");
	static CString szFilter = _T("Scalable Vector Graphics (*.svg)|*.svg|");
	CFileDialog fileDlg( FALSE, _T(".svg"), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter, NULL);
	
	if (fileDlg.DoModal() != IDOK)
		return;
	
	CString filename=fileDlg.GetFileName();
	lasttime = fileDlg.GetFileExt();
	
	GetCurrentModel()->ExportToSVG(filename);
}

void CSVGDemoView::OnUpdateExportSvg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
