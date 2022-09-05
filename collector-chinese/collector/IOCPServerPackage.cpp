#include "StdAfx.h"
#include "IOCPServerPackage.h"



HWND g_hwnd = NULL;

CIOCPServerPackage::CIOCPServerPackage()
{

	m_pParent = NULL;

	m_bInitWinSockFlag = FALSE;

	m_nThreadNum = 0;

	m_hCompletePort = NULL;

	m_socketListen = NULL;

	m_strErrorMsg = _T("");
}; // ������캯��dd  by me


CIOCPServerPackage::CIOCPServerPackage(CWnd* pParent)
{
	m_pParent = pParent;

	m_bInitWinSockFlag = FALSE;

	m_nThreadNum = 0;

	m_hCompletePort = NULL;

	m_socketListen = NULL;

	m_strErrorMsg = _T("");
}

CIOCPServerPackage::~CIOCPServerPackage(void)
{
	CloseSocket();
}

void CIOCPServerPackage::CloseSocket()
{

	if (m_socketListen == 0 || m_hCompletePort == INVALID_HANDLE_VALUE)
	{

		WSACleanup();
		return;
	}

	while (m_nThreadNum > 0)
	{
		PostQueuedCompletionStatus(m_hCompletePort, 0, NULL, NULL);
		Sleep(100);
	}

	//if (m_lstSocketOlp==NULL)  return;

	CSocketOverlap* pSocketOlp = NULL;
	POSITION pos = m_lstSocketOlp.GetHeadPosition();
	while (pos)
	{
		pSocketOlp = m_lstSocketOlp.GetNext(pos);
		if (pSocketOlp->m_socket)
		{
			closesocket(pSocketOlp->m_socket);
			pSocketOlp->m_socket = NULL;
		}

		if (pSocketOlp->m_overLapped.hEvent)
		{
			WSACloseEvent(pSocketOlp->m_overLapped.hEvent);
			pSocketOlp->m_overLapped.hEvent = NULL;
		}

		delete pSocketOlp;
	}
	m_lstSocketOlp.RemoveAll();

	while (m_lstSocketOlp.GetHeadPosition())
	{
		delete m_lstSocketOlp.RemoveHead();
	}

	if (m_hCompletePort)
	{
		CloseHandle(m_hCompletePort);
		m_hCompletePort = NULL;
	}

	if (m_socketListen)
	{
		closesocket(m_socketListen);
		m_socketListen = NULL;
	}

	if (m_bInitWinSockFlag)
	{
		WSACleanup();
	}
}


void  MakeTestData()
{

	typedef  struct TagClientDataStruct
	{
		unsigned short  netId;		//zigbee�����
		unsigned short netAddr;  //zigbee��ַ
		unsigned  short event;  //�¼�����, 0-������1-�ػ���2-̧��3-���£�4 ����
		char      time[19]; //ʱ��
		unsigned  short steps;  // ���߲���
		char   employeeNo[10];   //Ա�����
		char   processNo[24];    //�����
		char   modelNo[8];    //�ͺ�
	}TagClientPacketrStruct, *PTagClientPacketrStruct;



	typedef  struct TagPacketStruct
	{
		unsigned short cmmd;
		unsigned short serialNo;
		unsigned short dataLength;
		char* data;
	}TagPacketStruct, *PTagPacketStruct;



	typedef  struct TagFullPacketStruct
	{
		unsigned short  start;
		unsigned short cmmd;
		unsigned short serialNo;
		unsigned short dataLength;
		char* data;
		unsigned   short   checksum;
	}TagFullPacketStruct, *PTagFullPacketStruct;


	TagClientDataStruct   cd;



	unsigned short  start = 0xaabb;
	unsigned short cmmd = 0x0000;
	unsigned short serialNo = 1;
	unsigned short dataLen = 0;
	char* data = NULL;
	unsigned short checkSum = 0;


	char  buf[256];
	char  dataBuf[256];

	char  *  pBuf = buf;

	int  packLen = 0;


	data = dataBuf;

	/////data ///////
	cd.netId = 0x1001;
	cd.netAddr = 0x2002;
	cd.event = 0x0000;
	memcpy(cd.time, "2016-11-30 11:06:18", 19);
	cd.steps = 0x0100;
	memcpy(cd.employeeNo, "0100101001" , 10);      //[10];   //Ա�����
	memcpy(cd.processNo, "301302303304305306307308", 24);    //[24];    //�����
	memcpy(cd.modelNo, "3902.601" ,8);      //[8]; �ͺ�

	CProtocol			m_cp;


	*((unsigned short*)data) = htons(cd.netId);
	data += 2;
	*((unsigned short*)data) = htons(cd.netAddr);
	data += 2;
	*((unsigned short*)data) = htons(cd.event);
	data += 2;
	memcpy(data, cd.time, strlen(cd.time));
	data += strlen(cd.time);
	*((unsigned short*)data) = htons(cd.steps);
	data += 2;

	int len = strlen(cd.employeeNo);
	memcpy(data, cd.employeeNo, 10);
	data += 10;
	memcpy(data, cd.processNo,24);
	data += 24;
	memcpy(data, cd.modelNo, 8);
	data += 8;

	////////////////////////////////

	dataLen = 69;

	*((unsigned short*)pBuf) = htons(start);
	pBuf += 2;
	*((unsigned short*)pBuf) = htons(cmmd);
	pBuf += 2;
	*((unsigned short*)pBuf) = htons(serialNo);
	pBuf += 2;
	*((unsigned short*)pBuf) = htons(dataLen);
	pBuf += 2;
	memcpy(pBuf, dataBuf, dataLen);
	pBuf += dataLen;

	checkSum = m_cp.LoopBuffer(buf + 2, 6 + dataLen);
	*((unsigned short*)pBuf) = htons(checkSum);
	//pBuf += 2;

	packLen = 8 + dataLen + 2;  //79


//aabb000000010045100120020000323031362d31312d33302031313a30363a3138000130313030313031303031333031333032333033333034333035333036333037333038333930322e3630310000
}



