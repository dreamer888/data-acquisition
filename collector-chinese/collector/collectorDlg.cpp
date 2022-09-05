
// collectorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "collectorDlg.h"
#include "afxdialogex.h"

#include "util.h"


#include "Protocol.h"


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <winsock2.h>
#include <vector>

#include "shellapi.h"

#include <fstream>

#include "DeviceManager.h"
using namespace std;

/*
唤梦科技
QQ  750339960
MOBILE  18665802636
*/


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };wrot
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcollectorDlg 对话框



CcollectorDlg::CcollectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLLECTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP12);
	
	OnOpenPropertySheet();


  

}

void CcollectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	//DDX_Control(pDX, IDC_EDIT1,m_status );
	//DDX_Control(pDX, IDC_STATIC_NET_STATUS, m_netstatus);
	DDX_Control(pDX, IDC_LIST2, m_status);
}


BEGIN_MESSAGE_MAP(CcollectorDlg, CDialogEx)

	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(IDS_STRING104, OnSetting)
	ON_COMMAND(IDS_STRING105, OnControl)
	ON_COMMAND(IDS_STRING106, OnSearch)
	ON_COMMAND(IDS_STRING107, OnUpgrade)
	ON_COMMAND(IDS_STRING108, OnLog)
	ON_COMMAND(IDS_STRING109, OnSkin)
	ON_COMMAND(IDS_STRING110, OnDevice)
	ON_MESSAGE(SOCKET_MSG, OnSocketMessage)
	ON_MESSAGE(WM_PARSE_PACKAGE, OnSocketParsePacket)
	ON_MESSAGE(WM_PAGE_MSG, OnPageMessage)

	ON_MESSAGE(WM_FRESH_LIST, OnFreshList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &OnNMDblclkList1)

	ON_WM_TIMER()
END_MESSAGE_MAP()


// CcollectorDlg 消息处理程序


void CcollectorDlg::  AddToolbar()
{


	CBitmap bm;
	UINT Resource[7] = { IDB_BITMAP7,IDB_BITMAP9,IDB_BITMAP8,IDB_BITMAP11,IDB_BITMAP14 ,IDB_BITMAP19,IDB_BITMAP21};          //位图ID数组
	int i;

	m_ImageList.Create(32, 32, ILC_COLOR24 | ILC_MASK, 0, 0);                  //创建Image List
	m_ToolBar.Create(TBSTYLE_FLAT | CCS_TOP | WS_CHILD | WS_VISIBLE | WS_BORDER | CCS_ADJUSTABLE, CRect(0, 0, 0, 0), this, IDR_TOOLBAR1);                    //创建Toolbar Control
	m_ToolBar.SetBitmapSize(CSize(32, 32));

	for (i = 0; i<7; i++)
	{
		bm.LoadBitmap(Resource[i]);
		m_ImageList.Add(&bm, (CBitmap *)NULL);
		bm.Detach();
	}

	m_ToolBar.SetImageList(&m_ImageList);

	TBBUTTON Buttons[7];                                                      //定义TBBUTTON结构体数组
	CString str;

	for (i = 0; i<7; i++)
	{
		str.LoadString(IDS_STRING104 + i);                                                //IDS_FILE是在String Table中添加的String
		Buttons[i].iString = m_ToolBar.AddStrings(str);
		
		Buttons[i].dwData = 0;
		Buttons[i].fsState = TBSTATE_ENABLED;
		Buttons[i].fsStyle = TBSTYLE_BUTTON;
		Buttons[i].iBitmap = i;
		Buttons[i].idCommand = IDS_STRING104 + i;   //按钮命令响应
	}
	m_ToolBar.AddButtons(7, Buttons);
	m_ToolBar.AutoSize();

	m_ToolBar.ShowWindow(SW_SHOW);

}

BOOL CcollectorDlg::LoadListItem()
{

	//CString strHead[] = { _T("网络号"),_T("网络地址"),_T("事件"),_T("步长"),_T("时间") };
	//m_listctrl.InsertColumn(6, strHead, DT_CENTER, NULL);
 
	m_listctrl.SetSortable(TRUE);
	//m_listctrl.SetEditable();
	 
	 
		m_listctrl.InsertColumn(0, _T("名稱"));
		m_listctrl.InsertColumn(1, _T("IP")); 
		m_listctrl.InsertColumn(2, _T("Net id")); //添加列名
		m_listctrl.InsertColumn(3, _T("Net addr"));
		m_listctrl.InsertColumn(4, _T("狀態"));
		m_listctrl.InsertColumn(5, _T("時間"));
		m_listctrl.InsertColumn(6, _T("描述"));

	m_listctrl.SetColumnWidth(0, 150); //设置列宽
	m_listctrl.SetColumnWidth(1, 150);
	m_listctrl.SetColumnWidth(2, 100);
	m_listctrl.SetColumnWidth(3, 100);
	m_listctrl.SetColumnWidth(4, 100);
	m_listctrl.SetColumnWidth(5, 200);
	m_listctrl.SetColumnWidth(6, 300);
	


	m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;

}

