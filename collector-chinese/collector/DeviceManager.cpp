// DeviceManager.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "DeviceManager.h"
#include "afxdialogex.h"

#include "DialogAddDevice.h"
#include "DialogSearch.h"
#include "util.h"  


// CDeviceManager 对话框

IMPLEMENT_DYNAMIC(CDeviceManager, CDialogEx)

CDeviceManager::CDeviceManager(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DEVICE_MANAGER, pParent)
	 
{

}

CDeviceManager::~CDeviceManager()
{
}

void CDeviceManager::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
	DDX_Control(pDX, IDC_COMBO1, m_ip1);
	DDX_Control(pDX, IDC_COMBO3, m_ip2);
	DDX_Control(pDX, IDC_COMBO4, m_address1);
	DDX_Control(pDX, IDC_COMBO5, m_address2);
	//DDX_CBIndex(pDX, IDC_COMBO2, m_timer);
	//DDV_MinMaxInt(pDX, m_timer, 5, 3000);
	DDX_Control(pDX, IDC_COMBO2, m_combox_timer);
}


BEGIN_MESSAGE_MAP(CDeviceManager, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeviceManager::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDeviceManager::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDeviceManager::OnBnClickedButton2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDeviceManager::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDeviceManager::OnNMDblclkList1)
 
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDeviceManager::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON8, &CDeviceManager::OnBnClickedButton8)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDeviceManager::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CDeviceManager 消息处理程序

BOOL CDeviceManager::IintListItem()
{


	m_listctrl.SetSortable(TRUE);
	//m_listctrl.SetEditable();


	m_listctrl.InsertColumn(0, _T("名稱"));
	m_listctrl.InsertColumn(1, _T("IP"));
	m_listctrl.InsertColumn(2, _T("Net id")); //添加列名
	m_listctrl.InsertColumn(3, _T("Net addr"));
	m_listctrl.InsertColumn(4, _T("狀態"));
	m_listctrl.InsertColumn(5, _T("時間"));
	m_listctrl.InsertColumn(6, _T("描述"));

	m_listctrl.SetColumnWidth(0, 150); //设置列宽
	m_listctrl.SetColumnWidth(1, 150);
	m_listctrl.SetColumnWidth(2, 100);
	m_listctrl.SetColumnWidth(3, 100);
	m_listctrl.SetColumnWidth(4, 100);
	m_listctrl.SetColumnWidth(5, 200);
	m_listctrl.SetColumnWidth(6, 315);



	m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listctrl.SetCheckboxeStyle(RC_CHKBOX_NORMAL);


	return TRUE;

}


BOOL CDeviceManager::LoadListItem()
{
 
	IintListItem();

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

			return false;
		}

		strTemp = _T("'");
		//strTemp += _T("%");

		//m_tszSQL.Format(_T("SELECT   *   FROM table_log"));
		//tszSQL += strTemp;

		//strTemp.Format(_T(" GROUP BY %s"), m_strKeyName);
		//tszSQL += strTemp;
		m_tszSQL = _T("select * from table_device");
		hr = pRecordset->Open((_bstr_t)m_tszSQL,
			_variant_t((IDispatch*)app->m_database.m_pConnection, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("fail to open recordset !"));
			return false;
		}

		if (pRecordset->adoEOF)
		{
			//this->ShowWindow(0);
 

			return false;

		}


		//pRecordset->Move(this->m_pageIndex*m_pageCount);
		//pRecordset->MoveFirst();

		 
		//m_listctrl.DeleteAllItems();
		int nCount = 0;
		while (!pRecordset->adoEOF)
			//while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;


				v = pRecordset->GetCollect(_variant_t((long)1));
				nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
				//if (v.vt != VT_I4) break;
				//nStudyId = v.lVal;
				strTemp = pRecordset->GetCollect(_variant_t((long)4));
				m_listctrl.SetItemText(nCount, 1, strTemp);
				//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);


				//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
				//m_listctrl.SetItemText(nCount, 2, strTemp);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
				m_listctrl.SetItemText(nCount, 2, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
				m_listctrl.SetItemText(nCount, 3, strTemp);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
				m_listctrl.SetItemText(nCount, 4, strTemp);

  
 
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
				m_listctrl.SetItemText(nCount, 5, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
				m_listctrl.SetItemText(nCount, 6, strTemp);
			 
				 
 

			pRecordset->MoveNext();
		 
  
		}
		//m_listBox.Invalidate();
		//pRecordset->Close();
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return false;
	}



	return TRUE;

}


