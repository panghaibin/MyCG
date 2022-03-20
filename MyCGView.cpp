// MyCGView.cpp : implementation of the CMyCGView class
//

#include "stdafx.h"
#include "MyCG.h"

#include "math.h"

#include "MyCGDoc.h"
#include "MyCGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyCGView

IMPLEMENT_DYNCREATE(CMyCGView, CView)

BEGIN_MESSAGE_MAP(CMyCGView, CView)
	//{{AFX_MSG_MAP(CMyCGView)
	ON_COMMAND(ID_LINE_PRE_DDA, OnLinePreDda)
	ON_COMMAND(ID_LINE_PRE_MIDPOINT, OnLinePreMidpoint)
	ON_COMMAND(ID_LINE_PRE_BH, OnLinePreBh)
	ON_COMMAND(ID_LINE_DRAW_MIDPOINT, OnLineDrawMidpoint)
	ON_COMMAND(ID_LINE_DRAW_DDA, OnLineDrawDda)
	ON_COMMAND(ID_LINE_DRAW_BH, OnLineDrawBh)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENU_CLEAR_SCREEN, OnClearScreen)
	ON_COMMAND(ID_CIRCLE_PRE_MIDPOINT, OnCirclePreMidpoint)
	ON_COMMAND(ID_CIRCLE_DRAW_MIDPOINT, OnCircleDrawMidpoint)
	ON_COMMAND(ID_ELLIPSE_PRE_MIDPOINT, OnEllipsePreMidpoint)
	ON_COMMAND(ID_ELLIPSE_DRAW_MIDPOINT, OnEllipseDrawMidpoint)
	ON_COMMAND(ID_CIRCLE_PRE_BH, OnCirclePreBh)
	ON_COMMAND(ID_CIRCLE_DRAW_BH, OnCircleDrawBh)
	ON_COMMAND(ID_FILL_SEED, OnFillSeed)
	ON_COMMAND(ID_FILL_EDGE, OnFillEdge)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_FILL_FOR_DRAW, OnFillForDraw)
	ON_COMMAND(ID_FILL_SCAN, OnFillScan)
	ON_COMMAND(ID_CUT_LINE_BY_CS, OnCutLineByCS)
	ON_COMMAND(ID_CUT_POLY_BY_SH, OnCutPolyBySH)
	ON_COMMAND(ID_TRANS_FOR_DRAW, OnTransForDraw)
	ON_COMMAND(ID_TRANS_SET_CNTR, OnTransSetCntr)
	ON_COMMAND(ID_TRANS_MOVE, OnTransMove)
	ON_COMMAND(ID_TRANS_ROT, OnTransRot)
	ON_COMMAND(ID_TRANS_SCALE, OnTransScale)
	ON_COMMAND(ID_BZR_ADD_POINT, OnBrzAddPoint)
	ON_COMMAND(ID_BZR_DRAW_SPLINE, OnBrzDrawSpline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCGView construction/destruction

CMyCGView::CMyCGView()
{
	// TODO: add construction code here

	m_func_flag = -1;
	m_is_start = -1;
//	m_p1.x=0;m_p1.y=0;
	m_r=0;
	m_a=0;
	m_b=0;

	test=0;

	m_draw = FALSE;
	m_init = FALSE;
	m_write = FALSE;
	StackCreat(&s);
	CutPolyInitPoint(&pp);

}

CMyCGView::~CMyCGView()
{
}

BOOL CMyCGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyCGView drawing

void CMyCGView::OnDraw(CDC* pDC)
{
	CMyCGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add m_draw code for native data here

	//	OnLinePreDda();
	//	DrawLineByBh(pDC, 100, 100, 400, 300, RGB(255, 0, 255));
	//	DrawCircleByMidpoint(pDC, 100, 100, 60, RGB(255,0,0));
	//	OnCirclePreMidpoint();
	//	DrawEllipseByMidpoint(pDC, 300, 200, 50, 20, RGB(255,0,0));
}

/////////////////////////////////////////////////////////////////////////////
// CMyCGView diagnostics

#ifdef _DEBUG
void CMyCGView::AssertValid() const
{
	CView::AssertValid();
}

void CMyCGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyCGDoc* CMyCGView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyCGDoc)));
	return (CMyCGDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyCGView message handlers

void CMyCGView::OnLinePreDda() 
{
	// TODO: Add your command handler code here
	m_func_flag = 0;
	OnLinePre();
}

void CMyCGView::OnLinePreMidpoint() 
{
	// TODO: Add your command handler code here
	m_func_flag = 1;
	OnLinePre();
}

void CMyCGView::OnLinePreBh() 
{
	// TODO: Add your command handler code her
	m_func_flag = 2;
	OnLinePre();
}

void CMyCGView::OnLineDrawMidpoint() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 4;
	m_is_start = 0;
}

void CMyCGView::OnLineDrawDda() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 3;
	m_is_start = 0;
}

void CMyCGView::OnLineDrawBh() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 5;
	m_is_start = 0;
}

void CMyCGView::DrawLineByDda(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color)
{
	int i;
	float length, x, y, dx, dy;
	length = abs(x1-x0);
	if (abs(y1-y0) > length)
	{
		length = abs(y1-y0);
	}
	dx = (float)((x1 - x0) / length);
 	dy = (float)((y1 - y0) / length);
	x = x0;
	y = y0;
	for (i = 1; i <= length; i++)
	{
		pDC->SetPixel((int)x, (int)y, color);
		x = x + dx;
		y = y + dy;
	}

}

void CMyCGView::DrawLineByMidpoint(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color)
{
	int a,b,d,d1,d2,x,y;

	x=x0;
	y=y0;
	a=y0-y1;
	b=x1-x0;

	int cx = (b>=0 ? 1 : (b=-b,-1));
	int cy = (a<=0 ? 1 : (a=-a,-1));

	if (-a<=b)
	{
		d=2*a+b;
		d1=2*a;
		d2=2*(a+b);
		while (x!=x1)
		{
			if(d<0)
			{
				y=y+cy;
				d=d+d2;
			}
			else
			{
				d=d+d1;
			}
			x=x+cx;
			pDC->SetPixel(x, y, color);
		}
	}
	else
	{
		d=a+2*b;
		d1=2*b;
		d2=2*(a+b);
		while(y!=y1)
		{
			if(d<0)
			{
				d=d+d1;
			}
			else
			{
				x=x+cx;
				d=d+d2;
			}
			y=y+cy;
			pDC->SetPixel(x, y, color);
		}
	}

//
//	d=2*a+b;
//	d1=2*a;
//	d2=2*(a+b);
//
//	pDC->SetPixel(x, y, color);
//	
//	while (x<=x1)
//	{
//		if (d<0)
//		{
//			x++;
//			y++;
//			d=d+d2;
//		}
//		else
//		{
//			x++;
//			d=d+d1;
//		}
//		pDC->SetPixel(x, y, color);
//	}
}

void CMyCGView::DrawLineByBh(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color)
{
	int temp;
	if (x1<x0)
	{
		temp=x0;
		x0=x1;
		x1=temp;
		temp=y0;
		y0=y1;
		y1=temp;
	}
	int x,y,dx,dy,e,i;
	x=x0;
	y=y0;
	dx=x1-x0;
	dy=y1-y0;
	if (abs(dx)>=abs(dy))
	{
		e=-dx;
		for(i=0; i<=dx; i++)
		{
			if (y0>y1)
			{
				dx=x1-x0;
				dy=y0-y1;
				pDC->SetPixel(x, y, color);
				x++;
				e=e+2*dy;
				if(e>=0)
				{
					y--;
					e=e-2*dx;
				}
			}
			else
			{
				pDC->SetPixel(x, y, color);
				x++;
				e=e+2*dy;
				if(e>=0)
				{
					y++;
					e=e-2*dx;
				}
			}
		}
	}
	else
	{
		if(y0>y1)
		{
			dx=x1-x0;
			dy=y0-y1;
			pDC->SetPixel(x, y, color);
			e=-dy;
			for (i=0; i<=dy; i++)
			{
				pDC->SetPixel(x, y, color);
				y--;
				e=e+2*dx;
				if(e>=0)
				{
					x++;
					e=e-2*dy;
				}
			}
		}
		else
		{
			e=-dy;
			for(i=0; i<=dy; i++)
			{
				pDC->SetPixel(x, y, color);
				y++;
				e=e+2*dx;
				if(e>=0)
				{
					x++;
					e=e-2*dy;
				}
			}
		}
	}
}

