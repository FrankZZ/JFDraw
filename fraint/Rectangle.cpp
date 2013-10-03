#include "stdafx.h"
#include "fraint.h"
#include "Shape.h"
#include "Rectangle.h"

namespace Fraint
{

	void Rectangle::Draw(CDC *pDC)
	{
		pDC->Rectangle(m_Rect);
	};

}