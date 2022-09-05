#pragma once


#include "afxcmn.h"
#include "afxwin.h"


// CPageControl �Ի���

class CPageControl : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageControl)

public:
	CPageControl();
	virtual ~CPageControl();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_LARGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnKillActive();
	virtual void OnOK();
	virtual BOOL OnApply();
	virtual BOOL OnSetActive();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	CIPAddressCtrl m_ipAddress;
	CEdit m_netId;
	CEdit m_netAddr;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
};
