
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "JFDraw.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Square.h"
#include "Ellipse.h"
#include "Polygon.h"
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

#ifndef SHAPETYPE_POLYGON
#define SHAPETYPE_POLYGON 5
#endif

#ifndef SHAPETYPE_LINETO
#define SHAPETYPE_LINETO 6
#endif

// CChildView

CChildView::CChildView()
	: m_LastPoint(-1, -1),
	m_StartPoint(-1, -1),
	m_TemporaryPen(PS_DOT, 1, RGB(0, 0, 0)),
	m_Shapes(),
	m_CurrentShapeType(SHAPETYPE_CIRCLE),
	m_CurrentShape(NULL),
	m_bMouseLeft(FALSE)
{
}

CChildView::~CChildView()
{
	

	for each (auto var in m_Shapes)
	{
		delete var;
	}

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
	ON_COMMAND(ID_SHAPE_P, &CChildView::OnShapePolygon)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_P, &CChildView::OnUpdateShapePolygon)
	ON_COMMAND(ID_SHAPE_LINETO, &CChildView::OnShapeLineto)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_LINETO, &CChildView::OnUpdateShapeLineto)
	ON_COMMAND(ID_UNDO, &CChildView::OnEditUndo)
	ON_WM_CHAR()
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

	this->RedrawShapes();
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_CurrentShape)
	{
		m_CurrentShape->AddChar(nChar);

		CWnd::InvalidateRect(m_CurrentShape->GetRect());
	}


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
	else if (m_CurrentShapeType == SHAPETYPE_POLYGON)
	{
		m_CurrentShape = new Fraint::Polygon(m_StartPoint);
	}

	m_CurrentShape->SetPenWidth(m_PenWidth);

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_StartPoint.x != -1)
	{
		CDC* pDC = GetDC();
		
		CRect cRect;
		GetClientRect(&cRect);

		if (point.x > cRect.left+5 && point.x < cRect.right-5 && point.y > cRect.top+5 && point.y < cRect.bottom-5)
		{
			if (m_bMouseLeft == TRUE)
			{
				m_bMouseLeft = FALSE;
			}

			if (m_CurrentShapeType != SHAPETYPE_SELECTOR && m_CurrentShapeType != SHAPETYPE_LINETO && m_CurrentShapeType != SHAPETYPE_POLYGON)
			{

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

				m_LastPoint = point;
			}
		} 
		else
		{
			m_bMouseLeft = TRUE;

			CPen* pOldPen = pDC->SelectObject(&m_TemporaryPen);

			pDC->SetROP2(R2_NOTXORPEN);

			if (m_LastPoint.x != -1)
			{
				m_CurrentShape->SetEndPoint(m_LastPoint);
				m_CurrentShape->Draw(pDC);
			}

			delete m_CurrentShape;
			
			pDC->SelectObject(pOldPen);

			m_LastPoint.x = -1;
			m_StartPoint.x = -1;
		}

		ReleaseDC(pDC);
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bMouseLeft == TRUE)
		return;

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
	else if (m_CurrentShapeType == SHAPETYPE_LINETO)
	{
		for (auto i = m_Shapes.rbegin(); i != m_Shapes.rend(); ++i)
		{
			if ((*i)->IsOn(point))
			{
				CDC* pDC = GetDC();

				pDC->MoveTo(m_CurrentShape->GetRect().CenterPoint());
				pDC->LineTo((*i)->GetRect().CenterPoint());

				break;
			}
		}
	}
	/*else if(m_CurrentShapeType == SHAPETYPE_POLYGON)
	{
		m_CurrentShape->SetEndPoint(point);
	}*/
	else if(m_CurrentShape)
	{
		CDC* pDC = GetDC();

		if (m_LastPoint.x != -1 || m_CurrentShapeType == SHAPETYPE_POLYGON)
		{
			m_CurrentShape->SetEndPoint(m_LastPoint);

			CPen pen;
			pen.CreatePen(PS_SOLID, m_CurrentShape->GetPenWidth(), RGB(0, 0, 0));

			CPen* oldPen = pDC->SelectObject(&pen);

			m_CurrentShape->Draw(pDC);

			CRect rect = m_CurrentShape->GetRect();
			rect.top += (rect.Height() / 2) - 10;

			string text = m_CurrentShape->GetText();
			CString cs(text.c_str());

			pDC->DrawText(cs, rect, DT_CENTER);

			pDC->SelectObject(oldPen);
		}

		ReleaseDC(pDC);

		m_Shapes.push_back(m_CurrentShape);

		//if (m_CurrentShape)
		//	delete m_CurrentShape;
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

		delete m_Shapes.back();


		m_Shapes.pop_back();
		
		RedrawShapes();
	}
}

// Wachten tot de Window geupdate is (invalidated rectangles erased) en dan de huidige shapes redrawen
void CChildView::RedrawShapes()
{
	//CRect rect(NULL);

	//GetClientRect(&rect);

	//CWnd::InvalidateRect(rect);

	CWnd::UpdateWindow();

	if (m_Shapes.empty() == false)
	{
		for (auto i : m_Shapes)
		{
			CPen pen;
			pen.CreatePen(PS_SOLID, i->GetPenWidth(), RGB(0, 0, 0));
			
			CDC* pDC = GetDC();

			CPen* oldPen = pDC->SelectObject(&pen);

			i->Draw(pDC);

			CRect rect = i->GetRect();
			rect.top += (rect.Height() / 2) - 10;

			string text = i->GetText();
			CString cs(text.c_str());

			pDC->DrawText(cs, rect, DT_CENTER);

			pDC->SelectObject(oldPen);
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

void CChildView::OnShapePolygon()
{
	m_CurrentShapeType = SHAPETYPE_POLYGON;
}

void CChildView::OnShapeLineto()
{
	m_CurrentShapeType = SHAPETYPE_LINETO;
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

void CChildView::OnUpdateShapePolygon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_POLYGON);
}

void CChildView::OnUpdateShapeLineto(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_CurrentShapeType == SHAPETYPE_LINETO);
}

void CChildView::OnBorderSize1()
{
	m_PenWidth = 1;
}

void CChildView::OnBorderSize2()
{
	m_PenWidth = 3;
}

void CChildView::OnBorderSize3()
{
	m_PenWidth = 5;
}

void CChildView::OnUpdateBorderSize1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 1);
}

void CChildView::OnUpdateBorderSize2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 3);
}

void CChildView::OnUpdateBorderSize3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_PenWidth == 5);
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

				if (segs.size() != 7)
				{
					continue;
				}

				CPoint startp(stoi(segs[1]), stoi(segs[2]));
				CPoint endp(stoi(segs[3]), stoi(segs[4]));
				int penWidth = stoi(segs[5]);
				string text = segs[6];

				Fraint::Shape* shape;

				if (segs[0] == "Circle")
				{
					shape = new Fraint::Circle(startp, endp);
				}
				else if (segs[0] == "Rectangle")
				{
					shape = new Fraint::Rectangle(startp, endp);
				}
				else if (segs[0] == "Ellipse")
				{
					shape = new Fraint::Ellipse(startp, endp);
				}
				else if (segs[0] == "Square")
				{
					shape = new Fraint::Square(startp, endp);
				}
				else
				{
					continue;
				}

				shape->SetPenWidth(penWidth);
				shape->SetText(text);

				m_Shapes.push_back(shape);
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
