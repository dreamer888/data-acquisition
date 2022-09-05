// DialogSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "DialogSearch.h"
#include "afxdialogex.h"



#define IDC_DELICTRL  0x3400

// CDialogSearch 对话框

IMPLEMENT_DYNAMIC(CDialogSearch, CDialogEx)

CDialogSearch::CDialogSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

	//{ _T("start"), _T("stop"), _T("up"), _T("down"), _T("cut") };
	m_eventName[0].Format(TEXT("start"));
	m_eventName[1].Format(TEXT("stop"));
	m_eventName[2].Format(TEXT("tack"));
	m_eventName[3].Format(TEXT("power on"));
	m_eventName[4].Format(TEXT("power off"));
	m_eventName[5].Format(TEXT("cut"));
	m_eventName[6].Format(TEXT("break"));
}

CDialogSearch::~CDialogSearch()
{
}

void CDialogSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);

	DDX_Control(pDX, IDC_MFCBUTTON1, m_previous);
	DDX_Control(pDX, IDC_MFCBUTTON2, m_next);
	DDX_Control(pDX, IDC_MFCBUTTON3, m_first);
	DDX_Control(pDX, IDC_MFCBUTTON4, m_last);
	DDX_Control(pDX, IDC_MFCBUTTON5, m_btEvent);
}


BEGIN_MESSAGE_MAP(CDialogSearch, CDialogEx)
	ON_WM_SIZE()
	ON_WM_CREATE()

	ON_BN_CLICKED(IDC_MFCBUTTON1, &CDialogSearch::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CDialogSearch::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CDialogSearch::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CDialogSearch::OnBnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON5, &CDialogSearch::OnBnClickedMfcbutton5)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCBUTTON6, &CDialogSearch::OnBnClickedMfcbutton6)
END_MESSAGE_MAP()


// CDialogSearch 消息处理程序




BOOL CDialogSearch::LoadEvents()
{
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	



	return TRUE;

}



