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

	// TODO:  �ڴ��������ר�ô���

	
	CWnd *pWnd = GetDlgItem(IDHELP);
	pWnd->ShowWindow(FALSE);

	pWnd = GetDlgItem(IDOK);
	pWnd->SetWindowText(_T("Confirm"));
	pWnd->ShowWindow(FALSE);

	pWnd = GetDlgItem(IDCANCEL);
	pWnd->SetWindowText(_T("�P�]"));

	GetDlgItem(ID_APPLY_NOW)->SetWindowText(_T("����"));

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
	


	this->SetWindowText(_T("ͨ���O�úͿ��� ..."));

	//this->m_bApply = false;

	return bResult;
}
