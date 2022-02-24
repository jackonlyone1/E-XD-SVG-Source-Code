// Xml.h: interface for the CXDXml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOKXML_H__A77B9829_2B3B_414F_8A0A_C60883CCB2DE__INCLUDED_)
#define AFX_HOKXML_H__A77B9829_2B3B_414F_8A0A_C60883CCB2DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <msxml.h> 
#import "msxml4.dll"
using namespace MSXML2;

#define _MAX_ARRAY	10

class CXDXmlNode;
class CXDNamedNode;
 
//===========================================================================
// Summary:
//      To use a CXDXml object, just call the constructor.
//      X D Xml
//===========================================================================

class CXDXml  
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// X D Xml, Constructs a CXDXml object.
	//		Returns A  value.
	CXDXml();
	
	//-----------------------------------------------------------------------
	// Summary:
	// C X D Xml, Destructor of class CXDXml
	// This member function is also a virtual function, you can Override it if you need,  
	//		Returns A  value.
	virtual ~CXDXml();

//////////////////////////////////////////////////////////////////////////
//	Inport Infomation from a XML file
//////////////////////////////////////////////////////////////////////////
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load, Call this function to read a specified number of bytes from the archive.
	//		Returns A Boolean value.  
	// Parameters:
	//		&strFile---&strFile, Specifies A CString type value.
//	Load XML File
	bool Load(const CString &strFile);

	BOOL Load(IStream* stream);
	BOOL Load(LPBYTE buffer, UINT size);
	BOOL Load(CFile& file);
//	BOOL Load(const CString& fileName);
	BOOL _Load(const _variant_t& value);
	BOOL LoadFromBuffer(LPBYTE lpBuffer, UINT length);
//	Load XML File Fragment
	
	//-----------------------------------------------------------------------
	// Summary:
	// Load Xml, Call this function to read a specified number of bytes from the archive.
	//		Returns A Boolean value.  
	// Parameters:
	//		&strXML---X M L, Specifies A CString type value.
	bool LoadXml(const CString &strXML);

//	Get a Node by the Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.
	CXDXmlNode GetNode(CString strNode);

//	Get a NodeList by the Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node List, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.
	CXDXmlNode GetNodeList(CString strNode);

//	Get the value of the node by Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	//		Returns A _variant_t value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.
	_variant_t GetNodeVal(CString strNode);

//	Get the node text by Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Text, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.  
	//		strDef---strDef, Specifies A CString type value.
	CString GetNodeText(CString strNode, CString strDef = _T(""));

//	Get a Node by the name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Find Parameter Node, Searches the list sequentially to find the first CObject pointer matching the specified CObject pointer. 
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		bstrParentEle---Parent Ele, Specifies a _bstr_t bstrParentEle object.  
	//		strParamName---Parameter Name, Specifies A CString type value.
	CXDXmlNode FindParamNode(_bstr_t bstrParentEle, CString strParamName);

//////////////////////////////////////////////////////////////////////////
//	Export Information to a XML file
//////////////////////////////////////////////////////////////////////////
//	Create Root
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Root, You construct a CXDXml object in two steps. First call the constructor, then call Create, which creates the object.
	//		Returns A Boolean value.  
	// Parameters:
	//		strRoot---strRoot, Specifies A CString type value.
	bool CreateRoot(CString strRoot);
 
	//-----------------------------------------------------------------------
	// Summary:
	// Add Xml Fragment, Adds an object to the specify list.
	//		Returns A Boolean value.  
	// Parameters:
	//		bstrXml---bstrXml, Specifies a _bstr_t bstrXml object.
	bool AddXmlFragment(_bstr_t bstrXml);
 
	//-----------------------------------------------------------------------
	// Summary:
	// Add Child Element, Adds an object to the specify list.
	//		Returns A Boolean value.  
	// Parameters:
	//		strElement---strElement, Specifies A CString type value.
	bool AddChildElement(CString strElement);
 
	//-----------------------------------------------------------------------
	// Summary:
	// Add Attribute, Adds an object to the specify list.
	//		Returns A Boolean value.  
	// Parameters:
	//		strName---strName, Specifies A CString type value.  
	//		strValue---strValue, Specifies A CString type value.
	bool AddAttribute(CString strName, CString strValue);
 
	//-----------------------------------------------------------------------
	// Summary:
	// Add Child Text Node, Adds an object to the specify list.
	//		Returns A Boolean value.  
	// Parameters:
	//		strNodeName---Node Name, Specifies A CString type value.  
	//		strValue---strValue, Specifies A CString type value.
	bool AddChildTextNode(CString strNodeName, CString strValue);
 
	//-----------------------------------------------------------------------
	// Summary:
	// Back To Parent, None Description.
	//		Returns A Boolean value.
	bool BackToParent();

