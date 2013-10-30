#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Ellipse.h"

namespace Fraint
{

	void Ellipse::Draw(CDC *pDC)
	{
		pDC->Ellipse(m_Rect);
	};

}