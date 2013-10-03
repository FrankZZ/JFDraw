#pragma once


namespace Fraint
{

	class Circle : public Shape
	{
		// Construction
	public:
		Circle(CPoint StartPoint) : Shape(StartPoint) {};
		Circle(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

		// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
	};

}