void   CcollectorDlg::InitControlPosition()
{
	CRect  rect;

	if (1)
	{
		if (m_ToolBar)
		{
			m_ToolBar.GetClientRect(&rect);
			int height = rect.Height();
			int width = 300;// rect.Width();
			//int bottom = rect.bottom;
			//rect.bottom = rect.top + 30;
			GetClientRect(&rect);
			rect.bottom = rect.top + height;
			rect.right = rect.left + width;

			m_ToolBar.MoveWindow(&rect);
		}
	}
	else
	{
		if (m_ToolBar)
		{
			m_ToolBar.GetClientRect(&rect);
			int height = rect.Height();
			int width = rect.Width() ;
			//int bottom = rect.bottom;
			//rect.bottom = rect.top + 30;
			GetClientRect(&rect);
			rect.bottom = rect.top + height;
			rect.right = rect.right -100;

			m_ToolBar.MoveWindow(&rect);
		}

	}
	if (m_listctrl)
	{
		GetClientRect(&rect);
		rect.top += 60;
		rect.bottom -= 110;
		//rect.bottom = rect.top + 30;
		m_listctrl.MoveWindow(&rect);
	}

	if(0)
	if (m_status)
	{
		m_status.GetClientRect(&rect);

		int height = rect.Height();
		//int width = rect.Width();

		GetClientRect(&rect);

		rect.bottom -= 60;
		rect.top = rect.bottom - height;
		m_status.MoveWindow(&rect);
	}


	if (1)
	{
		if (m_status)
		{
			GetClientRect(&rect);

			rect.top = rect.bottom - 89- 35;
			//rect.bottom = rect.top + 30;
			m_status.MoveWindow(&rect);
		}
	}
	else
	{
		if (m_status)
		{
			GetClientRect(&rect);
			rect.top = rect.top + 80;
			rect.left = rect.right - 200;

			m_status.MoveWindow(&rect);
		}

	}
}

BOOL CcollectorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	 

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	ShowWindow(SW_SHOWMAXIMIZED);
	AddToolbar();
	LoadListItem();
	RefreshList();


	m_timer = GetPrivateProfileInt(_T("device"), _T("timer"), 20, _T("config.ini"));
	this->SetTimer(1, m_timer*1000,0);
	//GetPrivateProfileString(_T("device"), _T("timer"), _T(""), para, sizeof(para), _T("config.ini"));

	InitControlPosition();

	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	app->m_hwnd = this->m_hWnd;

	
	unsigned short port = GetPrivateProfileInt(_T("system"), _T("port"), 8000, CONFIG);
	if (0)
	{
		//1.加载套接字库
		if (!m_iocpModel.LoadSocketLib())
		{
			AfxMessageBox(_T("Fail to load socket lib !"));
			WriteLog(_T("Fail to load socket lib "));
			return FALSE;
		}
		m_iocpModel.SetHwnd(this->m_hWnd);
		this->m_iocpModel.Start();

	}
	
	else
	{
		m_serverIOCP.m_hWnd = this->m_hWnd;
		m_serverIOCP.StartServer(8000);
	}
	
	CString cs;
	//TCHAR buf[255];
	char str[255];
	//_itot(, buf, 10);
	//cs = _T("tcp server is started ! \r\n ip = 127.0.0.1  port = ");
 

	_SYSTEMTIME st;
	GetLocalTime(&st);// / GetLocalTime();
					   //t = GetCurrentTime();  //UTC 1974 
	CString logStr ;
	logStr.Format(_T("%04d-%02d-%02d %02d:%02d:%02d   "), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	m_status.AddString(_T("  "));
	m_status.AddString(_T("  "));
	cs.Format(_T("tcp server is started !   ip = %s  port = %d"), m_serverIOCP.GetLocalIp1(), port);
	logStr  += cs;
	m_status.AddString(logStr);


	//memset(str , 0 , sizeof(str));
	//WCharToMByte(logStr, str,  sizeof(str));
	WriteLog(logStr.GetBuffer());

	m_tickCount = ::GetTickCount();
	
	//CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	TCHAR skin[10];
	GetPrivateProfileString(_T("skin"), _T("skinId"), _T("1"), skin, sizeof(skin), _T("config.ini"));
	m_skin = _ttoi(skin);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CcollectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if ((nID & 0xFFF0) == IDS_STRING104)
	{
		AfxMessageBox(_T("关于深圳市唤梦科技"));
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CcollectorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CcollectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcollectorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CRect  rect;
	//GetClientRect(&rect);

	
		if (m_ToolBar)
		{
			m_ToolBar.GetClientRect(&rect);
			int height = rect.Height();
			int width = 100;// rect.Width();
			//int bottom = rect.bottom;
			//rect.bottom = rect.top + 30;
			GetClientRect(&rect);
			rect.bottom = rect.top + height;
			rect.right = rect.left + width;

			m_ToolBar.MoveWindow(&rect);

			//CEdit * p = (CEdit *)GetDlgItem(IDC_EDIT1);
			

			//rect.bottom = rect.top + height;
			rect.left  = rect.left + 500;
			rect.right = rect.left + 90;

			//p->MoveWindow(&rect);
			//p->ShowWindow(true);
			//p->Invalidate();
		}
	
	

	if (m_listctrl)
	{
		GetClientRect(&rect);
		rect.top += 60;
		rect.bottom -= 70+30+ 10;
		//rect.bottom = rect.top + 30;
		m_listctrl.MoveWindow(&rect);
	}

	
	
		if (m_status)
		{
			GetClientRect(&rect);

			rect.top = rect.bottom - 89- 35;
			//rect.bottom = rect.top + 30;
			m_status.MoveWindow(&rect);
		}
	
	
	
	// TODO: 在此处添加消息处理程序代码
}

void CcollectorDlg::OnOpenPropertySheet()
{
	m_psheet = new  CMyPropertySheet();// (_T("setting and control"));
	m_psheet->AddPage(&m_PageSetting);
	m_psheet->AddPage(&m_PageControl);
	m_psheet->AddPage(&m_PageSearch);
	m_psheet->AddPage(&m_PageUpgrade);
	
	//m_psheet->m_psh.dwFlags |= PSH_NOAPPLYNOW;
	
}


void CcollectorDlg::OnSetting()
{

	//AfxMessageBox(_T("setting"));

	m_psheet->m_index = 0;
	m_psheet->m_pHwnd = this->m_hWnd;
	m_psheet->DoModal();
	
}


void CcollectorDlg::OnControl()
{

	//AfxMessageBox(_T("setting"));


	m_psheet->m_index = 1;
	m_psheet->m_pHwnd = this->m_hWnd;
	m_psheet->DoModal();

}


void CcollectorDlg::OnSearch()
{

	//AfxMessageBox(_T("setting"));


	m_psheet->m_index = 2;
	m_psheet->m_pHwnd = this->m_hWnd;
	m_psheet->DoModal();

}


void CcollectorDlg::OnUpgrade()
{

	//AfxMessageBox(_T("setting"));


	m_psheet->m_index = 3;
	m_psheet->m_pHwnd = this->m_hWnd;
	m_psheet->DoModal();

}


void CcollectorDlg::OnLog()
{

	ShellExecute(NULL, _T("open"), _T("log.txt"), NULL, NULL, SW_SHOW);
 

}


void CcollectorDlg::OnSkin()
{
	TCHAR skinId[10];
	m_skin = (m_skin + 1) % 4;

	wsprintf(skinId, _T("%d") , m_skin);



	WritePrivateProfileString(_T("skin"), _T("skinId"), skinId, CONFIG);
	
	//GetPrivateProfileString(_T("skin"), _T("skinId"), _T("1"), skinId, sizeof(skinId), _T("config.ini"));

	CcollectorApp *app = (CcollectorApp *)AfxGetApp();
	if (m_skin == 1)
		app->m_face.Start(_T("facefile\\BluePinna.urf"));
	else	if (m_skin == 2)
		app->m_face.Start(_T("facefile\\GtBase.urf"));
	else if (m_skin == 3)
		app->m_face.Start(_T("facefile\\GtClassic.urf"));
	else 	if (m_skin == 0)
		;// app->m_face.Start(NULL);

	//app->m_face.Start(_T("facefile\\BluePinna.urf"));
}


void CcollectorDlg::OnDevice()
{
	CDeviceManager  deviceDlg; 
	deviceDlg.DoModal();


}

BOOL CcollectorDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_psheet)
	{
		delete m_psheet;
		m_psheet = NULL;
	}


	_SYSTEMTIME st;
	GetLocalTime(&st);// /  		   //t = GetCurrentTime();  //UTC 1974 
 
	CString cs; 
	cs.Format (_T("%04d-%02d-%02d %02d:%02d:%02d   process is destroyed! ") , st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	WriteLog(cs.GetBuffer());

	 

	return CDialogEx::DestroyWindow();
}


