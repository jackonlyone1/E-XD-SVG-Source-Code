// Xml.cpp: implementation of the CXDXml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include  <io.h>
#include "XDXml.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool REPORT_ERROR(HRESULT hr, CString strTitle)
{
	TRACE(_T("%d, %s."), hr, strTitle);
	return false;
}

bool REPORT_ERROR(_com_error &e, CString strTitle)
{
	TRACE(_T("Error: Title: %s."), strTitle);
	TRACE(_T("Code = %08lx."), e.Error());
	TRACE(_T("Code Meaning = %s."), (char*)e.ErrorMessage());
	TRACE(_T("Source = %s."), (char*)e.Source());
	TRACE(_T("Error Description = %s."), (char*)e.Description());
	return false;
}

bool REPORT_ERROR(MSXML2::IXMLDOMParseErrorPtr errPtr, CString strTitle, CString strDsc)
{
	TRACE(_T("Error: Title: %s, Dsc: %s."), strTitle, strDsc);
	TRACE(_T("Error Code = 0x%x, File Pod = %d."), errPtr->errorCode, errPtr->filepos);
	TRACE(_T("Line = %ld; Line Pos : %ld; Reason = %s."), errPtr->line, errPtr->linepos, (char*)errPtr->reason);
	TRACE(_T("SrcText = %s; URL = %s."), errPtr->srcText, errPtr->url);
	return false;
}

CXDXml::CXDXml(): m_spDOMDocument(NULL), m_spDOMElement(NULL), m_bHasInit(false)
{
}

CXDXml::~CXDXml()
{
}
#define BCGP_HR_SUCCEEDED_OK(hr) (SUCCEEDED(hr) && hr == S_OK)

//////////////////////////////////////////////////////////////////////////
//	Inport Infomation from a XML file
//////////////////////////////////////////////////////////////////////////

bool CXDXml::Load(const CString &strFile)
{
	return (bool)_Load(_variant_t(_bstr_t(strFile)));
// 	if (false == CreateDocument()) return false;
// 
// //	Load the data from a XML file
// 	m_spDOMDocument->Putasync(S_FALSE);
// 	if(m_spDOMDocument->load((_bstr_t)strFile) == false)
// 	{
// 		MSXML2::IXMLDOMParseErrorPtr pDOMError = m_spDOMDocument->GetparseError();
// 		return REPORT_ERROR(pDOMError, _T("Load.load"));
// 	}
// 
// 	return true;
}
// 
// BOOL CXDXml::Load(const CString& fileName)
// {
// 	return _Load(_variant_t(_bstr_t(fileName)));
// }


BOOL CXDXml::Load(CFile& file)
{
	HRESULT result = E_INVALIDARG;
	BOOL bRes = FALSE;
	
	const UINT size = (UINT)file.GetLength();
	if (size > 0)
	{
		BYTE* buffer = new BYTE[size];
		if (buffer != NULL)
		{
			if (file.Read(buffer, size) == size)
			{
				bRes = Load(buffer, (UINT)size);
//				result = GetLastResult();
			}
			
			delete [] buffer;
		}
	}
	
//	SetLastResult(result);
	
	return bRes;
}

BOOL CXDXml::LoadFromBuffer(LPBYTE lpBuffer, UINT length)
{
	
	
	BOOL bReturn = Load(lpBuffer, length);
	// The MSXML parser is not nearly as robust as the internal one.
	// recover if needed!
	if(!bReturn)
	{
		return FALSE;
	}
	
	
	return bReturn;
}

BOOL CXDXml::Load(LPBYTE buffer, UINT size)
{
	HRESULT result = E_INVALIDARG;
	BOOL bRes = FALSE;
	
	if (size > 0)
	{
		HGLOBAL hGlobal = ::GlobalAlloc(GHND, size);
		if (hGlobal != NULL)
		{
			LPVOID lpVoid = ::GlobalLock(hGlobal);
			
			if (lpVoid != NULL)
			{
				memcpy(lpVoid, buffer, size);
				
				::GlobalUnlock(hGlobal);
				
				IStream* stream = NULL;
				result = ::CreateStreamOnHGlobal(hGlobal, FALSE, &stream);
				
				if (BCGP_HR_SUCCEEDED_OK(result) && stream != NULL)
				{
					bRes = Load(stream);
//					GetLastResult();
				}
				
				if (stream != NULL)
				{
					stream->Release();
				}
			}
			
			::GlobalFree(hGlobal);
		}
	}
	
//	SetLastResult(result);
	
	return bRes;
}

