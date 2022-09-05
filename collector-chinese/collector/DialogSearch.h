#pragma once
#include "afxcmn.h"
#include "ReportCtrl.h"

#include "MyDatabase.h"

#include "DeliCtrl.h"
#include "afxwin.h"
#include "afxbutton.h"

// CDialogSearch 对话框

class CDialogSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSearch)

public:
	CDialogSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSearch();


	BOOL LoadListItem();
	BOOL ReLoadListItem();
	BOOL LoadEvents();
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//CListCtrl m_listctrl;
	CReportCtrl m_listctrl;
	virtual BOOL OnInitDialog(); 
	_RecordsetPtr pRecordset;
	int m_pageIndex;
	int m_pageCount;
	int m_maxPage;
	
	CString  m_tszSQL; 
	CDeliCtrl  m_DeliCtrl;
	int  m_event[8];// [6];
	//unsigned short m_pageCount;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	CString  m_eventName[7];

	BOOL m_bDisplayEvent;
	

	

	CMFCButton m_previous;
	CMFCButton m_next;
	
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedMfcbutton3();
	afx_msg void OnBnClickedMfcbutton4();
	CMFCButton m_first;
	CMFCButton m_last;
	afx_msg void OnBnClickedMfcbutton5();
	CMFCButton m_btEvent;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMfcbutton6();
};