TCHAR eventArray[5][15] = { _T("start") ,_T("stop"), _T("up") ,_T("down") ,_T("cut") };

LRESULT  CcollectorDlg:: OnSocketMessage(WPARAM wParam, LPARAM lParam)
{
	char*   buf  = (char*)lParam;

	if (buf == NULL  ||  strlen(buf)==0 )   return 0;

	if (0 == wParam)
	{
		TCHAR wbuf[1024];

		_SYSTEMTIME st;
		GetLocalTime(&st);// / GetLocalTime();
						  //t = GetCurrentTime();  //UTC 1974 
		CString cs;
		cs.Format(_T("%04d-%02d-%02d %02d:%02d:%02d   "), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		MByteToWChar((LPCSTR)buf, wbuf, sizeof(wbuf));

		cs += wbuf;
		this->m_status.AddString(cs);

		WriteLog(cs.GetBuffer());

	}
	else if (1 == wParam)
	{
		char * source = (char*)lParam;
		const char *delimeter = ",";
		char *p;
		WCHAR wbuf[1024];
		int i = 0;
		p = strtok(source, delimeter);

		MByteToWChar(p, wbuf, sizeof(wbuf));
		int n = m_listctrl.InsertItem(0, wbuf);
		i++;
		while (p)
		{
			
			p = strtok(NULL, delimeter);
			if (!p || i >4)  break;
			MByteToWChar(p, wbuf, sizeof(wbuf));
			m_listctrl.SetItemText(n, i, wbuf);


			if (3==i  && !strcmp(p,"stop"))
			{

				m_listctrl.SetItemBkColor(n, -1, ::GetSysColor(COLOR_INFOBK));
				m_listctrl.SetItemTextColor(n, -1, RGB(255, 0, 0));

				m_listctrl.SetItemBkColor(n, 3, RGB(255, 0, 0));
				m_listctrl.SetItemTextColor(n, 3, RGB(255, 255, 255));

			}
			i++;

		}
		
		_SYSTEMTIME st;
		GetSystemTime(&st);// / GetLocalTime();
				   //t = GetCurrentTime();  //UTC 1974 
		CString cs;


		cs.Format(_T("%04d-%02d-%02d %02d:%02d:%02d   ") , st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		m_listctrl.SetItemText(n, i, cs);

	}
	return 0;
}




BOOL  CcollectorDlg::WriteLog(TCHAR *buf)
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

BOOL  CcollectorDlg::WriteLog1(char *buf)
{


	CStdioFile  m_logFile;
	TCHAR    wbuf[255];
	if (!m_logFile.Open(_T("log.txt"), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate))
	{
		AfxMessageBox(_T("Fail to create  log file !"));
		return FALSE ;
	}
	m_logFile.SeekToEnd();

	MByteToWChar((LPCSTR)buf, wbuf, sizeof(wbuf));
	m_logFile.WriteString(wbuf);
	
	m_logFile.WriteString(_T("\n"));
	
	 
	m_logFile.Close();

	return TRUE;
}
LRESULT  CcollectorDlg::OnSocketParsePacket(WPARAM wParam, LPARAM lParam)
{

	TagIpPacketStruct  * ipPack = (TagIpPacketStruct*)lParam;

	TagPacketStruct * pack = (TagPacketStruct*)&ipPack->pack;

	if (pack->cmmd == CMMD_CONTROL_UPGRADE)
	{

		struct TagUpgradeResDataStruct
		{
			unsigned short  netId;
			unsigned short   netAddr;
			char  fileName[30]; // 不足30的 空余地方填充0

		};

		TagUpgradeResDataStruct*  dataPack = (TagUpgradeResDataStruct*)pack->data;
		char * ip = ipPack->ip;
	 
		char  msg[512]; 
		sprintf(msg, "%s id=%04x addr=%04x name=%s transfered !", ip, ntohs(dataPack->netId), ntohs(dataPack->netAddr) , dataPack->fileName);
		OnSocketMessage(0, (LPARAM)msg);
	
		return  0 ; 

		/*   test data  :
		sample:

		起始两个字节 0xAA 0xBB

		cmmd = 0x0001
		serialNo = 0x0006
		dataLength =0x0022  //34

		data指向一个结构体 TagUpgradeResDataStruct， 赋值如下 ：

		netId=0x1001
		netAddr=0x2002
		fileName[30]="system"   //0x73 0x79 0x73  0x74 0x65  0x6d     0x0000.......

		checkSum = 0x0000 //这里可以任意写一个2字节的校验码
		该完整的数据包是
		0xaa 0xbb 0x0001 0x0006 0x0022 0x1001 0x2002 0x73 0x79 0x73  0x74 0x65  0x6d  ....填充24个  0x0000.....       校验码 0x0000


		 
		去掉前缀0x 后 拷贝到串口调试助手，按十六进制 发送 即可
		aa bb 0001 0006  0022 1001 2002 73 79 73  74 65  6d 0000.... 0000


		aabb0001000600221001200273797374656d0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

		*/
	}//if (pack->cmmd == CMMD_CONTROL_UPGRADE)


	
	
	else if (pack->cmmd == CMMD_NORMAL_DATA)
	{


		CSocketOverlap* pSocketOlp = NULL;
		if (true)
		{

			POSITION pos = m_serverIOCP.m_lstSocketOlp.GetHeadPosition();
			while (pos)
			{
				pSocketOlp = m_serverIOCP.m_lstSocketOlp.GetNext(pos);
				if (pSocketOlp)
				{
					if (strcmp(inet_ntoa(pSocketOlp->m_ClientAddress.sin_addr), ipPack->ip) == 0)
					{

						unsigned  short  start = htons(0xaabb);
						unsigned short  cmmd = htons(pack->cmmd);
						unsigned short  serialNo = htons(pack->serialNo);
						unsigned short   dataLen = htons(pack->dataLength);

						unsigned short netId = *(unsigned short*)pack->data;
						unsigned short netAddr = *(unsigned short*)(pack->data + 2);

						unsigned short event = *(unsigned short*)(pack->data + 4);
						if (event > 9)  return 0;

						unsigned short  checkSum = 0;

						char  respondBuffer[14];

						char  * p = (char*)respondBuffer;
						*(unsigned short*)p = start; p += 2;
						*(unsigned short*)p = cmmd; p += 2;
						*(unsigned short*)p = serialNo; p += 2;
						*(unsigned short*)p = dataLen; p += 2;
						*(unsigned short*)p = netId; p += 2;
						*(unsigned short*)p = netAddr; p += 2;
						checkSum = pSocketOlp->m_cp.CheckSum(p + 2, 10);
						*(unsigned short*)p = htons(checkSum); //p += 2;
						m_serverIOCP.SendData((char*)respondBuffer, 14);  //回传数据
						break;
					}
				}
			}//while



		}//if (true)  //if (pcs->checkIp)

		
		


		TagClientDataStruct cd;
		TagClientDataStruct *dataPack = &cd; //(TagClientDataStruct *)pack->data;

		char * ip = ipPack->ip;
		TCHAR wbuf_ip[256];
		CString cs, netId, netAddress, event, steps, employeeNo, processNo, modelNo, dtime;
		char temp[255];

		//_SYSTEMTIME st;
		//GetLocalTime(&st);//GetSystemTime

/*
		if (this->m_bUseTimeInterval)
		{
			if (::GetTickCount() - m_tickCount >= this->m_timeInterval * 60000)
			{

				m_listctrl.DeleteAllItems();
				m_listctrl.Invalidate();
				m_tickCount = ::GetTickCount();
			}
		}
		else
		{
			int c = m_listctrl.GetItemCount();
			if (c >= m_recordCount)
			{

				m_listctrl.DeleteAllItems();
				m_listctrl.Invalidate();

			}
		}

*/

		MByteToWChar((LPCSTR)ip, wbuf_ip, sizeof(wbuf_ip));

	//	int n = m_listctrl.InsertItem(0, wbuf_ip);


		dataPack->netId = *(unsigned short*)pack->data;
		netId.Format(_T("0x%04x"), ntohs(dataPack->netId));
		//m_listctrl.SetItemText(n, 1, netId);

		dataPack->netAddr = *(unsigned short*)(pack->data + 2);
		netAddress.Format(_T("0x%04x"), ntohs(dataPack->netAddr));
		//m_listctrl.SetItemText(n, 2, netAddress);

		dataPack->event = *(unsigned short*)(pack->data + 4);
		event.Format(_T("%s"), eventArray[ntohs(dataPack->event)]);
		//cs.Format(_T("%d"),  ntohs(dataPack->event) );
		//m_listctrl.SetItemText(n, 3, event);


/*
		if (ntohs(dataPack->event) == 1)
		{
			m_listctrl.SetItemBkColor(n, 3, RGB(255, 0, 0));
			m_listctrl.SetItemTextColor(n, 3, RGB(255, 255, 255));
		}
		*/

		memcpy(dataPack->time, (pack->data + 6), 19);
		memset(temp, 0, sizeof(temp));
		memcpy(temp, dataPack->time, sizeof(dataPack->time));
		dtime = temp;
		//m_listctrl.SetItemText(n, 8, dtime);


		dataPack->steps = *(unsigned short*)(pack->data + 25);
		steps.Format(_T("%d"), ntohs(dataPack->steps));
		//m_listctrl.SetItemText(n, 4, steps);

		memcpy(dataPack->empyoyeeNo, pack->data + 27, 10);
		memset(temp, 0, sizeof(temp));
		memcpy(temp, dataPack->empyoyeeNo, sizeof(dataPack->empyoyeeNo));
		employeeNo = temp;
		//m_listctrl.SetItemText(n, 5, employeeNo);

		memcpy(dataPack->processNo, pack->data + 37, 24);
		memset(temp, 0, sizeof(temp));
		memcpy(temp, dataPack->processNo, sizeof(dataPack->processNo));
		processNo = temp;
		//m_listctrl.SetItemText(n, 6, processNo);

		memcpy(dataPack->modelNo, pack->data + 61, 8);
		memset(temp, 0, sizeof(temp));
		memcpy(temp, dataPack->modelNo, sizeof(dataPack->modelNo));
		modelNo = temp;
		//m_listctrl.SetItemText(n, 7, modelNo);

		try
		{
			_variant_t RecordsAffected;
			int nCount = 0;
			//		CString strTemp = _T("");
			TCHAR tszSQL[512];
			_RecordsetPtr pRecordset;
			CcollectorApp *app = (CcollectorApp *)AfxGetApp();

			HRESULT hr = pRecordset.CreateInstance(_T("ADODB.Recordset"));
			if (!SUCCEEDED(hr))
			{
				WriteLog(_T("ADO Recordset - CreateInstance failed."));

				return  -1;
			}

			//_stscanf(tszStartTime + 1, _T("%d-%d-%d %d:%d:%d"), &year, &mon, &day, &hour, &min, &sec);
			//tmStart = CTime(year, mon, day, hour, min, sec);

			CString strDateTime;
			strDateTime.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)dtime);



			//if(pApp->m_pRecordset->State) pApp->m_pRecordset->Close();
			// table_id  自动生成的no
			_stprintf(tszSQL, _T("INSERT INTO table_log ( event_id,pan_id,zigbee_address,ip,steps,employee_no,process_no,model_no,create_time) VALUES (%d,%0x, %0x ,\'%s\',%d ,\'%s\',\'%s\',\'%s\',%s )"),
				ntohs(dataPack->event), ntohs(dataPack->netId), ntohs(dataPack->netAddr), wbuf_ip, ntohs(dataPack->steps), employeeNo, processNo, modelNo, strDateTime);

			hr = app->m_database.m_pConnection->Execute((_bstr_t)tszSQL, &RecordsAffected, adCmdText);
			if (!SUCCEEDED(hr))
			{
				WriteLog(_T("fail to excute sql."));
				if (pRecordset->State) pRecordset->Close();
				return -137;
			}

		}
		catch (_com_error e)
		{
			CString strErrorMsg = _T("");
			strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
			TRACE(strErrorMsg);
			WriteLog(strErrorMsg.GetBuffer());
			return  -1;
		}

		return  0;

	}//else if (pack->cmmd == CMMD_NORMAL_DATA)



	else if (pack->cmmd == CMMD_HEART_BEAT)
	{


		CSocketOverlap* pSocketOlp = NULL;
	
		TagClientDataStruct cd;
		TagClientDataStruct *dataPack = &cd; //(TagClientDataStruct *)pack->data;

		char * ip = ipPack->ip;
		TCHAR wbuf_ip[256];
		CString cs, netId, netAddress, dtime;
		char temp[255];

		

		MByteToWChar((LPCSTR)ip, wbuf_ip, sizeof(wbuf_ip));

		//	int n = m_listctrl.InsertItem(0, wbuf_ip);


		dataPack->netId = *(unsigned short*)pack->data;
		netId.Format(_T("0x%04x"), ntohs(dataPack->netId));
		//m_listctrl.SetItemText(n, 1, netId);

		dataPack->netAddr = *(unsigned short*)(pack->data + 2);
		netAddress.Format(_T("0x%04x"), ntohs(dataPack->netAddr));
		//m_listctrl.SetItemText(n, 2, netAddress);
 


		/*
		if (ntohs(dataPack->event) == 1)
		{
		m_listctrl.SetItemBkColor(n, 3, RGB(255, 0, 0));
		m_listctrl.SetItemTextColor(n, 3, RGB(255, 255, 255));
		}
		*/

		memcpy(dataPack->time, (pack->data + 4), 19);
		memset(temp, 0, sizeof(temp));
		memcpy(temp, dataPack->time, sizeof(dataPack->time));
		dtime = temp;
		//m_listctrl.SetItemText(n, 8, dtime);



		try
		{
			_variant_t RecordsAffected;
			int nCount = 0;
			//	 
			TCHAR tszSQL[512];
			//_RecordsetPtr pRecordset;
			CcollectorApp *app = (CcollectorApp *)AfxGetApp();
 			 
			_SYSTEMTIME st;
			GetLocalTime(&st);// / GetLocalTime();
							  //t = GetCurrentTime();  //UTC 1974 
			CString timeStr;
			timeStr.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			CString strDateTime;
			strDateTime.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)timeStr);

			_stprintf(tszSQL, _T("update table_log  set time=%s  where ip=\'%s\'  And  zigbee_address=\'%s\' "), strDateTime, wbuf_ip, netAddress);

			HRESULT hr = app->m_database.m_pConnection->Execute((_bstr_t)tszSQL, &RecordsAffected, adCmdText);
			if (!SUCCEEDED(hr))
			{
				CString strErrorMsg = _T("");
				strErrorMsg.Format(_T(" %s , fail to excute sql: %s "), strDateTime, tszSQL);
				 
				WriteLog(tszSQL);
				//if (pRecordset->State) pRecordset->Close();
				return -137;
			}

		}
		catch (_com_error e)
		{
			CString strErrorMsg = _T("");
			strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
			TRACE(strErrorMsg);
			WriteLog(strErrorMsg.GetBuffer());
			return  -1;
		}

		return  0;

	}//else if (pack->cmmd == CMMD_NORMAL_DATA)


}


