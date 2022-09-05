
// collectorDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"

#include "ReportCtrl.h"


#include "PageSetting.h"
#include "PageControl.h"
#include "PageSearch.h"
#include "PageUpgrade.h"

#include "MyPropertySheet.h"
#include "afxwin.h"

#include "IOCPModel.h"

   #include "IOCPServerPackage.h"




// CcollectorDlg 对话框
class CcollectorDlg : public CDialogEx
{
// 构造
public:
	CcollectorDlg(CWnd* pParent = NULL);	// 标准构造函数

	CImageList m_ImageList;
	CToolBarCtrl m_ToolBar;
	CPageSetting  m_PageSetting;
	CPageControl  m_PageControl;
	CPageSearch  m_PageSearch;
	CPageUpgrade  m_PageUpgrade;
	//CPropertySheet * m_psheet;
	CMyPropertySheet * m_psheet;

	//CFile m_logFile;

	BOOL  LoadListItem();
	BOOL  RefreshList();
	void  AddToolbar();
	void  InitControlPosition();
	void  OnOpenPropertySheet();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLECTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnSetting();
	afx_msg void OnControl();
	afx_msg void OnSearch();
	
	afx_msg void OnUpgrade(); 
	afx_msg void OnLog();
	afx_msg void OnSkin();
	afx_msg void OnDevice();
	
	

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSocketMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSocketParsePacket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPageMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFreshList(WPARAM wParam, LPARAM lParam);

	
	
public:
	//CListCtrl m_listctrl;
	CReportCtrl m_listctrl;
	int m_timer;

	//CMyListCtrl  m_listctrl;
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL DestroyWindow();
	BOOL SendControlMessage(CSocketOverlap *pSocketOlp, TagPageControlStruct * pcs);
	BOOL SendUpgradeMessage(CSocketOverlap *pSocketOlp, TagPageUpgradeStruct * pcs);

	
	BOOL  WriteLog1(char *buf);

	BOOL  WriteLog(TCHAR *buf);

	CListBox m_status;
	CIOCPModel  m_iocpModel;
	
	
	CIOCPServerPackage  m_serverIOCP;
	bool  m_bUseTimeInterval; 
	int  m_timeInterval;
	int m_recordCount; 
	DWORD  m_tickCount; 


	CString m_eventName[5];
	int m_skin;
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
