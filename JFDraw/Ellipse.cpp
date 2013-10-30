#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Ellipse.h"

namespace Fraint
{
	Ellipse::Ellipse(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint)
	{
		Ellipse::Init();
	};

	Ellipse::Ellipse(CPoint StartPoint) : Shape(StartPoint)
	{
		Ellipse::Init();
	};

	void Ellipse::Init()
	{
		m_Name = "Ellipse";
	}

	void Ellipse::Draw(CDC *pDC)
	{
		pDC->Ellipse(m_Rect);
	};
}