void CMyCGView::OnLinePre()
{
	CDC *pDC = GetDC();

	int x0, y0, x1, y1;
	int i=0;
	int step=5;
	int sleep_time=1;
	int x_offset, y_offset;
	COLORREF my_color[6] = {RGB(0, 0, 255), RGB(0, 255, 0), RGB(255, 0, 0),
							RGB(0, 255, 255), RGB(255,0,  255), RGB(255, 255, 0)};
//	函数指针，减少冗余代码
	void (CMyCGView::*DrawLine)(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color);
	
	if (m_func_flag==0)
	{
		x_offset=-50, y_offset=-50;
		DrawLine = CMyCGView::DrawLineByDda;
	}else if(m_func_flag==1)
	{
		x_offset=400, y_offset=-50;
		DrawLine = CMyCGView::DrawLineByMidpoint;
	}else if(m_func_flag==2)
	{
		x_offset=850, y_offset=-50;
		DrawLine = CMyCGView::DrawLineByBh;
	}

	for(x0=100,y0=300,x1=300,y1=300; y0>=100; y0=y0-step, i++)
	{
		(this->*DrawLine)(pDC, x0+x_offset, y0+y_offset, x1+x_offset, y1+y_offset, my_color[i%6]);
		Sleep(sleep_time);
	}
	for(x0=100,y0=100,x1=300,y1=300; x0<=500; x0=x0+step, i++)
	{
		(this->*DrawLine)(pDC, x0+x_offset, y0+y_offset, x1+x_offset, y1+y_offset, my_color[i%6]);
		Sleep(sleep_time);
	}
	for(x0=500,y0=100,x1=300,y1=300; y0<=500; y0=y0+step, i++)
	{
		(this->*DrawLine)(pDC, x0+x_offset, y0+y_offset, x1+x_offset, y1+y_offset, my_color[i%6]);
		Sleep(sleep_time);
	}
	for(x0=500,y0=500,x1=300,y1=300; x0>=100; x0=x0-step, i++)
	{
		(this->*DrawLine)(pDC, x0+x_offset, y0+y_offset, x1+x_offset, y1+y_offset, my_color[i%6]);
		Sleep(sleep_time);
	}
	for(x0=100,y0=500,x1=300,y1=300; y0>=300; y0=y0-step, i++)
	{
		(this->*DrawLine)(pDC, x0+x_offset, y0+y_offset, x1+x_offset, y1+y_offset, my_color[i%6]);
		Sleep(sleep_time);
	}

	ReleaseDC(pDC);
}

void CMyCGView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

//	限定flag在指定内才执行
	if ((3<=m_func_flag && m_func_flag<=5) 
		|| (10<=m_func_flag && m_func_flag<=13) 
		|| (15==m_func_flag)
		|| (19<=m_func_flag && m_func_flag<=20))
	{
		CDC *pDC=GetDC();
		pDC->SelectStockObject(NULL_BRUSH);
		//	void (CMyCGView::*DrawLine)(CDC *pDC, int x0, int y0, int x1, int y1, COLORREF color);
		if (m_is_start==0)  //是起点
		{
			m_p0 = m_p1 = point; //记录第一次单击鼠标位置，定起点
			m_is_start++;
		}
		else if(m_is_start==1)
		{
			m_p1 = point;  //记录第二次单击鼠标的位置，定终点的点
			m_is_start--;   // 为新绘图作准备
			if(m_func_flag==3)
			{
				DrawLineByDda(pDC, m_p0.x, m_p0.y, m_p1.x, m_p1.y, RGB(255,0,0));
			}
			else if(m_func_flag==4)
			{
				DrawLineByMidpoint(pDC, m_p0.x, m_p0.y, m_p1.x, m_p1.y, RGB(255,0,0));
			}
			else if(m_func_flag==5)
			{
				DrawLineByBh(pDC, m_p0.x, m_p0.y, m_p1.x, m_p1.y, RGB(255,0,0));
			}
			else if(m_func_flag==10)
			{
				m_r = DrawCircleCalcRadius(m_p0, m_p1);
				DrawCircleByMidpoint(pDC, m_p0.x, m_p0.y, m_r, RGB(255,0,0));
			}
			else if(m_func_flag==11)
			{
				m_r = DrawCircleCalcRadius(m_p0, m_p1);
				DrawCircleByBh(pDC, m_p0.x, m_p0.y, m_r, RGB(255,0,0));
			}
			else if(m_func_flag==12)
			{
				m_a=abs(m_p1.x-m_p0.x);
				m_b=abs(m_p1.y-m_p0.y);
				DrawEllipseByMidpoint(pDC, m_p0.x, m_p0.y, m_a, m_b, RGB(255,0,0));
			}
			else if(m_func_flag==15)
			{
				int draw_mode=pDC->SetROP2(R2_XORPEN);
				pDC->SelectStockObject(WHITE_PEN);

				pDC->MoveTo(m_p0.x,m_p0.y);
				pDC->LineTo(m_p1.x,m_p1.y);
				pDC->SetROP2(draw_mode);

				CPen PenRed(PS_SOLID, 1, RGB(255,0,0));
				pDC->SelectObject(&PenRed);
				CutLineByCS(pDC, m_p0.x, m_p0.y, m_p1.x, m_p1.y);
			}
			else if(m_func_flag==19 || m_func_flag==20)
			{
				CPen PenBlack(PS_SOLID, 1, RGB(0,0,0));
				TransDrawPolyPoint(pp, &PenBlack, R2_XORPEN);
			}

		}
		ReleaseDC(pDC); //释放设备环境
	}
	
	if(m_func_flag==14)
	{
		fill_seed_x = point.x;
		fill_seed_y = point.y;
		m_func_flag = -1;
		FillBySeedMain();
	}

	if(m_func_flag==16)
	{
		CDC *pDC=GetDC();
		int draw_mode=pDC->SetROP2(R2_XORPEN);
		pDC->SelectStockObject(WHITE_PEN);
		//	pDC->SelectStockObject(NULL_BRUSH);
		if (m_is_start==0)
		{
			CutPolyAddPoint(&pp, point.x, point.y);
			m_p0 = m_p1 = point;
			m_is_start++;
		}
		else if(m_is_start==1)
		{
			m_p1 = point;
			if (!CutPolyIsPointClose(pp, point))
			{
				pDC->MoveTo(m_p0.x,m_p0.y);
				pDC->LineTo(m_p1.x,m_p1.y);
				CutPolyAddPoint(&pp, point.x, point.y);
				m_p0 = m_p1 = point;
			}
			else
			{
				pDC->MoveTo(m_p0.x, m_p0.y);
				pDC->LineTo((pp.next)->x, (pp.next)->y);
				
				pDC->SetROP2(draw_mode);
				CutPolyBySH();

//				Sleep(1000);
//				CPen PenRed(PS_SOLID, 1, RGB(255,0,0));
//				CutPolyDrawPolyPoint(pp, &PenRed, draw_mode);

				m_is_start--;
				CutPolyInitPoint(&pp);
			}
		}
		ReleaseDC(pDC); 
	}

	if(m_func_flag==17)
	{
		CDC *pDC=GetDC();
		int draw_mode=pDC->SetROP2(R2_XORPEN);
		pDC->SelectStockObject(WHITE_PEN);
		//	pDC->SelectStockObject(NULL_BRUSH);
		if (m_is_start==0)
		{
			TransAddPoint(&pp, point.x, point.y);
			m_p0 = m_p1 = point;
			m_is_start++;
		}
		else if(m_is_start==1)
		{
			m_p1 = point;
			if (!TransIsPointClose(pp, point))
			{
				pDC->MoveTo(m_p0.x,m_p0.y);
				pDC->LineTo(m_p1.x,m_p1.y);
				TransAddPoint(&pp, point.x, point.y);
				m_p0 = m_p1 = point;
			}
			else
			{
				CPen PenBlack(PS_SOLID, 1, RGB(0,0,0));
				pDC->MoveTo(m_p0.x, m_p0.y);
				pDC->LineTo((pp.next)->x, (pp.next)->y);
				int xr,yr;
				TransCalcCntrPoint(pp, &xr, &yr);
				TransSetCntrPoint(&pp, xr, yr);
				TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
				pDC->SetROP2(draw_mode);

				m_is_start=-1;
			}
		}
		ReleaseDC(pDC); 
	}

	if(m_func_flag==18)
	{
		if (m_is_start==0)
		{
			CPen PenBlack(PS_SOLID, 1, RGB(0,0,0));
			TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
			TransSetCntrPoint(&pp, point.x, point.y);
			TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);

			m_is_start=-1;
		}
	}

	if (m_func_flag==22)
	{
		CDC *pDC=GetDC();
		int draw_mode=pDC->SetROP2(R2_XORPEN);
		pDC->SelectStockObject(WHITE_PEN);
		if (m_is_start==0)
		{
			pDC->SelectStockObject(BLACK_PEN);
			pDC->Ellipse(point.x-5, point.y-5, point.x+5, point.y+5);
			pDC->SelectStockObject(WHITE_PEN);
			BrzAddPoint(&pp, point.x, point.y);
			m_p0 = m_p1 = point;
			m_is_start++;
		}
		else if(m_is_start==1)
		{
			m_p1 = point;
			pDC->SelectStockObject(BLACK_PEN);
			pDC->Ellipse(point.x-5, point.y-5, point.x+5, point.y+5);
			pDC->SelectStockObject(WHITE_PEN);
			pDC->MoveTo(m_p0.x,m_p0.y);
			pDC->LineTo(m_p1.x,m_p1.y);
			BrzAddPoint(&pp, point.x, point.y);
			m_p0 = m_p1 = point;
		}
		ReleaseDC(pDC); 
	}

	CView::OnLButtonDown(nFlags, point);
}

