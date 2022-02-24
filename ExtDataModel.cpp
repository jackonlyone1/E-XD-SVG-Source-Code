// ExtDataModel.cpp: implementation of the CExtDataModel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExtDataModel.h"
#include "SVGDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CExtDataModel construction/destruction

IMPLEMENT_SERIAL(CExtDataModel, CFODataModel, 0)

CExtDataModel::CExtDataModel()
{
	//FOTO:Add you code here.
	SetPointLimitWithPage(TRUE);
	m_rectPosition = CRect(0,0, 3000,3000);
	SetCanvasSize(m_rectPosition.Size());
	ShowGrid(FALSE);
}

CExtDataModel::CExtDataModel(const CExtDataModel& source)
{
	*this			= source;
}

CExtDataModel::~CExtDataModel()
{
	//FOTO:Add you code here.

}

CFODataModel* CExtDataModel::Copy() const
{
	return (new CExtDataModel(*this));
}

CExtDataModel& CExtDataModel::operator=(const CExtDataModel& source)
{
	(*(CFODataModel*)this) = source;

	return (*this);
}

void CExtDataModel::DoInitData()
{
	CFODataModel::DoInitData();

	//FOTO:Add you code here.

}

void CExtDataModel::DoInitCreateShape(CFODrawShape *pShape)
{
	CFODataModel::DoInitCreateShape(pShape);
}

void CExtDataModel::NotifyObserver(LPARAM lHint, CObject*pHint)
{
	CFODataModel::NotifyObserver(lHint,pHint);

	//FOTO:Add you code here.

}

void CExtDataModel::UpdateTitle()
{
	CFODataModel::UpdateTitle();

//	if(m_pOwner == NULL)
//	{
//		return;
//	}
//
//	if(m_pOwner->GetSafeHwnd() != NULL)
//	{
//		if(m_pOwner ->IsKindOf(RUNTIME_CLASS(CFODrawView)))
//		{
//			CFODrawView *pView = (CFODrawView *) m_pOwner;
//			CDocument *m_pDocument = (CDocument *)pView->GetDocument();
//			if(m_pDocument != NULL)
//			{
//				if (m_strTitleOrg.IsEmpty() && !m_pDocument->GetTitle().IsEmpty())
//					m_strTitleOrg = m_pDocument->GetTitle();
//				
//				if (!m_strTitleOrg.IsEmpty())
//				{
//					TCHAR szStr[256+_MAX_PATH];
//					_tcscpy(szStr, m_strTitleOrg);
//					if (IsDirty())
//					{
//						if(m_strTitleOrg.Find(_T("*"))<0)
//						{
//							lstrcat(szStr, _T(" *"));
//						}
//					}
//					if (m_pDocument->GetTitle() != szStr)
//					{
//						m_pDocument->SetTitle(szStr);
//						m_pDocument->UpdateFrameCounts();
//					}
//				}
//			}
//		}
//	}
}

void CExtDataModel::DoActionChange(const CFOBaseAction* pAction)
{
	CFODataModel::DoActionChange(pAction);
	
	// FODO:Add your own specify code here.

}


CString CExtDataModel::CreateBaseName(UINT nType)
{
	/*switch(nType)
	{
	case MY_DROPMENUBUTTON:
		{
			return _T("DropMenuButton");
		}
		break;

	case MY_DROPCOLORBUTTON:
		{
			return _T("DropColorButton");
		}
		break;

	default:
		{*/
			return CFODataModel::CreateBaseName(nType);
		/*}
		break;
	}*/

}

CString CExtDataModel::CreateBaseCaption(UINT nType)
{
	/*switch(nType)
	{
	case MY_DROPMENUBUTTON:
		{
			return _T("Drop Menu Button");
		}
		break;

	case MY_DROPCOLORBUTTON:
		{
			return _T("Color");
		}
		break;

	default:
		{*/
			return CFODataModel::CreateBaseCaption(nType);
		/*}
		break;
	}*/

}

CString CExtDataModel::GetUniqueName(UINT nType)
{
	return CFODataModel::GetUniqueName(nType);
}

CString CExtDataModel::GetUniqueCaption(UINT nType)
{

	return CFODataModel::GetUniqueCaption(nType);
}

