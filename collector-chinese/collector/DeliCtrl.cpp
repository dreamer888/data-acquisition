// DeliCtrl.cpp : 实现文件
//

#include "stdafx.h"
//#include "CMS.h"
#include "DeliCtrl.h"
#include "resource.h"
//#include "DialogProcess.h"

// CDeliCtrl

IMPLEMENT_DYNAMIC(CDeliCtrl, CWnd)

CDeliCtrl::CDeliCtrl()
{
//	m_pContext = NULL;
	m_pPenBlack = NULL;
	m_pPenWhite = NULL;
	m_pPenBlue = NULL;
	m_pPenRed = NULL;
	m_pPenBold = NULL;

	m_pBrushWhite = NULL;
	m_pBrushYellow = NULL;
	m_pBrushBlue = NULL;
	m_pBrushRed = NULL;

	m_pBrushBlack = NULL;
	m_nHScrollRange = 0;
	m_nVScrollRange = 0;
	m_nHScrollPos = 0;
	m_nVScrollPos = 0;
	m_nHScrollIncr = 2;
	m_nVScrollIncr = 2;

	m_ptCursor.x = 0;
	m_ptCursor.y = 0;
	m_nCurRecord = -1;
}

CDeliCtrl::~CDeliCtrl()
{
	if(m_pPenBlack) delete m_pPenBlack;
	if(m_pPenWhite) delete m_pPenWhite;
	if(m_pPenBlue ) delete m_pPenBlue;
	if(m_pPenRed ) delete m_pPenRed;
	if(m_pPenBold) delete m_pPenBold;

	if( m_pBrushWhite) delete m_pBrushWhite;
	if( m_pBrushYellow ) delete m_pBrushYellow;
	if( m_pBrushBlue) delete m_pBrushBlue;
	if( m_pBrushRed ) delete m_pBrushRed;
	if (m_pBrushBlack) delete m_pBrushBlack;
}


BEGIN_MESSAGE_MAP(CDeliCtrl, CWnd)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	
	//ON_BN_CLICKED(IDC_BT_RECORD, OnBnClickedButtonRecord)
END_MESSAGE_MAP()



// CDeliCtrl 消息处理程序

BOOL CDeliCtrl::Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class
//	m_pContext = pContext;

	BOOL bRet = CWnd::Create(NULL, NULL, dwStyle, rect, pParentWnd, nID, NULL);
	if( !bRet ) return FALSE;
	return TRUE;
}


int CDeliCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_ftDeli.CreateFont(10, 0, 0, 0, FW_THIN,0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("宋体"));//arial,DEFAULT_CHARSET
	//m_ftDeli.CreatePointFont(7 * 10 , _T("宋体"), NULL);

//	m_ftDeliCheckTime.CreateFont(24, 0, 0, 0, FW_THIN,0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
//		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("arial"));//arial,DEFAULT_CHARSET
	m_ftDeliCheckTime.CreatePointFont(13 * 10 , _T("arial"), NULL);

	m_pPenBlack = new CPen(PS_SOLID, 2, RGB(0,0,0));
	m_pPenWhite = new CPen(PS_SOLID, 1, RGB(255,255,255));
	m_pPenBlue = new CPen(PS_SOLID, 2, RGB(0,0,255));
	m_pPenRed = new CPen(PS_SOLID, 2, RGB(255,0,0));
	m_pPenBold = new CPen(PS_SOLID, 8, RGB(0,0,0));

	m_pBrushWhite = new CBrush(RGB(255,255,255));
	m_pBrushYellow = new CBrush(RGB(255,255,0));
	m_pBrushBlue = new CBrush(RGB(0,0,255));

	m_pBrushBlack = new CBrush(RGB(0, 0, 0));

	m_pBrushRed = new CBrush(RGB(255,0,0));

	//m_btRecord.Create(_T("记录"), WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), this, IDC_BT_RECORD);
	 
	 
		m_eventName[0].Format(TEXT("開機"));
		m_eventName[1].Format(TEXT("關機"));
		m_eventName[2].Format(TEXT("倒縫"));
		m_eventName[3].Format(TEXT("剪線"));
		m_eventName[4].Format(TEXT("啟動"));
		m_eventName[5].Format(TEXT("停止"));
		m_eventName[6].Format(TEXT("斷線"));
	 
	return 0;
}


