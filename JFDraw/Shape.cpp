#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"

namespace Fraint
{
	Shape::Shape(CPoint StartPoint, CPoint EndPoint) : m_StartPoint(StartPoint), 
		
		m_Rect(StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y)
	{
		// Stub
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
	};

	void Shape::Serialize(CArchive& archive)
	{
		if (archive.IsStoring()) // Write
		{
			archive << m_StartPoint << m_EndPoint;
		}
		else
		{
			archive >> m_StartPoint >> m_EndPoint;
		}
	}
}