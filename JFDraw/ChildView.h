
// ChildView.h : interface of the CChildView class
//
#pragma once
#include "Shape.h"
#include <vector>

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

private:
	CPoint m_StartPoint;
	CPoint m_LastPoint;
	
	Fraint::Shape* m_CurrentShape;

	std::vector<Fraint::Shape*> m_Shapes;
	
	int m_CurrentShapeType;

	CPen m_TemporaryPen;

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();
	

private:
	void RedrawShapes();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeSelectortool();
	afx_msg void OnEditDelete();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
};