BOOL CXDXml::Load(IStream* stream)
{
	STATSTG stat = {0};
	stream->Stat(&stat, STATFLAG_NONAME);
	ULONGLONG size = stat.cbSize.QuadPart;
	if (size == 0)
	{
//		SetLastResult(E_INVALIDARG);
		return FALSE;
	}
	
	return _Load(_variant_t(stream, TRUE));
}

BOOL CXDXml::_Load(const _variant_t& value)
{
	if (false == CreateDocument()) return false;

	m_spDOMDocument->put_validateOnParse((VARIANT_BOOL)0);
	m_spDOMDocument->put_resolveExternals((VARIANT_BOOL)0);
	m_spDOMDocument->Putasync(S_FALSE);
	if(m_spDOMDocument->load(value) == false)
	{
		MSXML2::IXMLDOMParseErrorPtr pDOMError = m_spDOMDocument->GetparseError();
		return REPORT_ERROR(pDOMError, _T("Load.load"));
	}

	return TRUE;
}

//	Init the XML and Load the XML data from a XML file
bool CXDXml::LoadXml(const CString &strXML)
{
	if (false == CreateDocument()) return false;

//	Load the data from a XML String
	if(m_spDOMDocument->loadXML((_bstr_t)strXML) == false)
	{
		MSXML2::IXMLDOMParseErrorPtr pDOMError = m_spDOMDocument->GetparseError();
		return REPORT_ERROR(pDOMError, _T("LoadXml.loadXML"));
	}

	return true;
}

CXDXmlNode CXDXml::GetNode(CString strNode)
{
	_bstr_t bstrNode = strNode;
 
	CXDXmlNode node;

	if (!m_bHasInit) return node;

	MSXML2::IXMLDOMNodePtr spDOMNode = m_spDOMDocument->selectSingleNode(bstrNode);
	node.SetNode(spDOMNode);

	return node;
}

CXDXmlNode CXDXml::GetNodeList(CString strNode)
{
	_bstr_t bstrNode = strNode;

	CXDXmlNode	node;
	if(!m_bHasInit) return node;

	MSXML2::IXMLDOMNodeListPtr spDOMNodeList = m_spDOMDocument->selectNodes(bstrNode);
	if (spDOMNodeList->Getlength() > 0)
		node.SetNodeList(spDOMNodeList);

	return node;
}

_variant_t CXDXml::GetNodeVal(CString strNode)
{
	_variant_t vtVal;
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		vtVal.vt = VT_NULL;

	return vtVal;
}

CString CXDXml::GetNodeText(CString strNode, CString strDef)
{
	_variant_t	vtVal;
	CString strText = strDef;
	_bstr_t bstrNode = strNode;

	if(!GetNodeVal(bstrNode, vtVal))
		return strText;

	if(vtVal.vt != VT_NULL && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BSTR);
		strText = vtVal.bstrVal;
	}
	return strText;
}

CXDXmlNode CXDXml::FindParamNode(_bstr_t bstrParentEle, CString strParamName)
{
	CXDXmlNode node;
	if(!m_bHasInit) return node;

	MSXML2::IXMLDOMNodeListPtr spDOMNodeList = m_spDOMDocument->selectNodes(bstrParentEle);
	if (spDOMNodeList->Getlength() < 1) return node;

	for (long i = 0; i < spDOMNodeList->Getlength(); i++)
	{
		MSXML2::IXMLDOMNodePtr spDOMNode = spDOMNodeList->Getitem(i);
		if (spDOMNode == NULL) continue;

		MSXML2::IXMLDOMNodePtr spDOMChildNode = spDOMNode->selectSingleNode(_bstr_t("NAME"));
		if (spDOMChildNode == NULL) continue;

		_bstr_t bstrName = spDOMChildNode->Gettext();
		if (_tcscmp((LPCTSTR)bstrName, strParamName) == 0)
		{
			node.SetNode(spDOMNode);
			break;
		}
	}

	return node;
}

bool CXDXml::BackToParent()
{
	if(!m_bHasInit || !m_stackDOMElement.CanPop())
		return false;

	return m_stackDOMElement.Pop(m_spDOMElement);
}

//////////////////////////////////////////////////////////////////////////
//	Export Information to a XML file
//////////////////////////////////////////////////////////////////////////

