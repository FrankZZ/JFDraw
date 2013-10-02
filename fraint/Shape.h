
// Shape.h : interface of the Shape class
//
#pragma once


class Shape
{
	// Construction
	public:
		Shape(CPoint StartPoint, CPoint EndPoint);
		Shape(CPoint StartPoint);

	// Attributes
	protected:
		CPoint m_StartPoint;
		CPoint m_EndPoint;
		CRect m_Rect;

	// Implementation
	public:
		virtual void Draw(CDC *pDC) {};
		void SetEndPoint(CPoint EndPoint);
		CRect GetRect() { return m_Rect; };
};
