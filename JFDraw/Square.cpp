#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Square.h"

namespace Fraint
{
	Square::Square(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint)
	{
		Square::Init();
	};

	Square::Square(CPoint StartPoint) : Shape(StartPoint)
	{
		Square::Init();
	};

	void Square::Init()
	{
		m_Name = "Square";
	};

	void Square::SetEndPoint(CPoint EndPoint)
	{
		Shape::SetEndPoint(EndPoint);
		
		m_Rect.NormalizeRect();

		if (m_Rect.Height() == m_Rect.Width())
			return;

		if (m_Rect.Height() > m_Rect.Width())
		{
			int width = m_Rect.Width();

			m_EndPoint.x = m_StartPoint.x + width;
			m_EndPoint.y = m_StartPoint.y + width;
		} 
		else
		{
			int height = m_Rect.Height();

			m_EndPoint.x = m_StartPoint.x + height;
			m_EndPoint.y = m_StartPoint.y + height;
		}

		m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y);
	}

	void Square::Draw(CDC *pDC)
	{
		pDC->Rectangle(m_Rect);
	};
}