bool CXDXml::CreateRoot(CString strRoot)
{
//	init XML first
	if (false == CreateDocument()) return false;

 	try
	{
		m_spDOMDocument->loadXML(_bstr_t(""));
		MSXML2::IXMLDOMProcessingInstructionPtr pDOMPI;
		pDOMPI = m_spDOMDocument->createProcessingInstruction(_bstr_t(_T("xml")), _bstr_t(_T("version=\"1.0\" encoding=\"UTF-8\"")));
		m_spDOMDocument->appendChild(pDOMPI);
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml::CreateRoot.appendChild."));
	}

 	try
	{
		m_spDOMElement = m_spDOMDocument->createElement(_bstr_t(strRoot));
		m_spDOMElement->setAttribute(_bstr_t("xmlns:xsi"), _bstr_t("http://www.w3.org/2001/XMLSchema-instance"));
		m_spDOMDocument->documentElement = m_spDOMElement;
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml::CreateRoot.Create Root."));
	}
	
	return true;
}

bool CXDXml::AddXmlFragment(_bstr_t bstrXml)
{
//	Init First
	MSXML2::IXMLDOMDocumentPtr spDocument;
	try
	{
		if(FAILED(spDocument.CreateInstance(__uuidof(MSXML2::DOMDocument))))
		{
			return REPORT_ERROR(-1, _T("CXDXml.AddXmlFragment.CreateInstance."));
		}

		spDocument->async = VARIANT_FALSE;
		if(spDocument->loadXML(bstrXml) != S_OK) 
		{
			MSXML2::IXMLDOMParseErrorPtr errPtr = spDocument->GetparseError();
			return REPORT_ERROR(errPtr, _T("CXDXml.AddXmlFragment.loadXML."));
		}
	}
	catch(_com_error e) 
	{
		return REPORT_ERROR(e, _T("CXDXml::AddXmlFragment.Failed Init."));
	}

//	Create a new document fragment
	MSXML2::IXMLDOMDocumentFragmentPtr spFragment;
	try
	{
		spFragment	= spDocument->createDocumentFragment();
		if (spFragment == NULL)
		{
			return REPORT_ERROR(GetLastError(), _T("CXDXml::AddXmlFragment.Create XMLDOMDocumentFragment return NULL."));
		}
		spFragment->appendChild(spDocument->documentElement);
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml::AddXmlFragment.Create XMLDOMDocumentFragment Failed."));
	}

//	Add the new fragment to the XML file
	try
	{
		m_spDOMElement->appendChild(spFragment);
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml::AddXmlFragment.Add XMLDOMDocumentFragment to  MSXML2::DOMDocument Failed."));
	}

	return true;
}

bool CXDXml::AddChildElement(CString strElement)
{
	if (!m_bHasInit) return false;

	m_stackDOMElement.Push(m_spDOMElement);
	try
	{
		MSXML2::IXMLDOMElementPtr spDOMElement = m_spDOMDocument->createElement(_bstr_t(strElement));
		m_spDOMElement->appendChild(spDOMElement);
		m_spDOMElement = spDOMElement;
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml.AddChildElement.Create Child Failed."));
	}

	return true;
}

bool CXDXml::AddAttribute(CString strName, CString strValue)
{
	if (!m_bHasInit) return false;

	try
	{
		m_spDOMElement->setAttribute(_bstr_t(strName), _bstr_t(strValue));
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml.AddChildElement.Create Child Failed."));
	}

	return true;
}

bool CXDXml::AddChildTextNode(CString strNodeName, CString strValue)
{
	if (!m_bHasInit || m_spDOMElement == NULL)
		return false;

	try
	{
		MSXML2::IXMLDOMElementPtr pDOMElem = m_spDOMDocument->createElement(_bstr_t(strNodeName));
		m_spDOMElement->appendChild(pDOMElem);

		MSXML2::IXMLDOMNodePtr pDOMNode = m_spDOMDocument->createTextNode(_bstr_t(strValue));
		pDOMElem->appendChild(pDOMNode);
	}
	catch(_com_error e)
	{
		return REPORT_ERROR(e, _T("CXDXml.AddChildTextNode. Create TEXT Failed."));
	}

	return true;
}

