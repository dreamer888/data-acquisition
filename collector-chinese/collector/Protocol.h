#pragma once


/*
唤梦科技
QQ  750339960
MOBILE  18665802636
*/

#define  WM_PARSE_PACKAGE WM_USER+ 803
#define  MAX_RECVIVE_BUFFER        256  //max  package length 

#define  MAX_DATA_LENGTH		 256//  4096  
/*
4k 下载数据, 单个数据包,不得超过4k, 设定一个限制，
是程序容错措施，避免data 长度出现错误，仍然无限处理的情况,
这个长度需要根据具体应用情况做适当的修正
对于本客户系统更新的配置文件的长度，我们暂且限制为4K
*/



# define  PACK_START1  0xAA   // 所有的通讯报文的起始，两个字节 0xAA 0xBB,不再设置报文结尾，通过数据包的长度，可以解析出结尾
# define  PACK_START2  0xBB

#define  CMMD_NORMAL_DATA 0          //下位机上传正常的数据 
#define  CMMD_CONTROL_UPGRADE 1   //上位机请求更新指定设备的系统
#define  CMMD_CONTROL_ON 2         //上位机请求开启指定的设备
#define  CMMD_CONTROL_OFF 3           //上位机请求关闭指定的设备
#define  CMMD_CONTROL_SYNC_TIME 4      //上位机请求同步下位机时间，用于矫正下位机时间
#define  CMMD_HEART_BEAT  5   
/*
上报设备状态， 设备心跳包，上报数据为
    zigebee网络的panid（十六进制数值） , zigbee网络本机地址（十六进制数值）,上报时间（格式字符串 YYYY-MM-DD HH-MM-SS），；
定时上报，时间间隔暂定为一分钟；  
本命令不需要上位机回应； 
上位机将心跳数据存放与数据库，上位机程序定时或者手动检查设备的状态
*/


//包头  0xAA 0xBB

//# 数据包，只有包头0xAA 0xBB， 不再设置结尾，通过数据包的长度，可以解析出结尾



typedef  struct TagClientDataStruct  
{
	unsigned short  netId;		//zigbee网络号
	unsigned short netAddr;  //zigbee网址
	unsigned  short event;  //事件类型, 0-开机，1-关机，2-抬起，3-放下，4 剪线
	char      time[19]; //时间
	unsigned  short steps;  // 行走步数
	char   empyoyeeNo[10];   //员工编号
	char   processNo[24];    //工序号
	char   modelNo[8];    //型号
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
0 --下位机 向上位机发送的普通数据（netId,netAddr,event,steps），这个指令不需要对方回应,
1--上位机请求下位机更新系统，下位机需要回应此命令，
2--上位机请求控制下位机设备的请求，比如开关机， 下位机需要回应命令
3--...
*/

/*
unsigned short serialNo
上下位机需要对命令进行回应确认的，需要设置序列号， 其他的情形，该字段忽略，可以任意设置没有实际意义
请求包和回应包，使用同一个序列号
*/

/*
unsigned short dataLength; 
要传输的数据的长度，
也就是 data字段的长度 

*/

/*
char* data;
需要传输的数据， 
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

起始两个字节 0xAA 0xBB

cmmd = 0x0000
serialNo = 0x0006
dataLength =0x0008

data指向一个结构体 TagClientDataStruct， 赋值如下 ：

netId=0x1001
netAddr=0x2002  
event =0x0000 ; 
time="2016-11-30 11:06:18" 
steps =0x0100
empyoyeeNo="0100101001"        //[10];   //员工编号
processNo="301302303304305306307308"     //[24];    //工序号
modelNo="3902.601"              //[8]; 型号

该完整的数据包是
0xaa 0xbb 0x0000 0x0006 0x0008 0x1001 0x2002  0x0000  0x0100 0x0042


0xaa 0xbb 0x0000 0x0006 0x0008 0x1001 0x2002  0x0000  0x0100 0x0042
去掉前缀0x 后 拷贝到串口调试助手，按十六进制 发送 即可
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
	 int 				m_nPackLength; //将要接收的包的长度，从包头中解析出来的

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
