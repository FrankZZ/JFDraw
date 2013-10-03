
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "fraint.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include <vector>

#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef SHAPETYPE_RECTANGLE
#define SHAPETYPE_RECTANGLE 0
#endif

#ifndef SHAPETYPE CIRCLE
#define SHAPETYPE_CIRCLE 1
#endif



// CChildView

CChildView::CChildView()
{
	m_LastPoint = *new CPoint(-1, -1);
	m_StartPoint = *new CPoint(-1, -1);

	m_Shapes = *new std::vector<Fraint::Shape*>();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_EDIT_UNDO, &CChildView::OnEditUndo)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_StartPoint = point;
	
	//m_CurrentShape = new Rectangle1(m_StartPoint);
	if (CfraintApp::CURRENT_SHAPE_TYPE == SHAPETYPE_CIRCLE)
	{
		m_CurrentShape = new Fraint::Circle(m_StartPoint);
	}
	else if (CfraintApp::CURRENT_SHAPE_TYPE == SHAPETYPE_RECTANGLE)
	{
		m_CurrentShape = new Fraint::Rectangle(m_StartPoint);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	if (m_StartPoint.x != -1)
	{
		CDC* pDC = GetDC();

		//pDC->SelectStockObject(BLACK_PEN);
		pDC->SelectObject(*new CPen (PS_DOT, 1, RGB (0, 0, 0)));

		pDC->SetROP2(R2_NOTXORPEN);
		
		if (m_LastPoint.x != -1)
		{
			m_CurrentShape->SetEndPoint(m_LastPoint);
			m_CurrentShape->Draw(pDC);
		}

			//pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, m_LastPoint.x, m_LastPoint.y);
		
		m_CurrentShape->SetEndPoint(point);
		m_CurrentShape->Draw(pDC);
		//pDC->Rectangle(m_StartPoint.x, m_StartPoint.y, point.x, point.y);
		
		ReleaseDC(pDC);
		
		m_LastPoint = point;
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDC* pDC = GetDC();

	if (m_LastPoint.x != -1)
	{
		m_CurrentShape->SetEndPoint(m_LastPoint);
		m_CurrentShape->Draw(pDC);
	}

	
	ReleaseDC(pDC);

	m_Shapes.push_back(m_CurrentShape);

	m_StartPoint.x = -1;
	m_LastPoint.x = -1;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnEditUndo()
{
	if (m_Shapes.empty() == false)
	{
		CWnd::InvalidateRect(m_Shapes.back()->GetRect());
		m_Shapes.pop_back();
	}

}
