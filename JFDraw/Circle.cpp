#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Circle.h"
#include <conio.h>

using namespace std;

namespace Fraint
{
	Circle::Circle(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint)
	{
		Circle::Init();
	};

	Circle::Circle(CPoint StartPoint) : Shape(StartPoint)
	{
		Circle::Init();
	};

	void Circle::Init()
	{
		m_Name = "Circle";
	}

	void Circle::SetEndPoint(CPoint EndPoint)
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

	void Circle::Draw(CDC *pDC)
	{
		CPen* oldPen = pDC->SelectObject(&m_Pen);

		pDC->Ellipse(m_Rect);

		pDC->SelectObject(oldPen);
	};

	/*
	bool Circle::IsOn(CPoint point)
	{
		
		int radius = m_Rect.CenterPoint().x - m_Rect.left;

		return (m_Rect.CenterPoint().x - point.x)^2 + (point.y - m_Rect.CenterPoint().y)^2 < radius^2;
	}
	*/
}