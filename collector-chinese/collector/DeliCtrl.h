#pragma once


// CDeliCtrl
//#include "Fm.h"

#define DELI_FRAME_TOP  200
#define DELI_FRAME_LEFT 20
#define DELI_FRAME_RIGHT 40
#define DELI_FRAME_BOTTOM 80

#define DELI_TOP_SPACE  (DELI_FRAME_TOP+80)
#define  DELI_BOTTOM_SPACE  80
#define  DELI_LEFT_SPACE  (DELI_FRAME_LEFT+200)
//#define  DELI_RIGHT_SPACE  240

#define	DELI_X_UNIT		100
#define DELI_Y_UNIT		50

#define  DELI_X_COUNT 24
#define DELI_Y_COUNT  10

#define  DELI_X_BOLD  9
#define  DELI_Y_BOLD  7

#define DELI_STAGE_COUNT_X 24
#define DELI_STAGE_UNIT_X  100
#define DELI_STAGE_COUNT_Y 14
#define DELI_STAGE_UNIT_Y  70
//#define DELI_STAGE_START_Y (DELI_TOP_SPACE+DELI_BOTTOM_SPACE+DELI_Y_COUNT*DELI_Y_UNIT)
const int DELI_STAGE_START_Y=DELI_TOP_SPACE+DELI_BOTTOM_SPACE+DELI_Y_COUNT * DELI_Y_UNIT;
const int DELI_STAGE_END_Y = DELI_STAGE_START_Y + DELI_STAGE_UNIT_Y * DELI_STAGE_COUNT_Y ;

#define DELI_PAGE_X		700
#define DELI_PAGE_Y		500

#define DT_SPACE_LEFT		10
#define DT_SPACE_TOP		10

#define DELI_MARK_DICUI		0x1
#define DELI_MARK_GJFB		0x2
#define DELI_MARK_GANGCHA	0x4
#define DELI_MARK_YINCHA	0x8
#define DELI_MARK_POMO		0x10
#define DELI_MARK_XIYANG	0x20
#define DELI_MARK_PGC		0x40

class CDeliCtrl : public CWnd
{
	DECLARE_DYNAMIC(CDeliCtrl)
public:
//	CFmContext* m_pContext;
	CPoint	m_ptCursor;
	int		m_nCurRecord;

	CMenu	m_PopMenu;
	int m_nHScrollRange;
	int m_nVScrollRange;
	int m_nHScrollPos;
	int m_nVScrollPos;
	int m_nHScrollIncr;
	int m_nVScrollIncr;


	CFont	m_ftDeli;
	CFont	m_ftDeliCheckTime;
	CPen*	m_pPenBlack;
	CPen*	m_pPenWhite;
	CPen*	m_pPenBlue;
	CPen*	m_pPenRed;
	CPen*	m_pPenBold;

	CBrush* m_pBrushWhite;
	CBrush* m_pBrushYellow;
	CBrush* m_pBrushBlue;
	CBrush* m_pBrushRed;
	CBrush* m_pBrushBlack;

	//CButton m_btRecord;

	int m_event[8];
	CString m_eventName[7];

private:
	void	CalcValueFromPoint(int nx, int ny, int* pMinute, int* pMM);
	void	CalcLMPointFromValue(int nMinute, int nMM, int* pX, int* pY);
//	int		CalcPointBelong(int nx, int ny);
	void	LogicPointFromClientPoint(LPPOINT ppt);
	void	ClientPointFromLogicPoint(LPPOINT ppt);
public:
	CDeliCtrl();
	virtual ~CDeliCtrl();
	virtual BOOL DestroyWindow();
	BOOL	Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID ); 
	void	OnDraw(CDC* pDC);
protected:
	afx_msg void OnPaint();
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPopDeliCev();
	afx_msg void OnPopDeliPre();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	DECLARE_MESSAGE_MAP()
};


