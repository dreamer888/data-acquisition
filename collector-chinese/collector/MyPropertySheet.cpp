#include "stdafx.h"
#include "MyPropertySheet.h"


CMyPropertySheet::CMyPropertySheet()
{
	
}


CMyPropertySheet::~CMyPropertySheet()
{
}


BOOL CMyPropertySheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  在此添加您的专用代码

	
	CWnd *pWnd = GetDlgItem(IDHELP);
	pWnd->ShowWindow(FALSE);

	pWnd = GetDlgItem(IDOK);
	pWnd->SetWindowText(_T("Confirm"));
	pWnd->ShowWindow(FALSE);

	pWnd = GetDlgItem(IDCANCEL);
	pWnd->SetWindowText(_T("關閉"));

	GetDlgItem(ID_APPLY_NOW)->SetWindowText(_T("應用"));

	GetDlgItem(ID_APPLY_NOW)->EnableWindow(TRUE);

	/*
	for (int i = 0; i < this->GetPageCount(); i++)
	{
		SetActivePage(i);
		//this->m_psh.dwFlags &= ~(PSH_HASHELP);

		//GetPage(i)->m_psp.dwFlags &= ~(PSP_HASHELP);
	}
	*/
	SetActivePage(m_index);
	


	this->SetWindowText(_T("通用設置和控制 ..."));

	//this->m_bApply = false;

	return bResult;
}
