#include "stdafx.h"
#include "fraint.h"
#include "Shape.h"
#include "Circle.h"

void Circle1::Draw(CDC *pDC)
{
	pDC->Ellipse(m_Rect);
};