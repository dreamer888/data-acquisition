#pragma once
#include <WinSock2.h>
#include <MSWSock.h>

# include "Protocol.h""

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#define MAX_BUF_SIZE	4096

enum EIoType
{
	TYPE_ACCEPT,
	TYPE_READ,
	TYPE_WRITE,
	TYPE_CLOSE,
	TYPE_UNKNOW
};
class CSocketOverlap
{
public:
	WSAOVERLAPPED m_overLapped;		//�첽�¼�
	SOCKET m_socket;			    //���ӵĿͻ���
	sockaddr_in       m_ClientAddress;
	unsigned short	  m_NetId;   //zigbee  id ;
	EIoType m_nIoType;				//�����¼�����
	char m_szBuf[MAX_BUF_SIZE];	    //�������ݵĻ�����
	int m_bufLen;
	CProtocol			m_cp;

	CRITICAL_SECTION             m_csReadWrite;

public:
	CSocketOverlap();
public:
	~CSocketOverlap(void);


};
