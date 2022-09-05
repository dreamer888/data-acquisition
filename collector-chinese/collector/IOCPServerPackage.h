#pragma once
#include "SocketOverlap.h"


#define SOCKET_MSG   WM_USER+2

class CIOCPServerPackage
{
public:
	CIOCPServerPackage();
	
	CIOCPServerPackage(CWnd* pParent);
public:
	~CIOCPServerPackage(void);

	CList<CSocketOverlap*, CSocketOverlap*>m_lstSocketOlp;//定义链表

	BOOL m_bInitWinSockFlag;

	CString m_strErrorMsg;

	SOCKET m_socketListen;

	LONG m_nThreadNum;

	HANDLE m_hCompletePort;

	CWnd* m_pParent;
	HWND  m_hWnd;

protected:
	//内部用的的函数，自我调用
	//服务的线程
	static DWORD WINAPI ThreadWorking(LPVOID lpVoid);
	//加载WinSock库
	BOOL InitWinSock();
	//关闭
	void CloseSocket();
	//发送消息
	BOOL SendMsg(CString strMsg);
	static BOOL  MySendMessage(HWND ghwnd, int wpara, char* ip, char * msg, int len);
public:
	//主要的功能：接口，给使用者来用的
	//启动服务器
	BOOL StartServer(UINT nListenPort);
	//停止服务器
	BOOL StopServer();
	//投递请求：Accept
	BOOL PostAccept(BOOL bFirst=FALSE);
	//投递请求：Recv
	BOOL PostRecv(CSocketOverlap* pItem,  BOOL  bAccept=FALSE);
	//发送数据
	BOOL SendData(char *pSendData, DWORD dwDataSize);
	//得到错误信息
	CString GetLastErrorMsg()
	{
		return m_strErrorMsg;
	}
	
	char * GetLocalIp();
	CString GetLocalIp1();
	in_addr  CIOCPServerPackage::GetLocalIp2();
	static BOOL GetPeerSockAddr(SOCKET listenSock, SOCKET clientSock, sockaddr_in  *peerAddr);

	LPFN_ACCEPTEX                m_lpfnAcceptEx;                // AcceptEx 和 GetAcceptExSockaddrs 的函数指针，用于调用这两个扩展函数
	LPFN_GETACCEPTEXSOCKADDRS    m_lpfnGetAcceptExSockAddrs;

	CRITICAL_SECTION             m_csContextList;

};
