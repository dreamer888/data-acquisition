// DialogAddDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "DialogAddDevice.h"
#include "afxdialogex.h"


// CDialogAddDevice 对话框

IMPLEMENT_DYNAMIC(CDialogAddDevice, CDialogEx)

CDialogAddDevice::CDialogAddDevice(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DEVICE, pParent)
	, m_name(_T(""))
	, m_description(_T(""))
	, m_panId(_T(""))
	, m_netAddress(_T(""))
{

}

CDialogAddDevice::~CDialogAddDevice()
{
}

void CDialogAddDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT4, m_description);
	DDX_Text(pDX, IDC_EDIT2, m_panId);
	DDX_Text(pDX, IDC_EDIT3, m_netAddress);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
}


BEGIN_MESSAGE_MAP(CDialogAddDevice, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogAddDevice::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogAddDevice::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogAddDevice::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialogAddDevice 消息处理程序


void CDialogAddDevice::OnBnClickedOk()
{
	
	CDialogEx::OnOK();
}


void CDialogAddDevice::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL CDialogAddDevice::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


//add
void CDialogAddDevice::OnBnClickedButton1()
{
 
	CString  tszSQL, where;
	CString  ip;

	UpdateData(TRUE);

	m_ip.GetWindowText(ip);
	where.Format(_T("where ip= \'%s\' and zigbee_address=\'%s\'"), ip, m_netAddress);
	tszSQL.Format(_T("select table_id  FROM table_device  "));
	tszSQL += where;
	if (CheckExist(tszSQL) == -1)
	{
		AfxMessageBox(_T("record exists  already !"));
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();
	try
	{
		_variant_t RecordsAffected;
		int nCount = 0;
		TCHAR tszSQL[512];
	 
	

		_SYSTEMTIME st;
		GetLocalTime(&st);// / GetLocalTime();
						  //t = GetCurrentTime();  //UTC 1974 
						  //name, description, type, ip, pan_id, zigbee_address, device_status, time
		CString time;
		CString status = _T("off");
		int type = 1;//终端
		time.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		CString strDateTime;
		strDateTime.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)time);



		if (m_netAddress.IsEmpty())
			type = 0; //网关
					  // table_id  自动生成的no
		_stprintf(tszSQL, _T("INSERT INTO table_device ( name,description,type,ip,pan_id,zigbee_address,device_status,time) VALUES (\'%s\',\'%s\',%d ,\'%s\',\'%s\',\'%s\',\'%s\',%s )"),
			m_name, m_description, type, ip, m_panId, m_netAddress, status, strDateTime);

		HRESULT hr = app->m_database.m_pConnection->Execute((_bstr_t)tszSQL, &RecordsAffected, adCmdText);
		if (!SUCCEEDED(hr))
		{
			app->WriteLog(_T("fail to excute sql."));
		 
		}

	}
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		app->WriteLog(strErrorMsg.GetBuffer());
		//return  ;
	}

}

BOOL  CDialogAddDevice::CheckExist(CString tszSQL)
{
_RecordsetPtr pRecordset;
CcollectorApp *app = (CcollectorApp *)AfxGetApp();

try
{
	_variant_t RecordsAffected;
	//CString tszSQL = _T("select * from table_device");
	CString strTemp = _T("");

	HRESULT hr = pRecordset.CreateInstance(_T("ADODB.Recordset"));
	if (!SUCCEEDED(hr))
	{
		TRACE(_T("ADO Recordset - CreateInstance failed."));

		return FALSE;
	}
 
	hr = pRecordset->Open((_bstr_t)tszSQL,
		_variant_t((IDispatch*)app->m_database.m_pConnection, true),
		adOpenStatic, adLockOptimistic, adCmdText);
	if (!SUCCEEDED(hr))
	{
		TRACE(_T("fail to open recordset !"));
		return false;
	}

	if (!pRecordset->adoEOF)
	{
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
		return -1;
	}
	else
	{
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
		return TRUE;
	}
	 
}//try
catch (_com_error e)
{
	CString strErrorMsg = _T("");
	strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
	TRACE(strErrorMsg);
	
	if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
 

	return FALSE;
}

return TRUE;

}
