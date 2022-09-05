#pragma once
#include "afxdlgs.h"
#include "MyFormView.h"

 
#define  MAX_FILE_NAME_LEN  30  //ϵͳ�ļ���������󳤶�
#define  MAX_FILE_LEN 1024* 50  //50k
#define  MAX_FILE_PACK_LEN   100//1024  //1k


class CMyPropertySheet :
	public CPropertySheet
{
public:
	CMyPropertySheet();
	virtual ~CMyPropertySheet();
	virtual BOOL OnInitDialog();

	int m_index;
	HWND  m_pHwnd;
	//bool  m_bApply;
};


struct TagPageControlStruct
{
	BOOL  checkAll;
	BOOL  checkIp;
	BOOL  checkNetId;
	BOOL   checkNetAddr;
	BOOL  controlCode;
	
	DWORD   ip;
	WORD  netId;
	WORD  netAddr;
	char  time[19];


};


struct TagPageUpgradeStruct
{
	BOOL  checkAll;
	BOOL  checkIp;
	BOOL  checkNetId;
	BOOL  checkNetAddr;

	DWORD ip;


	WORD  netId;
	WORD  netAddr;


	char  fileName[255]; //����ط����0
	char  fname[MAX_FILE_NAME_LEN];
	

};



struct TagUpgradeDataStruct
{
	unsigned short  netId;
	unsigned short   netAddr;

	unsigned short    totalPack; //�ܵ�pack���� 
	unsigned short    packNo;    //pack��� 
	unsigned short    packLen;  // �˴�Ϊ��ǰpack�ĳ��ȣ���׼pack�ĳ���ΪMAX_FILE_PACK_LEN 1024byte�� 
	char  fileName[30]; // ����30�� ����ط����0

	//36 bytes  
	char  * packData;  //packData[packLen];
};


/*


*/



