#pragma once
#include "afxwin.h"


// CUpgrade 对话框

class CPageUpgrade : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageUpgrade)

public:
	CPageUpgrade();
	virtual ~CPageUpgrade();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_LARGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual BOOL OnApply();
	 
	afx_msg void OnBnClickedButton1();
	CEdit m_path;
	CString m_fileName;
	CString m_fname;
	CIPAddressCtrl m_ipAddress;
	CEdit m_netId;
	CEdit m_netAddr;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck2();
};
