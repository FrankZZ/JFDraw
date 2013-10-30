#pragma once

#include <string>

using namespace std;

namespace Fraint
{
	class Rectangle : public Shape
	{
		// Construction
	public:
		Rectangle(CPoint StartPoint);
		Rectangle(CPoint StartPoint, CPoint EndPoint);

		// Implementation
	public:
		void Init();
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
	};
}