BOOL CDialogSearch::LoadListItem()
{
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	//m_pageCount = 50;
	m_pageIndex = 0;

	//CString strHead[] = { _T("网络号"),_T("网络地址"),_T("事件"),_T("步长"),_T("时间") };
	//m_listctrl.InsertColumn(6, strHead, DT_CENTER, NULL);

	for (int i = 0; i < 8; i++)
		m_event[i] = 0;

	m_listctrl.SetSortable(TRUE);
	m_listctrl.SetEditable();
	m_listctrl.SetCheckboxeStyle(RC_CHKBOX_NORMAL);
	m_listctrl.SortItems(0,TRUE);
	
	
	
		m_listctrl.InsertColumn(0, _T("記錄id"));
		m_listctrl.InsertColumn(1, _T("IP"));
		m_listctrl.InsertColumn(2, _T("Net id")); //添加列名
		m_listctrl.InsertColumn(3, _T("Net addr"));
		m_listctrl.InsertColumn(4, _T("事件"));
		m_listctrl.InsertColumn(5, _T("步長"));
		m_listctrl.InsertColumn(6, _T("僱員id"));
		m_listctrl.InsertColumn(7, _T("流程id"));
		m_listctrl.InsertColumn(8, _T("模型id"));

		m_listctrl.InsertColumn(9, _T("時間"));
	

	m_listctrl.SetColumnWidth(0, 90); //设置列宽
	m_listctrl.SetColumnWidth(1, 150); //设置列宽
	m_listctrl.SetColumnWidth(2, 90);
	m_listctrl.SetColumnWidth(3, 90);
	m_listctrl.SetColumnWidth(4, 90);
	m_listctrl.SetColumnWidth(5, 90);
	m_listctrl.SetColumnWidth(6, 90);
	m_listctrl.SetColumnWidth(7, 200);
	m_listctrl.SetColumnWidth(8, 90);
	m_listctrl.SetColumnWidth(9, 150);
	
	//int w = 90 * 7 + 150 * 2 +200;
	//w= 1130;
	// hscroll =20 ;

	m_listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listctrl.SortItems(0, TRUE);  // why not ok ??


	//_stprintf(tszSQL, _T("INSERT INTO table_log ( event_id,pan_id,zigbee_address,ip,steps,create_time) VALUES (%d,%d, %d ,\'%s\',%d ,%s )"),
	//	ntohs(dataPack->event), ntohs(dataPack->netId), ntohs(dataPack->netAddr), wbuf_ip, ntohs(dataPack->steps), strDateTime);
	int count = 0;
	try
	{
		_variant_t RecordsAffected;
		CString tszSQL = _T("");
		CString strTemp = _T("");
	
		int nCount = 0;

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

			m_maxPage = 0;

			

				this->m_previous.EnableWindow(0);
			
			
				this->m_next.EnableWindow(0);

				if (pRecordset->State && pRecordset->GetRecordCount() <= 0)
				{
					this->m_first.EnableWindow(0);
					this->m_last.EnableWindow(0);
				}

			
			return false;

		}


		//pRecordset->Move(this->m_pageIndex*m_pageCount);
		pRecordset->MoveFirst();

		m_maxPage = pRecordset->GetRecordCount() / m_pageCount ;
		if (pRecordset->GetRecordCount() % m_pageCount > 0)
			m_maxPage++;

		m_listctrl.DeleteAllItems();

		while (!pRecordset->adoEOF )
			//while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;

			if (count < m_pageCount)
			{

				v = pRecordset->GetCollect(_variant_t((long)0));
				nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
				//if (v.vt != VT_I4) break;
				//nStudyId = v.lVal;
				strTemp = pRecordset->GetCollect(_variant_t((long)4));
				m_listctrl.SetItemText(nCount, 1, strTemp);
				//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
				m_listctrl.SetItemText(nCount, 2, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
				m_listctrl.SetItemText(nCount, 3, strTemp);

				
				

				v = pRecordset->GetCollect(_variant_t((long)1));
				int event = v.intVal;

				if (event >= 0 && event <= 4)
				{
					
					m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
				}

			}
			v = pRecordset->GetCollect(_variant_t((long)1));
			int event = v.intVal;

			if (event >= 0 && event <= 6)
			{
				m_event[event] ++;

			}


			if (count < m_pageCount)
			{
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
				m_listctrl.SetItemText(nCount, 5, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
				m_listctrl.SetItemText(nCount, 6, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
				m_listctrl.SetItemText(nCount, 7, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
				m_listctrl.SetItemText(nCount, 8, strTemp);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
				m_listctrl.SetItemText(nCount, 9, strTemp);

			}

			pRecordset->MoveNext();
			count++;

			

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

	if(count>0)
	{
		//PositionEnum p = 
		//pRecordset->PutAbsolutePage(2);

		pRecordset->MoveFirst();
		//m_pageIndex = 0;
		if (count > m_pageCount)
		{
			
			pRecordset->Move(m_pageCount);
			m_pageIndex = 0;
		}
	}
	if (0 == m_pageIndex )
	{

		this->m_previous.EnableWindow(0);
	}
	
	if ( m_maxPage<=1)
	{

		this->m_next.EnableWindow(0);
	}
	

	if (m_maxPage>0)
		m_pageIndex++;

	if (pRecordset->State && pRecordset->GetRecordCount() <= 0)
	{
		this->m_first.EnableWindow(0); 
		this->m_last.EnableWindow(0);
	}


	/*
	m_event[1] = 2000;
	m_event[2] = 200;
	m_event[3] = 50;
	m_event[4] = 5;
	*/
	int max = 0;
	
	for (int i = 0; i < 7; i++)
	{
		if (m_event[i] > max)
			max = m_event[i];

	}
	m_event[7] = max;

	for (int i = 0; i < 7; i++)
	{
		m_DeliCtrl.m_event[i] = m_event[i];
#ifdef DEBUG
		m_DeliCtrl.m_event[i] = 20 * i + 20;

#endif // DEBUG

		
	}
#ifdef DEBUG
	m_DeliCtrl.m_event[7] = m_DeliCtrl.m_event[6];
#else 
	m_DeliCtrl.m_event[7] = m_event[7];

#endif // DEBUG

	return TRUE;

}



BOOL CDialogSearch::ReLoadListItem()
{
	CcollectorApp *app = (CcollectorApp *)AfxGetApp();

	//m_pageCount = 50;
	m_pageIndex = 0;

	//CString strHead[] = { _T("网络号"),_T("网络地址"),_T("事件"),_T("步长"),_T("时间") };
	//m_listctrl.InsertColumn(6, strHead, DT_CENTER, NULL);

	for (int i = 0; i < 8; i++)
		m_event[i] = 0;


	m_listctrl.DeleteAllItems();

	int count = 0;
	try
	{
		_variant_t RecordsAffected;
		CString tszSQL = _T("");
		CString strTemp = _T("");

		int nCount = 0;

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

			m_maxPage = 0;



			this->m_previous.EnableWindow(0);


			this->m_next.EnableWindow(0);

			if (pRecordset->State && pRecordset->GetRecordCount() <= 0)
			{
				this->m_first.EnableWindow(0);
				this->m_last.EnableWindow(0);
			}


			return false;

		}


		//pRecordset->Move(this->m_pageIndex*m_pageCount);
		pRecordset->MoveFirst();

		m_maxPage = pRecordset->GetRecordCount() / m_pageCount;
		if (pRecordset->GetRecordCount() % m_pageCount > 0)
			m_maxPage++;

		m_listctrl.DeleteAllItems();

		while (!pRecordset->adoEOF)
			//while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;

			if (count < m_pageCount)
			{

				v = pRecordset->GetCollect(_variant_t((long)0));
				nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
				//if (v.vt != VT_I4) break;
				//nStudyId = v.lVal;
				strTemp = pRecordset->GetCollect(_variant_t((long)4));
				m_listctrl.SetItemText(nCount, 1, strTemp);
				//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
				m_listctrl.SetItemText(nCount, 2, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
				m_listctrl.SetItemText(nCount, 3, strTemp);




				v = pRecordset->GetCollect(_variant_t((long)1));
				int event = v.intVal;

				if (event >= 0 && event <= 4)
				{

					m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
				}

			}
			v = pRecordset->GetCollect(_variant_t((long)1));
			int event = v.intVal;

			if (event >= 0 && event <= 6)
			{
				m_event[event] ++;

			}


			if (count < m_pageCount)
			{
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
				m_listctrl.SetItemText(nCount, 5, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
				m_listctrl.SetItemText(nCount, 6, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
				m_listctrl.SetItemText(nCount, 7, strTemp);
				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
				m_listctrl.SetItemText(nCount, 8, strTemp);

				strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
				m_listctrl.SetItemText(nCount, 9, strTemp);

			}

			pRecordset->MoveNext();
			count++;



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

	if (count>0)
	{
		//PositionEnum p = 
		//pRecordset->PutAbsolutePage(2);

		pRecordset->MoveFirst();
		//m_pageIndex = 0;
		if (count > m_pageCount)
		{

			pRecordset->Move(m_pageCount);
			m_pageIndex = 0;
		}
	}
	if (0 == m_pageIndex)
	{

		this->m_previous.EnableWindow(0);
	}

	if (m_maxPage <= 1)
	{

		this->m_next.EnableWindow(0);
	}


	if (m_maxPage>0)
		m_pageIndex++;

	if (pRecordset->State && pRecordset->GetRecordCount() <= 0)
	{
		this->m_first.EnableWindow(0);
		this->m_last.EnableWindow(0);
	}


	/*
	m_event[1] = 2000;
	m_event[2] = 200;
	m_event[3] = 50;
	m_event[4] = 5;
	*/
	int max = 0;

	for (int i = 0; i < 7; i++)
	{
		if (m_event[i] > max)
			max = m_event[i];

	}
	m_event[7] = max;

	for (int i = 0; i < 7; i++)
	{
		m_DeliCtrl.m_event[i] = m_event[i];
#ifdef DEBUG
		m_DeliCtrl.m_event[i] = 20 * i + 20;

#endif // DEBUG


	}
#ifdef DEBUG
	m_DeliCtrl.m_event[7] = m_DeliCtrl.m_event[6];
#else 
	m_DeliCtrl.m_event[7] = m_event[7];

#endif // DEBUG

	return TRUE;

}





BOOL CDialogSearch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


	this->m_DeliCtrl.ShowWindow(0);

	ShowWindow(SW_SHOWMAXIMIZED);

	m_bDisplayEvent = FALSE;


	if (!LoadListItem())
	{

	for (int i = 0; i < 8; i++)
	{
		m_DeliCtrl.m_event[i] = 0;

	}
    }


	//UpdateData(true);

	//this->SetTimer(1, 5 * 1000, 0);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	CRect  rcButton;
	if (m_listctrl)
	{
	
	GetClientRect(&rect);
	m_previous.GetClientRect(&rcButton);

	
		 
			CRect rc(0, 0+ rcButton.Height() + 10, 1800, rect.Height()-20);;
			m_listctrl.MoveWindow(&rc);

			CRect rc1(0, 0 + rcButton.Height() + 10, 700, 500);
			m_DeliCtrl.MoveWindow(&rc1);

		  
	
			//m_DeliCtrl.ShowWindow(TRUE);

			//m_previous.ShowWindow(TRUE);
			//m_next.ShowWindow(TRUE);
		
	}


}

/*
void CDialogSearch::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	CRect  rcButton;
	if (m_listctrl)
	{

		GetClientRect(&rect);
		m_previous.GetClientRect(&rcButton);

		if (rect.Width() < 1170 + 200)  //1366 
		{
			rect.top += rcButton.Height() + 8;
			rect.right -= 210;
			rect.bottom = rect.Height() + 20;
			m_listctrl.MoveWindow(&rect);



			CRect rc(20, 20, 200, 200);

			GetClientRect(&rect);
			rc.right = rect.right - 5;
			rc.left = rect.right - 205;// rc.Width();

			rc.top = rect.top + 8 + rcButton.Height();
			rc.bottom = rc.top + 200;// rc.Height();
			m_DeliCtrl.MoveWindow(&rc);
		}
		else
		{
			CRect rc(0, 0 + rcButton.Height() + 10, 1155, rect.Height() - 20);;
			m_listctrl.MoveWindow(&rc);

			CRect rc1(rc.right + 10, rc.top, rc.right + 10 + 200, rc.top + 10 + 200);
			m_DeliCtrl.MoveWindow(&rc1);

		}


		m_DeliCtrl.ShowWindow(TRUE);

		m_previous.ShowWindow(TRUE);
		m_next.ShowWindow(TRUE);

	}


} */


BOOL CDialogSearch::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


int CDialogSearch::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rc(20, 20,800, 600);
	m_DeliCtrl.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rc, this, IDC_DELICTRL);

	//| WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL, 

	// TODO:  在此添加您专用的创建代码

	return 0;
}




//previous
void CDialogSearch::OnBnClickedMfcbutton1()
{

	//AfxMessageBox(TEXT("fuck"));
	// TODO: 在此添加控件通知处理程序代码

	m_pageIndex--;
	if ( m_pageIndex<=1)
	{

		this->m_previous.EnableWindow(0);
	}

	this->m_next.EnableWindow(1);

	
	
	try {

		if (pRecordset->GetRecordCount() < 2 * m_pageCount)
			pRecordset->MoveFirst();
		else if (m_pageIndex <= 1)
			pRecordset->MoveFirst();
		else
			pRecordset->Move(-2*m_pageCount);


		int count = 0;
		int nCount = 0;

		m_listctrl.DeleteAllItems();

		while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;
			
			v = pRecordset->GetCollect(_variant_t((long)0));
			nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
			//if (v.vt != VT_I4) break;
			//nStudyId = v.lVal;
			strTemp = pRecordset->GetCollect(_variant_t((long)4));
			m_listctrl.SetItemText(nCount, 1, strTemp);
			//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
			m_listctrl.SetItemText(nCount, 2, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
			m_listctrl.SetItemText(nCount, 3, strTemp);

			
			v = pRecordset->GetCollect(_variant_t((long)1));
			int event = v.intVal;

			if (event >= 0 && event <= 6)
			{
				//m_event[event] ++;
				//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)1)));
				m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
			}

			
		


			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
			m_listctrl.SetItemText(nCount, 5, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
			m_listctrl.SetItemText(nCount, 6, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
			m_listctrl.SetItemText(nCount, 7, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
			m_listctrl.SetItemText(nCount, 8, strTemp);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
			m_listctrl.SetItemText(nCount, 9, strTemp);


			pRecordset->MoveNext();
			count++;



		}
		//m_listctrl.Invalidate();
		//pRecordset->Close();
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return;
	}

}



//next
void CDialogSearch::OnBnClickedMfcbutton2()
{
	// TODO: 在此添加控件通知处理程序代码


	//AfxMessageBox(TEXT("fuck"));


	//pRecordset->PutAbsolutePage()

	this->m_previous.EnableWindow(1);
	
	m_pageIndex++; 
	if(m_maxPage == m_pageIndex)
	{

		this->m_next.EnableWindow(0);
	}

	try{

	//pRecordset->Move(m_pageCount);
	int count = 0;
	int nCount = 0;
	m_listctrl.DeleteAllItems();
	while (!pRecordset->adoEOF  && count < m_pageCount)
	{

		_variant_t v;
		CString strTemp;
	
		v = pRecordset->GetCollect(_variant_t((long)0));
		nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
		//if (v.vt != VT_I4) break;
		//nStudyId = v.lVal;
		strTemp = pRecordset->GetCollect(_variant_t((long)4));
		m_listctrl.SetItemText(nCount, 1, strTemp);
		//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
		m_listctrl.SetItemText(nCount, 2, strTemp);
		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
		m_listctrl.SetItemText(nCount, 3, strTemp);

		//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)1)));
		//m_listctrl.SetItemText(nCount, 4, strTemp);//event
		v = pRecordset->GetCollect(_variant_t((long)1));
		int event = v.intVal;

		if (event >= 0 && event <= 6)
		{
			//m_event[event] ++;
			m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
		}

		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
		m_listctrl.SetItemText(nCount, 5, strTemp);
		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
		m_listctrl.SetItemText(nCount, 6, strTemp);
		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
		m_listctrl.SetItemText(nCount, 7, strTemp);
		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
		m_listctrl.SetItemText(nCount, 8, strTemp);

		strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
		m_listctrl.SetItemText(nCount, 9, strTemp);


		pRecordset->MoveNext();
		count++;



	}
	//m_listctrl.Invalidate();
	//pRecordset->Close();
}//try
catch (_com_error e)
{
	CString strErrorMsg = _T("");
	strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
	TRACE(strErrorMsg);
	//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



	return ;
}

}


BOOL CDialogSearch::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	if(pRecordset->State)
	pRecordset->Close();

	return CDialogEx::DestroyWindow();
}


void CDialogSearch::OnBnClickedMfcbutton3()
{
	m_pageIndex= 1;
	if (m_pageIndex <= 1)
	{

		this->m_previous.EnableWindow(0);
	}

	if(this->m_maxPage>1)
	this->m_next.EnableWindow(1);



	try {

		if (pRecordset->State && pRecordset->GetRecordCount() > 0)
			pRecordset->MoveFirst();
		else
			return;

		int count = 0;
		int nCount = 0;

		m_listctrl.DeleteAllItems();

		while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;

			v = pRecordset->GetCollect(_variant_t((long)0));
			nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
			//if (v.vt != VT_I4) break;
			//nStudyId = v.lVal;
			strTemp = pRecordset->GetCollect(_variant_t((long)4));
			m_listctrl.SetItemText(nCount, 1, strTemp);
			//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
			m_listctrl.SetItemText(nCount, 2, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
			m_listctrl.SetItemText(nCount, 3, strTemp);

			//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)1)));
			//m_listctrl.SetItemText(nCount, 4, strTemp);//event
			v = pRecordset->GetCollect(_variant_t((long)1));
			int event = v.intVal;

			if (event >= 0 && event <= 6)
			{
				//m_event[event] ++;
				m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
			}

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
			m_listctrl.SetItemText(nCount, 5, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
			m_listctrl.SetItemText(nCount, 6, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
			m_listctrl.SetItemText(nCount, 7, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
			m_listctrl.SetItemText(nCount, 8, strTemp);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
			m_listctrl.SetItemText(nCount, 9, strTemp);


			pRecordset->MoveNext();
			count++;



		}
		//m_listctrl.Invalidate();
		//pRecordset->Close();
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return;
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CDialogSearch::OnBnClickedMfcbutton4()
{
	m_pageIndex = this->m_maxPage;
	if (m_pageIndex >=0 )
	{

		this->m_next.EnableWindow(0);
	}

	if (this->m_maxPage>1)
		this->m_previous.EnableWindow(1);



	try {

		if (pRecordset->State && pRecordset->GetRecordCount() > 0)
			pRecordset->MoveLast();
		else
			return;

		if (pRecordset->GetRecordCount() <= this->m_pageCount)
			pRecordset->MoveFirst();
		else
			pRecordset->Move(-m_pageCount+1);

		int count = 0;
		int nCount = 0;

		m_listctrl.DeleteAllItems();

		while (!pRecordset->adoEOF  && count < m_pageCount)
		{

			_variant_t v;
			CString strTemp;

			v = pRecordset->GetCollect(_variant_t((long)0));
			nCount = m_listctrl.InsertItem(0, (LPCTSTR)(_bstr_t)v);
			//if (v.vt != VT_I4) break;
			//nStudyId = v.lVal;
			strTemp = pRecordset->GetCollect(_variant_t((long)4));
			m_listctrl.SetItemText(nCount, 1, strTemp);
			//m_listctrl.SetItemData(nCount, (DWORD_PTR)nStudyId);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)2)));
			m_listctrl.SetItemText(nCount, 2, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)3)));
			m_listctrl.SetItemText(nCount, 3, strTemp);

			//strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)1)));
			//m_listctrl.SetItemText(nCount, 4, strTemp);//event
			v = pRecordset->GetCollect(_variant_t((long)1));
			int event = v.intVal;

			if (event >= 0 && event <= 6)
			{
				//m_event[event] ++;
				m_listctrl.SetItemText(nCount, 4, this->m_eventName[event]);//event
			}

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)5)));
			m_listctrl.SetItemText(nCount, 5, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)6)));
			m_listctrl.SetItemText(nCount, 6, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)7)));
			m_listctrl.SetItemText(nCount, 7, strTemp);
			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)8)));
			m_listctrl.SetItemText(nCount, 8, strTemp);

			strTemp = (LPCTSTR)(_bstr_t)(pRecordset->GetCollect(_variant_t((long)9)));
			m_listctrl.SetItemText(nCount, 9, strTemp);


			pRecordset->MoveNext();
			count++;



		}
		//m_listctrl.Invalidate();
		//pRecordset->Close();
	}//try
	catch (_com_error e)
	{
		CString strErrorMsg = _T("");
		strErrorMsg.Format(_T("Database operator error!\rSource:%s\nDescription:%s"), e.Source(), e.Description());
		TRACE(strErrorMsg);
		//if (pRecordset != NULL && pRecordset->State) pRecordset->Close();



		return;
	}
}


void CDialogSearch::OnBnClickedMfcbutton5()
{
	// TODO: 在此添加控件通知处理程序代码

	m_bDisplayEvent = !m_bDisplayEvent;


	if (m_bDisplayEvent)
	{
		m_btEvent.SetTooltip(_T("Display event diagram"));
		this->m_first.ShowWindow(0);
		this->m_last.ShowWindow(0);
		this->m_previous.ShowWindow(0);
		this->m_next.ShowWindow(0);

		m_listctrl.ShowWindow(0);
		this->m_DeliCtrl.ShowWindow(1);

	 
	}
	else
	{
		m_btEvent.SetTooltip(_T("Close"));
		this->m_first.ShowWindow(1);
		this->m_last.ShowWindow(1);
		this->m_previous.ShowWindow(1);
		this->m_next.ShowWindow(1);

		m_listctrl.ShowWindow(1);
		this->m_DeliCtrl.ShowWindow(0);

	}
}




void CDialogSearch::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReLoadListItem();


	CDialogEx::OnTimer(nIDEvent);
}


void CDialogSearch::OnBnClickedMfcbutton6()
{
	// TODO: 在此添加控件通知处理程序代码
	ReLoadListItem();
}
