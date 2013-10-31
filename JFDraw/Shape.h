
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
			string m_Name;
			string m_Text = ".";

		private:
			int m_PenWidth;

		// Implementation
		public:
			virtual void Init() {};
			virtual void Draw(CDC *pDC) =0 {};
			virtual void SetEndPoint(CPoint EndPoint);
			CRect GetRect() { return m_Rect; };
			bool IsOn(CPoint point);
			virtual string ToString();
			void SetPenWidth(int width);
			int GetPenWidth();
			string GetText();
			void SetText(string text);
	};
};