//	Save the XML data to a XML file use the strFile name
bool CXDXml::SaveXml(const CString &strFile)
{
	if (!m_bHasInit) return false;

	try
	{
		if (FAILED(m_spDOMDocument->save(_bstr_t(strFile))))
			return REPORT_ERROR(-1, _T("CXDXml.SaveXml.Save XML File Failed."));
	}
	catch (_com_error e) 
	{
		return REPORT_ERROR(e, _T("CXDXml.SaveXml.Save XML File Failed."));
	}

	return true;
}

MSXML2::IXMLDOMDocumentPtr CXDXml::GetDocumentPtr()
{
	if (!m_bHasInit) return NULL;
	return m_spDOMDocument;
}

_bstr_t CXDXml::GetXml()
{
	if (m_bHasInit)
		return m_spDOMDocument->xml;
	return _bstr_t("");
}

bool CXDXml::CreateDocument()
{
//	Init the XML
	if (m_spDOMDocument != NULL) return true;

	try
	{
		if (FAILED(m_spDOMDocument.CreateInstance(__uuidof(MSXML2::DOMDocument))))
			return REPORT_ERROR(-1, _T("Create Instanse Failed."));

		m_spDOMDocument->async = false; 
	}
	catch (_com_error e)
	{
		return REPORT_ERROR(e, _T("Create Instanse Failed."));
	}
	m_bHasInit = true;
	return true;
}

bool CXDXml::GetNodeVal(_bstr_t bstrNode, _variant_t& vtVal)
{
	MSXML2::IXMLDOMNodePtr pDOMNode;
	BSTR bstrComtent;
	CString strComtent(_T(""));

	vtVal.vt = VT_EMPTY;
	if(m_bHasInit == false)
	{
		return REPORT_ERROR(0L, _T("CXDXml::GetNodeVal.Init XMLDOM First."));
	}

	try
	{
		pDOMNode = m_spDOMDocument->selectSingleNode(bstrNode);
		if(pDOMNode == NULL)
		{
			return REPORT_ERROR(0L, _T("CXDXml::GetNodeVal.Can't Find Item."));
		}
		if(FAILED(pDOMNode->get_text(&bstrComtent)))
		{
			return REPORT_ERROR(-1, _T("CXDXml::GetNodeVal.getNamedItem."));
		}
		
		vtVal = bstrComtent;
		return true;
	}
	catch(_com_error e) 
	{
		return REPORT_ERROR(e, _T("CXDXml::GetNodeVal.getNamedItem."));
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
//	CXDXmlNode
//////////////////////////////////////////////////////////////////////////

CXDXmlNode::CXDXmlNode()
{
	m_spDOMNode		= NULL;
	m_spDOMNodeList	= NULL;
}

void CXDXmlNode::SetNode(MSXML2::IXMLDOMNodePtr node)
{
	m_spDOMNode = node;
}

void CXDXmlNode::SetNodeList(MSXML2::IXMLDOMNodeListPtr list)
{
	m_spDOMNodeList = list;
}

bool CXDXmlNode::SetParamVal(_variant_t vtVal)
{
	if(m_spDOMNode == NULL)
		return false;
	if(vtVal.vt == VT_NULL || vtVal.vt == VT_EMPTY)
		return false;

	_bstr_t	bstrText = m_spDOMNode->GetnodeName();
	if(_tcscmp((LPCTSTR)bstrText, _T("PARAM")) != 0)
		return false;

	MSXML2::IXMLDOMNodePtr spValNode = m_spDOMNode->selectSingleNode(_T("VALUE"));
	if(spValNode == NULL)
		return false;

	vtVal.ChangeType(VT_BSTR);
	HRESULT	hr = spValNode->put_text(vtVal.bstrVal);

	return SUCCEEDED(hr);
}

CXDNamedNode CXDXmlNode::GetNamedNode()
{
	CXDNamedNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	MSXML2::IXMLDOMNamedNodeMapPtr attributes = m_spDOMNode->Getattributes();
	node.SetNode(attributes);
	return node;
}

CXDNamedNode CXDXmlNode::GetNamedNode(_bstr_t bstrNode)
{
	CXDNamedNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	MSXML2::IXMLDOMNodePtr spDOMNode = m_spDOMNode->selectSingleNode(bstrNode);
	if (NULL == spDOMNode) 
		return node;

	MSXML2::IXMLDOMNamedNodeMapPtr attributes = spDOMNode->Getattributes();
	node.SetNode(attributes);
	return node;
}

CXDXmlNode CXDXmlNode::GetFirstChildNode()
{
	CXDXmlNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	node.SetNode(m_spDOMNode->GetfirstChild());

	return node;
}

CXDXmlNode CXDXmlNode::GetNextChildNode()
{
	CXDXmlNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	node.SetNode(m_spDOMNode->GetnextSibling());

	return node;
}

CXDXmlNode CXDXmlNode::GetChildNodes()
{
	CXDXmlNode node;
	
	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;
		
		m_spDOMNode = m_spDOMNodeList->nextNode();
		
		if(m_spDOMNode == NULL)
			return node;
	}
	
	node.SetNodeList(m_spDOMNode->GetchildNodes());
	
	return node;
}

CXDXmlNode CXDXmlNode::GetItemNode(const int &nIndex)
{
	CXDXmlNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	node.SetNode(m_spDOMNodeList->Getitem(nIndex));

	return node;
}

CXDXmlNode CXDXmlNode::GetNode(CString strNode)
{
	_bstr_t bstrNode = strNode;
	CXDXmlNode node;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	MSXML2::IXMLDOMNodePtr spDOMNode = m_spDOMNode->selectSingleNode(bstrNode);
	node.SetNode(spDOMNode);

	return node;
}

CXDXmlNode CXDXmlNode::GetNodeList(CString strNode)
{
	_bstr_t bstrNode = strNode;

	CXDXmlNode node;
	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return node;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return node;
	}

	MSXML2::IXMLDOMNodeListPtr list = m_spDOMNode->selectNodes(bstrNode);
	if(list->Getlength() < 1)
		list = NULL;

	node.SetNodeList(list);

	return node;
}

