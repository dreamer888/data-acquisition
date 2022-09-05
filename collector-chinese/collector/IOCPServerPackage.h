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

	CList<CSocketOverlap*, CSocketOverlap*>m_lstSocketOlp;//��������

	BOOL m_bInitWinSockFlag;

	CString m_strErrorMsg;

	SOCKET m_socketListen;

	LONG m_nThreadNum;

	HANDLE m_hCompletePort;

	CWnd* m_pParent;
	HWND  m_hWnd;

protected:
	//�ڲ��õĵĺ��������ҵ���
	//������߳�
	static DWORD WINAPI ThreadWorking(LPVOID lpVoid);
	//����WinSock��
	BOOL InitWinSock();
	//�ر�
	void CloseSocket();
	//������Ϣ
	BOOL SendMsg(CString strMsg);
	static BOOL  MySendMessage(HWND ghwnd, int wpara, char* ip, char * msg, int len);
public:
	//��Ҫ�Ĺ��ܣ��ӿڣ���ʹ�������õ�
	//����������
	BOOL StartServer(UINT nListenPort);
	//ֹͣ������
	BOOL StopServer();
	//Ͷ������Accept
	BOOL PostAccept(BOOL bFirst=FALSE);
	//Ͷ������Recv
	BOOL PostRecv(CSocketOverlap* pItem,  BOOL  bAccept=FALSE);
	//��������
	BOOL SendData(char *pSendData, DWORD dwDataSize);
	//�õ�������Ϣ
	CString GetLastErrorMsg()
	{
		return m_strErrorMsg;
	}
	
	char * GetLocalIp();
	CString GetLocalIp1();
	in_addr  CIOCPServerPackage::GetLocalIp2();
	static BOOL GetPeerSockAddr(SOCKET listenSock, SOCKET clientSock, sockaddr_in  *peerAddr);

	LPFN_ACCEPTEX                m_lpfnAcceptEx;                // AcceptEx �� GetAcceptExSockaddrs �ĺ���ָ�룬���ڵ�����������չ����
	LPFN_GETACCEPTEXSOCKADDRS    m_lpfnGetAcceptExSockAddrs;

	CRITICAL_SECTION             m_csContextList;

};
