#include "stdafx.h"
#include "fraint.h"
#include "Shape.h"
#include "Circle.h"

namespace Keks
{

	void Circle::Draw(CDC *pDC)
	{
		pDC->Ellipse(m_Rect);
	};

}