CString CXDXmlNode::GetNodeText(const CString &strNode, CString strDef)
{
	_variant_t vtVal;
	CString	strText = strDef;
	_bstr_t	bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return strText;

	if(vtVal.vt != VT_EMPTY && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BSTR);
		strText = vtVal.bstrVal;
	}
	return strText;
}

void CXDXmlNode::GetNodeValue(const CString &strNode, CString &strNodeText)
{
	strNodeText = _T("");

	_variant_t	vtVal;
	_bstr_t	bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return;

	if(vtVal.vt != VT_EMPTY && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BSTR);
		strNodeText = vtVal.bstrVal;
	}
}

int CXDXmlNode::GetNodeInt(const CString &strNode, int nDef)
{
	_variant_t	vtVal;

	TCHAR *pCharStop = NULL;

	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return nDef;

	CString strX = CString(vtVal.bstrVal);
	double dValue = (float)_tcstod(strX.GetBuffer(strX.GetLength()), &pCharStop);
	if(dValue != 0.0 && dValue < 1.0 && dValue > -1.0)
	{
		dValue = 1.0;
	}

	return CFODrawHelper::RoundValue(dValue);
}

float CXDXmlNode::GetNodeFloat(const CString &strNode, float fDef)
{
	_variant_t	vtVal;
	
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return fDef;
	
	TCHAR *pCharStop = NULL;
	CString strValue(vtVal.bstrVal);
	return (float)_tcstod(strValue.GetBuffer(strValue.GetLength()), &pCharStop);
}

double CXDXmlNode::GetNodeDouble(const CString &strNode, double dDef)
{
	_variant_t	vtVal;
	
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return dDef;
	
	TCHAR *pCharStop = NULL;
	CString strValue(vtVal.bstrVal);
	return _tcstod(strValue.GetBuffer(strValue.GetLength()), &pCharStop);
}

void CXDXmlNode::GetNodeValue(const CString &strNode, int &nNodeInt)
{
	nNodeInt = 0;

	_variant_t	vtVal;
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return;

	if(vtVal.vt != VT_EMPTY && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_I4);
		nNodeInt = vtVal.lVal;
	}
}

bool CXDXmlNode::GetNodeBool(const CString &strNode, bool bDef)
{
	_variant_t	vtVal;

	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return bDef;

	if(vtVal.vt != VT_EMPTY && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BOOL);
		return (vtVal.boolVal == 0)? false:true;
	}
	return bDef;
}

void CXDXmlNode::GetNodeValue(const CString &strNode, bool &bNodeBool)
{
	bNodeBool = false;

	_variant_t vtVal;
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return;

	if(vtVal.vt != VT_EMPTY && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BOOL);
		bNodeBool = (vtVal.boolVal == 0)? false:true;
	}
}

CString CXDXmlNode::GetXml()
{
	CString strXml = _T("");

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return strXml;
		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return strXml;
	}

	strXml = CString((wchar_t*)m_spDOMNode->xml);
	return strXml;
}