void CMyCGView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CDC *pDC=GetDC();

	//	在左上角输出坐标
	char position[50];
	sprintf(position, "(%4d, %4d)       ", point.x, point.y);
	pDC->TextOut(5, 5, position);

	//	限定flag在指定内才执行
	if ((3<=m_func_flag && m_func_flag<=5) 
		|| (10<=m_func_flag && m_func_flag<=13) 
		|| (15==m_func_flag)
		|| (19<=m_func_flag && m_func_flag<=21) )
	{
		//	CDC *pDC=GetDC();
		int draw_mode=pDC->SetROP2(R2_XORPEN);
		pDC->SelectStockObject(NULL_BRUSH);   
		if(m_is_start==1)
		{
			CPoint pre_point, cur_point;
			pre_point=m_p1;
			cur_point=point;

			CPen PenBlack(PS_SOLID, 1, RGB(0,0,0));
			CPen PenWhite(PS_SOLID, 1, RGB(255,255,255));

			if(m_func_flag==3)
			{
				DrawLineByDda(pDC, m_p0.x, m_p0.y, pre_point.x, pre_point.y, RGB(255,255,255));
				DrawLineByDda(pDC, m_p0.x, m_p0.y, cur_point.x, cur_point.y, RGB(255,255,255));
			}
			else if(m_func_flag==4)
			{
				DrawLineByMidpoint(pDC, m_p0.x, m_p0.y, pre_point.x, pre_point.y, RGB(255,255,255));
				DrawLineByMidpoint(pDC, m_p0.x, m_p0.y, cur_point.x, cur_point.y,RGB(255,255,255));
			}
			else if(m_func_flag==5)
			{
				DrawLineByBh(pDC, m_p0.x, m_p0.y, pre_point.x, pre_point.y, RGB(255,255,255));
				DrawLineByBh(pDC, m_p0.x, m_p0.y, cur_point.x, cur_point.y,RGB(255,255,255));
			}
			else if(m_func_flag==10)
			{
				m_r = DrawCircleCalcRadius(m_p0, pre_point);
				DrawCircleByMidpoint(pDC, m_p0.x, m_p0.y, m_r, RGB(255,255,255));
				m_r = DrawCircleCalcRadius(m_p0, cur_point);
				DrawCircleByMidpoint(pDC, m_p0.x, m_p0.y, m_r, RGB(255,255,255));
			}
			else if(m_func_flag==11)
			{
				m_r = DrawCircleCalcRadius(m_p0, pre_point);
				DrawCircleByBh(pDC, m_p0.x, m_p0.y, m_r, RGB(255,255,255));
				m_r = DrawCircleCalcRadius(m_p0, cur_point);
				DrawCircleByBh(pDC, m_p0.x, m_p0.y, m_r, RGB(255,255,255));
			}
			else if(m_func_flag==12)
			{
				m_a=abs(pre_point.x-m_p0.x);
				m_b=abs(pre_point.y-m_p0.y);
				DrawEllipseByMidpoint(pDC, m_p0.x, m_p0.y, m_a, m_b, RGB(255,255,255));
				
				m_a=abs(m_p0.x-cur_point.x);
				m_b=abs(m_p0.y-cur_point.y);
				DrawEllipseByMidpoint(pDC, m_p0.x, m_p0.y, m_a, m_b, RGB(255,255,255));
			}
			else if(m_func_flag==15)
			{
				pDC->SelectStockObject(WHITE_PEN);
				pDC->MoveTo(m_p0.x, m_p0.y);
				pDC->LineTo(pre_point.x, pre_point.y);

				pDC->MoveTo(m_p0.x, m_p0.y);
				pDC->LineTo(cur_point.x, cur_point.y);
			}
			else if(m_func_flag==19)
			{
				TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
				TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
				TransMove(&pp, cur_point.x-pre_point.x, cur_point.y-pre_point.y);
				TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
				TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
			}
			else if(m_func_flag==20)
			{
				int xr, yr;
				TransGetCntrPoint(pp, &xr, &yr);
				double theta;
				theta = TransRotCalcTheta(xr, yr, pre_point.x, pre_point.y, cur_point.x, cur_point.y);

				TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
				TransRot(&pp, theta);
				TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
			}

			m_p1=point;
		}
		pDC->SetROP2(draw_mode);
		//	ReleaseDC(pDC);
	}

	ReleaseDC(pDC);
	
	CView::OnMouseMove(nFlags, point);
}

void CMyCGView::OnClearScreen() 
{
	// TODO: Add your command handler code here
	
	RedrawWindow();
	m_func_flag = -1;
	m_is_start = -1;

	m_draw = FALSE;
	m_init = FALSE;
	m_write = FALSE;

	StackCreat(&s);
	CutPolyInitPoint(&pp);

}

void CMyCGView::OnCirclePreMidpoint() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 6;
	OnCirclePre();
}

void CMyCGView::OnCircleDrawMidpoint() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 10;
	m_is_start = 0;
}

void CMyCGView::OnEllipsePreMidpoint() 
{
	// TODO: Add your command handler code here

	m_func_flag = 8;
	OnEllipsePre();
}

