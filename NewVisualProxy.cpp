// NewVisualProxy.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "NewVisualProxy.h"
#include "SVGDemo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewVisualProxy, CFOPVisualProxy)

CNewVisualProxy::CNewVisualProxy()
{

}

CNewVisualProxy::~CNewVisualProxy()
{

}

/////////////////////////////////////////////////////////////////////////////
// CNewVisualProxy diagnostics

#ifdef _DEBUG
void CNewVisualProxy::AssertValid() const
{
	CObject::AssertValid();
}

void CNewVisualProxy::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

CString CNewVisualProxy::GenerateDimText(int nLength)
{
	CString strReturn;
	strReturn.Format(_T("%u Pixel"),nLength);
	return strReturn;
}

void CNewVisualProxy::DoGenAddiToolTips(CString &strGen, const UINT &nType)
{
	if(nType == 31056)
	{
		strGen = _T("Key Setting...");
	}
	else if(nType == 31057)
	{
		strGen = _T("Event Setting...");
	}
	else
	{
		CFOPVisualProxy::DoGenAddiToolTips(strGen,nType);
	}
}

void CNewVisualProxy::GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType)
{
	
	CFOPVisualProxy::GenerateDefaultPorts(mpSpot,nShapeType);
}

BOOL CNewVisualProxy::GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack)
{
	
	return TRUE;
}

void CNewVisualProxy::DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType)
{
	{
		CFOPVisualProxy::DoDrawAddiWithType(pDC,rcPos,nType);
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CNewVisualProxy2, CFOPGDIPlusProxy)

CNewVisualProxy2::CNewVisualProxy2()
{

}

CNewVisualProxy2::~CNewVisualProxy2()
{

}

/////////////////////////////////////////////////////////////////////////////
// CNewVisualProxy2 diagnostics

#ifdef _DEBUG
void CNewVisualProxy2::AssertValid() const
{
	CObject::AssertValid();
}

void CNewVisualProxy2::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

CString CNewVisualProxy2::GenerateDimText(int nLength)
{
	CString strReturn;
	strReturn.Format(_T("%u Pixel"),nLength);
	return strReturn;
}

void CNewVisualProxy2::DoGenAddiToolTips(CString &strGen, const UINT &nType)
{
	if(nType == 31056)
	{
		strGen = _T("Key Setting...");
	}
	else if(nType == 31057)
	{
		strGen = _T("Event Setting...");
	}
	else
	{
		CFOPGDIPlusProxy::DoGenAddiToolTips(strGen,nType);
	}
}

void CNewVisualProxy2::GenerateDefaultPorts(CArray<FOP_PortScale,FOP_PortScale>* mpSpot,const int &nShapeType)
{

	CFOPGDIPlusProxy::GenerateDefaultPorts(mpSpot,nShapeType);
}

BOOL CNewVisualProxy2::GetBitmap(const CString &strFile,CFOBitmap &bmp, int cx, int cy,COLORREF crBack)
{
	
	cx;
	cy;
	crBack;

	return TRUE;
}

void CNewVisualProxy2::DoDrawAddiWithType(CDC *pDC,const CRect &rcPos,const UINT &nType)
{
	
	{
		CFOPGDIPlusProxy::DoDrawAddiWithType(pDC,rcPos,nType);
	}
}
