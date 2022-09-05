#pragma once
#include "afxcmn.h"


// CDialogAddDevice 对话框

class CDialogAddDevice : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAddDevice)

public:
	CDialogAddDevice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogAddDevice();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DEVICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	virtual BOOL OnInitDialog();
	CString m_name;
	CString m_description;
	CString m_panId;
	CString m_netAddress;
	CIPAddressCtrl m_ip;
	afx_msg void OnBnClickedButton1();
	BOOL  CheckExist(CString);
	
		;
};