CString CXDXmlNode::GetText()
{
	CString strText = _T("");

	if (m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return strText;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return strText;
	}

	strText = CString((wchar_t*)m_spDOMNode->Gettext());
	return strText;
}

CString CXDXmlNode::GetNodeName()
{
	CString strName = _T("");

	if (m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return strName;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return strName;
	}

	strName = CString((wchar_t*)m_spDOMNode->GetnodeName());

	return strName;
}

_variant_t CXDXmlNode::GetNodeVal(const CString &strNode)
{
	_variant_t vtVal;
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		vtVal.vt = VT_NULL;

	return vtVal;
}

bool CXDXmlNode::GetNextNode()
{
	if(m_spDOMNodeList == NULL)
		return false;

	m_spDOMNode = m_spDOMNodeList->nextNode();

	if(m_spDOMNode == NULL)
		return false;

	return true;
}

bool CXDXmlNode::GetNextNode(CString& strName, CString& strVal)
{
	if(m_spDOMNodeList == NULL)
		return false;
	
	m_spDOMNode = m_spDOMNodeList->nextNode();
	if(m_spDOMNode == NULL)
		return false;

	MSXML2::IXMLDOMNodePtr spDOMNameNode	= m_spDOMNode->selectSingleNode(_bstr_t(_T("NAME")));
	MSXML2::IXMLDOMNodePtr spDOMValNode		= m_spDOMNode->selectSingleNode(_bstr_t(_T("VALUE")));
	
	strName.Empty();
	strVal.Empty();
	if(spDOMNameNode != NULL)
	{
		BSTR bstrName;
		spDOMNameNode->get_text(&bstrName);
		strName = bstrName;
	}
	if(spDOMValNode != NULL)
	{
		BSTR bstrVal;
		spDOMValNode->get_text(&bstrVal);
		strVal = bstrVal;
	}
	
	return true;
}

bool CXDXmlNode::GetNodeVal(_bstr_t bstrNode, _variant_t& vtVal)
{
	vtVal.vt = VT_EMPTY;

	if(m_spDOMNode == NULL)
	{
		if(m_spDOMNodeList == NULL)
			return false;

		m_spDOMNode = m_spDOMNodeList->nextNode();

		if(m_spDOMNode == NULL)
			return false;
	}
	
	BSTR bstrComtent;
	MSXML2::IXMLDOMNodePtr	spDOMNode;
	
	try
	{
		if(bstrNode == _bstr_t(""))
			spDOMNode = m_spDOMNode;
		else
			spDOMNode = m_spDOMNode->selectSingleNode(bstrNode);

		if(spDOMNode == NULL)
		{
			return REPORT_ERROR(0L, _T("CXDXmlNode::GetNodeVal.Can't find NamedItem ."));
		}

		if(FAILED(spDOMNode->get_text(&bstrComtent)))
		{
			return REPORT_ERROR(-1, _T("CXDXmlNode::GetNodeVal.getNamedItem."));
		}

		vtVal.vt = VT_BSTR;
		vtVal.bstrVal = bstrComtent;
		return true;
	}
	catch(_com_error e) 
	{
		return REPORT_ERROR(e, _T("CXDXmlNode::GetNodeVal.getNamedItem."));
	}
	
	return false;
}

bool CXDXmlNode::IsEmpty()
{
	if(m_spDOMNode == NULL && m_spDOMNodeList == NULL)
		return true;
	return false;
}

int CXDXmlNode::GetNodeListSize()
{
	if(m_spDOMNode == NULL && m_spDOMNodeList == NULL)
		return 0;
	if(m_spDOMNode != NULL && m_spDOMNodeList == NULL)
		return 1;

	return m_spDOMNodeList->Getlength();
}

//////////////////////////////////////////////////////////////////////////
//	CXDNamedNode
//////////////////////////////////////////////////////////////////////////
CXDNamedNode::CXDNamedNode()
{
	m_spNamedNodeMap = NULL;
}

void CXDNamedNode::SetNode(MSXML2::IXMLDOMNamedNodeMapPtr namedNode)
{
	m_spNamedNodeMap = namedNode;
}

CXDXmlNode CXDNamedNode::GetFirstNode()
{
	CXDXmlNode node;
	if (NULL == m_spNamedNodeMap) return node;

	node.SetNode(m_spNamedNodeMap->nextNode());

	return node;
}

