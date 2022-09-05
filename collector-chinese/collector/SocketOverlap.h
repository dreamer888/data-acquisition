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
	WSAOVERLAPPED m_overLapped;		//异步事件
	SOCKET m_socket;			    //连接的客户端
	sockaddr_in       m_ClientAddress;
	unsigned short	  m_NetId;   //zigbee  id ;
	EIoType m_nIoType;				//网络事件类型
	char m_szBuf[MAX_BUF_SIZE];	    //接收数据的缓冲区
	int m_bufLen;
	CProtocol			m_cp;

	CRITICAL_SECTION             m_csReadWrite;

public:
	CSocketOverlap();
public:
	~CSocketOverlap(void);


};
