#pragma once


namespace Fraint
{

	class Square : public Shape
	{
		// Construction
	public:
		Square(CPoint StartPoint) : Shape(StartPoint) {};
		Square(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

		// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
		void SetEndPoint(CPoint point);
	};
}