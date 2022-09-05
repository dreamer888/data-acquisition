#include "StdAfx.h"
#include "Protocol.h"


/*
���οƼ�
QQ  750339960
MOBILE  18665802636
*/

CProtocol::CProtocol(void)
{
	InitEnv();
}

CProtocol::~CProtocol(void)
{
	CleanEnv();	
}

void CProtocol::InitEnv()
{
	m_nReviceBufferCount=0;
	m_nPackLength = 0;

	m_bHasStartFlag1=FALSE;
	m_bHasStartFlag2=FALSE;
	//m_bHasPack= FALSE;
	//m_packData =NULL;
	m_nPackDataLen=0;	
	m_cLastChar = 0xFF;
	memset((char*)&m_PacketHeaderStruct,0, sizeof(m_PacketHeaderStruct));
	memset((char*)&m_PacketStruct, 0 ,sizeof(m_PacketStruct));
	m_PacketStruct.data =  NULL;
	//m_pBuffer = new char[MAX_RECVIVE_BUFFER];
}

void CProtocol::CleanEnv()
{
	if(m_PacketStruct.data!=NULL)
	{
      delete []m_PacketStruct.data;
	  m_PacketStruct.data =NULL;
	}
}


BOOL CProtocol::DealNormalChar(char ch)
{
	    if(m_nReviceBufferCount<sizeof(TagPacketHeaderStruct))
		{
			m_packHead[m_nReviceBufferCount]=ch;
		}				
		else if(m_nReviceBufferCount>=sizeof(TagPacketHeaderStruct)  &&  m_nReviceBufferCount< m_nPackLength)
		{
			m_PacketStruct.data[m_nReviceBufferCount-sizeof(TagPacketHeaderStruct)] = ch;
		}
		else if (m_nReviceBufferCount >= m_nPackLength  && m_nReviceBufferCount < m_nPackLength + 2)
		{
			m_checkSum[m_nReviceBufferCount- m_nPackLength] = ch;
		}
		   

		m_nReviceBufferCount++;
		m_cLastChar = ch;

		if(m_nReviceBufferCount ==sizeof(TagPacketHeaderStruct))//�������һ����ͷ��
		{
			m_PacketHeaderStruct = *((TagPacketHeaderStruct*)((char*)m_packHead));
			m_nPackDataLen =ntohs(m_PacketHeaderStruct.dataLength);

			m_PacketStruct.cmmd= ntohs(m_PacketHeaderStruct.cmmd);
			m_PacketStruct.serialNo = ntohs(m_PacketHeaderStruct.serialNo);
			m_PacketStruct.dataLength= ntohs(m_PacketHeaderStruct.dataLength);
			 
			if (m_PacketStruct.dataLength > MAX_DATA_LENGTH) // ��Ϊ���ݴ����쳣
			{
				CleanEnv();
				InitEnv();
				return FALSE;
			}
			 
			if (m_PacketStruct.dataLength > 0)
			{
				m_PacketStruct.data = new char[m_PacketStruct.dataLength];
			}
			
			/*
			else if(m_PacketStruct.dataLength==0)//�� ����Ҫ����,,ֱ�ӽ�����
			{
				ParsePackage();
				CleanEnv();
				InitEnv();
				return  TRUE;
			}
			*/

			m_nPackLength = sizeof(TagPacketHeaderStruct)+m_PacketStruct.dataLength;
			//return  TRUE;

		}

		if(m_nReviceBufferCount>sizeof(TagPacketHeaderStruct) && m_nReviceBufferCount==m_nPackLength+2)//�Ѿ��������һ������	
		{
			unsigned short  checksum = CheckSum();  
			//unsigned short  checksum = CheckSum(m_PacketStruct.cmmd, m_PacketStruct.serialNo, m_PacketStruct.dataLength, m_PacketStruct.data);
			if (ntohs(*((unsigned short*)m_checkSum)) == checksum)
			//if (TRUE)
			{
				ParsePackage();
				CleanEnv();
				InitEnv();
				return  TRUE;
			}
			else
			{
				CleanEnv();
				InitEnv();
				return  FALSE;
			}
		}
	
	return  TRUE;

}