BOOL CcollectorDlg:: SendControlMessage(CSocketOverlap *pSocketOlp, TagPageControlStruct * pcs)
{

	BOOL  checkAll;
	BOOL  checkIp;
	BOOL  checkNetId;
	BOOL   checkNetAddr;
	BOOL    controlCode; // 0 -off, 1- on , 2 --
	DWORD   ip;
	WORD  netId;
	WORD  netAddr;


	TagFullPacketStruct pfs;
	char  data[256];

	

	WSABUF wbuf;
	OVERLAPPED ol;
	ZeroMemory(&ol, sizeof(OVERLAPPED));


	WSABUF *p_wbuf = &wbuf;
	OVERLAPPED *p_ol = &ol;
	DWORD             dwBytes = 0, dwFlags = 0;
	char buffer[512];

	char *  pbuf = p_wbuf->buf = buffer;

	p_wbuf->len = 0;
	*(unsigned short*)pbuf = htons(0xAABB);
	p_wbuf->len += 2;
	pbuf += 2;
	controlCode = pcs->controlCode;
	*(unsigned short*)pbuf = htons(controlCode);  //cmmd
	p_wbuf->len += 2;
	pbuf += 2;
	*(unsigned short*)pbuf = htons(CProtocol::GetSerialNo()); //暂定为1 ，
	p_wbuf->len += 2; pbuf += 2;

	if(controlCode == 4)
	    *(unsigned short*)pbuf = htons(4+19);  // data length 
	else 
		*(unsigned short*)pbuf = htons(4);  // data length 

	p_wbuf->len += 2; pbuf += 2;

	*(unsigned short*)pbuf = htons(pcs->netId);//0x2001 
	p_wbuf->len += 2; pbuf += 2;

	*(unsigned short*)pbuf = htons(pcs->netAddr); //0x2002
	p_wbuf->len += 2; pbuf += 2;

	if (controlCode == 4)
	{
		memcpy(pbuf, pcs->time, sizeof(pcs->time));
		p_wbuf->len += 19; pbuf += 19;
	}
	//unsigned  int check = htons(pSocketOlp->m_cp.CheckSum(pfs.cmmd, pfs.serialNo, pfs.dataLength, pfs.data));
	unsigned  int check = htons(pSocketOlp->m_cp.CheckSum(p_wbuf->buf + 2, p_wbuf->len - 2));//起始码不参加校验 !!!

	*(unsigned short*)pbuf = check;
	p_wbuf->len += 2;  //pbuf += 2;

					   // on----   AA BB 00 02 00 01 00 04 20 01 20 02 00 4A 
					   //off---  AA BB 00 03 00 01 00 04 20 01 20 02 00 4B 

	int nBytesSent = WSASend(pSocketOlp->m_socket, p_wbuf, 1, &dwBytes, dwFlags, p_ol, NULL);

	return TRUE;

}


