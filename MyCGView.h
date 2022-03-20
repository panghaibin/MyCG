// MyCGView.h : interface of the CMyCGView class
//
/////////////////////////////////////////////////////////////////////////////
#pragma warning(disable : 4244)

#if !defined(AFX_MYCGVIEW_H__10C1F43B_3A04_471D_9182_3E52C35B7CA2__INCLUDED_)
#define AFX_MYCGVIEW_H__10C1F43B_3A04_471D_9182_3E52C35B7CA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct EDGE
{
	float x;
	float delta_x;
	int y_max;
	EDGE* ptrNext;
}EDGE;

typedef struct SqStack {
	int* base;
	int* top;
	int stacksize;
}SqStack;

typedef struct PolyPoint {
	int x;
	int y;
	PolyPoint *next;
}PolyPoint;

#define first_size 400
#define add_size 40


class CMyCGView : public CView
{
protected: // create from serialization only
	CMyCGView();
	DECLARE_DYNCREATE(CMyCGView)

// Attributes
public:
	CMyCGDoc* GetDocument();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCGView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to m_draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	double BrzBernstein(int m, int n, double t);
	int BrzCombination(int m, int n);
	void BrzDrawSpline(PolyPoint p, CPen *pen, int draw_mode);
	void BrzDrawPointLine(PolyPoint p, CPen *pen_line, CPen *pen_point, int draw_mode);
	void BrzAddPoint(PolyPoint *p, int x,int y);
	void BrzInitPoint(PolyPoint *p);
	void OnTransRotShowMsg();
	void OnTransMoveShowMsg();
	void OnTransScalcShowMsg();
	void TransScalc(PolyPoint *p, double sx, double sy);
	void TransCalcCntrPoint(PolyPoint p, int *x, int *y);
	double TransRotCalcTheta(int xr, int yr, int x0, int y0, int x1, int y1);
	void TransRot(PolyPoint *p, double n);
	void TransMove(PolyPoint *p, int dx, int dy);
	void TransDrawCntrPoint(PolyPoint p, CPen *pen, int draw_mode);
	void TransGetCntrPoint(PolyPoint p, int *x, int *y);
	void TransSetCntrPoint(PolyPoint *p, int x,int y);
	void TransDrawPolyPoint(PolyPoint p, CPen *pen, int draw_mode);
	bool TransIsPointClose(PolyPoint p, CPoint m);
	void TransAddPoint(PolyPoint *p, int x, int y);
	void TransInitPoint(PolyPoint *p);
	void CutPolyBySHCheckEdge(int edge, int xy, int cmp);
	void CutPolyBySH();
	void CutPolyDrawPolyPoint(PolyPoint p, CPen *pen, int draw_mode);
	void OnCutDrawWin();
	bool CutPolyIsPointClose(PolyPoint p, CPoint m);
	void CutPolyAddPoint(PolyPoint *p, int x, int y);
	PolyPoint pp;
	//	PolyPoint npp;
	void CutPolyInitPoint(PolyPoint *p);
	int CutLineByCS(CDC *pDC, int x0, int y0, int x1, int y1);
	int CutGetCode(int x, int y);
	void FillBySeedMain();
	int fill_seed_y;
	int fill_seed_x;
	void FillBySeed(int x, int y, COLORREF boundaryColor, COLORREF newColor,CDC*pDC);
	int FillByEdgeRversion(CPoint m_p0, CPoint m_p1, CDC* pDC,int _y,int remark);
	void FillDrawLine(CPoint m_p0, CPoint m_p1, CDC* pDC);
	bool FillDrawLineIsClose(CPoint m_p0, CPoint m_p1);
	void OnEllipsePre();
	void DrawEllipseByMidpoint(CDC *pDC, int x0, int y0, int a, int b, COLORREF color);
	int DrawCircleCalcRadius(CPoint m_p1, CPoint p2);
	int test;
	void DrawCircleByBh(CDC *pDC, int x0, int y0, int r, COLORREF color);
	void OnCirclePre();
	void DrawCircleByMidpoint(CDC *pDC, int x0, int y0, int r, COLORREF color);

	//	m_func_flag=-1: 无
	//	0/1/2: 直线段 DDA/中点/FillDrawLine 预绘制  
	//	3/4/5: 直线段 DDA/中点/FillDrawLine 橡皮筋绘制
	//	6/7: 圆形 中点/FillDrawLine 预绘制
	//	8/9(del): 椭圆 中点/FillDrawLine(del) 预绘制
	//	10/11: 圆形 中点/FillDrawLine 橡皮筋绘制
	//	12/13(del): 椭圆 中点/FillDrawLine(del) 橡皮筋绘制
	//  14: 种子填充
	//  15: 直线段裁剪 Cohen-Sutherland编码
	//  16: 多边形裁剪 Sutherland-Hodgman算法
	//  17: 图形变换 绘制图形
	//  18: 设置图形中点
	//  19/20/21: 平移/旋转/缩放图形
	//  22/23/24: 贝塞尔添加点/移动点/删除点
	int m_func_flag;

//	1: 是起点 0: 是终点
	int m_is_start;
//	起点坐标
	CPoint m_p0;
//	终点坐标
	CPoint m_p1;
//	圆半径
	int m_r;
//	椭圆a,b
	int m_a;
	int m_b;

	BOOL m_draw;
	BOOL m_init;
	BOOL m_write;
	int m_max_y;

	EDGE* ET[1080];
	EDGE* AET;
	EDGE* TEMP;

	SqStack s;
	void StackCreat(SqStack* s);
	void StackPush(SqStack* s, int e);
	int StackPop(SqStack* s);
	bool StackIsEmpty(SqStack *s);

	int _y;

	int LEFT;
	int RIGHT;
	int BOTTOM;
	int TOP;
	int WL;
	int WR;
	int WB;
	int WT;

	void OnLinePre();
	void DrawLineByBh(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color);
	void DrawLineByMidpoint(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color);
	void DrawLineByDda(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color);

	virtual ~CMyCGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyCGView)
	afx_msg void OnLinePreDda();
	afx_msg void OnLinePreMidpoint();
	afx_msg void OnLinePreBh();
	afx_msg void OnLineDrawMidpoint();
	afx_msg void OnLineDrawDda();
	afx_msg void OnLineDrawBh();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClearScreen();
	afx_msg void OnCirclePreMidpoint();
	afx_msg void OnCircleDrawMidpoint();
	afx_msg void OnEllipsePreMidpoint();
	afx_msg void OnEllipseDrawMidpoint();
	afx_msg void OnCirclePreBh();
	afx_msg void OnCircleDrawBh();
	afx_msg void OnFillSeed();
	afx_msg void OnFillEdge();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFillForDraw();
	afx_msg void OnFillScan();
	afx_msg void OnCutLineByCS();
	afx_msg void OnCutPolyBySH();
	afx_msg void OnTransForDraw();
	afx_msg void OnTransSetCntr();
	afx_msg void OnTransMove();
	afx_msg void OnTransRot();
	afx_msg void OnTransScale();
	afx_msg void OnBrzAddPoint();
	afx_msg void OnBrzDrawSpline();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

#ifndef _DEBUG  // debug version in MyCGView.cpp
inline CMyCGDoc* CMyCGView::GetDocument()
   { return (CMyCGDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCGVIEW_H__10C1F43B_3A04_471D_9182_3E52C35B7CA2__INCLUDED_)
