#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Circle.h"

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
		pDC->Ellipse(m_Rect);
	};
}