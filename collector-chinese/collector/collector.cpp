
// collector.cpp : ����Ӧ�ó��������Ϊ��
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


// CcollectorApp ����

CcollectorApp::CcollectorApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CcollectorApp ����

CcollectorApp theApp;


// CcollectorApp ��ʼ��

BOOL CcollectorApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�


	/*
	//locale loc("chs");//���塰�������á�Ϊ���ķ�ʽ  
					  //wchar_t str[]=L"�й�";  

	setlocale(LC_ALL, ".950");
	cout << _T("���") << endl;
	AfxMessageBox(_T("���"));

	// 936;  gbk2312
	setlocale(LC_ALL, ".936");  //BIG
	cout << _T("���") << endl;
	AfxMessageBox(_T("���"));
	*/

	HANDLE m_hMutex = ::CreateMutex(NULL, TRUE, _T("collector"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("collector is running already !"));//�����Ի���ȷ�ϲ������еڶ���ʵ����
		return FALSE;
	}

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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


	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


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
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}



int CcollectorApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
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
