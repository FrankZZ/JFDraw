#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Rectangle.h"

namespace Fraint
{

	void Rectangle::Draw(CDC *pDC)
	{
		pDC->Rectangle(m_Rect);
	};

}