public:	
//	Save XML File
	
	//-----------------------------------------------------------------------
	// Summary:
	// Save Xml, Call this function to save the specify data to a file.
	//		Returns A Boolean value.  
	// Parameters:
	//		&strFile---&strFile, Specifies A CString type value.
	bool SaveXml(const CString &strFile);

//	Get Document point
	MSXML2::IXMLDOMDocumentPtr GetDocumentPtr();

//	Get XML
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Xml, Returns the specified value.
	//		Returns A _bstr_t value.
	_bstr_t GetXml();

protected:
//	have init the XML
 
	// Has Initial, Specify A Boolean value.  
	bool m_bHasInit;
//	a point for the elemnent
	MSXML2::IXMLDOMElementPtr	m_spDOMElement;
//	a point for the document
	MSXML2::IXMLDOMDocumentPtr	m_spDOMDocument;

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Document, You construct a CXDXml object in two steps. First call the constructor, then call Create, which creates the object.
	//		Returns A Boolean value.
	bool CreateDocument();

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	//		Returns A Boolean value.  
	// Parameters:
	//		bstrNode---bstrNode, Specifies a _bstr_t bstrNode object.  
	//		vtVal---vtVal, Specifies a _variant_t& vtVal object.
	bool GetNodeVal(_bstr_t bstrNode, _variant_t& vtVal);

public:
	class CStack
	{
	public:
		CStack() { m_nCount = 0; }
		~CStack() { }
		
		bool Push(MSXML2::IXMLDOMElementPtr item)
		{
			if(m_nCount >= _MAX_ARRAY)
				return false;
			m_spaDOMElements[m_nCount] = item;
			m_nCount++;
			return true;
		}
		bool Pop(MSXML2::IXMLDOMElementPtr& item)
		{
			if(m_nCount < 1)
				return false;
			m_nCount--;
			item = m_spaDOMElements[m_nCount];
			return true;
		}
		bool CanPop()
		{
			if(m_nCount < 1)
				return false;
			return true;
		}
		bool CanPush()
		{
			if(m_nCount >= _MAX_ARRAY)
				return false;
			return true;
		}
		
		int m_nCount;
		MSXML2::IXMLDOMElementPtr m_spaDOMElements[_MAX_ARRAY];
	};

protected:
	//	a stack to save the element
 
	// D O M Element, This member specify CStack object.  
	CStack m_stackDOMElement;

};

 
//===========================================================================
// Summary:
//      To use a CXDXmlNode object, just call the constructor.
//      X D Xml Node
//===========================================================================

class CXDXmlNode
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// X D Xml Node, Constructs a CXDXmlNode object.
	//		Returns A  value.
	CXDXmlNode();
//	Set the Node
	void SetNode(MSXML2::IXMLDOMNodePtr node);
//	Set the Node List
	void SetNodeList(MSXML2::IXMLDOMNodeListPtr list);
//	Set value
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Parameter Value, Sets a specify value to current class CXDXmlNode
	//		Returns A Boolean value.  
	// Parameters:
	//		vtVal---vtVal, Specifies a _variant_t vtVal object.
	bool SetParamVal(_variant_t vtVal);