BOOL CIOCPServerPackage::InitWinSock()
{
#ifdef  DEBUG

	MakeTestData();

#endif

	if (!m_bInitWinSockFlag)
	{
		WORD wRequestVersion;
		WSADATA wsaData;
		int nRet;

		wRequestVersion = 2 << 8 | 2;

		nRet = WSAStartup(wRequestVersion, &wsaData);

		if (nRet != 0)
		{
			m_strErrorMsg = _T("���ؿ�ʧ�ܣ�");
			AfxMessageBox(_T("Fil to start  socket "));
			return FALSE;
		}

		if ((wsaData.wVersion >> 8) != 2 || (wsaData.wVersion & 0xff) != 2)
		{
			m_strErrorMsg = _T("��İ汾���ԣ�");
			AfxMessageBox(_T("Fil to start  socket "));
			WSACleanup();
			return FALSE;
		}

		m_bInitWinSockFlag = TRUE;
	}

	return TRUE;
}




BOOL CIOCPServerPackage::PostAccept(BOOL bFirst)
{
	DWORD dwDataSize = 0;

	CSocketOverlap* pItem = new CSocketOverlap;

	pItem->m_nIoType = TYPE_ACCEPT;
	pItem->m_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	//pItem->m_listenSock = m_socketListen;
	BOOL bRet = AcceptEx(m_socketListen, pItem->m_socket, pItem->m_szBuf, NULL, sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &dwDataSize, &pItem->m_overLapped);
	if (!bRet)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			if (pItem)
			{
				delete pItem;
				pItem = NULL;
			}
			return FALSE;
		}
	}

	//if(!bFirst)
	//m_lstSocketOlp.AddTail(pItem);  //�߼� ���䲻�Ͻ�  ����������Ҫ�޸�

									//
	HANDLE hTemp = CreateIoCompletionPort((HANDLE)pItem->m_socket, m_hCompletePort, (ULONG_PTR)&pItem->m_socket, 0);
	if (NULL == hTemp)
	{
		//if (!bFirst)
		//m_lstSocketOlp.RemoveTail();

		if (pItem)
		{
			delete pItem;
			pItem = NULL;
		}

		return FALSE;
	}

	return TRUE;
}