BOOL CcollectorDlg::SendUpgradeMessage(CSocketOverlap *pSocketOlp, TagPageUpgradeStruct * pcs)
{


	fstream iofile;
	iofile.open (pcs->fileName, ios::binary| ios::in );
	if (!iofile || iofile.bad())
	{
		AfxMessageBox(_T("Fail to open  file !"));
		return FALSE;
		exit(0);
	}

# ifdef DEBUG 
	CFile file;
	if (!file.Open(_T("test.bin"), CFile::modeCreate| CFile::modeRead | CFile::typeBinary | CFile::modeWrite))
	{
		AfxMessageBox(_T("Fail to open upgrade file  !"));
		return FALSE;
	}
	 
	file.Close();


	fstream testfile;
	testfile.open("test.bin", ios::binary | ios::out );

	if (!testfile || testfile.bad())
	{
		AfxMessageBox(_T("Fail to open  file !"));
		return FALSE;
		exit(0);
	}
#endif


	iofile.seekg(0, ios::end);
	int fileLen = iofile.tellg();
	iofile.seekg(0, ios::beg);
	int readLen = 0;
	int packNo = 0;
	unsigned short wantReadLen = 0;
	int remainLen = fileLen;
	unsigned short totalPack = fileLen / MAX_FILE_PACK_LEN;
	if (fileLen% MAX_FILE_PACK_LEN) 
		totalPack++;
	while (!iofile.eof()  && remainLen>0)
	{
		BOOL  checkAll;
		BOOL  checkIp;
		BOOL  checkNetId;
		BOOL   checkNetAddr;
		BOOL    controlCode; //CMMD_CONTROL_UPGRADE
		DWORD   ip;
		WORD  netId;
		WORD  netAddr;


		TagFullPacketStruct pfs;
		char  data[256];



		WSABUF wbuf;
		OVERLAPPED ol;
		ZeroMemory(&ol, sizeof(OVERLAPPED));


		WSABUF *p_wbuf = &wbuf;
		OVERLAPPED *p_ol = &ol;
		DWORD             dwBytes = 0, dwFlags = 0;
		char buffer[MAX_FILE_PACK_LEN+ 50]; //记住这是一个内部的临时变量 

		char *  pbuf = p_wbuf->buf = buffer;

		p_wbuf->len = 0;
		*(unsigned short*)pbuf = htons(0xAABB);
		p_wbuf->len += 2;
		pbuf += 2;
		controlCode = CMMD_CONTROL_UPGRADE;
		*(unsigned short*)pbuf = htons(controlCode);  //cmmd
		p_wbuf->len += 2;
		pbuf += 2;
		*(unsigned short*)pbuf = htons(CProtocol::GetSerialNo()); //暂定为1 ，
		p_wbuf->len += 2; pbuf += 2;
		*(unsigned short*)pbuf = htons(4);  // data length 
		p_wbuf->len += 2; pbuf += 2;

		*(unsigned short*)pbuf = htons(pcs->netId);//0x2001 
		p_wbuf->len += 2; pbuf += 2;

		*(unsigned short*)pbuf = htons(pcs->netAddr); //0x2002
		p_wbuf->len += 2; pbuf += 2;

		/////////begin of  data///////////////////////
		wantReadLen = min(remainLen, MAX_FILE_PACK_LEN);

		*(unsigned short*)pbuf = htons(totalPack);// 
		p_wbuf->len += sizeof(unsigned short); pbuf += sizeof(unsigned short);

		*(unsigned short*)pbuf = htons(packNo);// 
		p_wbuf->len += sizeof(unsigned short); pbuf += sizeof(unsigned short);
		*(unsigned short*)pbuf = htons(wantReadLen);  //current pack  length 
		p_wbuf->len += sizeof(unsigned short); pbuf += sizeof(unsigned short);

		memset(pbuf, 0, sizeof(pcs->fname));
		strcpy(pbuf, pcs->fname);
		p_wbuf->len += sizeof(pcs->fname); pbuf += sizeof(pcs->fname);  //30


		
		char  tempBuf[MAX_FILE_PACK_LEN];
		iofile.read(tempBuf, wantReadLen);

# ifdef DEBUG 
		testfile.write(tempBuf, wantReadLen);
#endif

		for (int i = 0; i < wantReadLen; i++)
		{
			pbuf[i] = tempBuf[i];
		}
		p_wbuf->len += wantReadLen;  pbuf += wantReadLen;
		remainLen -= wantReadLen;
		packNo++;
		////////////end of  data //////////

		*(unsigned short*)(buffer + 6) = 36 + wantReadLen;  //对数据长度进行修正


		//unsigned  int check = htons(pSocketOlp->m_cp.CheckSum(pfs.cmmd, pfs.serialNo, pfs.dataLength, pfs.data));
		unsigned  int check = htons(pSocketOlp->m_cp.CheckSum(p_wbuf->buf + 2, p_wbuf->len - 2));//起始码不参加校验 !!!

		*(unsigned short*)pbuf = check;
		p_wbuf->len += 2;  //pbuf += 2;

						   // on----   AA BB 00 02 00 01 00 04 20 01 20 02 00 4A 
						   //off---  AA BB 00 03 00 01 00 04 20 01 20 02 00 4B 

		int nBytesSent = WSASend(pSocketOlp->m_socket, p_wbuf, 1, &dwBytes, dwFlags, p_ol, NULL);

	}//while 

	iofile.close();

# ifdef DEBUG 
	testfile.close();
#endif
	return TRUE;

}

