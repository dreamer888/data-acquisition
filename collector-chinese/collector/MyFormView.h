#pragma once



// CMyFormView ������ͼ

class CMyFormView : public CFormView
{
	DECLARE_DYNCREATE(CMyFormView)

public :
	CMyFormView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyFormView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