void CDeliCtrl::OnDraw(CDC* pDC)
{
	int nLoop, nx, ny, nx1, ny1, nw, nh;
	//pDC->SetMapMode(MM_LOMETRIC);

	CRect rc;
	this->GetParent()->GetClientRect(rc);

	CFont* pOldFont;
	//if(rc.Width()>1466)
		pOldFont = pDC->SelectObject(&m_ftDeliCheckTime);
	//else 
		//pOldFont = pDC->SelectObject(&m_ftDeli);
		

	//TCHAR tszText[7];

	/*
	//CBrush* pOldBrush = pDC->SelectObject(m_pBrushYellow);
	nx = DELI_LEFT_SPACE + DELI_X_UNIT;
	ny = -DELI_TOP_SPACE - DELI_Y_UNIT * 4;
	nw = nx + DELI_X_UNIT * 8;
	nh = ny - DELI_Y_UNIT * 3;
	pDC->FillRect(CRect(nx,ny,nw,nh) ,m_pBrushYellow); 
	*/

	CPen* pOldPen = pDC->SelectObject(m_pPenWhite);
	
	 
	int startx = 100;// 150;
	int starty = 40;
	

	//pDC->MoveTo(startx, starty);
	//pDC->LineTo(startx, 180);
	pDC->MoveTo(0, 440-40);
	pDC->LineTo(700, 440-40);

	int gap = 8 * 6;// 10 * 6;
	nw = 40;// 50;  //witdh

	

	nh = 440-40;// 190 - 5;//height
	
	CString cs;
	
	for (int i = 0; i < 7; i++)
	{
		nx = startx + i*gap+ i*nw;
		ny = 0 + nh - this->m_event[i] * ((float)nh) / (float)this->m_event[7];
		//ny =  nh - this->m_event[i] * ((float)nh) / (float)this->m_event[5];

		nx1 = nx + nw;
		ny1 = 440-40;

		if (m_event[7]>0)
		pDC->FillRect(CRect(nx, ny, nx1, ny1), m_pBrushYellow);

		cs.Format(_T("%s"), m_eventName[i]);
		 pDC->TextOut(nx+5, 440+20-40, cs);

		 if (m_event[7] > 0)
		 {
			 cs.Format(_T("%d"), m_event[i]);
			 if(ny>=starty)
			 pDC->TextOut(nx, ny - starty/2, cs);
			 else
			pDC->TextOut(nx, ny, cs);
		 }

	}
	
	pDC->SelectObject(pOldFont);
	pDC->SelectObject(pOldPen);
}

void CDeliCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	

	dc.SetMapMode(MM_TEXT);
	CRect rc ;
	GetClientRect(rc);


	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CBitmap Bm ;
	int nh = DELI_PAGE_X;//DELI_LEFT_SPACE + DELI_RIGHT_SPACE + DELI_X_UNIT*DELI_X_COUNT;
	int nv = DELI_PAGE_Y;//DELI_TOP_SPACE + DELI_BOTTOM_SPACE + DELI_Y_UNIT*DELI_Y_COUNT;

	BOOL b01 = Bm.CreateCompatibleBitmap(&dc, nh, nv);
	if(!b01) {
		::ReleaseDC(m_hWnd, MemDC.m_hDC);
		return ;
	}
	CBitmap* pOldBm = MemDC.SelectObject(&Bm);	
	// Do not call CWnd::OnPaint() for painting messages

	//MemDC.FillRect(CRect(0, 0, nh, nv), m_pBrushWhite);
	//MemDC.FillRect(CRect(0, 0, nh, nv), m_pBrushBlue);
	MemDC.FillRect(rc, m_pBrushBlack);
	OnDraw(&MemDC);

	//MemDC.SetMapMode(MM_TEXT);	

	dc.BitBlt(0, 
				0, 
				rc.Width(), 
				rc.Height(),
				&MemDC,
				m_nHScrollPos, 
				m_nVScrollPos,
				SRCCOPY);
//	MemDC.SelectObject(pOldPen);
//	MemDC.SelectObject(pOldBrush);
//	MemDC.SelectObject(pOldFont);
	MemDC.SelectObject(pOldBm);
	Bm.DeleteObject();
	::ReleaseDC(m_hWnd, MemDC.m_hDC);//lgl
	// Do not call CWnd::OnPaint() for painting messages
}

void CDeliCtrl::LogicPointFromClientPoint(LPPOINT ppt)
{
	CClientDC dc(this);
//	double dPixelsPerMMX = (double)(dc.GetDeviceCaps(HORZRES))/(double)(dc.GetDeviceCaps(HORZSIZE));
//	double dPixelsPerMMY = (double)(dc.GetDeviceCaps(VERTRES))/(double)(dc.GetDeviceCaps(VERTSIZE));
	//ppt->x = (ppt->x+m_nHScrollPos) * LOGIC_DOT_PER_MM * dc.GetDeviceCaps(HORZSIZE) / dc.GetDeviceCaps(HORZRES);
//	ppt->y = -((ppt->y+m_nVScrollPos) * LOGIC_DOT_PER_MM * dc.GetDeviceCaps(VERTSIZE) / dc.GetDeviceCaps(VERTRES));
}

