#include "stdafx.h"
#include "fraint.h"
#include "Shape.h"
#include "Rectangle.h"

void Rectangle1::Draw(CDC *pDC)
{
	pDC->Rectangle(m_Rect);
};