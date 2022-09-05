#include "StdAfx.h"
#include "SocketOverlap.h"

CSocketOverlap::CSocketOverlap()
{
	memset(&m_overLapped,0,sizeof(WSAOVERLAPPED));
	m_socket = NULL;
	//m_listenSock = NULL;
	memset(m_szBuf,0,sizeof(m_szBuf));
	m_nIoType = TYPE_UNKNOW;
	m_overLapped.hEvent = WSACreateEvent();

}

CSocketOverlap::~CSocketOverlap(void)
{

	
}