void CDeviceManager::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogAddDevice  dlg;
	dlg.DoModal();
}


void CDeviceManager::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	TCHAR param[50];

	UpdateData(TRUE);
	//_itot(m_timer, param,10);
	this->GetDlgItem(IDC_COMBO2)->GetWindowText(param, sizeof(param));
	if (_tcscmp(param, _T(""))==0)
	{
		_tcscpy(param, _T("0"));
	}
	WritePrivateProfileString(_T("device"), _T("timer"), param, _T("config.ini"));

	this->GetDlgItem(IDC_COMBO1)->GetWindowText(param, sizeof(param));
	WritePrivateProfileString(_T("device"), _T("ip1"), param, _T("config.ini"));
	this->GetDlgItem(IDC_COMBO3)->GetWindowText(param, sizeof(param));
	WritePrivateProfileString(_T("device"), _T("ip2"), param, _T("config.ini"));
	this->GetDlgItem(IDC_COMBO4)->GetWindowText(param, sizeof(param));
	WritePrivateProfileString(_T("device"), _T("zigbee_address1"), param, _T("config.ini"));
	this->GetDlgItem(IDC_COMBO5)->GetWindowText(param, sizeof(param));
	WritePrivateProfileString(_T("device"), _T("zigbee_address2"), param, _T("config.ini"));

	CcollectorApp *app = (CcollectorApp *)AfxGetApp();
	//app->m_dlg.RefreshList();
	::PostMessage(app->m_hwnd, WM_FRESH_LIST,0,0);

	CDialogEx::OnOK();
}


void CDeviceManager::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

	int dwStates = RC_ITEM_CHECKED;
	//m_listctrl.DeleteAllItems(RC_ITEM_CHECKED);
	int nItemCount = m_listctrl.GetItemCount();
	for (int i = 0; i < nItemCount; i++)
	{
		if (m_listctrl.ExamItemStates(i, dwStates))
		{
			CString  ip, panId, netAddress;
			ip = m_listctrl.GetItemText(i, 1).Trim();
			panId = m_listctrl.GetItemText(i, 2).Trim();
			netAddress = m_listctrl.GetItemText(i, 3).Trim();
		

			CcollectorApp *app = (CcollectorApp *)AfxGetApp();
			try
			{
				_variant_t RecordsAffected;
		 	 
				CString tszSQL;
				CString  where;
				where.Format(_T("where ip= \'%s\' and zigbee_address=\'%s\'"), ip, netAddress);
				tszSQL.Format(_T("delete  FROM table_device  "));
				tszSQL += where;
  
				HRESULT hr = app->m_database.m_pConnection->Execute((_bstr_t)tszSQL, &RecordsAffected, adCmdText);
				if (!SUCCEEDED(hr))
				{
					app->WriteLog(_T("fail to excute sql."));
		 
				}

			}//try
			catch (_com_error e)
			{
				CString strErrorMsg = _T("");
				strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
				TRACE(strErrorMsg);
				app->WriteLog(strErrorMsg.GetBuffer());
				return  ;
			}

			m_listctrl.DeleteItem(i--);
			nItemCount--;
			//nDelCount++;
		}
	}
}


