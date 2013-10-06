#include "stdafx.h"
#include "fraint.h"
#include "Shape.h"
namespace Fraint
{
	Shape::Shape(CPoint StartPoint, CPoint EndPoint)
		: m_StartPoint(StartPoint),
		m_Rect(StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y)
	{
	};

	Shape::Shape(CPoint StartPoint)
	{
		m_StartPoint = StartPoint;
		m_Rect = *new CRect(0, 0, 0, 0);
	};

	void Shape::SetEndPoint(CPoint EndPoint)
	{
		m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, EndPoint.x, EndPoint.y);
	};

	bool Shape::IsOn(CPoint point)
	{
		return m_Rect.PtInRect(point);
	}
}