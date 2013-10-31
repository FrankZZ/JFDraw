#include "stdafx.h"
#include "JFDraw.h"
#include "Shape.h"
#include <vector>
#include "Polygon.h"

using namespace std;

namespace Fraint
{
	Polygon::Polygon(CPoint StartPoint, CPoint EndPoint) : 
		Shape(StartPoint, EndPoint),
		m_vPoints()
	{
		Polygon::Init();
	};

	Polygon::Polygon(CPoint StartPoint) : 
		Shape(StartPoint),
		m_vPoints()
	{
		Polygon::Init();
	};

	void Polygon::SetEndPoint(CPoint point)
	{
		m_vPoints.push_back(point);
	}

	void Polygon::Init()
	{
		m_Name = "Polygon";
		m_vPoints.push_back(m_StartPoint);
	};

	void Polygon::Draw(CDC *pDC)
	{
		pDC->Polygon(&m_vPoints[0], m_vPoints.size());
	};
}