void  CDeviceManager::InitControls()
{
	m_combox_timer.AddString(_T(""));
	m_combox_timer.AddString(_T("10"));
	m_combox_timer.AddString(_T("20"));
	m_combox_timer.AddString(_T("30"));
	m_combox_timer.AddString(_T("40"));
	m_combox_timer.AddString(_T("50"));
	m_combox_timer.AddString(_T("60"));
	m_combox_timer.AddString(_T("70"));
	m_combox_timer.AddString(_T("80"));
	m_combox_timer.AddString(_T("90"));
	m_combox_timer.AddString(_T("100"));
	m_combox_timer.AddString(_T("110"));
	m_combox_timer.AddString(_T("120"));

	m_ip1.AddString(_T(""));
	m_ip2.AddString(_T(""));
	m_address1.AddString(_T(""));
	m_address2.AddString(_T(""));

	TCHAR para[50];

	int   timer=GetPrivateProfileInt(_T("device"), _T("timer"), 20, _T("config.ini"));
	GetPrivateProfileString(_T("device"), _T("timer"), _T(""), para, sizeof(para), _T("config.ini"));
	this->GetDlgItem(IDC_COMBO2)->SetWindowText(para);
	GetPrivateProfileString(_T("device"), _T("ip1"), _T(""), para, sizeof(para), _T("config.ini"));
	m_ip1.SetWindowText( para);
	GetPrivateProfileString(_T("device"), _T("ip2"), _T(""), para, sizeof(para), _T("config.ini"));
	m_ip2.SetWindowText(para);
	GetPrivateProfileString(_T("device"), _T("zigbee_address1"), _T(""), para, sizeof(para), _T("config.ini"));
	m_address1.SetWindowText(para);
	GetPrivateProfileString(_T("device"), _T("zigbee_address2"), _T(""), para, sizeof(para), _T("config.ini"));
	m_address2.SetWindowText(para);

	UpdateData(0);
	m_timeId = 0;
	if (timer>0)
		this->SetTimer(m_timeId, timer * 1000, NULL);

	_RecordsetPtr pRecordset;
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();
	try
	{
		_variant_t RecordsAffected;

		CString where = _T("");
		CString ip1, ip2, address1, address2, strTemp;

		HRESULT hr = pRecordset.CreateInstance(_T("ADODB.Recordset"));
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("ADO Recordset - CreateInstance failed."));

			return  ;
		}
		m_tszSQL = _T("select distinct  ip  from table_device  ");
		hr = pRecordset->Open((_bstr_t)m_tszSQL,
			_variant_t((IDispatch*)app->m_database.m_pConnection, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("fail to open recordset !"));
			return  ;
		}
		 
		while (!pRecordset->adoEOF)
		{
			CString strTemp;
			strTemp = pRecordset->GetCollect(_variant_t((long)0));
			strTemp = strTemp.Trim();
			m_ip1.AddString(strTemp);
			m_ip2.AddString(strTemp);
			pRecordset->MoveNext();
		}
	 
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
		return  ;
	}
	if (pRecordset != NULL && pRecordset->State) pRecordset->Close();

	try
	{
		_variant_t RecordsAffected;

		CString where = _T("");
		CString ip1, ip2, address1, address2, strTemp;

		 
		m_tszSQL = _T("select distinct zigbee_address   from table_device  ");
		HRESULT hr = pRecordset->Open((_bstr_t)m_tszSQL,
			_variant_t((IDispatch*)app->m_database.m_pConnection, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("fail to open recordset !"));
			return;
		}
	 
		while (!pRecordset->adoEOF)
		{
			CString strTemp;
			strTemp = pRecordset->GetCollect(_variant_t((long)0));
			strTemp = strTemp.Trim();
			m_address1.AddString(strTemp);
			m_address2.AddString(strTemp);
			pRecordset->MoveNext();
		}

	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		if (pRecordset != NULL && pRecordset->State) pRecordset->Close();
		return;
	}
	if (pRecordset != NULL && pRecordset->State) pRecordset->Close();

    UpdateData(0);
	return; 
}
BOOL  CDeviceManager::RefreshList()
{
	
	UpdateData(TRUE);


	m_listctrl.DeleteAllItems();

	_RecordsetPtr pRecordset;
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	try
	{
		_variant_t RecordsAffected;
		 
		CString where = _T("");
		CString ip1, ip2, address1, address2,strTemp;

		HRESULT hr = pRecordset.CreateInstance(_T("ADODB.Recordset"));
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("ADO Recordset - CreateInstance failed."));

			return false;
		}

		m_ip1.GetWindowTextW(ip1);
		m_ip2.GetWindowTextW(ip2);
		m_address1.GetWindowTextW(address1);
		m_address2.GetWindowTextW(address2);

	
		m_tszSQL = _T("select * from table_device  ");

		if(ip1.IsEmpty() && ip2.IsEmpty() && address1.IsEmpty() && address2.IsEmpty() )
		     where = _T("");
		else 
		    where = _T("where ");

			if (!ip1.IsEmpty())
			{
				strTemp.Format(_T("ip>=\'%s\'"), ip1);
				where += strTemp;
			}

			if (!ip2.IsEmpty())
			{
				if (!ip1.IsEmpty())
				{
					where += _T(" And ");
				}
				strTemp.Format(_T("ip<=\'%s\'"), ip2);
				where += strTemp;
			}

			if (!address1.IsEmpty())
			{
				if (!(ip1.IsEmpty() && ip2.IsEmpty()))
				{
					where += _T(" And ");
				}
				strTemp.Format(_T("zigbee_address>=\'%s\'"), address1);
				where += strTemp;
			}

			if (!address2.IsEmpty())
			{
				if (!(ip1.IsEmpty() && ip2.IsEmpty() && address1.IsEmpty()))
				{
					where += _T(" And ");
				}
				strTemp.Format(_T("zigbee_address<=\'%s\'"), address2);
				where += strTemp;
			}

		m_tszSQL += where;

		hr = pRecordset->Open((_bstr_t)m_tszSQL,
			_variant_t((IDispatch*)app->m_database.m_pConnection, true),
			adOpenStatic, adLockOptimistic, adCmdText);
		if (!SUCCEEDED(hr))
		{
			TRACE(_T("fail to open recordset !"));
			return false;
		}

		if (pRecordset->adoEOF)
		{
	
			return false;

		}

	
		int nCount = 0;
		int timeout = GetPrivateProfileInt(_T("KeepAlive"), _T("timeout"), 60, _T("config.ini"));
		while (!pRecordset->adoEOF)
			//while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;


			v = pRecordset->GetCollect(_variant_t((long)1));
			nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
			//if (v.vt != VT_I4) break;
			//nStudyId = v.lVal;
			strTemp = pRecordset->GetCollect(_variant_t((long)4));
			m_listctrl.SetItemText(nCount, 1, strTemp);
			//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);


			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
			m_listctrl.SetItemText(nCount, 2, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
			m_listctrl.SetItemText(nCount, 3, strTemp);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
			//m_listctrl.SetItemText(nCount, 4, strTemp);



			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
			int y, mm, d, h, m, s;
			char buf[40];
			WCharToMByte(strTemp.GetBuffer(), buf, sizeof(buf));
			sscanf(buf, "%04d-%02d-%02d %02d:%02d:%02d", &y, &mm, &d, &h, &m, &s);

			CTime time1(y, mm, d, h, m, s);// = CTime::GetCurrentTime();	
			_SYSTEMTIME st;
			GetLocalTime(&st);// / GetLocalTime();
			CTime time2(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			CTimeSpan timeSpan = time2 - time1; // 得到总的秒数
			int nTSeconds = timeSpan.GetTotalSeconds();
			if (nTSeconds > timeout)
			{
				m_listctrl.SetItemBkColor(nCount, 4, RGB(255, 0, 0));
				m_listctrl.SetItemTextColor(nCount, 4, RGB(255, 255, 255));
				m_listctrl.SetItemText(nCount, 4, _T("未知"));  //time
			}
			else
			{
				m_listctrl.SetItemBkColor(nCount, 4, RGB(0, 0, 255));
				m_listctrl.SetItemTextColor(nCount, 4, RGB(255, 255, 255));
				m_listctrl.SetItemText(nCount, 4, _T("開"));  //time
			}
			m_listctrl.SetItemText(nCount, 5, strTemp);  //time
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
			m_listctrl.SetItemText(nCount, 6, strTemp);




			pRecordset->MoveNext();


		}
		//m_listBox.Invalidate();
		//pRecordset->Close();
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return false;
	}



	return  TRUE;
}


