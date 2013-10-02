#pragma once


class Rectangle1 : public Shape
{
	// Construction
	public:
		Rectangle1(CPoint StartPoint) : Shape(StartPoint) {};
		Rectangle1(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

	// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
};