//	Get Current Attribute
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Named Node, Returns the specified value.
	//		Returns A CXDNamedNode value.
	CXDNamedNode GetNamedNode();
//	Get Current Attribute by Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Named Node, Returns the specified value.
	//		Returns A CXDNamedNode value.  
	// Parameters:
	//		bstrNode---bstrNode, Specifies a _bstr_t bstrNode object.
	CXDNamedNode GetNamedNode(_bstr_t bstrNode);

//	Get Current First Child Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get First Child Node, Returns the specified value.
	//		Returns A CXDXmlNode value.
	CXDXmlNode GetFirstChildNode();
//	Get Current First Child Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Next Child Node, Returns the specified value.
	//		Returns A CXDXmlNode value.
	CXDXmlNode GetNextChildNode();

//	Get All Child Nodes
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Child Nodes, Returns the specified value.
	//		Returns A CXDXmlNode value.
	CXDXmlNode GetChildNodes();
	
//	Get Current Node by index
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Item Node, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		&nIndex---&nIndex, Specifies A integer value.
	CXDXmlNode GetItemNode(const int &nIndex);
//	Get Current Node by Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.
	CXDXmlNode GetNode(CString strNode);
//	Get Current NodeList by Node name
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node List, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		strNode---strNode, Specifies A CString type value.
	CXDXmlNode GetNodeList(CString strNode);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		&strNodeText---Node Text, Specifies A CString type value.
	void GetNodeValue(const CString &strNode, CString &strNodeText);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		&nNodeInt---Node Int, Specifies A integer value.
	void GetNodeValue(const CString &strNode, int &nNodeInt);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		&bNodeBool---Node Bool, Specifies A Boolean value.
	void GetNodeValue(const CString &strNode, bool &bNodeBool);

//	Get Node Value
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Text, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		strDef---strDef, Specifies A CString type value.
	CString	GetNodeText(const CString &strNode, CString strDef = _T(""));
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Int, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		nDef---nDef, Specifies A integer value.
	int	GetNodeInt(const CString &strNode, int nDef = 0);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Float, Returns the specified value.
	//		Returns a float value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		fDef---fDef, Specifies A float value.
	float GetNodeFloat(const CString &strNode, float fDef = 0.0f);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Double, Returns the specified value.
	//		Returns A double value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		dDef---dDef, Specifies a double dDef = 0.0 object.
	double GetNodeDouble(const CString &strNode, double dDef = 0.0);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Bool, Returns the specified value.
	//		Returns A Boolean value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		bDef---bDef, Specifies A Boolean value.
	bool GetNodeBool(const CString &strNode, bool bDef = false);

//	Get Node Value. ie: bool, INT....
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	//		Returns A _variant_t value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.
	_variant_t GetNodeVal(const CString &strNode);

//	Get The Next Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Next Node, Returns the specified value.
	//		Returns A Boolean value.
	bool GetNextNode();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Next Node, Returns the specified value.
	//		Returns A Boolean value.  
	// Parameters:
	//		strName---strName, Specifies A CString type value.  
	//		vtVal---vtVal, Specifies A CString type value.
	bool GetNextNode(CString& strName, CString& vtVal);

	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Xml, Returns the specified value.
	//		Returns a CString type value.
	CString	GetXml();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Text, Returns the specified value.
	//		Returns a CString type value.
	CString	GetText();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Name, Returns the specified value.
	//		Returns a CString type value.
	CString GetNodeName();
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Name, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		&nItem---&nItem, Specifies A integer value.
	CString GetNodeName(const int &nItem);

//	Both the Node and NodeList are NULL
	
	//-----------------------------------------------------------------------
	// Summary:
	// Is Empty, Determines if the given value is correct or exist.
	//		Returns A Boolean value.
	bool IsEmpty();
//	Get the Size of NodeList
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node List Size, Returns the specified value.
	//		Returns a int type value.
	int GetNodeListSize();

