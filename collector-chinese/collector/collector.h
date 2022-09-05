
// collector.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once



#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号



#define  WM_PAGE_MSG  WM_USER+202

#include "appface.h"  
// CcollectorApp: 
// 有关此类的实现，请参阅 collector.cpp
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

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	
};

extern CcollectorApp theApp;