void CMyCGView::OnEllipseDrawMidpoint() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 12;
	m_is_start = 0;
}

void CMyCGView::OnCirclePreBh() 
{
	// TODO: Add your command handler code here
	
	m_func_flag = 7;
	OnCirclePre();

}

void CMyCGView::OnCircleDrawBh() 
{
	// TODO: Add your command handler code here
	m_func_flag = 11;
	m_is_start = 0;
}

//DEL void CMyCGView::OnEllipsePreBh() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	m_func_flag = 9;
//DEL }

//DEL void CMyCGView::OnEllipseDraWTh() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	m_func_flag = 13;
//DEL 	m_is_start = 0;
//DEL }

void CMyCGView::DrawCircleByMidpoint(CDC *pDC, int x0, int y0, int r, COLORREF color)
{
//	char te[50];
//	sprintf(te, "%4d  %4d   %4d    %4d      ", x0,y0,r,test);
//	pDC->TextOut(600, 100+test*18, te);
//	test++;

	int x, y, d;

	x=0;
	y=r;
	d=1-r;
	pDC->SetPixel(x0, y0+r, color);
	pDC->SetPixel(x0, y0-r, color);
	pDC->SetPixel(x0+r, y0, color);
	pDC->SetPixel(x0-r, y0, color);
	while (x<y)
	{
		if(d<0)
		{
			d+=2*x+3;
		}
		else
		{
			d+=2*(x-y)+5;
			y--;
		}
		x++;
		pDC->SetPixel(x0+x, y0+y, color);
		pDC->SetPixel(x0-x, y0+y, color);
		pDC->SetPixel(x0+x, y0-y, color);
		pDC->SetPixel(x0-x, y0-y, color);
		pDC->SetPixel(x0+y, y0+x, color);
		pDC->SetPixel(x0-y, y0+x, color);
		pDC->SetPixel(x0+y, y0-x, color);
		pDC->SetPixel(x0-y, y0-x, color);
	}
	
}

void CMyCGView::OnCirclePre()
{
	CDC *pDC = GetDC();
	//	int r;
	int i, j;
	int x_offset, y_offset;
	COLORREF my_color[3] = {RGB(0, 0, 255), RGB(255, 0, 0), RGB(0, 255, 0), 
							//	RGB(0, 255, 255), RGB(255,0,  255), RGB(255, 255, 0)
							};
	POINT p[9]={{100,100}, {200,100}, {300,100}, 
				{100,200}, {200,200}, {300,200}, 
				{100,300}, {200,300}, {300,300}};
	int r[3]={100, 80, 60};
	void (CMyCGView::*DrawCircle)(CDC *pDC, int x0, int y0, int r, COLORREF color);

	if (m_func_flag == 6)
	{
		x_offset = 50, y_offset = 50;
		DrawCircle = CMyCGView::DrawCircleByMidpoint;
	}else if(m_func_flag == 7)
	{
		x_offset = 500, y_offset = 50;
		DrawCircle = CMyCGView::DrawCircleByBh;
	}

	for (i=0; i<9; i++){
		for (j=0; j<3; j++)
		{
			(this->*DrawCircle)(pDC, p[i].x+x_offset, p[i].y+y_offset, r[j], my_color[(j)%3]);
		}
	}

	ReleaseDC(pDC);
}

void CMyCGView::DrawCircleByBh(CDC *pDC, int x0, int y0, int r, COLORREF color)
{
//	char te[50];
//	sprintf(te, "%4d  %4d   %4d    %4d      ", x0,y0,r,test);
//	pDC->TextOut(1000, 100+test*18, te);
//	test++;

	int x, y, p;
	x=0;
	y=r;
	//	p=1.5-2*r;
	p=3-2*r;
	while (x<y)
	{
		pDC->SetPixel(x0 + x, y0 + y, color);
		pDC->SetPixel(x0 - x, y0 + y, color);
		pDC->SetPixel(x0 + x, y0 - y, color);
		pDC->SetPixel(x0 - x, y0 - y, color);
		pDC->SetPixel(x0 + y, y0 + x, color);
		pDC->SetPixel(x0 - y, y0 + x, color);
		pDC->SetPixel(x0 + y, y0 - x, color);
		pDC->SetPixel(x0 - y, y0 - x, color);
		if(p<0)
		{
			p += 4 * x + 6;
			//	p=p+8*x+12;
		}
		else
		{
			p += 4 * (x - y) + 10;
			//	p=p+8*(x-y)+20;
			y--;
		}
		x++;
	}
}

int CMyCGView::DrawCircleCalcRadius(CPoint m_p0, CPoint m_p1)
{
	int dx = m_p0.x-m_p1.x;
	int dy = m_p0.y-m_p1.y;
	return (int)sqrt(dx*dx+dy*dy);
}

void CMyCGView::DrawEllipseByMidpoint(CDC *pDC, int x0, int y0, int a, int b, COLORREF color)
{
	int x,y;
	float d1,d2;
	x=0;
	y=b;
	d1=b*b+a*a*(-b+0.25);
	//	pDC->SetPixel(x+x0, y+y0, color);
	while (b*b*(x+1)<a*a*(y-0.5))
	{
		if (d1<0)
		{
			d1 += b*b*(2*x+3);
        }
		else
		{
			d1+=(b*b*(2*x+3)+a*a*(-2*y+2));
			y--;
        }
		x++;
		pDC->SetPixel(x0+x,y0+y,color);
		pDC->SetPixel(x0+x,y0-y,color);
		pDC->SetPixel(x0-x,y0+y,color);
		pDC->SetPixel(x0-x,y0-y,color);
	} // 上半部分
    //	d2=(b*(x+0.5))*(b*(x+0.5))+(a*(y-1))*(a*(y-1))-(a*b)*(a*b);
    d2=sqrt(b*(x+0.5))+sqrt(a*(y-1))-sqrt(a*b);
    while (y>0)
	{
		if (d2<0)
        {
			d2 += b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
		}
        else
		{
			d2 += a*a*(-2*y+3);
		} 
		y--;
		pDC->SetPixel(x0+x,y0+y,color);
		pDC->SetPixel(x0+x,y0-y,color);
		pDC->SetPixel(x0-x,y0+y,color);
		pDC->SetPixel(x0-x,y0-y,color);
	} //下半部分
}

void CMyCGView::OnEllipsePre()
{
	CDC *pDC = GetDC();
	int i, j;
	int x_offset, y_offset;
	COLORREF my_color[6] = {RGB(0, 0, 255), RGB(255, 0, 0), RGB(0, 255, 0), 
							RGB(0, 255, 255), RGB(255,0,  255), RGB(255, 255, 0)
							};
	int a[6] = {200, 170, 100, 40};
	
	void (CMyCGView::*DrawEllipse)(CDC *pDC, int x0, int y0, int a, int b, COLORREF color);

	if (m_func_flag == 8)
	{
		x_offset=1050, y_offset=150;
		DrawEllipse = CMyCGView::DrawEllipseByMidpoint;
	}

	for (i=0;i<4;i++)
	{
		for (j=3;j>=0;j--)
		{
			if (a[i]!=a[j])
			{
				(this->*DrawEllipse)(pDC, 100+x_offset, 100+y_offset, a[i], a[j], my_color[(i+j)%3]);
			}
		}
	}
	ReleaseDC(pDC);
}

