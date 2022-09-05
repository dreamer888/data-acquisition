// PageSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "PageSearch.h"
#include "afxdialogex.h"

#include "MyPropertySheet.h"


// CPageSearch 对话框


class  CMyPropertySheet;

IMPLEMENT_DYNAMIC(CPageSearch, CPropertyPage)

CPageSearch::CPageSearch()
	: CPropertyPage(IDD_PROPPAGE_LARGE2)
	, m_pageCount(100)
{

}

CPageSearch::~CPageSearch()
{
}

void CPageSearch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT10, m_pageCount);
}


BEGIN_MESSAGE_MAP(CPageSearch, CPropertyPage)
END_MESSAGE_MAP()


// CPageSearch 消息处理程序


BOOL CPageSearch::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//this->SetWindowText(_T("Search"));  //  does not  work !
	//TC_ITEM tc;
	//tc.mask = TCIF_TEXT;
	//tc.pszText = _T("檢索");
	//((CPropertySheet*)GetParent())->GetTabControl()->SetItem(2, &tc);

	m_pageCount=GetPrivateProfileInt(_T("search"), _T("pageCount"), 100, _T("config.ini"));

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a Search
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CPageSearch::OnKillActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	//if ((CPropertySheet*)GetParent())->GetTabControl()->m_index != 2)
	


	//if (((CMyPropertySheet*)GetParent())->GetActiveIndex()==2)
		//((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);


	//return FALSE;
	
	return CPropertyPage::OnKillActive();
}


