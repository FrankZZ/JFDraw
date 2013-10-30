
// Shape.h : interface of the Shape class
//
#pragma once

#include <string>

using namespace std;

namespace Fraint
{
	class Shape : public CObject
	{
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
			string m_Name;

		private:
			int m_PenWidth;

		// Implementation
		public:
			virtual void Init() {};
			virtual void Draw(CDC *pDC) {};
			virtual void SetEndPoint(CPoint EndPoint);
			CRect GetRect() { return m_Rect; };
			bool IsOn(CPoint point);
			virtual string ToString();
			void SetPenWidth(int width);
			int GetPenWidth();
	};
};