void CMyCGView::OnFillEdge() 
{
	// TODO: Add your command handler code here
	CDC* pDC;
	CPoint p;
	CPoint p_temp;
	pDC = GetDC();
	int count = 0;
	int x_, y_;
	//	int _y;
	BOOL first=TRUE;
	int k;
	int flag;
	COLORREF w = RGB(255, 255, 255);
	COLORREF b = RGB(0, 0, 0);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	while(!StackIsEmpty(&s))
	{
		flag = 0;
		if(first)
		{
			m_p0.y = StackPop(&s);
			m_p0.x = StackPop(&s);
			m_p1.y = StackPop(&s);
			m_p1.x = StackPop(&s);
			p.y = StackPop(&s);
			p.x = StackPop(&s);
			p_temp.y = StackPop(&s);
			p_temp.x = StackPop(&s);
			StackPush(&s, p_temp.x);
			StackPush(&s, p_temp.y);
			
			k = (m_p1.y - m_p0.y) * (p.y - m_p1.y);
			if (k >= 0)
				flag = 0;
			else
				flag = 1;
			_y = FillByEdgeRversion(m_p0, m_p1, pDC, _y,flag);
			first = FALSE;
		}
		else
		{
			m_p0 = m_p1;
			m_p1 = p;
			p.y = StackPop(&s);
			p.x = StackPop(&s);
			k = (m_p1.y - m_p0.y)*(p.y-m_p1.y);
			if (k >= 0)
				flag = 0;
			else
				flag = 1;
			_y=FillByEdgeRversion(m_p0, m_p1, pDC,_y,flag);
		}
		if(flag==1)
		{
			x_ = m_p1.x;
			y_ = m_p1.y;
			for (; x_ < cx; x_++)
			{
				if (pDC->GetPixel(x_, y_) == w)
				{
					pDC->SetPixelV(x_, y_, b);
				}
				else
				{
					pDC->SetPixelV(x_, y_, w);
				}
			}
		}
	}
	if(StackIsEmpty(&s))
	{

		_y = FillByEdgeRversion(m_p1, p, pDC, _y, 0);
		x_ = p.x;
		y_ = p.y;
		k = (p_temp.y - p.y) * (p.y - m_p1.y);
		if (k <= 0)
			flag = 0;
		else
			flag = 1;
		if(flag==0)
		{
			for (; x_ < cx; x_++)
			{
				if (pDC->GetPixel(x_, y_) == w)
				{
					pDC->SetPixelV(x_, y_, b);
				}
				else
				{
					pDC->SetPixelV(x_, y_, w);
				}
			}
		}
	}
	ReleaseDC(pDC);
}

void CMyCGView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CPoint p;
	CDC* pDC;
	EDGE* e;
	EDGE* mark=NULL;
	pDC = GetDC();
	float _x, _delat_x;
	int _y_max;
	int i=0;
	if(m_draw)
	{
		if(!m_init)
		{
			m_p0 = point;
			m_p1 = m_p0;
			m_init = TRUE;

			StackPush(&s, m_p0.x);
			StackPush(&s, m_p0.y);
		}
		else if(!FillDrawLineIsClose(m_p0,point))
		{
			m_write = TRUE;
			p = m_p1;
			m_p1 = point;
			FillDrawLine(p, m_p1, pDC);

			StackPush(&s, point.x);
			StackPush(&s, point.y);
		}
		else
		{
			p = m_p0;
			m_draw = FALSE;
			FillDrawLine(m_p1, m_p0, pDC);

			StackPush(&s, m_p0.x);
			StackPush(&s, m_p0.y);
		}
		if(m_write==TRUE)
		{
			if(m_p1.y>m_max_y)
			{
				m_max_y = m_p1.y;
			}
			if(p.y==m_p1.y)
			{
			}
			else if (p.y>m_p1.y)
			{
				_y_max = p.y;
				if(p.x==m_p1.x)
				{
					_delat_x = 0;
				}
				else
				{
					_delat_x = ((float)p.x - (float)m_p1.x) / ((float)p.y - (float)m_p1.y);
				}
				_x = m_p1.x;
				e = (EDGE*)malloc(sizeof(EDGE));
				e->delta_x = _delat_x;
				e->y_max = _y_max;
				e->x = (float)_x;
				e->ptrNext = NULL;
				for (mark= ET[m_p1.y]; mark->ptrNext != (void *)0; mark = mark->ptrNext);
				mark->ptrNext = e;

			}
			else
			{
				_y_max = m_p1.y;
				if (p.x == m_p1.x)
				{
					_delat_x = 0;
				}
				else
				{
					_delat_x = ((float)p.x - (float)m_p1.x) / ((float)p.y - (float)m_p1.y);
				}
				_x = p.x;
				e = (EDGE*)malloc(sizeof(EDGE));
				e->delta_x = _delat_x;
				e->y_max = _y_max;
				e->x = (float)_x;
				e->ptrNext = NULL;
				for (mark = ET[p.y]; mark->ptrNext != (void *)0; mark = mark->ptrNext);
				mark->ptrNext=e;
			}
			if(p==m_p0)
			{
				m_write = FALSE;
			}
			
			
		}
	}
	ReleaseDC(pDC);


	CView::OnLButtonUp(nFlags, point);
}

bool CMyCGView::FillDrawLineIsClose(CPoint m_p0, CPoint m_p1)
{
//	判断点击的两点距离，相近则合在一起
	int a, b;
	int num = 15;
	a = abs(m_p0.x - m_p1.x);
	b = abs(m_p0.y - m_p1.y);
	if (a > num || b > num)
		return FALSE;
	else
		return TRUE;
}

void CMyCGView::FillDrawLine(CPoint m_p0, CPoint m_p1, CDC *pDC)
{
	pDC->MoveTo(m_p0.x, m_p0.y);
	pDC->LineTo(m_p1.x, m_p1.y);
//	int i, s1, s2, interchange,x,y;
//	float dx, dy, f, temp;
//	x = m_p0.x;
//	y = m_p0.y;
//	dx = abs(m_p1.x - m_p0.x); dy = abs(m_p1.y - m_p0.y);
//	if ((m_p1.x - m_p0.x) >= 0) s1 = 1; else s1 = -1;
//	if ((m_p1.y - m_p0.y) >= 0) s2 = 1; else s2 = -1;
//	if (dy > dx)
//	{
//		temp = dx;
//		dx = dy;
//		dy = temp;
//		interchange = 1;
//	}
//	else interchange = 0;
//	f = 2 * dy - dx;
//	pDC->SetPixelV(x, y, RGB(0, 0, 0));
//	for(i=1;i<=dx;i++)
//	{
//		if(f>=0)
//		{
//			if (interchange == 1) x += s1;
//			else y += s2;
//			f =f- 2 * dx;
//		}
//		if (interchange == 1)y += s2;
//		else x += s1;
//		pDC->SetPixelV(x, y, RGB(0, 0, 0));
//		f =f+ 2 * dy;
//	}

}

void CMyCGView::OnFillForDraw() 
{
	// TODO: Add your command handler code here
	m_draw = TRUE;
	m_init = FALSE;
	m_write = FALSE;
	int i;
	for (i=0;i<1080;i++)
	{
		ET[i] = (EDGE*)malloc(sizeof(EDGE));
		ET[i]->ptrNext = NULL;
	}
}

void CMyCGView::OnFillSeed() 
{
	// TODO: Add your command handler code here
	m_func_flag = 14;

	CDC *pDC = GetDC();
	pDC->TextOut(150, 10, "在所画图案内点击以进行填充");
	ReleaseDC(pDC);
}

void CMyCGView::StackCreat(SqStack *s) 
{
	s->base = (int*)malloc(first_size * sizeof(int));
	s->top = s->base; s->stacksize = first_size;
}

void CMyCGView::StackPush(SqStack *s, int e)
{
	if (s->top - s->base >= s->stacksize) {
		s->base = (int*)realloc(s->base, (s->stacksize + add_size) * sizeof(int));
		s->top = s->base + s->stacksize; s->stacksize = s->stacksize + add_size;
	}
	*s->top = e; s->top++;
}

int CMyCGView::StackPop(SqStack *s)
{
	return *--(s->top);
}