CXDXmlNode CXDNamedNode::GetNextNode()
{
	CXDXmlNode node;
	if (NULL == m_spNamedNodeMap) return node;

	node.SetNode(m_spNamedNodeMap->nextNode());

	return node;
}

int CXDNamedNode::GetSize()
{
	if (NULL == m_spNamedNodeMap) return 0;

	return m_spNamedNodeMap->Getlength();
}

CXDXmlNode CXDNamedNode::GetItemNode(int i)
{
	CXDXmlNode node;
	if (NULL == m_spNamedNodeMap) return node;

	node.SetNode(m_spNamedNodeMap->Getitem(i));

	return node;
}

CString	CXDNamedNode::GetNodeText(const CString &strNode, CString strDef)
{
	_variant_t	vtVal;
	CString strText = strDef;
	_bstr_t bstrNode = strNode;

	if(!GetNodeVal(bstrNode, vtVal))
		return strText;

	if(vtVal.vt != VT_NULL && vtVal.vt != VT_NULL)
	{
		vtVal.ChangeType(VT_BSTR);
		strText = vtVal.bstrVal;
	}
	return strText;
}

int	CXDNamedNode::GetNodeInt(const CString &strNode, int nDef)
{
	_variant_t	vtVal;
	
	TCHAR *pCharStop = NULL;
	
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return nDef;
	
	CString strX = CString(vtVal.bstrVal);
	double dValue = (float)_tcstod(strX.GetBuffer(strX.GetLength()), &pCharStop);
	if(dValue != 0.0 && dValue < 1.0 && dValue > -1.0)
	{
		dValue = 1.0;
	}
	
	return CFODrawHelper::RoundValue(dValue);

}

float CXDNamedNode::GetNodeFloat(const CString &strNode, float fDef)
{
	_variant_t	vtVal;
	
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return fDef;

	TCHAR *pCharStop = NULL;
	CString strValue(vtVal.bstrVal);
	return (float)_tcstod(strValue.GetBuffer(strValue.GetLength()), &pCharStop);
}

double CXDNamedNode::GetNodeDouble(const CString &strNode, double dDef)
{
	_variant_t	vtVal;
	
	_bstr_t bstrNode = strNode;
	if(!GetNodeVal(bstrNode, vtVal))
		return dDef;
	
	TCHAR *pCharStop = NULL;
	CString strValue(vtVal.bstrVal);
	return _tcstod(strValue.GetBuffer(strValue.GetLength()), &pCharStop);
}

BOOL CXDNamedNode::GetNodeVal(const _bstr_t &bstrNode, _variant_t& vtVal)
{
	vtVal.vt = VT_EMPTY;

	if (NULL == m_spNamedNodeMap) return FALSE;

	try
	{
		MSXML2::IXMLDOMNodePtr pNode = m_spNamedNodeMap->getNamedItem(bstrNode);
		if (NULL != pNode)
		{
			BSTR bstrComtent;
			if(FAILED(pNode->get_text(&bstrComtent)))
			{
				REPORT_ERROR(-1, _T("CXDXmlNode::GetNodeVal"), _T("get_text"));
			}

			vtVal.vt = VT_BSTR;
			vtVal.bstrVal = bstrComtent;
			return TRUE;
		}
	}
	catch(_com_error e) 
	{
		REPORT_ERROR(e, _T("CXDXmlNode::GetNodeVal: getNamedItem"));
	}
	
	return FALSE;
}

BOOL CXDNamedNode::SetNodeText(const CString &strNode, const CString &strVal)
{
	return SetNodeVal(_bstr_t(strNode), _bstr_t(strVal));
}

BOOL CXDNamedNode::SetNodeVal(const _bstr_t &bstrNode, const _bstr_t& bstrVal)
{
	if (NULL == m_spNamedNodeMap) return FALSE;

	try
	{
		MSXML2::IXMLDOMNodePtr pNode = m_spNamedNodeMap->getNamedItem(bstrNode);
		if (NULL != pNode)
		{
			if(FAILED(pNode->put_text(bstrVal)))
			{
				REPORT_ERROR(-1, _T("CXDXmlNode::GetNodeVal"), _T("put_text"));
			}
			return TRUE;
		}
	}
	catch(_com_error e) 
	{
		REPORT_ERROR(e, _T("CXDXmlNode::GetNodeVal:getNamedItem."));
	}
	
	return FALSE;
}