LRESULT  CcollectorDlg::OnFreshList(WPARAM wParam, LPARAM lParam)
{
		
		int timer = GetPrivateProfileInt(_T("device"), _T("timer"), 10, _T("config.ini"));
		if (m_timer != timer)
		{
			m_timer = timer;
			KillTimer(1);
			this->SetTimer(1, m_timer * 1000, 0);
		}

	RefreshList();
	return  1;
}

LRESULT  CcollectorDlg:: OnPageMessage(WPARAM wParam, LPARAM lParam)
{

	if (1== wParam)// control
	{
		BOOL  checkAll;
		BOOL  checkIp;
		BOOL  checkNetId;
		BOOL   checkNetAddr;
		BOOL    controlCode; // 0 -off, 1- on , 2 --
		DWORD   ip;
		WORD  netId;
		WORD  netAddr;
		TagPageControlStruct * pcs = (TagPageControlStruct*)lParam;


		
		//CClientContext * pcp = NULL;
		CSocketOverlap* pSocketOlp = NULL;
		if (pcs->checkIp)
		{
			DWORD   ip = pcs->ip;
			POSITION pos = m_serverIOCP.m_lstSocketOlp.GetHeadPosition();
			while (pos)
			{
				pSocketOlp = m_serverIOCP.m_lstSocketOlp.GetNext(pos);
				if (pSocketOlp)
				{
					if (ntohl(pSocketOlp->m_ClientAddress.sin_addr.S_un.S_addr) == pcs->ip)				
						break;				
				}
			}//while

			if(pSocketOlp)
			    SendControlMessage(pSocketOlp, pcs);

		}//if (pcs->checkIp)
		else if (pcs->checkAll)
		{
			POSITION pos = m_serverIOCP.m_lstSocketOlp.GetHeadPosition();
			while (pos)
			{
				pSocketOlp = m_serverIOCP.m_lstSocketOlp.GetNext(pos);
				if (pSocketOlp)
				{
					SendControlMessage(pSocketOlp, pcs);
				}
			}//while		

		}
	 
	}

	else  if (3 == wParam)  //upgrade 
	{
		BOOL  checkAll;
		BOOL  checkIp;
		BOOL  checkNetId;
		BOOL   checkNetAddr;
		//BOOL    controlCode; // 0 -off, 1- on , 2 --
		DWORD   ip;
		WORD  netId;
		WORD  netAddr;
		TagPageUpgradeStruct * pcs = (TagPageUpgradeStruct*)lParam;

		CSocketOverlap* pSocketOlp = NULL;
		if (pcs->checkIp)
		{
			DWORD   ip = pcs->ip;
			POSITION pos = m_serverIOCP.m_lstSocketOlp.GetHeadPosition();
			while (pos)
			{
				pSocketOlp = m_serverIOCP.m_lstSocketOlp.GetNext(pos);
				if (pSocketOlp)
				{
					if (ntohl(pSocketOlp->m_ClientAddress.sin_addr.S_un.S_addr) == pcs->ip)
						break;
				}
			}//while

			if (pSocketOlp)
				SendUpgradeMessage(pSocketOlp, pcs);

		}//if (pcs->checkIp)
		else if (pcs->checkAll)
		{
			POSITION pos = m_serverIOCP.m_lstSocketOlp.GetHeadPosition();
			while (pos)
			{
				pSocketOlp = m_serverIOCP.m_lstSocketOlp.GetNext(pos);
				if (pSocketOlp)
				{
					SendUpgradeMessage(pSocketOlp, pcs);
				}
			}//while		

		}
	}

	return 0;
}


