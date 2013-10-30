#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

namespace Fraint
{
	Shape::Shape(CPoint StartPoint, CPoint EndPoint) : 
		m_StartPoint(StartPoint), 
		m_Rect(StartPoint.x, StartPoint.y, EndPoint.x, EndPoint.y)
	{
		// Constructor
	};

	string ltos(long l)
	{
		ostringstream s;
		s << l;

		return s.str();
	};

	Shape::Shape(CPoint StartPoint)
		: m_StartPoint(StartPoint),
		m_Rect(0, 0, 0, 0)
	{
	};

	void Shape::SetEndPoint(CPoint EndPoint)
	{
		m_EndPoint = EndPoint;

		m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, EndPoint.x, EndPoint.y);
	};

	bool Shape::IsOn(CPoint point)
	{
		return m_Rect.PtInRect(point);
	};

	string Shape::ToString()
	{
		return m_Name + ","
			+ ltos(m_StartPoint.x) + "," + ltos(m_StartPoint.y) 
			+ "," + ltos(m_EndPoint.x) + "," + ltos(m_EndPoint.y) 
		+ "\n";
	}
};