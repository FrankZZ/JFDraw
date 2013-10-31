#pragma once

#include <string>
#include <vector>

using namespace std;

namespace Fraint
{
	class Polygon : public Shape
	{
		// Construction
	public:
		Polygon(CPoint StartPoint);
		Polygon(CPoint StartPoint, CPoint EndPoint);

		// Implementation
	public:
		void Init();
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
		void SetEndPoint(CPoint point);

	private:
		vector <CPoint> m_vPoints;
	};
}