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
		m_EndPoint(EndPoint),
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

	void Shape::SetPenWidth(int width)
	{
		m_PenWidth = width;
	}

	int Shape::GetPenWidth()
	{
		return m_PenWidth;
	}

	string Shape::GetText()
	{
		return m_Text;
	}

	void Shape::SetText(string text)
	{
		m_Text = text;
	}

	void Shape::AddChar(int nChar)
	{
		if (nChar == 8)
		{
			m_Text = m_Text.substr(0, m_Text.length()-1);
		}
		else
			m_Text += nChar;

	}

	string Shape::ToString()
	{
		return m_Name + ","
			+ ltos(m_StartPoint.x) + "," + ltos(m_StartPoint.y) 
			+ "," + ltos(m_EndPoint.x) + "," + ltos(m_EndPoint.y) 
			+ "," + ltos(m_PenWidth)
			+ "," + m_Text
		+ "\n";
	}
};