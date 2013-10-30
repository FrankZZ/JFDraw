
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "JFDraw.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "Ellipse.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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

#ifndef SHAPETYPE SELECTOR
#define SHAPETYPE_SELECTOR 2
#endif

#ifndef SHAPETYPE_SQUARE
#define SHAPETYPE_SQUARE 3
#endif

#ifndef SHAPETYPE_ELLIPSE
#define SHAPETYPE_ELLIPSE 4
#endif


// CChildView

CChildView::CChildView()
	: m_LastPoint(-1, -1),
	m_StartPoint(-1, -1),
	m_TemporaryPen(PS_DOT, 1, RGB(0, 0, 0)),
	m_Shapes(),
	m_CurrentShapeType(SHAPETYPE_CIRCLE),
	m_CurrentShape(NULL)
{
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
	ON_WM_SIZE()
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CChildView::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CChildView::OnShapeCircle)
	ON_COMMAND(ID_SHAPE_SELECTORTOOL, &CChildView::OnShapeSelectortool)
	ON_COMMAND(ID_EDIT_DELETE, &CChildView::OnEditDelete)
	ON_COMMAND(ID_FILE_OPEN32778, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE32779, &CChildView::OnFileSave)
	ON_COMMAND(ID_SHAPE_SQUARE, &CChildView::OnShapeSquare)
	ON_COMMAND(ID_SHAPE_ELLIPSE, &CChildView::OnShapeEllipse)
	ON_COMMAND(ID_SHAPESIZE_1, &CChildView::OnBorderSize1)
	ON_UPDATE_COMMAND_UI(ID_SHAPESIZE_1, &CChildView::OnUpdateBorderSize1)
	ON_COMMAND(ID_SHAPESIZE_2, &CChildView::OnBorderSize2)
	ON_COMMAND(ID_SHAPESIZE_3, &CChildView::OnBorderSize3)
	ON_UPDATE_COMMAND_UI(ID_SHAPESIZE_2, &CChildView::OnUpdateBorderSize2)
	ON_UPDATE_COMMAND_UI(ID_SHAPESIZE_3, &CChildView::OnUpdateBorderSize3)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_RECTANGLE, &CChildView::OnUpdateShapeRectangle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_CIRCLE, &CChildView::OnUpdateShapeCircle)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_SELECTORTOOL, &CChildView::OnUpdateShapeSelectorTool)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_SQUARE, &CChildView::OnUpdateShapeSquare)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_ELLIPSE, &CChildView::OnUpdateShapeEllipse)
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
	if (m_CurrentShapeType == SHAPETYPE_CIRCLE)
	{
		m_CurrentShape = new Fraint::Circle(m_StartPoint);
	}
	else if (m_CurrentShapeType== SHAPETYPE_RECTANGLE)
	{
		m_CurrentShape = new Fraint::Rectangle(m_StartPoint);
	}
	else if (m_CurrentShapeType== SHAPETYPE_ELLIPSE)
	{
		m_CurrentShape = new Fraint::Ellipse(m_StartPoint);
	}
	else if (m_CurrentShapeType== SHAPETYPE_SQUARE)
	{
		m_CurrentShape = new Fraint::Square(m_StartPoint);
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_StartPoint.x != -1)
	{
		if (m_CurrentShapeType != SHAPETYPE_SELECTOR)
		{
			CDC* pDC = GetDC();

			CPen* pOldPen = pDC->SelectObject(&m_TemporaryPen);

			pDC->SetROP2(R2_NOTXORPEN);
		
			if (m_LastPoint.x != -1)
			{
				m_CurrentShape->SetEndPoint(m_LastPoint);
				m_CurrentShape->Draw(pDC);
			}

			m_CurrentShape->SetEndPoint(point);
			m_CurrentShape->Draw(pDC);

			pDC->SelectObject(pOldPen);
			ReleaseDC(pDC);
		
			m_LastPoint = point;
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_CurrentShapeType == SHAPETYPE_SELECTOR)
	{
		for(auto i = m_Shapes.rbegin(); i != m_Shapes.rend(); ++i)
		{
			if ((*i)->IsOn(point))
			{
				m_CurrentShape = *i;
				break;
			}
		}
	}
	else if(m_CurrentShape)
	{
		CDC* pDC = GetDC();

		if (m_LastPoint.x != -1)
		{
			m_CurrentShape->SetEndPoint(m_LastPoint);
			m_CurrentShape->Draw(pDC);
		}

		ReleaseDC(pDC);

		m_Shapes.push_back(m_CurrentShape);
	}

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
		
		RedrawShapes();
	}
}

