
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "JFDraw.h"

#include "Shape.h"
#include "Rectangle.h"
#include "Circle.h"
#include <iostream>
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


// CChildView

CChildView::CChildView()
	: m_LastPoint(-1, -1),
	m_StartPoint(-1, -1),
	m_TemporaryPen(PS_DOT, 1, RGB(0, 0, 0)),
	m_Shapes(),
	m_CurrentShapeType(SHAPETYPE_CIRCLE)
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
	else
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

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	RedrawShapes();
	
	// CWnd::MoveWindow(0, 0, cx, cy);
	
	CWnd::OnSize(nType, cx, cy);
}

void CChildView::OnShapeRectangle() 
	{ m_CurrentShapeType = SHAPETYPE_RECTANGLE; }

void CChildView::OnShapeCircle() 
	{ m_CurrentShapeType = SHAPETYPE_CIRCLE; }

void CChildView::OnShapeSelectortool() 
	{ m_CurrentShapeType = SHAPETYPE_SELECTOR; }

void CChildView::OnEditDelete()
{
	CWnd::InvalidateRect(m_CurrentShape->GetRect());
	
	m_Shapes.erase(std::remove(m_Shapes.begin(), m_Shapes.end(), m_CurrentShape), m_Shapes.end());

	RedrawShapes();
}

void CChildView::OnFileOpen()
{
	CFileDialog* fd = new CFileDialog(true, _T("jfd"), _T("*.jfd"));
	CString fileName;

	fd->m_ofn.lpstrTitle = TEXT("Open save file");
	fd->m_ofn.lpstrFilter = TEXT("JFDraw Files (*.jfd)");

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		CFile openFile;
		openFile.Open(fileName, CFile::modeRead);

		CArchive archive(&openFile, CArchive::load);
	}

	fileName.ReleaseBuffer();
}

void CChildView::OnFileSave()
{
	CFileDialog* fd = new CFileDialog(false, _T("jfd"), _T("*.jfd"));
	CString fileName;

	fd->m_ofn.lpstrTitle = TEXT("Save file");
	fd->m_ofn.lpstrFilter = TEXT("JFDraw Files (*.jfd)");

	if (fd->DoModal() == IDOK)
	{
		fileName = fd->GetPathName();

		CFile saveFile;
		saveFile.Open(fileName, CFile::modeCreate | CFile::modeWrite);

		CArchive archive(&saveFile, CArchive::store);

		for (int i = 0; i < m_Shapes.size(); i++)
		{
			Fraint::Shape* shape = m_Shapes[i];

			shape->Serialize(archive);
		}

		archive.Close();
		saveFile.Close();
	}

	fileName.ReleaseBuffer();
}