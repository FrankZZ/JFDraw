
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
	bool m_bMouseLeft;
	
	Fraint::Shape* m_CurrentShape;

	std::vector<Fraint::Shape*> m_Shapes;
	
	int m_CurrentShapeType;

	CPen m_TemporaryPen;

	int m_PenWidth = 1;

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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
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
	afx_msg void OnShapeSquare();
	afx_msg void OnShapeEllipse();
	void Reset();

	afx_msg void OnBorderSize1();
	afx_msg void OnUpdateBorderSize1(CCmdUI *pCmdUI);
	afx_msg void OnBorderSize2();
	afx_msg void OnBorderSize3();
	afx_msg void OnUpdateBorderSize2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBorderSize3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeSelectorTool(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeSquare(CCmdUI *pCmdUI);
	afx_msg void OnUpdateShapeEllipse(CCmdUI *pCmdUI);
	afx_msg void OnShapePolygon();
	afx_msg void OnUpdateShapePolygon(CCmdUI *pCmdUI);
	afx_msg void OnShapeLineto();
	afx_msg void OnUpdateShapeLineto(CCmdUI *pCmdUI);
};