
// collector.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once



#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������



#define  WM_PAGE_MSG  WM_USER+202

#include "appface.h"  
// CcollectorApp: 
// �йش����ʵ�֣������ collector.cpp
//

#include "MyDatabase.h"

#define  WM_FRESH_LIST  WM_USER +234 

//#define  TIMEOUT  30 //seconds

class CcollectorApp : public CWinApp
{
public:
	CcollectorApp();
	BOOL  WriteLog(TCHAR *buf);

	CAppFace m_face;

	CMyDatabase   m_database;
	HWND  m_hwnd;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	
};

extern CcollectorApp theApp;