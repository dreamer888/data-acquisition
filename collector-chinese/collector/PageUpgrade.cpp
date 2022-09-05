// Upgrade.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "collector.h"
#include "PageUpgrade.h"
#include "afxdialogex.h"
#include "MyPropertySheet.h"

#include "util.h"  
#include <fstream>
using namespace std;



// CUpgrade �Ի���

IMPLEMENT_DYNAMIC(CPageUpgrade, CPropertyPage)

CPageUpgrade::CPageUpgrade()
	: CPropertyPage(IDD_PROPPAGE_LARGE3)
{

}

CPageUpgrade::~CPageUpgrade()
{
}

void CPageUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_path);
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS2, m_ipAddress);
	DDX_Control(pDX, IDC_EDIT6, m_netId);
	DDX_Control(pDX, IDC_EDIT8, m_netAddr);
}


BEGIN_MESSAGE_MAP(CPageUpgrade, CPropertyPage)
	 
	ON_BN_CLICKED(IDC_BUTTON1, &CPageUpgrade::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK4, &CPageUpgrade::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK6, &CPageUpgrade::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK2, &CPageUpgrade::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CUpgrade ��Ϣ�������


BOOL CPageUpgrade::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���

	if (((CMyPropertySheet*)GetParent())->m_index == 3)
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
	else
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(FALSE);
	return CPropertyPage::OnSetActive();
}

 


void CPageUpgrade::OnBnClickedButton1()
{
	TCHAR szModuleFileName[MAX_PATH]; // ȫ·����
	TCHAR drive[_MAX_DRIVE];  // �̷����ƣ�����˵C�̰���D�̰�
	TCHAR dir[_MAX_DIR]; // Ŀ¼
	TCHAR fname[_MAX_FNAME];  // ��������
	TCHAR ext[_MAX_EXT]; //��׺��һ��Ϊexe������dll
	
	CFileDialog    fileDlg(TRUE,  // TRUE��Open��FALSE����Save As�ļ��Ի���
		_T(".bin"),  // Ĭ�ϵĴ��ļ�������
		_T(""), // Ĭ�ϴ򿪵��ļ��� 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,  // ��ѡ��
		_T("bin file(*.bin)|*.bin|all files(*.*) |*.*||")  // �򿪵��ļ�����
	);
	if(NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //��õ�ǰ���̵��ļ�·��
		return ;
	_tsplitpath_s(szModuleFileName, drive, dir, fname, ext);
	m_fileName = drive;
	m_fileName += dir;
	fileDlg.m_ofn.lpstrInitialDir = m_fileName;//��ʼ��·����
	if (fileDlg.DoModal() == IDOK)
	{
		m_fileName = fileDlg.GetPathName();//����ѡ���������ļ����ƣ�
	}
	
	m_path.SetWindowTextW(m_fileName);
	_tsplitpath_s(m_fileName, drive, dir, fname, ext);
	this->m_fname = fname;
	UpdateData(0);

	
}

BOOL CPageUpgrade::OnApply()
{
	if (((CMyPropertySheet*)GetParent())->m_index == 3)
	{
		UpdateData(TRUE);

		if (((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck() == 0 && ((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck() == 0)
		{
			AfxMessageBox(_T("Plese choose the scope !"));
			return  FALSE;;
		}
		CString  cs; 
		this->m_path.GetWindowTextW(cs);
		if (cs.IsEmpty())
		{
			AfxMessageBox(_T("Plese choose the file !"));
			return  FALSE;;
		}

		if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck() && ((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck() == 0)
		{
			AfxMessageBox(_T("net addr need ip  !"));
			return  FALSE;;
		}

	
		CMyPropertySheet* ppp = (CMyPropertySheet*)GetParent();
		HWND  phwnd = ppp->m_pHwnd;
		TagPageUpgradeStruct pst;
		CButton * cb;
		cb = (CButton *)GetDlgItem(IDC_CHECK4);
		pst.checkAll = cb->GetCheck();

		cb = (CButton *)GetDlgItem(IDC_CHECK6);
		pst.checkIp = cb->GetCheck();

		cb = (CButton *)GetDlgItem(IDC_CHECK1);
		pst.checkNetId = cb->GetCheck();

		cb = (CButton *)GetDlgItem(IDC_CHECK2);
		pst.checkNetAddr = cb->GetCheck();

		m_ipAddress.GetAddress(pst.ip);

		this->m_netId.GetWindowText(cs);
		pst.netId = _tcstol(cs, NULL, 16); // _ttoi(cs);

		if (((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck() == 0)
			pst.netAddr = 0;
		else
		{
			this->m_netAddr.GetWindowText(cs);
			pst.netAddr = _tcstol(cs, NULL, 16);
		}

		cb = (CButton *)GetDlgItem(IDC_CHECK3);

		if (!cb->GetCheck())
		{
			pst.netAddr = 0;  //net_addrΪ0  ����ʾ�鲥�������Ը�id�µ����� zigbee�ն���Ч 
		}
	 
		memset(pst.fileName, 0, sizeof(pst.fileName));
		WCharToMByte(m_fileName, pst.fileName, sizeof(pst.fileName));

		memset(pst.fname, 0, sizeof(pst.fname));
		WCharToMByte(this->m_fname, pst.fname, sizeof(pst.fname));

	   

		::SendMessage(phwnd, WM_PAGE_MSG, ((CMyPropertySheet*)GetParent())->m_index, (LPARAM)&pst);
	}

	return CPropertyPage::OnApply();
}


BOOL CPageUpgrade::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CButton * cb = (CButton *)GetDlgItem(IDC_CHECK1);
	cb->EnableWindow(0);
	this->m_netId.EnableWindow(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPageUpgrade::OnBnClickedCheck4()
{
	 
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK1); //id
	cb->SetCheck(FALSE);
	cb = (CButton *)GetDlgItem(IDC_CHECK2); //address
	cb->SetCheck(FALSE);
	cb = (CButton *)GetDlgItem(IDC_CHECK6); //ip
	cb->SetCheck(0);
}


void CPageUpgrade::OnBnClickedCheck6()
{
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK4);
	cb->SetCheck(FALSE);
}


void CPageUpgrade::OnBnClickedCheck2()
{
	CButton * cb;

	cb = (CButton *)GetDlgItem(IDC_CHECK4);
	cb->SetCheck(FALSE);
}
