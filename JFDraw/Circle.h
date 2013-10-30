#pragma once

#include <string>

using namespace std;

namespace Fraint
{
	class Circle : public Shape
	{
		// Construction
	public:
		Circle(CPoint StartPoint);
		Circle(CPoint StartPoint, CPoint EndPoint);

		// Implementation
	public:
		void Init();
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
		void SetEndPoint(CPoint point);
	};
}