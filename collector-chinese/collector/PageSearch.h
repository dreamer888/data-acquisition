#pragma once

#include "DialogSearch.h"

// CPageControl 对话框

class CPageSearch : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageSearch)

public:
	CPageSearch();
	virtual ~CPageSearch();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_LARGE2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