bool CMyCGView::StackIsEmpty(SqStack *s)
{
	if (s->top == s->base)
		return TRUE;
	else
		return FALSE;
}

int CMyCGView::FillByEdgeRversion(CPoint m_p0, CPoint m_p1, CDC *pDC, int _y, int remark)
{
	CPoint point,p;
	point = m_p1;
	COLORREF w = RGB(255, 255, 255);
	COLORREF b = RGB(0, 0, 0);
	int cy = GetSystemMetrics(SM_CYFULLSCREEN);
	int cx = GetSystemMetrics(SM_CXFULLSCREEN);
	int mark = 0;

	int i, s1, s2, interchange,x,y;
	float dx, dy, f, temp;
	x = m_p0.x;
	y = m_p0.y;
	dx = abs(m_p1.x - m_p0.x); dy = abs(m_p1.y - m_p0.y);
	if ((m_p1.x - m_p0.x) >= 0) s1 = 1; else s1 = -1;
	if ((m_p1.y - m_p0.y) >= 0) s2 = 1; else s2 = -1;
	if (dy >= dx)
	{
		temp = dx;
		dx = dy;
		dy = temp;
		interchange = 1;
	}
	else interchange = 0;
	f = 2 * dy - dx;
	//pDC->SetPixelV(x, y, RGB(0, 0, 0));
	/*p.x = x;
	if (pDC->GetPixel(p.x, y) == w)
	{
		pDC->SetPixelV(p.x, y, b);
	}
	else
	{
		pDC->SetPixelV(p.x, y, w);
	}*/
		_y = y;
	for(i=0;i<=dx;i++)
	{

		if(i!=dx)
		{
			if (f >= 0)
			{
				if (interchange == 1) x += s1;
				else  y += s2;
				f = f - 2 * dx;
			}
			if (interchange == 1)y += s2;
			else x += s1;
			//pDC->SetPixelV(x, y, RGB(0, 0, 0));
			p.x = x;
			//p.y = y;
			if (_y != y && i != dx)
			{
				_y = y;
				for (; p.x < cx; p.x++)
				{
					if (pDC->GetPixel(p.x, y) == w)
					{
						pDC->SetPixelV(p.x, y, b);
					}
					else
					{
						pDC->SetPixelV(p.x, y, w);
					}
				}
			}
			f = f + 2 * dy;
		}
		else
		{
			if (f > 0)
			{
				if (m_p1.y > m_p0.y)
					_y--;
				else
					_y++;
			}
		}
	}
	return _y;
}

void CMyCGView::FillBySeed(int x, int y, COLORREF boundaryColor, COLORREF newColor, CDC *pDC)
{
	COLORREF c = pDC->GetPixel(x,y);
	if ((c != boundaryColor) && (c != newColor))
	{	                   // 前者说明已画到边界，后者说明该点已画过
		pDC->SetPixelV(x, y, newColor);
		FillBySeed(x, y + 1, boundaryColor, newColor,pDC);
		FillBySeed(x, y - 1, boundaryColor, newColor, pDC);
		FillBySeed(x - 1, y, boundaryColor, newColor, pDC);
		FillBySeed(x + 1, y, boundaryColor, newColor, pDC);
	}
}

void CMyCGView::OnFillScan() 
{
	// TODO: Add your command handler code here
	AET = (EDGE*)malloc(sizeof(EDGE));
	AET->ptrNext = NULL;
	int i = 0,  y = 0;
	float x;
	CDC* pDC;
	pDC = GetDC();
	for (y = 0; y < m_max_y; y++)
	{
		EDGE*p = AET;
		while (p->ptrNext)
		{
			if (p->ptrNext->y_max == y)
			{
				EDGE* pDlete = p->ptrNext;
				p->ptrNext = pDlete->ptrNext;
				pDlete->ptrNext = 0;
				free(pDlete);
			}
			else
			{
				p = p->ptrNext;
			}

		}
		while (ET[y]->ptrNext)
		{
			EDGE* PInsert = ET[y]->ptrNext;
			EDGE* p = AET;
			while (p->ptrNext)
			{
				if (PInsert->x > p->ptrNext->x)
				{
					p = p->ptrNext;
					continue;
				}
				if (PInsert->x == p->ptrNext->x && PInsert->delta_x > p->ptrNext->delta_x)
				{

					p = p->ptrNext;
					continue;
				}
				break;
			}
		ET[y]->ptrNext = PInsert->ptrNext;
		PInsert->ptrNext = p->ptrNext;
		p->ptrNext = PInsert;
		}

		 p = AET;
		while (p->ptrNext && p->ptrNext->ptrNext)
		{
			for (x = p->ptrNext->x; x < p->ptrNext->ptrNext->x; x++)
			{
				pDC->SetPixelV(floor(x), y, BLACK_PEN);
			}
			p = p->ptrNext->ptrNext;
		}

		p = AET;
		while (p->ptrNext)
		{
			p->ptrNext->x += p->ptrNext->delta_x;
			p = p->ptrNext;
		}
	}
	ReleaseDC(pDC);
	
}

void CMyCGView::FillBySeedMain()
{
	COLORREF bc = RGB(0, 0, 0);
	COLORREF nc = RGB(0, 0, 0);
	CDC *pDC = GetDC();
	FillBySeed(fill_seed_x, fill_seed_y, bc, nc, pDC);
	ReleaseDC(pDC);
}

void CMyCGView::OnCutLineByCS() 
{
	// TODO: Add your command handler code here
	m_func_flag = 15;
	m_is_start = 0;

	OnCutDrawWin();
}

void CMyCGView::OnCutPolyBySH()
{
	// TODO: Add your command handler code here
	m_func_flag = 16;
	m_is_start = 0;
	CutPolyInitPoint(&pp);
	OnCutDrawWin();
}

int CMyCGView::CutGetCode(int x, int y)
{
	int c=0;
	
	if (x<WL)
	{
		c=c|LEFT;
	}
	else if (x>WR)
	{
		c=c|RIGHT;
	}
	
	if (y<WT)
	{
		c=c|BOTTOM;
	}
	else if (y>WB)
	{
		c=c|TOP;
	}
	
	return c;
}

int CMyCGView::CutLineByCS(CDC *pDC, int x0, int y0, int x1, int y1)
{
	//	CDC *pDC=GetDC();
	int code0,code1,code,x,y;
	code0=CutGetCode(x0,y0);   //(x0,y0)处的编码
	code1=CutGetCode(x1,y1);   //(x0,y0)处的编码
	while (code0!=0||code1!=0)  //当code0不等于0或code1不等于0
	{
		if ((code0&code1)!=0) return 0;  //当code0与 code1不等于0，在同侧；
		code=code0;
		if (code0==0)  code=code1;
		if ((LEFT&code)!=0)               //求交点
		{
			x=WL;
			y=y0+(y1-y0)*(WL-x0)/(x1-x0);
		}
		else if ((RIGHT&code)!=0)
		{
			x=WR;
			y=y0+(y1-y0)*(WR-x0)/(x1-x0);
		}
		else if ((BOTTOM&code)!=0)
		{
			y=WT;
			x=x0+(x1-x0)*(WT-y0)/(y1-y0);
		} 
		else if ((TOP&code)!=0)
		{
			y=WB;
			x=x0+(x1-x0)*(WB-y0)/(y1-y0);
		} 
		if (code==code0)
		{
			x0=x;y0=y;
			code0=CutGetCode(x,y);
		}
		else
		{
			x1=x;y1=y;
			code1=CutGetCode(x,y);
		}
	}  
	//end while,表示code0，code1都为0，其中的线段为可视部分
	pDC->MoveTo(x0,y0);
	pDC->LineTo(x1,y1);
}

void CMyCGView::CutPolyInitPoint(PolyPoint *p)
{
	p->x=0;
	p->y=0;
	p->next=NULL;
}

