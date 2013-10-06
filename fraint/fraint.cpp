
// fraint.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "fraint.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef SHAPETYPE_RECTANGLE
#define SHAPETYPE_RECTANGLE 0
#endif

#ifndef SHAPETYPE CIRCLE
#define SHAPETYPE_CIRCLE 1
#endif

// CfraintApp

BEGIN_MESSAGE_MAP(CfraintApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CfraintApp::OnAppAbout)
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CfraintApp::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CfraintApp::OnShapeCircle)
	ON_COMMAND(ID_ABOUT_AA, &CfraintApp::OnHelpAbout)
END_MESSAGE_MAP()


int CfraintApp::CURRENT_SHAPE_TYPE = SHAPETYPE_RECTANGLE;

// CfraintApp construction

CfraintApp::CfraintApp()
{
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("fraint.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CfraintApp object

CfraintApp theApp;


// CfraintApp initialization

BOOL CfraintApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CfraintApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CfraintApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CfraintApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CfraintApp message handlers





void CfraintApp::OnShapeRectangle()
{
	CfraintApp::CURRENT_SHAPE_TYPE = SHAPETYPE_RECTANGLE;
	//MessageBox(0, L"Rectangle", L"Draw", 0);
}


void CfraintApp::OnShapeCircle()
{
	CfraintApp::CURRENT_SHAPE_TYPE = SHAPETYPE_CIRCLE;
	//MessageBox(0, L"Circle", L"Draw", 0);
}


void CfraintApp::OnHelpAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}