#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Circle.h"

namespace Fraint
{

	void Circle::SetEndPoint(CPoint EndPoint)
	{
		m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, EndPoint.x, EndPoint.y);
		m_Rect.NormalizeRect();

		if (m_Rect.Height() == m_Rect.Width())
			return;

		if (m_Rect.Height() > m_Rect.Width())
		{
			int height = m_Rect.Height();
			m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, m_StartPoint.x + height, m_StartPoint.y + height);
		} 
		else
		{
			int width = m_Rect.Width();
			m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, m_StartPoint.x + width, m_StartPoint.y + width);
		}
	}

	void Circle::Draw(CDC *pDC)
	{
		pDC->Ellipse(m_Rect);
	};

}