BOOL CIOCPServerPackage::PostRecv(CSocketOverlap* pItem, BOOL bAccept)
{
	if(!bAccept)
	if (pItem->m_bufLen>0  && pItem->m_bufLen<256)  //lgl
	{
		//SendData(pItem->m_szBuf, pItem->m_bufLen);
		pItem->m_cp.m_hwnd = this->m_hWnd;
		pItem->m_cp.m_ip = inet_ntoa(pItem->m_ClientAddress.sin_addr);
		pItem->m_cp.LoopBuffer(pItem->m_szBuf, pItem->m_bufLen);
		//MySendMessage(g_hwnd, 0, inet_ntoa(pItem->m_ClientAddress.sin_addr), pItem->m_szBuf, strlen(pItem->m_szBuf));

		
	}

	memset(pItem->m_szBuf, 0, sizeof(pItem->m_szBuf));
	DWORD dwRecvNum = 0;
	DWORD dwFlag = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = pItem->m_szBuf;
	wsaBuf.len = MAX_BUF_SIZE;
	pItem->m_nIoType = TYPE_READ;
	int nRet = WSARecv(pItem->m_socket, &wsaBuf, 1, &dwRecvNum, &dwFlag, &pItem->m_overLapped, FALSE);
	if (nRet != 0)
	{
		if (GetLastError() != ERROR_IO_PENDING)
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CIOCPServerPackage::SendData(char *pSendData, DWORD dwDataSize)
{
	POSITION pos = m_lstSocketOlp.GetHeadPosition();
	CSocketOverlap *pItem = NULL;
	WSABUF wsaBuf;
	DWORD dwRecvNum = 0, dwFlag = 0;		//���븳��ֵ
	while (pos)
	{
		pItem = m_lstSocketOlp.GetNext(pos);
		if (pItem->m_socket)
		{
			wsaBuf.buf = pSendData;
			wsaBuf.len = dwDataSize;
			pItem->m_nIoType = TYPE_WRITE;// ���� ��
			if (SOCKET_ERROR == WSASend(pItem->m_socket, &wsaBuf, 1, &dwRecvNum, dwFlag, &pItem->m_overLapped, NULL))
			{
				pItem->m_nIoType = TYPE_READ;		//lgl
				if (WSAGetLastError() != ERROR_IO_PENDING)
				{
					int nResult = GetLastError();
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}



BOOL  CIOCPServerPackage::MySendMessage(HWND ghwnd, int wpara, char* ip, char * msg, int len)
{
	char tempbuf[512];
	char buf[512];
	memset(tempbuf, 0, sizeof(tempbuf));
	memset(buf, 0, sizeof(buf));
	_SYSTEMTIME st;
	GetLocalTime(&st);// 
					  //GetSystemTime   not correct , in hour 
					  //dont use  this  api  ,,,,, ! t = GetCurrentTime();  //UTC 1974 

	//sprintf(tempbuf, "%04d-%02d-%02d %02d:%02d:%02d   ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	strcpy(tempbuf, ip);
	strcat(tempbuf, " ");
	strcat(tempbuf, msg);
	//strcat(tempbuf, ",");

	//strcat(tempbuf, buf);

	//::SendMessage(ghwnd, SOCKET_MSG, 0, (LPARAM)p_wbuf->buf);
	::SendMessage(ghwnd, SOCKET_MSG, wpara, (LPARAM)tempbuf);
	return  TRUE;
}
//������Ϣ
BOOL CIOCPServerPackage::SendMsg(CString strMsg)
{
	BOOL bRet = FALSE;
	if (m_pParent)
	{
		bRet = m_pParent->SendMessage(SOCKET_MSG, (WPARAM)strMsg.GetBuffer(), (LPARAM)(sizeof(TCHAR)*(strMsg.GetLength() + 1)));
	}
	return bRet;
}
BOOL CIOCPServerPackage::StartServer(UINT nListenPort)
{
	if (!InitWinSock())
	{
		m_strErrorMsg = _T("����winsock��ʧ�ܣ�");
		CloseSocket();
		return FALSE;
	}
	g_hwnd = this->m_hWnd;
	m_socketListen = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == m_socketListen)
	{
		m_strErrorMsg = _T("��������socketʧ�ܣ�");
		AfxMessageBox(_T("Fail to create  socket "));
		CloseSocket(); //�������� ��
		return FALSE;
	}
	sockaddr_in sockAddrServer;
	sockAddrServer.sin_family = AF_INET;
	sockAddrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_addr("127.0.0.1");
	sockAddrServer.sin_port = htons(nListenPort);
	if (SOCKET_ERROR == bind(m_socketListen, (const SOCKADDR*)&sockAddrServer, sizeof(sockAddrServer)))
	{
		m_strErrorMsg = _T("bind����");
		//CloseSocket();
		AfxMessageBox(_T("Fail to bind  socket "));
		closesocket(m_socketListen);
		WSACleanup();
		return FALSE;
	}
	if (SOCKET_ERROR == listen(m_socketListen, SOMAXCONN))
	{
		m_strErrorMsg = _T("listenʧ�ܣ�");
		AfxMessageBox(_T("Fail to listen  socket "));
		CloseSocket();
		return FALSE;
	}

	//������ɶ˿�ģ��
	m_hCompletePort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (INVALID_HANDLE_VALUE == m_hCompletePort)
	{
		m_strErrorMsg = _T("������ɶ˿�ʧ�ܣ�");
		AfxMessageBox(_T("Fail to create  iocp  "));
		CloseSocket();
		return FALSE;
	}

	CreateIoCompletionPort((HANDLE)m_socketListen, m_hCompletePort, (ULONG_PTR)&m_socketListen, 0);


	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	DWORD  dwBytes;

	if (SOCKET_ERROR == WSAIoctl(
		m_socketListen,
		SIO_GET_EXTENSION_FUNCTION_POINTER,
		&GuidGetAcceptExSockAddrs,
		sizeof(GuidGetAcceptExSockAddrs),
		&m_lpfnGetAcceptExSockAddrs,
		sizeof(m_lpfnGetAcceptExSockAddrs),
		&dwBytes,
		NULL,
		NULL))
	{

		//this->_ShowMessage(_T("WSAIoctl δ�ܻ�ȡGuidGetAcceptExSockAddrs����ָ�롣�������: %d\n"), WSAGetLastError());
		//this->_DeInitialize();
		return false;
	}

	PostAccept(TRUE);

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int nThreadNum = sysInfo.dwNumberOfProcessors * 2;
	for (int i = 0; i<nThreadNum; i++)
	{
		HANDLE hThread = NULL;
		hThread = CreateThread(NULL, 0, ThreadWorking, this, CREATE_SUSPENDED, 0);
		if (hThread != INVALID_HANDLE_VALUE)
		{
			Sleep(20);
			ResumeThread(hThread);
			CloseHandle(hThread);
		}
	}
	return TRUE;
}
BOOL CIOCPServerPackage::StopServer()
{
	CloseSocket();
	return TRUE;
}

DWORD WINAPI CIOCPServerPackage::ThreadWorking(LPVOID lpVoid)
{
	CIOCPServerPackage* pThis = (CIOCPServerPackage*)lpVoid;
	DWORD dwRecvNum = 0;
	SOCKET *pSocket = NULL;
	CSocketOverlap* pSocketOlp = NULL;
	BOOL bRet = FALSE;
	CString strValue;

	InterlockedIncrement(&pThis->m_nThreadNum);

	while (1)
	{
		bRet = GetQueuedCompletionStatus(pThis->m_hCompletePort, &dwRecvNum, (PULONG_PTR)&pSocket, (LPOVERLAPPED*)&pSocketOlp, INFINITE);
		if (!bRet)
		{
			continue;
		}
		int nRet = GetLastError();
		if (dwRecvNum <= 0 && pSocket && (TYPE_WRITE == pSocketOlp->m_nIoType || TYPE_READ == pSocketOlp->m_nIoType))
		{
			//pThis->SendMsg(_T("�ͻ��������ߣ�"));
			//MySendMessage(ghwnd, 0, char* ip, char * msg, int len)
			MySendMessage(g_hwnd, 0, inet_ntoa(pSocketOlp->m_ClientAddress.sin_addr), "disconnected !", strlen("disconnected !"));
			//closesocket(pSocketOlp->m_socket);
			WSACloseEvent(pSocketOlp->m_overLapped.hEvent);
			pThis->m_lstSocketOlp.RemoveAt(pThis->m_lstSocketOlp.Find(pSocketOlp));
			delete pSocketOlp;
		}

		if (pSocket && pSocketOlp)
		{
			WSAResetEvent(pSocketOlp->m_overLapped.hEvent);

			switch (pSocketOlp->m_nIoType)
			{
			case TYPE_ACCEPT:
			{
				//TODO:�õ��ͻ��˵�IP��ַ
				//strValue.Format(_T("�ͻ���:%d������"),pSocketOlp->m_socket);
				//pThis->SendMsg(strValue);

				SOCKADDR_IN* ClientAddr = NULL;
				SOCKADDR_IN* LocalAddr = NULL;
				int remoteLen = sizeof(SOCKADDR_IN), localLen = sizeof(SOCKADDR_IN);

				//GetPeerSockAddr(pThis->m_socketListen, pSocketOlp->m_socket, &pSocketOlp->m_ClientAddress);

				if (*pSocket == pThis->m_socketListen)
				{

					pThis->m_lstSocketOlp.AddTail(pSocketOlp);  //�߼� ���䲻�Ͻ�  ����������Ҫ�޸�
					pThis->m_lpfnGetAcceptExSockAddrs(pSocketOlp->m_szBuf, 0,
						sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, (LPSOCKADDR*)&LocalAddr, &localLen, (LPSOCKADDR*)&ClientAddr, &remoteLen);
					pSocketOlp->m_ClientAddress = (sockaddr_in)*ClientAddr;
					pSocketOlp->m_bufLen = dwRecvNum;
					char *pAddress = inet_ntoa(pSocketOlp->m_ClientAddress.sin_addr);
					MySendMessage(g_hwnd, 0, inet_ntoa(pSocketOlp->m_ClientAddress.sin_addr), "connected !", strlen("connected !"));
					pThis->PostAccept(FALSE); 
					pThis->PostRecv(pSocketOlp, TRUE);  //  ���ɾ���� ��   no 
				}
				
						
				::QueueUserWorkItem(ThreadWorking, pThis, WT_EXECUTELONGFUNCTION);
				break;
			}
			case TYPE_READ:
				//strValue.Format(_T("%d��%s"), pSocketOlp->m_socket, pSocketOlp->m_szBuf);
				//pThis->SendMsg(strValue);


				pSocketOlp->m_bufLen = dwRecvNum;
				pThis->PostRecv(pSocketOlp);
				break;
			case TYPE_WRITE:
				break;

			default:
				break;
			}
		}
		else if (!pSocket && !pSocketOlp)
		{
			break;
		}
	}

	InterlockedDecrement(&pThis->m_nThreadNum);

	return 1;
}

char * CIOCPServerPackage::GetLocalIp(void)
{
	char name[155];

	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {     //��ȡ������
		if ((hostinfo = gethostbyname(name)) != NULL) { //��Щ���ǻ��IP�ĺ���
			strcpy(name, inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list)); //��ȡ����ip
		}
	}
	return name;


}

CString CIOCPServerPackage::GetLocalIp1()
{
	char name[155];
	CString cs;

	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {     //��ȡ������
		if ((hostinfo = gethostbyname(name)) != NULL) { //��Щ���ǻ��IP�ĺ���
			cs = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list); //��ȡ����ip
		}
	}
	return cs;


}


in_addr  CIOCPServerPackage::GetLocalIp2()
{
	char name[155];
	CString cs;

	in_addr  addr;

	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {     //��ȡ������
		if ((hostinfo = gethostbyname(name)) != NULL) { //��Щ���ǻ��IP�ĺ���
			addr = *(struct in_addr *)*hostinfo->h_addr_list; //��ȡ����ip
		}

	}

	return  addr;

}

/*
WSANOTINITIALISED����ʹ�ô�API֮ǰӦ���ȳɹ��ص���WSAStartup()��
WSAENETDOWN��WINDOWS�׽ӿ�ʵ�ּ�⵽������ϵͳʧЧ��
WSAEFAULT��namelen����������
WSAEINPROGRESS��һ��������WINDOWS�׽ӿڵ������������С�
WSAENOTCONN �׽ӿ�δ���ӡ�
WSAENOTSOCK�������ֲ���һ���׽ӿڡ�*/
BOOL CIOCPServerPackage::GetPeerSockAddr(SOCKET listenSock, SOCKET clientSock, sockaddr_in  *peerAddr)
{
	//���ӵĿͻ���
	sockaddr_in       clientAddress;
	int  len;

	int err = setsockopt(clientSock,
		SOL_SOCKET,
		SO_UPDATE_ACCEPT_CONTEXT,
		(char *)&listenSock,
		sizeof(listenSock));
	int ret = getpeername(clientSock, (struct sockaddr *)peerAddr, &len);
	if (ret != 0)
	{

		ret = WSAGetLastError();

		if (ret == WSAENOTCONN)
		{
			ret = 0;
		}
		return  FALSE;
	}

	return  TRUE;
}