CFODrawShape *CExtDataModel::DoCreateShapeByType(UINT m_drawshape,
														CRect &rcCreate,
														CString strFileName,
														CFOToolBoxItem *pCurItem)
{
	CFODrawShape *pReturn = NULL;
	/*CString strCaption;
	CString strName;
	strCaption = "";
	strName = "";
	CPoint ptTrack = rcCreate.TopLeft();
	if(m_drawshape != FO_COMP_NONE)
	{
		CRect rc(rcCreate);
		rc.NormalizeRect();
		if(rc.IsRectEmpty()||(rc.Width()<=10 && rc.Height()<20))
		{
			switch(m_drawshape)
			{
			case MY_DROPMENUBUTTON:
				{
					rc = CRect(ptTrack.x-80,ptTrack.y-15,ptTrack.x+80,ptTrack.y+15);
				}
				break;

			case MY_DROPCOLORBUTTON:
				{
					rc = CRect(ptTrack.x-80,ptTrack.y-15,ptTrack.x+80,ptTrack.y+15);
				}
				break;
				
			default:
				{
				}
				break;
			}
		}

		switch(m_drawshape)
		{
		case MY_DROPMENUBUTTON:
			{
				pReturn = new CMyDropMenuButtonShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;
			
		case MY_DROPCOLORBUTTON:
			{
				pReturn = new CMyColorPickerShape;
				pReturn->AddRef();
				pReturn->Create(rc,"");
				pReturn->UpdatePosition();
				strCaption = GetUniqueCaption(pReturn->GetType());
				strName = GetUniqueName(pReturn->GetType());
				pReturn->SetObjectCaption(strCaption);
				pReturn->SetObjectName(strName);
			}
			break;

		default:
			{*/
				pReturn = CFODataModel::DoCreateShapeByType(m_drawshape,rcCreate,strFileName);
			/*}
			break;
		}
	}*/
	return pReturn;
}

CFOCompositeShape *CExtDataModel::DoCreateCompositeShapeByType(UINT m_drawshape,
																  CRect &rcCreate,
																  CArray<FOPORTVALUE,FOPORTVALUE> *arInitPorts,
																  CString strFileName,
																  UINT nResID,
																  CFOToolBoxItem *pCurItem)
{
	CFOCompositeShape *pReturn = CFODataModel::DoCreateCompositeShapeByType(m_drawshape,
															rcCreate,
															arInitPorts,
															strFileName,
															nResID,
															pCurItem);
	// FODO: Add your own specify code here.

	return pReturn;
}


void CExtDataModel::SetModifiedFlag(BOOL b)
{
	CFODataModel::SetModifiedFlag(b);
	
	//FOTO:Add you code here.

}

BOOL CExtDataModel::IsModified()
{

	//FOTO:Add you code here.

	return CFODataModel::IsModified();
}

void CExtDataModel::Serialize(CArchive& ar)
{
	CFODataModel::Serialize(ar);
	if(ar.IsStoring())
	{
		//FOTO:Add you code here.

	}
	else
	{
		//FOTO:Add you code here.

	}
}

/////////////////////////////////////////////////////////////////////////////
// CPrintBaseJob serialization
CFile* CExtDataModel::GetFile(LPCTSTR lpszFileName, UINT nOpenFlags,
							 CFileException* pError)
{
	CMirrorFile* pFile = new CMirrorFile;
	ASSERT(pFile != NULL);
	if (!pFile->Open(lpszFileName, nOpenFlags, pError))
	{
		delete pFile;
		pFile = NULL;
	}
	return pFile;
}

void CExtDataModel::ReleaseFile(CFile* pFile, BOOL bAbort)
{
	ASSERT_KINDOF(CFile, pFile);
	if (bAbort)
		pFile->Abort(); // will not throw an exception
	else
		pFile->Close();
	delete pFile;
}

BOOL CExtDataModel::OpenDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyWrite, &fe);
	if (pFile == NULL)
	{
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		if (pFile->GetLength() != 0)
			Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
		
	return TRUE;
}

