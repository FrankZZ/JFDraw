#pragma once

namespace Fraint
{

	class Rectangle : public Shape
	{
		// Construction
	public:
		Rectangle(CPoint StartPoint) : Shape(StartPoint) {};
		Rectangle(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

		// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
	};

}