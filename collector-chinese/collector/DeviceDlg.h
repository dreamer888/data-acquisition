#pragma once


// CDeviceDlg �Ի���

class CDeviceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDeviceDlg)

public:
	CDeviceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
