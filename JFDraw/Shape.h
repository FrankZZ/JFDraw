
// Shape.h : interface of the Shape class
//
#pragma once

namespace Fraint
{
	class Shape : public CObject
	{
		//DECLARE_SERIAL(Shape)

		// Construction
		public:
			Shape(CPoint StartPoint, CPoint EndPoint);
			Shape(CPoint StartPoint);
			Shape();

		// Attributes
		protected:
			CPoint m_StartPoint;
			CPoint m_EndPoint;
			CRect m_Rect;
			CPen m_Pen;
			CBrush m_Brush;

		// Implementation
		public:
			virtual void Draw(CDC *pDC) {};
			virtual void SetEndPoint(CPoint EndPoint);
			CRect GetRect() { return m_Rect; };
			bool IsOn(CPoint point);

			virtual CString ToString();
	};
};