#pragma once

#include "DialogSearch.h"

// CPageControl �Ի���

class CPageSearch : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageSearch)

public:
	CPageSearch();
	virtual ~CPageSearch();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_LARGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnSetActive();


	int m_pageCount;
};
