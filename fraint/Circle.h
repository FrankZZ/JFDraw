#pragma once


class Circle1 : public Shape
{
	// Construction
	public:
		Circle1(CPoint StartPoint) : Shape(StartPoint) {};
		Circle1(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

	// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
};