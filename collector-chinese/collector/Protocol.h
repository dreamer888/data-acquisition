#pragma once


/*
���οƼ�
QQ  750339960
MOBILE  18665802636
*/

#define  WM_PARSE_PACKAGE WM_USER+ 803
#define  MAX_RECVIVE_BUFFER        256  //max  package length 

#define  MAX_DATA_LENGTH		 256//  4096  
/*
4k ��������, �������ݰ�,���ó���4k, �趨һ�����ƣ�
�ǳ����ݴ��ʩ������data ���ȳ��ִ�����Ȼ���޴�������,
���������Ҫ���ݾ���Ӧ��������ʵ�������
���ڱ��ͻ�ϵͳ���µ������ļ��ĳ��ȣ�������������Ϊ4K
*/



# define  PACK_START1  0xAA   // ���е�ͨѶ���ĵ���ʼ�������ֽ� 0xAA 0xBB,�������ñ��Ľ�β��ͨ�����ݰ��ĳ��ȣ����Խ�������β
# define  PACK_START2  0xBB

#define  CMMD_NORMAL_DATA 0          //��λ���ϴ����������� 
#define  CMMD_CONTROL_UPGRADE 1   //��λ���������ָ���豸��ϵͳ
#define  CMMD_CONTROL_ON 2         //��λ��������ָ�����豸
#define  CMMD_CONTROL_OFF 3           //��λ������ر�ָ�����豸
#define  CMMD_CONTROL_SYNC_TIME 4      //��λ������ͬ����λ��ʱ�䣬���ڽ�����λ��ʱ��
#define  CMMD_HEART_BEAT  5   
/*
�ϱ��豸״̬�� �豸���������ϱ�����Ϊ
    zigebee�����panid��ʮ��������ֵ�� , zigbee���籾����ַ��ʮ��������ֵ��,�ϱ�ʱ�䣨��ʽ�ַ��� YYYY-MM-DD HH-MM-SS������
��ʱ�ϱ���ʱ�����ݶ�Ϊһ���ӣ�  
�������Ҫ��λ����Ӧ�� 
��λ�����������ݴ�������ݿ⣬��λ������ʱ�����ֶ�����豸��״̬
*/


//��ͷ  0xAA 0xBB

//# ���ݰ���ֻ�а�ͷ0xAA 0xBB�� �������ý�β��ͨ�����ݰ��ĳ��ȣ����Խ�������β



typedef  struct TagClientDataStruct  
{
	unsigned short  netId;		//zigbee�����
	unsigned short netAddr;  //zigbee��ַ
	unsigned  short event;  //�¼�����, 0-������1-�ػ���2-̧��3-���£�4 ����
	char      time[19]; //ʱ��
	unsigned  short steps;  // ���߲���
	char   empyoyeeNo[10];   //Ա�����
	char   processNo[24];    //�����
	char   modelNo[8];    //�ͺ�
}TagClientPacketrStruct, *PTagClientPacketrStruct;


typedef  struct TagPacketHeaderStruct   
{
	//unsigned short start;
	unsigned short cmmd;
	unsigned short serialNo;
	unsigned short dataLength;
}TagPacketHeaderStruct, *PTagPacketHeaderStruct; 

/* 
unsigned short cmmd
0 --��λ�� ����λ�����͵���ͨ���ݣ�netId,netAddr,event,steps�������ָ���Ҫ�Է���Ӧ,
1--��λ��������λ������ϵͳ����λ����Ҫ��Ӧ�����
2--��λ�����������λ���豸�����󣬱��翪�ػ��� ��λ����Ҫ��Ӧ����
3--...
*/

/*
unsigned short serialNo
����λ����Ҫ��������л�Ӧȷ�ϵģ���Ҫ�������кţ� ���������Σ����ֶκ��ԣ�������������û��ʵ������
������ͻ�Ӧ����ʹ��ͬһ�����к�
*/

/*
unsigned short dataLength; 
Ҫ��������ݵĳ��ȣ�
Ҳ���� data�ֶεĳ��� 

*/

/*
char* data;
��Ҫ��������ݣ� 
*/

typedef  struct TagPacketStruct
{
	unsigned short cmmd;
	unsigned short serialNo;
	unsigned short dataLength;  
	char* data;  
}TagPacketStruct, *PTagPacketStruct; 


/*
sample:

��ʼ�����ֽ� 0xAA 0xBB

cmmd = 0x0000
serialNo = 0x0006
dataLength =0x0008

dataָ��һ���ṹ�� TagClientDataStruct�� ��ֵ���� ��

netId=0x1001
netAddr=0x2002  
event =0x0000 ; 
time="2016-11-30 11:06:18" 
steps =0x0100
empyoyeeNo="0100101001"        //[10];   //Ա�����
processNo="301302303304305306307308"     //[24];    //�����
modelNo="3902.601"              //[8]; �ͺ�

�����������ݰ���
0xaa 0xbb 0x0000 0x0006 0x0008 0x1001 0x2002  0x0000  0x0100 0x0042


0xaa 0xbb 0x0000 0x0006 0x0008 0x1001 0x2002  0x0000  0x0100 0x0042
ȥ��ǰ׺0x �� ���������ڵ������֣���ʮ������ ���� ����
aa bb 0000 0006  0008 1001 2002 0000 0100 0042


aabb00000006000810012002000001000042
*/

typedef  struct TagIpPacketStruct
{
	TagPacketStruct pack;
	 
	char* ip;
}TagIpPacketStruct, *PTagIpPacketStruct;


typedef  struct TagFullPacketStruct
{
	unsigned short  start;
	unsigned short cmmd;
	unsigned short serialNo;
	unsigned short dataLength;
	char* data;
	unsigned   short   checksum;
}TagFullPacketStruct, *PTagFullPacketStruct;



class CProtocol
{
public:
	CProtocol(void);
	~CProtocol(void);

	

	 int 				m_nReviceBufferCount;
	 int 				m_nPackLength; //��Ҫ���յİ��ĳ��ȣ��Ӱ�ͷ�н���������

	BOOL                m_bHasStartFlag1;
	BOOL                m_bHasStartFlag2;

	char				m_cLastChar;
	char				m_packHead[6]; 
	char				m_checkSum[2];

	int					m_nPackDataLen;
	TagPacketStruct     m_PacketStruct;
	TagPacketHeaderStruct  m_PacketHeaderStruct;
	BOOL				GetPackage(char ch);

	BOOL                ParsePackage();
	int					GetPackDataLen(TagPacketStruct*pack);

	BOOL				DealNormalChar(char ch);
	void				InitEnv();
	void				CleanEnv();

	BOOL				LoopBuffer( char *  buffer,int len);
	unsigned short 		CheckSum();
	unsigned short      CheckSum(char *  buffer, int len);
	unsigned short 	CProtocol::CheckSum(unsigned short cmmd, unsigned short serial,unsigned short length, char* data);

	static unsigned short     GetSerialNo();
	

	CWnd*			 m_pOwner; 
	HWND			m_hwnd;
	char * m_ip;   
	unsigned short  m_netId; //

};
