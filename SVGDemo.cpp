// SVGDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SVGDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SVGDemoDoc.h"
#include "SVGDemoView.h"
#include "NewVisualProxy.h"
//#include "NewConvertXML.h"
#include "AppLookDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoApp

BEGIN_MESSAGE_MAP(CSVGDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CSVGDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoApp construction

CSVGDemoApp::CSVGDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	dDrawingScale = 1.0;
	m_bLoadText = TRUE;
	m_nDefHatch = 34;
	m_DefTexture = 68;
	Conversion = 0.20;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSVGDemoApp object

CSVGDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoApp initialization

BOOL CSVGDemoApp::InitInstance()
{
	// E-XD++ Library Add line.
	AfxOleInit();
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	//E-XD++ Library add lines.
	
	//E-XD++ Library add lines.
	FOInit(RUNTIME_CLASS(CNewVisualProxy));
	FOEnableXPStyle(TRUE);
	gfxData.InitGUIType(GUI_SILVER);
	gfxData.fo_bWithLinkFeature = FALSE;
	gfxData.m_strDefToolboxFile = _T("svg.dat");
#if _MSC_VER <= 1200 // MFC 6.0 or earlier
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif // MFC 6.0 or earlier

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SVGDEMTYPE,
		RUNTIME_CLASS(CSVGDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSVGDemoView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	CAppLookDlg dlg (TRUE);
	dlg.DoModal ();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSVGDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSVGDemoApp message handlers


CString CSVGDemoApp::CreateTempXML(CString strSVG)
{
// 	CNewConvertXML m_xmlRoot;
// 	CFile in;
// 	CString Decl;
// 	Decl =_T("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
// 	in.Open(strSVG,CFile::modeRead);
// 	CString strXML = strSVG.Left(strSVG.GetLength()-4) + _T("22220000.xml");
// 	if(m_xmlRoot.XMLRead(&in,_T("")))
// 	{
// 		in.Close();
// 		in.Open(strXML,CFile::modeCreate|CFile::modeWrite);
// 		in.Write(Decl,Decl.GetLength());
// 		m_xmlRoot.XMLWrite(&in,-1); // Set -1 to zero for intenting
// 		in.Close();
// 		
// 	}
// 	else
// 	{
// 		in.Close();
// 	}
// 	return strXML;
	return _T("");
}

void CSVGDemoApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	OnFileNew();
	CSVGDemoView *pView = (CSVGDemoView *)FOGetActiveView();
	if(pView != NULL)
	{
		pView->OnConvertSvgShapes();
	}
}

void CSVGDemoApp::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
