#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Rectangle.h"

using namespace std;

namespace Fraint
{
	Rectangle::Rectangle(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint)
	{
		Rectangle::Init();
	};

	Rectangle::Rectangle(CPoint StartPoint) : Shape(StartPoint)
	{
		Rectangle::Init();
	};

	void Rectangle::Init()
	{
		m_Name = "Rectangle";
	};

	void Rectangle::Draw(CDC *pDC)
	{
		pDC->Rectangle(m_Rect);
	};
}