// PageControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "collector.h"
#include "PageControl.h"
#include "afxdialogex.h"

#include "MyPropertySheet.h"
// CPageControl �Ի���

#include "util.h" 

IMPLEMENT_DYNAMIC(CPageControl, CPropertyPage)

CPageControl::CPageControl()
	: CPropertyPage(IDD_PROPPAGE_LARGE1)
{

}

CPageControl::~CPageControl()
{
}

void CPageControl::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ipAddress);
	DDX_Control(pDX, IDC_EDIT1, m_netId);
	DDX_Control(pDX, IDC_EDIT6, m_netAddr);
}


BEGIN_MESSAGE_MAP(CPageControl, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK4, &CPageControl::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK3, &CPageControl::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK1, &CPageControl::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPageControl::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_RADIO3, &CPageControl::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO2, &CPageControl::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CPageControl ��Ϣ�������


BOOL CPageControl::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//this->SetWindowText(_T("Control"));  //  does not  work !
	TC_ITEM tc;
	tc.mask = TCIF_TEXT;
	//tc.pszText = _T("Control");
	//((CPropertySheet*)GetParent())->GetTabControl()->SetItem(1, &tc);

	CButton * cb = (CButton *)GetDlgItem(IDC_CHECK1);
	cb->EnableWindow(0);
	this->m_netId.EnableWindow(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CPageControl::OnKillActive()
{
	// TODO: �ڴ����ר�ô����/����û���

	//AfxMessageBox(_T("control page kill active "));
	//if (((CMyPropertySheet*)GetParent())->m_index == 1)
		//return FALSE;
	return CPropertyPage::OnKillActive();
}


void CPageControl::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���



	CPropertyPage::OnOK();
}


BOOL CPageControl::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (((CMyPropertySheet*)GetParent())->m_index == 1)
	{
		UpdateData(TRUE);

		if (((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck() == 0 && ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck() == 0 && ((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck() == 0)
		{
			AfxMessageBox(_T("Plese choose the scope !"));
			return  FALSE;;
		}
		if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() == 0 && ((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() == 0 && ((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck() == 0)
		{
			AfxMessageBox(_T("Plese choose the operation !"));
			return  FALSE;;
		}

		if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck()  && ((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck() == 0)
		{
			AfxMessageBox(_T(" net addr need ip  !"));
			return  FALSE;;
		}

		
		CString cs;
		//cs.Format(_T("control  app , entrance  %d"), ((CMyPropertySheet*)GetParent())->m_index);
		//AfxMessageBox(cs);
		
		CMyPropertySheet* ppp= (CMyPropertySheet*)GetParent();
		HWND  phwnd = ppp->m_pHwnd;
		TagPageControlStruct pst;
		CButton * cb;
		cb = (CButton *)GetDlgItem(IDC_CHECK4);	
		pst.checkAll = cb->GetCheck();

		cb = (CButton *)GetDlgItem(IDC_CHECK3);
		pst.checkIp = cb->GetCheck();  

		cb = (CButton *)GetDlgItem(IDC_CHECK1);
		pst.checkNetId = cb->GetCheck();

		cb = (CButton *)GetDlgItem(IDC_CHECK2);
		pst.checkNetAddr = cb->GetCheck();

		m_ipAddress.GetAddress(pst.ip);

		this->m_netId.GetWindowText(cs);
		pst.netId = _tcstol(cs, NULL , 16); // _ttoi(cs);

		if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck() == 0)
			pst.netAddr = 0;
		else
		{
			this->m_netAddr.GetWindowText(cs);
			pst.netAddr = _tcstol(cs, NULL, 16);
		}

/*
#define  CMMD_NORMAL_DATA 0          //��λ���ϴ����������� 
#define  CMMD_CONTROL_UPGRADE 1   //��λ���������ָ���豸��ϵͳ
#define  CMMD_CONTROL_ON 2         //��λ��������ָ�����豸
#define  CMMD_CONTROL_OFF 3           //��λ������ر�ָ�����豸
*/
		cb = (CButton *)GetDlgItem(IDC_RADIO1);
		 if(cb->GetCheck())
			 pst.controlCode =  2;
		 cb = (CButton *)GetDlgItem(IDC_RADIO2);
		 if (cb->GetCheck())
			 pst.controlCode = 3;

		 cb = (CButton *)GetDlgItem(IDC_RADIO3);
		 if (cb->GetCheck())
			 pst.controlCode = 4;

		 if (pst.controlCode == 4)
		 {
			 COleDateTime time = COleDateTime::GetCurrentTime();
			 CString ct = time.Format(TEXT("%Y-%m-%d %H:%M:%S"));
			 LPCTSTR  pct = ct.GetBuffer();
			 char buf[40]; 
			 WCharToMByte(ct.GetBuffer(), buf, sizeof(buf));
			 memcpy(pst.time, buf, 19);

		 }

		cb = (CButton *)GetDlgItem(IDC_CHECK3);

		if (!cb->GetCheck())
		{
			pst.netAddr = 0;  //net_addrΪ0  ����ʾ�鲥�������Ը�id�µ����� zigbee�ն���Ч 
		}

		::SendMessage(phwnd, WM_PAGE_MSG, ((CMyPropertySheet*)GetParent())->m_index, (LPARAM)&pst);
	}

	return CPropertyPage::OnApply();
}


BOOL CPageControl::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (((CMyPropertySheet*)GetParent())->m_index == 1)
	{
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
		
	}
	else
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(FALSE);



	return CPropertyPage::OnSetActive();
}


void CPageControl::OnBnClickedCheck4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * cb;
	
	cb = (CButton *)GetDlgItem(IDC_CHECK1);
	cb->SetCheck(FALSE);
	cb = (CButton *)GetDlgItem(IDC_CHECK2);
	cb->SetCheck(FALSE);
	cb = (CButton *)GetDlgItem(IDC_CHECK3);
	cb->SetCheck(0);

	UpdateData(FALSE);
}


void CPageControl::OnBnClickedCheck3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK4);
	cb->SetCheck(FALSE);
}


void CPageControl::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK4);
	cb->SetCheck(FALSE);
}


void CPageControl::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK4);
	cb->SetCheck(FALSE);
}


void CPageControl::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CPageControl::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