BOOL CExtDataModel::SaveDocument(LPCTSTR lpszPathName)
{
	CFileException fe;
	CFile* pFile = NULL;
	pFile = GetFile(lpszPathName, CFile::modeCreate |
		CFile::modeReadWrite | CFile::shareExclusive, &fe);
	
	if (pFile == NULL)
	{
		
		return FALSE;
	}
	strCurOpenFormFile = CString(lpszPathName);
	CArchive saveArchive(pFile, CArchive::store | CArchive::bNoFlushOnDelete);
	saveArchive.m_bForceFlat = FALSE;
	TRY
	{
		CWaitCursor wait;
		Serialize(saveArchive);     // save me
		saveArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	CATCH_ALL(e)
	{
		ReleaseFile(pFile, TRUE);
		
		return FALSE;
	}
	END_CATCH_ALL
		
	return TRUE;        // success
}

void CExtDataModel::OnDrawShape(CDC *pDC,const CRect &rcView)
{
	CFODataModel::OnDrawShape(pDC,rcView);
	//FOTO:Add you code here.

}

void CExtDataModel::OnDrawBack(CDC *pDC,const CRect &rcClip)
{
	CFODataModel::OnDrawBack(pDC,rcClip);
	//FOTO:Add you code here.

}


/////////////////////////////////////////////////////////////////////////////
// CExtDataModel diagnostics

#ifdef _DEBUG
void CExtDataModel::AssertValid() const
{
	CFODataModel::AssertValid();
}

void CExtDataModel::Dump(CDumpContext& dc) const
{
	CFODataModel::Dump(dc);
}
#endif //_DEBUG

void CExtDataModel::ExportToSVG(CString strFileName)
{
    USES_CONVERSION;
    
    CStdioFile outFile;
    CFileException ex;
    CString str;
	
	{
		if (!outFile.Open(strFileName, CFile::modeWrite | CFile::modeCreate| CFile::typeText, &ex))
		{ ex.ReportError();
        return;
		}
    }
	
    TRY
    {   
        outFile.WriteString(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"));
		outFile.WriteString(_T("<!-- Create with UCanCode Software (http://www.ucancode.net/) -->\n"));
		
		FOPRect rcPos = GetPagePosition();
		CString strO;
		strO.Format(_T("<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" style=\"background-color:#FFFFFF\" id=\"main\" viewBox=\"0 0 %d %d\" width=\"%d\" height=\"%d\">\n"), rcPos.Width(), rcPos.Height(), rcPos.Width(), rcPos.Height());
        outFile.WriteString(strO);
		
		if(1) // Export background to svg.
		{
			FOPRect rcBack = GetPagePosition();
			
			CFORectShape *pRect = new CFORectShape;
			pRect->SetKeyId1(_T("ucc_svg"));
			//	pRect->AddRef();
			pRect->Create(rcBack);
			pRect->SetLineWidth(0);
			pRect->SetNullPen(TRUE);
			COLORREF crBack = GetBkColor();
			COLORREF crPattern = GetPatternColor();
			
			pRect->SetBkColor(crBack);
			pRect->SetPatternColor(crPattern);
			pRect->SetBrushType(GetBrushType());
			pRect->RemoveAllPorts();
			pRect->ExportToSVG(&outFile);
			//	pRect->Release();
			
			delete pRect;
			pRect = NULL;
		}
		
        // the visibility of page is not defined yet
        // if (!pPage->IsVisible()) return;
        
		CFODrawShape* pObj = NULL;
		
		int nCountShape = GetShapes()->GetCount();
		int xy = 0;
		for(xy = 0; xy < nCountShape; xy ++)
		{
			pObj = (CFODrawShape* )GetShapes()->GetObject(xy);
			if(pObj != NULL)
			{
				
				pObj->ExportToSVG(&outFile);
				
			}
		}
		
        outFile.WriteString(_T("\n</svg>"));  // end of svg fragment
		
        strFileName = outFile.GetFilePath();  // save the full path of svg file
		
        outFile.Close();
    }
    
    CATCH (CFileException, e)
    {
#ifdef _DEBUG
        afxDump << "File "<<strFileName<<" creation error.\n";
#endif
    }
    END_CATCH
		
		TCHAR NameBuff[255];                          // the name of preview html file
    if(GetTempPath(255, NameBuff)==0) {           // in case no temp directory available
		_tcscpy(NameBuff, _T("SVG_Preview.html"));  // put it in the current directory
    }
    else {
		_tcscat(NameBuff, _T("SVG_Preview.html"));
    }
	
	
    if (!outFile.Open(NameBuff, CFile::modeWrite | CFile::modeCreate| CFile::typeText, &ex))
    {
		ex.ReportError();
		return;
    }
	
    TRY
    {
		CString s;
		s.Format(_T("<EMBED SRC=\"%s\" WIDTH=\"%d\" HEIGHT=\"%d\">"),
			strFileName, GetCanvasSize().cx, GetCanvasSize().cy);
		outFile.WriteString(s);
		outFile.Close();
		
		//  ShellExecute(NULL, _T("open"), NameBuff, NULL, NULL, SW_SHOWNORMAL);
    }
    CATCH (CFileException, e)
    {
#ifdef _DEBUG
		afxDump << "File "<<NameBuff<<" creation error.\n";
#endif
    }
    END_CATCH
		
		
		str = outFile.GetFilePath();
	
	//    AfxGetApp()->GetMainWnd()->SendMessage(SVIZ_WM_SVGEXPORT_UPDATED, (WPARAM)&(str), 0);
}