void	CDeliCtrl::ClientPointFromLogicPoint(LPPOINT ppt)
{
	CClientDC dc(this);
	//ppt->x = (ppt->x * dc.GetDeviceCaps(HORZRES)) / dc.GetDeviceCaps(HORZSIZE) / LOGIC_DOT_PER_MM - m_nHScrollPos;
	//ppt->y = ((-ppt->y) * dc.GetDeviceCaps(VERTRES)) / dc.GetDeviceCaps(VERTSIZE) / LOGIC_DOT_PER_MM - m_nVScrollPos;
}


void CDeliCtrl::CalcValueFromPoint(int nx, int ny, int* pMinute, int* pMM)
{
	CClientDC dc(this);
	//double dPixelsPerMMX = (double)(dc.GetDeviceCaps(HORZRES))/(double)(dc.GetDeviceCaps(HORZSIZE));
	//double dPixelsPerMMY = (double)(dc.GetDeviceCaps(VERTRES))/(double)(dc.GetDeviceCaps(VERTSIZE));
	
	 //*pMinute = (int)(60.0 * ((((double)nx/dPixelsPerMMX)*LOGIC_DOT_PER_MM - DELI_LEFT_SPACE) / DELI_X_UNIT));
	 //*pMM = 100 - (int)(10.0 * ((((double)ny/dPixelsPerMMY)*LOGIC_DOT_PER_MM - DELI_TOP_SPACE) / DELI_Y_UNIT));
}

void CDeliCtrl::CalcLMPointFromValue(int nMinute, int nMM, int* pX, int* pY)
{
	*pX = nMinute * DELI_X_UNIT / 60 + DELI_LEFT_SPACE;
	*pY = -( (100 - nMM) * DELI_Y_UNIT / 10 + DELI_TOP_SPACE);
}

void CDeliCtrl::OnPopDeliCev() 
{
	
}

void CDeliCtrl::OnPopDeliPre() 
{
	// TODO: Add your command handler code here
	
	
}

BOOL CDeliCtrl::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::DestroyWindow();
}

void CDeliCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(rc);
	switch(nSBCode)
	{
	case SB_LEFT:			//Scroll to far left.
		m_nHScrollPos = 0;
		break;
	case SB_LINELEFT:		//Scroll left.
		m_nHScrollPos = max(0, m_nHScrollPos - m_nHScrollIncr);
		break;
	case SB_PAGELEFT:		//Scroll one page left.
		m_nHScrollPos -= (rc.Width()  / 2) ;
		m_nHScrollPos = max(0, m_nHScrollPos);
		break;
	case SB_LINERIGHT:		//Scroll right one line.
		m_nHScrollPos += m_nHScrollIncr;
		m_nHScrollPos = min( m_nHScrollPos, m_nHScrollRange);
		break;
	case SB_PAGERIGHT:		//Scroll one page right.
		m_nHScrollPos += (rc.Width() / 2) ;
		m_nHScrollPos = min( m_nHScrollPos, m_nHScrollRange);
		break;
	case SB_RIGHT:			//Scroll to far right.
		m_nHScrollPos = m_nHScrollRange;
		break;
	case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
	case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter.
		m_nHScrollPos = nPos;
		break;
	case SB_ENDSCROLL:		//End scroll.
	default:
		break;
	}
	SetScrollPos(SB_HORZ, m_nHScrollPos, TRUE );
	 
	Invalidate();		
//	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDeliCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rc;
	GetClientRect(rc);

	switch(nSBCode)
	{
	case SB_TOP:			//Scroll to far TOP.
		m_nVScrollPos = 0;
		break;
	case SB_LINEUP:		//Scroll left.
		m_nVScrollPos = max(0, m_nVScrollPos - m_nHScrollIncr);
		break;
	case SB_PAGEUP:		//Scroll one page left.
		m_nVScrollPos -= (rc.Height() / 2);
		m_nVScrollPos = max(0, m_nVScrollPos);
		break;
	case SB_LINEDOWN:		//Scroll right one line.
		m_nVScrollPos += m_nHScrollIncr;
		m_nVScrollPos = min( m_nVScrollRange, m_nVScrollPos);
		break;
	case SB_PAGEDOWN :		//Scroll one page right.
		m_nVScrollPos += (rc.Height() / 2) ;
		m_nVScrollPos = min( m_nVScrollPos, m_nVScrollRange);
		break;
	case SB_BOTTOM:			//Scroll to far right.
		m_nVScrollPos = m_nVScrollRange;
		break;
	case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
	case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter.
		m_nVScrollPos = nPos;
		break;
	case SB_ENDSCROLL:		//End scroll.
	default:
		break;
	}
	SetScrollPos(SB_VERT, m_nVScrollPos, TRUE );
	 

	Invalidate();	
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CDeliCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
}

