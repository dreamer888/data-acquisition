#pragma once
//#include "afxcmn.h"


// CPageSetting 对话框

class CPageSetting : public CPropertyPage
{
	DECLARE_DYNAMIC(CPageSetting)

public:
	CPageSetting();
	virtual ~CPageSetting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROPPAGE_LARGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	UINT m_port;
	virtual BOOL OnKillActive();
	virtual BOOL OnApply();
	virtual void OnCancel();
	virtual INT_PTR DoModal();
	virtual BOOL OnSetActive();
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	in_addr  GetLocalIp();
	CIPAddressCtrl m_ip;
	
	afx_msg void OnBnClickedRadio1();
};