BOOL  CcollectorDlg::RefreshList()
{

	//UpdateData(TRUE);


	m_listctrl.DeleteAllItems();

	_RecordsetPtr pRecordset;
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	try
	{
		_variant_t RecordsAffected;

		CString where = _T("");
		CString ip1, ip2, address1, address2, strTemp;
		TCHAR para[50];

		HRESULT hr = pRecordset.CreateInstance(_T("ADODB.Recordset"));
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("ADO Recordset - CreateInstance failed."));

			return false;
		}
  
	 
		GetPrivateProfileString(_T("device"), _T("ip1"), _T(""), para, sizeof(para), _T("config.ini"));
		ip1 = para;
		GetPrivateProfileString(_T("device"), _T("ip2"), _T(""), para, sizeof(para), _T("config.ini"));
		ip2 = para;
		GetPrivateProfileString(_T("device"), _T("zigbee_address1"), _T(""), para, sizeof(para), _T("config.ini"));
		address1 = para;
		GetPrivateProfileString(_T("device"), _T("zigbee_address2"), _T(""), para, sizeof(para), _T("config.ini"));
		address2 = para;

		CString tszSQL = _T("select * from table_device  ");

		if (ip1.IsEmpty() && ip2.IsEmpty() && address1.IsEmpty() && address2.IsEmpty())
		where = _T("");
		else
		where = _T("where ");

		if (!ip1.IsEmpty())
		{
			strTemp.Format(_T("ip>=\'%s\'"), ip1);
			where += strTemp;
		}

		if (!ip2.IsEmpty())
		{
			if (!ip1.IsEmpty())
			{
				where += _T(" And ");
			}
			strTemp.Format(_T("ip<=\'%s\'"), ip2);
			where += strTemp;
		}

		if (!address1.IsEmpty())
		{
			if (!(ip1.IsEmpty() && ip2.IsEmpty()))
			{
				where += _T(" And ");
			}
			strTemp.Format(_T("zigbee_address>=\'%s\'"), address1);
			where += strTemp;
		}

		if (!address2.IsEmpty())
		{
			if (!(ip1.IsEmpty() && ip2.IsEmpty() && address1.IsEmpty()))
			{
				where += _T(" And ");
			}
			strTemp.Format(_T("zigbee_address<=\'%s\'"), address2);
			where += strTemp;
		}

		tszSQL += where;

		hr = pRecordset->Open((_bstr_t)tszSQL,
			_variant_t((IDispatch*)app->m_database.m_pConnection, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("fail to open recordset !"));
			return false;
		}

	 

		int nCount = 0; 
		int timeout = GetPrivateProfileInt(_T("KeepAlive"), _T("timeout"), 60, _T("config.ini"));
		while (!pRecordset->adoEOF)
			//while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;


			v = pRecordset->GetCollect(_variant_t((long)1));
			nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
			//if (v.vt != VT_I4) break;
			//nStudyId = v.lVal;
			strTemp = pRecordset->GetCollect(_variant_t((long)4));
			m_listctrl.SetItemText(nCount, 1, strTemp);
			//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);


			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
			m_listctrl.SetItemText(nCount, 2, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
			m_listctrl.SetItemText(nCount, 3, strTemp);

			//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
			//m_listctrl.SetItemText(nCount, 4, strTemp);  //status


		

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));	
			int y, mm, d, h, m, s;	 
			char buf[40];
			WCharToMByte(strTemp.GetBuffer(), buf, sizeof(buf));
			sscanf(buf, "%04d-%02d-%02d %02d:%02d:%02d" ,&y, &mm, &d, &h, &m, &s);
		
			CTime time1(y, mm, d, h, m, s);// = CTime::GetCurrentTime();	
			_SYSTEMTIME st;
			GetLocalTime(&st);// / GetLocalTime();
			CTime time2(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			CTimeSpan timeSpan = time2 - time1; // 得到总的秒数
			int nTSeconds = timeSpan.GetTotalSeconds();
			if (nTSeconds > timeout)
			{
				m_listctrl.SetItemBkColor(nCount, 4, RGB(255, 0, 0));
				m_listctrl.SetItemTextColor(nCount, 4, RGB(255, 255, 255));
				m_listctrl.SetItemText(nCount, 4, _T("未知"));  //time
			}
			else
			{
				m_listctrl.SetItemBkColor(nCount, 4, RGB(0, 0, 255));
				m_listctrl.SetItemTextColor(nCount, 4, RGB(255, 255, 255));
				m_listctrl.SetItemText(nCount, 4, _T("開"));  //time
			}
			m_listctrl.SetItemText(nCount, 5, strTemp);  //time


			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
			m_listctrl.SetItemText(nCount, 6, strTemp);

			pRecordset->MoveNext();


		}
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
	 
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return false;
	}



	return  TRUE;
}


void CcollectorDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem<m_listctrl.GetItemCount())//判断双击位置是否在有数据的列表项上面
	{
		CString  ip, panId, netAddress;
		ip = m_listctrl.GetItemText(nItem, 1).Trim();
		panId = m_listctrl.GetItemText(nItem, 2).Trim();
		netAddress = m_listctrl.GetItemText(nItem, 3).Trim();
		CDialogSearch  dlg;
		CString  where;
		where.Format(_T("where ip= \'%s\' and zigbee_address=\'%s\'"), ip, netAddress);
		dlg.m_tszSQL.Format(_T("SELECT   *   FROM table_log  "));
		dlg.m_tszSQL += where;
		dlg.m_pageCount = 100;
		//AfxMessageBox(dlg.m_tszSQL);
		dlg.DoModal();

	}



	*pResult = 0;
}



void CcollectorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RefreshList();


	CDialogEx::OnTimer(nIDEvent);
}