BOOL CPageSearch::OnApply()
{
	// TODO: 在此添加专用代码和/或调用基类
	
	if (((CMyPropertySheet*)GetParent())->m_index == 2)
	{
	 
	 
		//((CMyPropertySheet*)GetParent())->m_bApply = true;
		UpdateData(TRUE);
	
		TCHAR count[50];
		
		this->GetDlgItem(IDC_EDIT10)->GetWindowText(count, sizeof(count));

		WritePrivateProfileString(_T("search"), _T("pageCount"), count, _T("config.ini"));// CONFIG);
		if (this->m_pageCount > 2000)
		{
			WritePrivateProfileString(_T("search"), _T("pageCount"), _T("2000"), _T("config.ini"));// CONFIG);

			m_pageCount = 2000;
		}



		

		UpdateData(FALSE);
	 
		CButton *cb7 = (CButton*)GetDlgItem(IDC_CHECK7);
		CButton *cb1 = (CButton*)GetDlgItem(IDC_CHECK1);
		CButton *cb2 = (CButton*)GetDlgItem(IDC_CHECK2);
		CButton *cb3 = (CButton*)GetDlgItem(IDC_CHECK3);
		CButton *cb4 = (CButton*)GetDlgItem(IDC_CHECK4);
		CButton *cb5 = (CButton*)GetDlgItem(IDC_CHECK5);


		CButton *cb8 = (CButton*)GetDlgItem(IDC_CHECK8);
		CButton *cb9 = (CButton*)GetDlgItem(IDC_CHECK9);
		CButton *cb10 = (CButton*)GetDlgItem(IDC_CHECK10);



		CEdit  * ed1 = (CEdit  * )GetDlgItem(IDC_EDIT1);
		CEdit  * ed6 = (CEdit  * )GetDlgItem(IDC_EDIT6);
		CEdit  * ed7 = (CEdit  * )GetDlgItem(IDC_EDIT7);


		CEdit  * ed11 = (CEdit  *)GetDlgItem(IDC_EDIT11);
		CEdit  * ed12 = (CEdit  *)GetDlgItem(IDC_EDIT12);
		CEdit  * ed13 = (CEdit  *)GetDlgItem(IDC_EDIT13);

		CIPAddressCtrl *  ip =  (CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS2);

		CDateTimeCtrl  * dt1 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
		CDateTimeCtrl  * dt2 = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER2);

		CDialogSearch  dlg;

		CString where = _T("");
		CString  and = _T("");
		CString cs = _T("");
		CString temp = _T("");

		if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck() || cb3->GetCheck() ||   cb4->GetCheck() || cb5->GetCheck() || cb8->GetCheck() || cb9->GetCheck() || cb10->GetCheck())
		{
			where = _T(" where ");

		}

		if (cb7->GetCheck())
		{
			
			ip->GetWindowTextW(temp);
			cs.Format(_T(" ip='%s' "), temp);
			where += cs;
		}

		if (cb1->GetCheck())
		{
			if (cb7->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			ed1->GetWindowTextW(temp);
			 
			//cs.Format(_T(" pan_id=%s "), cs);  // 2种方式都是 ok的，加不加' 都可以的 
			cs.Format(_T(" pan_id='%s' "), temp);
			where += cs;
		}

		if (cb2->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;

			ed6->GetWindowTextW(temp);
			cs.Format(_T(" zigbee_address='%s' "), temp);
			where += cs;
		}

		if (cb3->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			ed7->GetWindowTextW(temp);
			int e = 0;
			if (temp.CompareNoCase(_T("start"))==0)
				e = 0;
			else if (temp.CompareNoCase(_T("stop"))==0)
				e = 1;
			else if (temp.CompareNoCase(_T("up"))==0)
				e = 2;
			else if (temp.CompareNoCase(_T("down"))==0)
				e = 3;
			else if (temp.CompareNoCase(_T("cut"))==0)
				e = 4;
			else
			{
				AfxMessageBox(_T("event input option is : start,stop,up,down,cut "));
				return CPropertyPage::OnApply();
			}
			//int e = _ttoi(temp);
			cs.Format(_T(" event_id=%d "),e);
			where += cs;
		}


		if (cb4->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck()  || cb3->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			CTime  t;
			dt1->GetTime(t);
			CString szDate;
			szDate = t.Format(TEXT("%Y-%m-%d %H:%M:%S"));
			CString strDateTime;
			strDateTime.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)szDate);
			cs.Format(_T(" create_time >= %s"), strDateTime);
			where += cs;
		}
		if (cb5->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck() || cb3->GetCheck()  || cb4->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			CTime  t;
			dt2->GetTime(t);
			CString szDate;
			szDate = t.Format(TEXT("%Y-%m-%d %H:%M:%S"));
			CString strDateTime;
			strDateTime.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)szDate);
			cs.Format(_T(" create_time <= %s"), strDateTime);
			where += cs;
		}


		if (cb8->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck() || cb3->GetCheck() || cb4->GetCheck() || cb5->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			ed11->GetWindowTextW(temp);
			cs.Format(_T(" employee_no='%s' "), temp);
			where += cs;
		}

		if (cb9->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck() || cb3->GetCheck() || cb4->GetCheck() || cb5->GetCheck() || cb8->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			ed12->GetWindowTextW(temp);
			cs.Format(_T(" process_no='%s' "), temp);
			where += cs;
		}
		if (cb10->GetCheck())
		{
			if (cb7->GetCheck() || cb1->GetCheck() || cb2->GetCheck() || cb3->GetCheck() || cb4->GetCheck() || cb5->GetCheck() || cb8->GetCheck() || cb9->GetCheck())
				and = _T(" and ");
			else
				and = _T(" ");
			where += and;
			ed13->GetWindowTextW(temp);
			
			cs.Format(_T(" model_no='%s' "),  temp);
			where += cs;
		}

		if (where.Compare(_T("")) == 0)
		{

			COleDateTime time;
			COleDateTime  timeEnd;
			time = COleDateTime::GetCurrentTime();
			CString ct = time.Format(TEXT("%Y-%m-%d %H:%M:%S"));	 
			COleDateTimeSpan  span ;
			span.m_span = 1;
		
			cs.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)ct);
		 

			timeEnd  = time - span;
			CString ct1 = timeEnd.Format(TEXT("%Y-%m-%d %H:%M:%S"));

			ct.Format(_T("CONVERT(DATETIME, \'%s\',120)"), (LPCTSTR)ct1);


			where.Format(_T(" where  create_time >= %s   and  create_time <= %s  "), ct,cs);
			 //  如果没有过滤条件，默认得到 当前时间 和前一天之间的记录 


		}
		dlg.m_tszSQL.Format(_T("SELECT   *   FROM table_log  "));
		dlg.m_tszSQL += where;

		CString order = TEXT(" order by table_id ");
		dlg.m_tszSQL += order;

		dlg.m_pageCount = m_pageCount;

		if(m_pageCount<=0 || m_pageCount>= 2000)
		{
			AfxMessageBox(_T("Page size scope is [1~2000] "));
			return CPropertyPage::OnApply();
		}
		dlg.DoModal();


	}
	return CPropertyPage::OnApply();
}


void CPageSearch::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	 

	CPropertyPage::OnCancel();
}


void CPageSearch::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	/*
	CString cs;
	cs.Format(_T("search  ok , entrance  %d"), ((CMyPropertySheet*)GetParent())->m_index);
	AfxMessageBox(cs);
	*/

	CPropertyPage::OnOK();
}


BOOL CPageSearch::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (((CMyPropertySheet*)GetParent())->m_index == 2)
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
	else
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(FALSE);



	return CPropertyPage::OnSetActive();
}