BOOL CDeviceManager::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	IintListItem();

	InitControls();

	RefreshList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDeviceManager::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CDeviceManager::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	int nItem = pNMListView->iItem;
	if (nItem >= 0 && nItem<m_listctrl.GetItemCount())//判断双击位置是否在有数据的列表项上面
	{
		CString  ip, panId ,netAddress;
		ip = m_listctrl.GetItemText(nItem ,1).Trim();
		panId = m_listctrl.GetItemText(nItem, 2).Trim();
		netAddress = m_listctrl.GetItemText(nItem, 3).Trim();
		CDialogSearch  dlg;
		CString  where;
		where.Format(_T("where ip= \'%s\' and zigbee_address=\'%s\'"), ip, netAddress);
		dlg.m_tszSQL.Format(_T("SELECT   *   FROM table_log  "));
		dlg.m_tszSQL += where;
		dlg.m_pageCount = 100; 
		//AfxMessageBox(dlg.m_tszSQL);
		dlg.DoModal();
		
	}

	 

	*pResult = 0;
}

 

void CDeviceManager::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CDeviceManager::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	RefreshList();
}


void CDeviceManager::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	RefreshList();

	CDialogEx::OnTimer(nIDEvent);
}


void CDeviceManager::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR param[50];
	this->KillTimer(m_timeId);
	UpdateData(TRUE);
	
	this->GetDlgItem(IDC_COMBO2)->GetWindowText(param, sizeof(param));
	int timer = _ttoi(param);
	if (timer == 0)
		return; 
	m_timeId = (m_timeId + 1) % 100000;
 
	this->SetTimer(m_timeId, timer *1000,NULL);

	//m_listctrl.Invalidate();

	 
}