// Wachten tot de Window geupdate is (invalidated rectangles erased) en dan de huidige shapes redrawen
void CChildView::RedrawShapes()
{
	CWnd::UpdateWindow();
	
	if (m_Shapes.empty() == false)
	{
		for (auto i : m_Shapes)
		{
			i->Draw(GetDC());
		}
	}
}

// Reset
void CChildView::Reset()
{
	if (m_Shapes.empty() == false)
	{
		for (auto i : m_Shapes)
		{
			CWnd::InvalidateRect(i->GetRect());
		}

		m_Shapes.clear();
		RedrawShapes();
	}
};

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	RedrawShapes();
	
	// CWnd::MoveWindow(0, 0, cx, cy);
	CWnd::OnSize(nType, cx, cy);
}

void CChildView::OnShapeRectangle() 
{
	m_CurrentShapeType = SHAPETYPE_RECTANGLE;
}

void CChildView::OnShapeCircle() 
{
	m_CurrentShapeType = SHAPETYPE_CIRCLE;
}

void CChildView::OnShapeSelectortool() 
{
	m_CurrentShapeType = SHAPETYPE_SELECTOR;
}

void CChildView::OnShapeSquare()
{
	m_CurrentShapeType = SHAPETYPE_SQUARE;
}

void CChildView::OnShapeEllipse()
{
	m_CurrentShapeType = SHAPETYPE_ELLIPSE;
}

void CChildView::OnUpdateShapeRectangle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_RECTANGLE);
}

void CChildView::OnUpdateShapeCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_CIRCLE);
}

void CChildView::OnUpdateShapeSelectorTool(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_SELECTOR);
}

void CChildView::OnUpdateShapeSquare(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_SQUARE);
}

void CChildView::OnUpdateShapeEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_ELLIPSE);
}

void CChildView::OnBorderSize1()
{
	m_PenWidth = 1;
}

void CChildView::OnBorderSize2()
{
	m_PenWidth = 2;
}

void CChildView::OnBorderSize3()
{
	m_PenWidth = 3;
}

void CChildView::OnUpdateBorderSize1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 1);
}

void CChildView::OnUpdateBorderSize2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 2);
}

void CChildView::OnUpdateBorderSize3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 3);
}

void CChildView::OnEditDelete()
{
	CWnd::InvalidateRect(m_CurrentShape->GetRect());
	
	m_Shapes.erase(std::remove(m_Shapes.begin(), m_Shapes.end(), m_CurrentShape), m_Shapes.end());
	RedrawShapes();
}

void CChildView::OnFileOpen()
{
	CFileDialog* fd = new CFileDialog(true, _T("jfd"), _T("*.jfd"));
	wstring fileName;

	fd->m_ofn.lpstrTitle = TEXT("Open save file");
	fd->m_ofn.lpstrFilter = TEXT("JFDraw Files (*.jfd)");

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		ifstream file(fileName);
		string rawline;
 
		CChildView::Reset();

		while (getline(file, rawline))
		{
			if (!rawline.empty())
			{
				stringstream line(rawline);
				string seg;
				vector<string> segs;

				while (getline(line, seg, ','))
				{
					segs.push_back(seg);
				}

				if (segs.size() != 5)
				{
					continue;
				}

				CPoint startp(stoi(segs[1]), stoi(segs[2]));
				CPoint endp(stoi(segs[3]), stoi(segs[4]));

				if (segs[0] == "Circle")
				{
					m_Shapes.push_back(new Fraint::Circle(startp, endp));
				}
				else if (segs[0] == "Rectangle")
				{
					m_Shapes.push_back(new Fraint::Rectangle(startp, endp));
				}
				else if (segs[0] == "Ellipse")
				{
					m_Shapes.push_back(new Fraint::Ellipse(startp, endp));
				}
				else if (segs[0] == "Square")
				{
					m_Shapes.push_back(new Fraint::Square(startp, endp));
				}
				else
				{
					continue;
				}
			}
		}
 
		RedrawShapes();
		file.close();
	}
}

void CChildView::OnFileSave()
{
	CFileDialog* fd = new CFileDialog(false, _T("jfd"), _T("*.jfd"));
	wstring fileName;

	fd->m_ofn.lpstrTitle = TEXT("Save file");
	fd->m_ofn.lpstrFilter = TEXT("JFDraw Files (*.jfd)");

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		ofstream file;
		file.open(fileName);

		if (m_Shapes.empty() == false)
		{
			for (auto i : m_Shapes)
			{
				file << i->ToString();
			}
		}

		file.close();

		delete fd;
	}
}