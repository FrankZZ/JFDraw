#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Circle.h"

namespace Fraint
{

	void Circle::Draw(CDC *pDC)
	{
		pDC->Ellipse(m_Rect);
	};

}