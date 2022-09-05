#include "stdafx.h"
#include "MyDatabase.h"

#define CONFIG  _T("config.ini")

CMyDatabase::CMyDatabase()
{
	m_pConnection = NULL;
}


CMyDatabase::~CMyDatabase()
{
}


_ConnectionPtr  CMyDatabase :: GetConnectPtr()
{
	return m_pConnection;
}
bool CMyDatabase::InitDataBase()
{
	HRESULT hr = m_pConnection.CreateInstance(_T("ADODB.Connection"));
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox(_T("Fail to create ADODB connection ! "));
		return  false;
	}

	TCHAR tszConn[256];
	//		CString strConn;

	try {

		TCHAR server[50];
		TCHAR database[50];
		TCHAR userid[50];
		TCHAR passwd[50];
		GetPrivateProfileString(_T("database"), _T("server"), _T("192.168.1.101\\HMKJ"), server, sizeof(server), CONFIG);
		GetPrivateProfileString(_T("database"), _T("database"), _T("hmkj"), database, sizeof(database), CONFIG);
		GetPrivateProfileString(_T("database"), _T("userid"), _T("sa"), userid, sizeof(userid), CONFIG);
		GetPrivateProfileString(_T("database"), _T("passwd"), _T("windows"), passwd, sizeof(passwd), CONFIG);
		_stprintf(tszConn, _T("Provider=SQLOLEDB;Server=%s;Database=%s;uid=%s;pwd=%s"), server, database, userid, passwd);

		
		hr = m_pConnection->Open((_bstr_t)tszConn, _T(""), _T(""), adModeUnknown); //ok 
		if (!SUCCEEDED(hr))
		{
			AfxMessageBox(_T("Fail to open database, plase check !"));
			m_pConnection.Release();
			m_pConnection = NULL;
			return  false;
		}
		
	}
	catch (_com_error e)
	{
		CString strErrorMsg;
		strErrorMsg.Format(_T("Database operator error!\r\nMessage:%s"), e.ErrorMessage());
		AfxMessageBox(strErrorMsg);
	}

	return   true;

}

bool CMyDatabase::ExitDataBase()
{
	
	if (m_pConnection && m_pConnection->State) 
	{
		m_pConnection->Close();
		m_pConnection = NULL;
	}

	return true;
}

