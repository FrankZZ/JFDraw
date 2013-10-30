#pragma once

namespace Fraint
{

	class Ellipse : public Shape
	{
		// Construction
	public:
		Ellipse(CPoint StartPoint) : Shape(StartPoint) {};
		Ellipse(CPoint StartPoint, CPoint EndPoint) : Shape(StartPoint, EndPoint) {};

		// Implementation
	public:
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
	};

}