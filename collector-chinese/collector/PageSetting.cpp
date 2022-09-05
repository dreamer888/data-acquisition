// PageSetting.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "collector.h"
#include "PageSetting.h"
#include "afxdialogex.h"
#include "MyPropertySheet.h"
#include  "util.h"

// CPageSetting �Ի���

IMPLEMENT_DYNAMIC(CPageSetting, CPropertyPage)

CPageSetting::CPageSetting()
	: CPropertyPage(IDD_PROPPAGE_LARGE)
	, m_port(0)
{

}

CPageSetting::~CPageSetting()
{
}

void CPageSetting::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxUInt(pDX, m_port, 1000, 60000);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
}


BEGIN_MESSAGE_MAP(CPageSetting, CPropertyPage)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &CPageSetting::OnIpnFieldchangedIpaddress1)
	
	ON_BN_CLICKED(IDC_RADIO1, &CPageSetting::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CPageSetting ��Ϣ�������


in_addr  CPageSetting::GetLocalIp()
{
	char name[155];
	CString cs;

	in_addr  addr;

	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0) {     //��ȡ������
		if ((hostinfo = gethostbyname(name)) != NULL) { //��Щ���ǻ��IP�ĺ���
			addr = *(struct in_addr *)*hostinfo->h_addr_list; //��ȡ����ip
		}

	}

	return  addr;

}
BOOL CPageSetting::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	//m_psp.dwFlags = m_psp.dwFlags | PSP_USETITLE;
	//m_psp.pszTitle = _T("Setting");
	//  cont work !
	
	//AfxMessageBox(_T("setting initdialog"));

	//TC_ITEM tc;
	//tc.mask = TCIF_TEXT;
	//tc.pszText = _T("Setting");
	//((CPropertySheet*)GetParent())->GetTabControl()->SetItem(0, &tc);

	CString cs;
	
	//TCHAR buffer[255];
	//GetPrivateProfileString(_T("system"), _T("port"),_T("8000"), buffer, sizeof(buffer), CONFIG);
	//cs = buffer;
	//this->m_port = _ttoi(buffer);
	SetDlgItemTextA(this->m_hWnd ,IDC_IPADDRESS1, inet_ntoa(GetLocalIp()));
	//this->m_ip.SetAddress (127, 0, 0, 1);
	//this->m_ip.EnableWindow(0);
	this->m_port = GetPrivateProfileInt(_T("system"), _T("port"), 8000, CONFIG);
	
	cs.Format(_T("%d"), this->m_port);
	this->GetDlgItem(IDC_EDIT1)->SetWindowText(cs);


	TCHAR server[50];
	TCHAR database[50];
	TCHAR userid[50];
	TCHAR passwd[50];
	GetPrivateProfileString(_T("database"), _T("server"), _T("192.168.1.101\\HMKJ"), server, sizeof(server), CONFIG);
	GetPrivateProfileString(_T("database"), _T("database"), _T("hmkj"), database, sizeof(database), CONFIG);
	GetPrivateProfileString(_T("database"), _T("userid"), _T("sa"), userid, sizeof(userid), CONFIG);
	GetPrivateProfileString(_T("database"), _T("passwd"), _T("windows"), passwd, sizeof(passwd), CONFIG);

	//3  server 4  name
	//2  database  5   pwd 

	this->GetDlgItem(IDC_EDIT3)->SetWindowText(server);
	this->GetDlgItem(IDC_EDIT4)->SetWindowText(userid);
	this->GetDlgItem(IDC_EDIT2)->SetWindowText(database);
	this->GetDlgItem(IDC_EDIT5)->SetWindowText(passwd);

	TCHAR timeout[10];
	GetPrivateProfileString(_T("KeepAlive"), _T("timeout"), _T("60"), timeout, sizeof(timeout), CONFIG);
	this->GetDlgItem(IDC_EDIT9)->SetWindowText(timeout);
	 
 
	this->UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPageSetting::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	

	//AfxMessageBox(_T("setting page ok "));


	//CString cs;
	//cs.Format(_T("setting  ok , entrance  %d"), ((CMyPropertySheet*)GetParent())->m_index);
	//AfxMessageBox(cs);

	CPropertyPage::OnOK();
}


BOOL CPageSetting::OnKillActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	//AfxMessageBox(_T("setting page kill active "));

	//if (((CMyPropertySheet*)GetParent())->m_index == 0)
		//return FALSE;
	return CPropertyPage::OnKillActive();
}


BOOL CPageSetting::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (((CMyPropertySheet*)GetParent())->m_index == 0)
	{

		this->UpdateData(TRUE);
		CString cs;
		cs.Format(_T("%d"), this->m_port);
		WritePrivateProfileString(_T("system"), _T("port"), cs, CONFIG);

	 
		TCHAR server[50];
		TCHAR database[50];
		TCHAR userid[50];
		TCHAR passwd[50];
		this->GetDlgItem(IDC_EDIT3)->GetWindowText(server, sizeof(server));
		this->GetDlgItem(IDC_EDIT4)->GetWindowText(userid, sizeof(userid));
		this->GetDlgItem(IDC_EDIT2)->GetWindowText(database, sizeof(database));
		this->GetDlgItem(IDC_EDIT5)->GetWindowText(passwd, sizeof(passwd));

		WritePrivateProfileString(_T("database"), _T("server"), server, CONFIG);
		WritePrivateProfileString(_T("database"), _T("userid"), userid, CONFIG);
		WritePrivateProfileString(_T("database"), _T("database"), database, CONFIG);
		WritePrivateProfileString(_T("database"), _T("passwd"), passwd, CONFIG);



		TCHAR timeout[10];
		this->GetDlgItem(IDC_EDIT9)->GetWindowText(timeout, sizeof(timeout));
		WritePrivateProfileString(_T("KeepAlive"), _T("timeout"), timeout, CONFIG);
	 
	
	}

	//((CMyPropertySheet*)GetParent())->m_bApply = true;

	return CPropertyPage::OnApply();
}


void CPageSetting::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//AfxMessageBox(_T("setting page cancel "));
	CPropertyPage::OnCancel();
}


INT_PTR CPageSetting::DoModal()
{
	// TODO: �ڴ����ר�ô����/����û���
	AfxMessageBox(_T("setting modal"));
	return CPropertyPage::DoModal();
}


BOOL CPageSetting::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (((CMyPropertySheet*)GetParent())->m_index == 0)
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
	else 
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(FALSE);


	return CPropertyPage::OnSetActive();
}


void CPageSetting::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CPageSetting::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