void CMyCGView::CutPolyAddPoint(PolyPoint *p, int x, int y)
{
//	temp.x = x;
//	temp.y = y;
//	temp.next = NULL;
	PolyPoint *t;
	t = p;
	while (t->next!=NULL)
	{
		t = t->next;
	}
	t->next = (PolyPoint*)malloc(sizeof(PolyPoint));
	t=t->next;
	t->x=x;
	t->y=y;
	t->next=NULL;
}

bool CMyCGView::CutPolyIsPointClose(PolyPoint p, CPoint m)
{
	PolyPoint *t = p.next;
	int a, b;
	int num = 15;
	a = abs(t->x - m.x);
	b = abs(t->y - m.y);
	if (a > num || b > num)
		return FALSE;
	else
		return TRUE;
}

void CMyCGView::OnCutDrawWin()
{
	LEFT = 1;
	RIGHT = 2;
	BOTTOM = 4;
	TOP = 8;
	WL=150;
	WR=650;
	WT=150;
	WB=550;

	CDC *pDC=GetDC();

    CPen PenRed(PS_SOLID,1,RGB(255,0,0));
    CPen PenBlue(PS_SOLID,1,RGB(0,0,255));

	pDC->SelectObject(&PenBlue);
	pDC->Rectangle(WL, WT, WR+1, WB+1);
	ReleaseDC(pDC);
}

void CMyCGView::CutPolyDrawPolyPoint(PolyPoint p, CPen *pen, int draw_mode)
{
	CDC *pDC=GetDC();
	int old_draw_mode=pDC->SetROP2(draw_mode);
	pDC->SelectObject(pen);

	PolyPoint *t=p.next;
	while (t!=NULL)
	{
		pDC->MoveTo(t->x, t->y);
		if (t->next!=NULL)
		{
			pDC->LineTo((t->next)->x, (t->next)->y);
		}
		else
		{
			pDC->LineTo((p.next)->x, (p.next)->y);
		}
		t=t->next;
	}

	pDC->SetROP2(old_draw_mode);
	ReleaseDC(pDC); 
}

void CMyCGView::CutPolyBySH()
{
	CPen PenWhite(PS_SOLID, 1, RGB(255,255,255));
	CPen PenRed(PS_SOLID, 1, RGB(255,0,0));
	int i;
	int edge[4] = {WL, WT, WR, WB};
	int xy[4] = {0, 1, 0, 1};
	int cmp[4] = {1, 1, 0, 0};

	for(i=0; i<4; i++)
	{
		Sleep(1000);
		CutPolyDrawPolyPoint(pp, &PenWhite, R2_COPYPEN);
		CutPolyBySHCheckEdge(edge[i], xy[i], cmp[i]);
		CutPolyDrawPolyPoint(pp, &PenRed, R2_COPYPEN);
	}

}

//	xy: 0时edge边为垂直x边，1相反
//	cmp: 0时坐标比edge小 为边界内，1相反
void CMyCGView::CutPolyBySHCheckEdge(int edge, int xy, int cmp)
{
	PolyPoint *op = pp.next;
	PolyPoint np;
	CutPolyInitPoint(&np);
	//	PolyPoint *t1 = np->next;
	int pos, npos;
	float pint;
	int ox, oy;
	int nx, ny;
	while (op!=NULL)
	{
		ox = op->x;
		oy = op->y;
		pos = (xy==0) ? ox : oy;
		if ((pos<=edge && cmp==0) || (pos>=edge && cmp==1))
		{
			CutPolyAddPoint(&np, ox, oy);
		}

		if (op->next!=NULL)
		{
			nx = op->next->x;
			ny = op->next->y;
		}
		else
		{
			nx = pp.next->x;
			ny = pp.next->y;
		}
		npos = (xy==0) ? nx : ny;
		if ((pos<edge && npos>edge) || (pos>edge && npos<edge))
		{
			if (xy==0)
			{
				pint = oy+(ny-oy)*(edge-ox)/(nx-ox);
				CutPolyAddPoint(&np, edge, pint);
			}
			else
			{
				pint = ox+(nx-ox)*(edge-oy)/(ny-oy);
				CutPolyAddPoint(&np, pint, edge);
			}
		}
		op = op->next;
	}

	pp.next=np.next;
}

void CMyCGView::OnTransForDraw() 
{
	// TODO: Add your command handler code here
	OnClearScreen();
	m_func_flag = 17;
	m_is_start = 0;
	TransInitPoint(&pp);
}

void CMyCGView::OnTransSetCntr() 
{
	// TODO: Add your command handler code here
	m_func_flag = 18;
	m_is_start = 0;
}

void CMyCGView::OnTransMove() 
{
	// TODO: Add your command handler code here
	m_func_flag = 19;
	m_is_start = 0;
	OnTransMoveShowMsg();
}

void CMyCGView::OnTransRot()
{
	// TODO: Add your command handler code here
	m_func_flag = 20;
	m_is_start = 0;
	OnTransRotShowMsg();
}

void CMyCGView::OnTransScale() 
{
	// TODO: Add your command handler code here
	m_func_flag = 21;
	OnTransScalcShowMsg();
	//	m_is_start = 0;
}
void CMyCGView::OnTransScalcShowMsg()
{
	CDC *pDC = GetDC();
	pDC->TextOut(200, 5, "[W]: Y方向1.1倍 [S]: Y方向0.9倍                 ");
	pDC->TextOut(200, 30, "[D]: X方向1.1倍 [A]: X方向0.9倍                 ");
	pDC->TextOut(200, 55, "[E]:   整体1.1倍 [Q]:   整体0.9倍                 ");
	ReleaseDC(pDC);
}

void CMyCGView::OnTransMoveShowMsg()
{
	CDC *pDC = GetDC();
	pDC->TextOut(200, 5, "[W]: Y方向 -5像素   [S]: Y方向 +5像素");
	pDC->TextOut(200, 30, "[D]: X方向 +5像素   [A]: X方向 -5像素");
	pDC->TextOut(200, 55, "或使用鼠标操控                                            ");
	ReleaseDC(pDC);
}

void CMyCGView::OnTransRotShowMsg()
{
	CDC *pDC = GetDC();
	pDC->TextOut(200, 5, "[W]: 顺时针20°   [S]: 逆时针20°                 ");
	pDC->TextOut(200, 30, "[D]: 顺时针10°   [A]: 逆时针10°                 ");
	pDC->TextOut(200, 55, "或使用鼠标操控                                            ");
	ReleaseDC(pDC);
}

void CMyCGView::TransInitPoint(PolyPoint *p)
{
//	直接调用裁剪多边形用上的函数，一样的
	CutPolyInitPoint(p);
}

void CMyCGView::TransAddPoint(PolyPoint *p, int x, int y)
{
	CutPolyAddPoint(p, x, y);
}

bool CMyCGView::TransIsPointClose(PolyPoint p, CPoint m)
{
	return CutPolyIsPointClose(p, m);
}

void CMyCGView::TransDrawPolyPoint(PolyPoint p, CPen *pen, int draw_mode)
{
	CutPolyDrawPolyPoint(p, pen, draw_mode);
}

//	把链表的头部作为中心点存储
void CMyCGView::TransSetCntrPoint(PolyPoint *p, int x, int y)
{
	p->x=x;
	p->y=y;
}

void CMyCGView::TransGetCntrPoint(PolyPoint p, int *x, int *y)
{
	*x=p.x;
	*y=p.y;
}

void CMyCGView::TransDrawCntrPoint(PolyPoint p, CPen *pen, int draw_mode)
{
	CDC *pDC=GetDC();
	int old_draw_mode=pDC->SetROP2(draw_mode);
	pDC->SelectObject(pen);

	int x, y;
	TransGetCntrPoint(p, &x, &y);
	pDC->Ellipse(x+5, y-5, x-5, y+5);

	pDC->SetROP2(old_draw_mode);
	ReleaseDC(pDC); 

}

