#pragma once
#include "afxcmn.h"
#include "ReportCtrl.h"
#include "afxwin.h"

// CDeviceManager 对话框

class CDeviceManager : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceManager)

public:
	CDeviceManager(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceManager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE_MANAGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();

	BOOL LoadListItem();
	BOOL IintListItem();
	BOOL  RefreshList();
	void  InitControls();
	CReportCtrl m_listctrl;
	CString m_tszSQL;
	//CListCtrl m_listctrl;
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
 
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_ip1;
	CComboBox m_ip2;
	CComboBox m_address1;
	CComboBox m_address2;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeCombo2();
	int m_timer;
	int  m_timeId;
	CComboBox m_combox_timer;
};
