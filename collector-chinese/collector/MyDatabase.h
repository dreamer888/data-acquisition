#pragma once

//#include  "util.h"


#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")



class CMyDatabase
{
public:
	CMyDatabase();
	virtual ~CMyDatabase();

	 bool InitDataBase();
	 bool ExitDataBase();

	 _ConnectionPtr  GetConnectPtr();

public :

	//CString m_strConnectString;
	 _ConnectionPtr m_pConnection;
	//_ConnectionPtr m_pConnBackup;

	
};