void CMyCGView::TransMove(PolyPoint *p, int dx, int dy)
{
	PolyPoint *t=p;
	while (t!=NULL)
	{
		t->x += dx;
		t->y += dy;
		t=t->next;
	}
}

BOOL CMyCGView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
//			CDC* pDC = GetDC();
//			pDC->TextOut(100, 200, "12332132");
//	ReleaseDC(pDC);

		CPen PenBlack(PS_SOLID, 1, RGB(0,0,0));
		CPen PenWhite(PS_SOLID, 1, RGB(255,255,255));
		if (19<=m_func_flag && m_func_flag<=21)
		{
			TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
			if (m_func_flag==19)
			{
				TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
				switch (pMsg->wParam)
				{
				case 'W':
					TransMove(&pp, 0, -5);
					break;
				case 'S':
					TransMove(&pp, 0, 5);
					break;
				case 'D':
					TransMove(&pp, 5, 0);
					break;
				case 'A':
					TransMove(&pp, -5, 0);
					break;
				}
				TransDrawCntrPoint(pp, &PenBlack, R2_XORPEN);
			}
			else if (m_func_flag==20)
			{
				double n=0.17453292519943295;
				switch (pMsg->wParam)
				{
				case 'W':
					TransRot(&pp, n*2);
					break;
				case 'S':
					TransRot(&pp, -n*2);
					break;
				case 'D':
					TransRot(&pp, n);
					break;
				case 'A':
					TransRot(&pp, -n);
					break;
				}
			}
			else if (m_func_flag==21)
			{
				switch (pMsg->wParam)
				{
				case 'W':
					TransScalc(&pp, 1, 1.1);
					break;
				case 'S':
					TransScalc(&pp, 1, 0.9);
					break;
				case 'D':
					TransScalc(&pp, 1.1, 1);
					break;
				case 'A':
					TransScalc(&pp, 0.9, 1);
					break;
				case 'E':
					TransScalc(&pp, 1.1, 1.1);
					break;
				case 'Q':
					TransScalc(&pp, 0.9, 0.9);
					break;
				}
			}
			TransDrawPolyPoint(pp, &PenWhite, R2_XORPEN);
		}
	}
	return CView::PreTranslateMessage(pMsg);
}

void CMyCGView::TransRot(PolyPoint *p, double n)
{
	int xr, yr, x, y;
	TransGetCntrPoint(*p, &xr, &yr);
	PolyPoint *t;
	t=p->next;
	while (t!=NULL)
	{
		x=t->x;
		y=t->y;
//		t->x = -xr*cos(n) + yr*sin(n) + x*cos(n) - y*sin(n) + xr;
//		t->y = -xr*sin(n) - yr*cos(n) + x*sin(n) + y*cos(n) + yr;
		t->x = x*cos(n) - y*sin(n) + xr*(1-cos(n)) + yr*sin(n);
		t->y = x*sin(n) + y*cos(n) + yr*(1-cos(n)) - xr*sin(n);
		t=t->next;
	}
}

double CMyCGView::TransRotCalcTheta(int xr, int yr, int x0, int y0, int x1, int y1)
{
	double a, b, c, theta;
	a = sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
	b = sqrt((xr-x0)*(xr-x0) + (yr-y0)*(yr-y0));
	c = sqrt((xr-x1)*(xr-x1) + (yr-y1)*(yr-y1));
	theta = acos((b*b+c*c-a*a) / (2*b*c));
	if ((xr-x0)*(y1-y0) - (yr-y0)*(x1-x0) > 0)
	{
		return -theta;
	}
	else
	{
		return theta;
	}
}

void CMyCGView::TransCalcCntrPoint(PolyPoint p, int *x, int *y)
{
	PolyPoint *t;
	t=p.next;
	int xr=0,yr=0,i=0;
	while(t!=NULL)
	{
		xr += t->x;
		yr += t->y;
		i++;
		t=t->next;
	}
	*x=xr/i;
	*y=yr/i;
}

void CMyCGView::TransScalc(PolyPoint *p, double sx, double sy)
{
	int xr,yr;
	TransGetCntrPoint(*p, &xr, &yr);
	PolyPoint *t;
	t=p->next;
	while(t!=NULL)
	{
		t->x = t->x*sx + xr*(1-sx);
		t->y = t->y*sy + yr*(1-sy);
		t=t->next;
	}
}

void CMyCGView::OnBrzAddPoint()
{
	// TODO: Add your command handler code here
	m_func_flag = 22;
	m_is_start = 0;
	BrzInitPoint(&pp);
	
}

void CMyCGView::OnBrzDrawSpline() 
{
	// TODO: Add your command handler code here
	m_func_flag = -1;
	m_is_start = -1;
	CPen PenRed(PS_SOLID, 1, RGB(0,255,255));
	BrzDrawSpline(pp, &PenRed, R2_XORPEN);
}

void CMyCGView::BrzInitPoint(PolyPoint *p)
{
	CutPolyInitPoint(p);
}

void CMyCGView::BrzAddPoint(PolyPoint *p, int x, int y)
{
	CutPolyAddPoint(p, x, y);
	p->x ++;
}

void CMyCGView::BrzDrawPointLine(PolyPoint p, CPen *pen_line, CPen *pen_point, int draw_mode)
{
	CDC *pDC=GetDC();
	int old_draw_mode=pDC->SetROP2(draw_mode);
	pDC->SelectObject(pen_line);

	PolyPoint *t=p.next;
	while (t!=NULL)
	{
		if (t->next!=NULL)
		{
			pDC->SelectObject(pen_line);
			pDC->MoveTo(t->x, t->y);
			pDC->LineTo((t->next)->x, (t->next)->y);
		}
		pDC->SelectObject(pen_point);
		pDC->Ellipse(t->x-5, t->y-5, t->x+5, t->y+5);
		t=t->next;
	}

	pDC->SetROP2(old_draw_mode);
	ReleaseDC(pDC); 
}

void CMyCGView::BrzDrawSpline(PolyPoint p, CPen *pen, int draw_mode)
{
	if (p.x-1 <= 0)
	{
		return;
	}
	CDC *pDC=GetDC();
	int old_draw_mode=pDC->SetROP2(draw_mode);
	pDC->SelectObject(pen);

	int n=p.x-1;
	double curx, cury, b;
	double dt=0.01, m=0.0;
	PolyPoint *t=p.next;
	pDC->MoveTo(t->x, t->y);
	for (int i=0; i<=(int)1/dt;i++)
	{
		curx=0.0;
		cury=0.0;
		t=p.next;
		int j=0;
		while (t!=NULL)
		{
			b = BrzBernstein(j,n,m);
			curx=curx + t->x*b;
			cury=cury + t->y*b;
			t=t->next;
			j++;
		}
		pDC->LineTo(curx, cury);
		m = m+dt;
	}

	pDC->SetROP2(old_draw_mode);
	ReleaseDC(pDC); 
}

int CMyCGView::BrzCombination(int m, int n)
{
	int i,j,a;
	if (m!=0)
	{
		a=1;
		for (i=m+1;i<=n;i++)
		{
			a=a*i;
		}
		for (j=1;j<=n-m;j++)
		{
			a=a/j;
		}
		return a;
	}
	else
	{
		return 1;
	}
}

double CMyCGView::BrzBernstein(int m, int n, double t)
{
	int i,j;
	double sum;
	sum=BrzCombination(m,n);

	for (i=1;i<=m;i++)
	{
		sum=sum*t;
	}
	for (j=1;j<=n-m;j++)
	{
		sum=sum*(1-t);
	}
	return sum;
}
