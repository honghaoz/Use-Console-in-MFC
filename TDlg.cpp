// TDlg.cpp : implementation file
//

#include "stdafx.h"
#include "T.h"
#include "TDlg.h"

// #include "iostream.h"
// #include <FSTREAM.H>
// #include<fstream>
// #include<iostream>
// using namespace std;

//////  [5/30/2013 10:07:20  by ZhangHonghao] ///////
//这段代码可以使用cout，否则只能使用printf
#ifndef __GUICON_H__
#define __GUICON_H__

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>

using namespace std;
// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;

void RedirectIOToConsole();

void RedirectIOToConsole()
{
	int hConHandle;
	HANDLE lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	
	// allocate a console for this app
	AllocConsole();
	// set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	coninfo.dwSize.Y = MAX_CONSOLE_LINES;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);
	// redirect unbuffered STDOUT to the console
	lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
	// redirect unbuffered STDIN to the console
	lStdHandle = GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "r" );
	*stdin = *fp;
	setvbuf( stdin, NULL, _IONBF, 0 );
	// redirect unbuffered STDERR to the console
	lStdHandle = GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle((INT_PTR)lStdHandle, _O_TEXT);
	fp = _fdopen( hConHandle, "w" );
	*stderr = *fp;
	setvbuf( stderr, NULL, _IONBF, 0 );
	// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
	// point to console as well
	ios::sync_with_stdio();
}

#endif 

//////  [5/30/2013 10:07:25  by ZhangHonghao] ///////

#include <io.h>
#include <fcntl.h>
	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CTDlg dialog

CTDlg::CTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTDlg, CDialog)
	//{{AFX_MSG_MAP(CTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTDlg message handlers

//////  [5/30/2013 10:05:42  by ZhangHonghao] ///////
//另一种实现cout的方法
void InitConsole()
{
	int nRet= 0;
	FILE* fp;
	AllocConsole();
	nRet= _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	fp = _fdopen(nRet, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);
}
//////  [5/30/2013 10:05:50  by ZhangHonghao] ///////

BOOL CTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

//////  [5/30/2013 10:06:37  by ZhangHonghao] ///////
//第一种方法，简单
	// 打开控件台
 	::AllocConsole();    // 打开控件台资源
     freopen("CONOUT$", "w+t", stdout);    // 申请写
	 freopen("CONIN$","r+t",stdin);  
//////  [5/30/2013 10:06:40  by ZhangHonghao] ///////

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTDlg::OnButton1() 
{
// 	// TODO: Add your control notification handler code here
// 	int FileNum = 0;
// 	CString *FilePathName;
// re://re open a file
// 	CFileDialog dlg(true,".txt","*.txt",OFN_ALLOWMULTISELECT,"Txt Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
// 	dlg.m_ofn.lpstrInitialDir = _T(".\\"); //这里就设置了对话框的默认目录
// 	dlg.m_ofn.lpstrTitle = "请选择数据：";
// 	int dialog_result;
// 	dialog_result = dlg.DoModal();
// 	
// 	if(dialog_result==IDOK) 
// 	{
// 		POSITION pos = dlg.GetStartPosition();
// 		while (pos != NULL)
// 		{
// 			FileNum++;
// 		}
// 		
// 		// 		FilePathName = new CString(FileNum);
// 		// 		FileNum = 0;
// 		// 		while (pos != NULL)
// 		// 		{
// 		// 			FilePathName[FileNum++]=dlg.GetNextPathName(pos);
// 		// 		}
// 		
// 	}
// 	else if(dialog_result==IDCANCEL)
// 	{
// 		AfxMessageBox("CANCEL");
// 
// 		return;
// 	}

	CString* FilePathName;
	int FileNum = 0;
re://re open a file
	CFileDialog dlg(true,".txt","*.txt",OFN_ALLOWMULTISELECT,"Txt Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|All Files (*.*)|*.*||");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	dlg.m_ofn.lpstrInitialDir = _T(".\\"); //这里就设置了对话框的默认目录
	dlg.m_ofn.lpstrTitle = "请选择开关刀闸参数表";
	int dialog_result;
	dialog_result = dlg.DoModal();
	if(dialog_result==IDOK) 
	{
		POSITION pos = dlg.GetStartPosition();
	//	FilePathName=dlg.GetPathName();
		while (pos != 0)
		{
			FileNum++;
			dlg.GetNextPathName(pos);
			AfxMessageBox("11");
		}
		AfxMessageBox("success");
	}
	else if(dialog_result==IDCANCEL)
	{
		AfxMessageBox("CANCEL");
		return;
	}
	
	//open failed
	if (dlg.GetPathName() == "*.txt")
	{
		AfxMessageBox("failed");
		goto re;
	}
}

void CTDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here

//测试
//  	string info("console info show.");
//      cout << info << endl;
//	printf("Asdasdasd");
	cout<<"SAd"<<endl;
	int i;
	cin>>i;
	cout<<"i="<<i<<endl;
}
