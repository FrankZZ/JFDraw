#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include "Square.h"

namespace Fraint
{

	void Square::SetEndPoint(CPoint EndPoint)
	{
		m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, EndPoint.x, EndPoint.y);
		
		m_Rect.NormalizeRect();

		if (m_Rect.Height() == m_Rect.Width())
			return;

		if (m_Rect.Height() > m_Rect.Width())
		{
			int width = m_Rect.Width();
			m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, m_StartPoint.x + width, m_StartPoint.y + width);
		} 
		else
		{
			int height = m_Rect.Height();
			m_Rect.SetRect(m_StartPoint.x, m_StartPoint.y, m_StartPoint.x + height, m_StartPoint.y + height);
		}
	}

	void Square::Draw(CDC *pDC)
	{
		pDC->Rectangle(m_Rect);
	};

}