protected:
//	A point for the Mode
	MSXML2::IXMLDOMNodePtr		m_spDOMNode;
//	A point for the ModeList
	MSXML2::IXMLDOMNodeListPtr  m_spDOMNodeList;

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	//		Returns A Boolean value.  
	// Parameters:
	//		bstrNode---bstrNode, Specifies a _bstr_t bstrNode object.  
	//		vtVal---vtVal, Specifies a _variant_t& vtVal object.
	bool GetNodeVal(_bstr_t bstrNode, _variant_t& vtVal);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Create Document, You construct a CXDXmlNode object in two steps. First call the constructor, then call Create, which creates the object.
	//		Returns A Boolean value.
	bool CreateDocument();
};

 
//===========================================================================
// Summary:
//      To use a CXDNamedNode object, just call the constructor.
//      X D Named Node
//===========================================================================

class CXDNamedNode
{
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	// X D Named Node, Constructs a CXDNamedNode object.
	//		Returns A  value.
	CXDNamedNode();
//	Set Attribute Node
	void SetNode(MSXML2::IXMLDOMNamedNodeMapPtr namedNode);

//	Get First Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get First Node, Returns the specified value.
	//		Returns A CXDXmlNode value.
	CXDXmlNode GetFirstNode();
//	Get Next Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Next Node, Returns the specified value.
	//		Returns A CXDXmlNode value.
	CXDXmlNode GetNextNode();

//	Get the Size
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Size, Returns the specified value.
	//		Returns a int type value.
	int GetSize();
//	Get Item Node
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Item Node, Returns the specified value.
	//		Returns A CXDXmlNode value.  
	// Parameters:
	//		i---Specifies A integer value.
	CXDXmlNode GetItemNode(int i);

//	Get Node Text
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Text, Returns the specified value.
	//		Returns a CString type value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		strDef---strDef, Specifies A CString type value.
	CString	GetNodeText(const CString &strNode, CString strDef = _T(""));
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Int, Returns the specified value.
	//		Returns a int type value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		nDef---nDef, Specifies A integer value.
	int	GetNodeInt(const CString &strNode, int nDef = 0);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Float, Returns the specified value.
	//		Returns a float value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		fDef---fDef, Specifies A float value.
	float GetNodeFloat(const CString &strNode, float fDef = 0.0f);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Double, Returns the specified value.
	//		Returns A double value.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		dDef---dDef, Specifies a double dDef = 0.0 object.
	double GetNodeDouble(const CString &strNode, double dDef = 0.0);
//	Set Node Text
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Node Text, Sets a specify value to current class CXDNamedNode
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&strNode---&strNode, Specifies A CString type value.  
	//		&strVal---&strVal, Specifies A CString type value.
	BOOL SetNodeText(const CString &strNode, const CString &strVal);

private:
//	A point for the Mode
	MSXML2::IXMLDOMNamedNodeMapPtr m_spNamedNodeMap;

protected:
	
	//-----------------------------------------------------------------------
	// Summary:
	// Get Node Value, Returns the specified value.
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&bstrNode---&bstrNode, Specifies a const _bstr_t &bstrNode object.  
	//		&vtVal---&vtVal, Specifies a _variant_t &vtVal object.
	BOOL GetNodeVal(const _bstr_t &bstrNode, _variant_t &vtVal);
	
	//-----------------------------------------------------------------------
	// Summary:
	// Set Node Value, Sets a specify value to current class CXDNamedNode
	//		Returns TRUE on success; FALSE otherwise.  
	// Parameters:
	//		&bstrNode---&bstrNode, Specifies a const _bstr_t &bstrNode object.  
	//		&vtVal---&vtVal, Specifies a const _bstr_t &vtVal object.
	BOOL SetNodeVal(const _bstr_t &bstrNode, const _bstr_t &vtVal);
};

#endif // !defined(AFX_HOKXML_H__A77B9829_2B3B_414F_8A0A_C60883CCB2DE__INCLUDED_)
