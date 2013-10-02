
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
	
	Shape* m_CurrentShape;
	
	std::vector<Shape*> m_Shapes;
	
	int m_CurrentShapeType;

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
};

