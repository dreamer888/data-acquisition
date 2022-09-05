
// collector.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "collector.h"


#include <atlstr.h>  
#include <locale.h>
#include   <iostream>  
#include "collectorDlg.h"

using   namespace   std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CcollectorApp

BEGIN_MESSAGE_MAP(CcollectorApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CcollectorApp 构造

CcollectorApp::CcollectorApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CcollectorApp 对象

CcollectorApp theApp;


// CcollectorApp 初始化

BOOL CcollectorApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。


	/*
	//locale loc("chs");//定义“区域设置”为中文方式  
					  //wchar_t str[]=L"中国";  

	setlocale(LC_ALL, ".950");
	cout << _T("你好") << endl;
	AfxMessageBox(_T("你好"));

	// 936;  gbk2312
	setlocale(LC_ALL, ".936");  //BIG
	cout << _T("你好") << endl;
	AfxMessageBox(_T("你好"));
	*/

	HANDLE m_hMutex = ::CreateMutex(NULL, TRUE, _T("collector"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("collector is running already !"));//弹出对话框确认不能运行第二个实例。
		return FALSE;
	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	//if (!AfxSocketInit())
	//{
	//	AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		//return FALSE;
//	}


	AfxEnableControlContainer();


	// Initialize OLE libraries
	if (!AfxOleInit())   //ADO  must us this  !  
	{
		AfxMessageBox(_T("Fail to  init  afx OLE  !"));
		return FALSE;
	}


	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	if (1)
	{
		TCHAR skin[10];
		GetPrivateProfileString(_T("skin"), _T("skinId"), _T("1"), skin, sizeof(skin), _T("config.ini"));
		if (_tcscmp(skin, _T("1")) == 0)
			m_face.Start(_T("facefile\\BluePinna.urf"));
		else if (_tcscmp(skin, _T("2")) == 0)
			m_face.Start(_T("facefile\\GtBase.urf"));
		else if (_tcscmp(skin, _T("3")) == 0)
			m_face.Start(_T("facefile\\GtClassic.urf"));
		else m_face.Start(NULL);
	}

	//WritePrivateProfileString(_T("skin"), _T("skinId"), _T("1"), _T("config.ini"));

	CcollectorDlg  dlg;
	m_pMainWnd = &dlg;
	//this->m_hwnd = dlg.m_hWnd;


	//m_face.SkinWindow(m_pMainWnd->m_hWnd, 0);



	//m_face.Start("facefile\\GtClassic.urf");
	//CMyDatabase::InitDataBase();
	m_database.InitDataBase();


	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



int CcollectorApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_face.IsValid())
	   m_face.Remove();
	m_database.ExitDataBase();

	return CWinApp::ExitInstance();
}




BOOL  CcollectorApp::WriteLog(TCHAR *buf)
{


	CStdioFile  m_logFile;
	TCHAR    wbuf[255];
	if (!m_logFile.Open(_T("log.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		AfxMessageBox(_T("Fail to create  log file !"));
		return FALSE;
	}
	m_logFile.SeekToEnd();


	m_logFile.WriteString(buf);
	//m_logFile.Write(_T("\r\n"), _tcslen(_T("\0\r\n\0")));
	m_logFile.WriteString(_T("\n"));


	m_logFile.Close();

	return TRUE;
}