BOOL CProtocol::GetPackage(char ch)
{
  
	
  if(PACK_START1==(unsigned char)ch)
  {
	  if(m_bHasStartFlag1==FALSE)  //������ͷ
	  {
		m_bHasStartFlag1 = TRUE;
		//m_nReviceBufferCount=1;
		m_cLastChar = ch;
		//m_nReviceBufferCount =0;
		return TRUE;

	  }
	  else if(m_bHasStartFlag2==FALSE )//��ͷ���󣬶�����һ��0xAA,�Դ���Ϊ��ʼ�ַ����¿�ʼ  0xAAAA
	  {
		m_bHasStartFlag1= TRUE;
		m_cLastChar = ch;
		//m_nReviceBufferCount =0;
		return TRUE;
	  }
	  else     //0xAABB...0xAA  //��Ϊ���ݴ���
	  {
		return DealNormalChar(ch);

	  }	
  }
  else if(PACK_START2==(unsigned char)ch)
  {
	  if((unsigned char)m_cLastChar==PACK_START1) //0xAABB
	  {
		m_bHasStartFlag1=TRUE;
		m_bHasStartFlag2=TRUE;
		m_cLastChar = ch;

	  }
	  else if(m_bHasStartFlag2)//��������  0xAA0xBB...0xBB...
	  {
		return DealNormalChar(ch);
	  }
	  else  //0xBB  // ����ֱ���������ַ���  ����Ҫ���³�ʼ������Ϊ�������ʹ��ڳ�ʼ��״̬ 
	  {
		//m_bHasStartFlag1 = FALSE;
		  return  FALSE;  
		
	  }
  }
  else if(m_bHasStartFlag2==TRUE) //������������ 
  {
	return DealNormalChar(ch);
  }
  else //�������ݣ�����ʼ��
  {
	 return  FALSE;
  }
	return  TRUE;
}


BOOL CProtocol::LoopBuffer( char *  buffer,int len)
{
	for (int i = 0; i < len; i++)
	{
		GetPackage(buffer[i]);
	}

	return  TRUE;
}

BOOL  CProtocol::ParsePackage()
{
	//m_PacketStruct
	//::SendMessage(m_pOwner->m_hWnd, WM_PARSE_PACKAGE, (WPARAM)0, (LPARAM)&m_PacketStruct);

	TagIpPacketStruct  ipPack;
	ipPack.ip = this->m_ip;
	ipPack.pack = m_PacketStruct;
	m_netId = ntohs(*((unsigned short *)m_PacketStruct.data)); 
	::SendMessage(m_hwnd, WM_PARSE_PACKAGE, (WPARAM)0, (LPARAM)&ipPack);
	return  TRUE;
}

int	CProtocol::GetPackDataLen(TagPacketStruct*pack)
{
  int len =    * ((int*)((char*)pack+4));  //pointer to  unsigned short dataLength;  
  return len;
}

unsigned short 	CProtocol::CheckSum(char *  buffer, int len)
{
	unsigned short sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum = (sum+buffer[i]) % 65535;
	}
	
	return  sum;
}




unsigned short 	CProtocol::CheckSum()
{
	unsigned short sum = 0;
	for (int i = 0; i<sizeof(m_packHead); i++)
		sum =(sum+ m_packHead[i]) % 65535;
	
	for (int i = 0; i<m_PacketStruct.dataLength; i++)
		sum = (sum+ m_PacketStruct.data[i]) % 65535;
	

	return  sum;
}

// ��ʼλ������У��
unsigned short 	CProtocol::CheckSum( unsigned short cmmd, unsigned short serial,unsigned short length, char* data)
{
	char head[6];
	char * pHead = head;
	unsigned short sum = 0;
	
	*((int*)pHead) = cmmd;
	pHead += sizeof(unsigned short);
	*((int*)pHead) = serial;
	pHead += sizeof(unsigned short);
	 
	*((int*)pHead) = length;
	

	for(int i=0; i<sizeof(head); i++)
		sum  = (sum+ head[i] ) % 65535;;
	
	for(int i = 0; i<length; i++)
		sum = (sum+data[i]) % 65535;
	

	return  sum;
}

 unsigned short  CProtocol::   GetSerialNo()
{
	if (true)
	{
		static  unsigned short num = 0;
		num = (num + 1) % 65535;
		return  num;
	}
	else
		return 1;  //for  test  purpose
}


/*
CheckSum(unsigned short cmmd, unsigned short serial,unsigned short length, char* data)

*/