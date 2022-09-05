// Upgrade.cpp : 实现文件
//

#include "stdafx.h"
#include "collector.h"
#include "PageUpgrade.h"
#include "afxdialogex.h"
#include "MyPropertySheet.h"

#include "util.h"  
#include <fstream>
using namespace std;



// CUpgrade 对话框

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


// CUpgrade 消息处理程序


BOOL CPageUpgrade::OnSetActive()
{
	// TODO: 在此添加专用代码和/或调用基类

	if (((CMyPropertySheet*)GetParent())->m_index == 3)
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);
	else
		((CMyPropertySheet*)GetParent())->GetDlgItem(ID_APPLY_NOW)->EnableWindow(FALSE);
	return CPropertyPage::OnSetActive();
}

 


void CPageUpgrade::OnBnClickedButton1()
{
	TCHAR szModuleFileName[MAX_PATH]; // 全路径名
	TCHAR drive[_MAX_DRIVE];  // 盘符名称，比如说C盘啊，D盘啊
	TCHAR dir[_MAX_DIR]; // 目录
	TCHAR fname[_MAX_FNAME];  // 进程名字
	TCHAR ext[_MAX_EXT]; //后缀，一般为exe或者是dll
	
	CFileDialog    fileDlg(TRUE,  // TRUE打开Open，FALSE保存Save As文件对话框
		_T(".bin"),  // 默认的打开文件的类型
		_T(""), // 默认打开的文件名 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR,  // 单选打开
		_T("bin file(*.bin)|*.bin|all files(*.*) |*.*||")  // 打开的文件类型
	);
	if(NULL == GetModuleFileName(NULL, szModuleFileName, MAX_PATH)) //获得当前进程的文件路径
		return ;
	_tsplitpath_s(szModuleFileName, drive, dir, fname, ext);
	m_fileName = drive;
	m_fileName += dir;
	fileDlg.m_ofn.lpstrInitialDir = m_fileName;//初始化路径。
	if (fileDlg.DoModal() == IDOK)
	{
		m_fileName = fileDlg.GetPathName();//返回选择或输入的文件名称，
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
			pst.netAddr = 0;  //net_addr为0  ，表示组播，操作对该id下的所有 zigbee终端有效 
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

	// TODO:  在此添加额外的初始化

	CButton * cb = (CButton *)GetDlgItem(IDC_CHECK1);
	cb->EnableWindow(0);
	this->m_netId.EnableWindow(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
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
