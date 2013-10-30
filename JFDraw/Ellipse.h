#pragma once

namespace Fraint
{
	class Ellipse : public Shape
	{
		// Construction
	public:
		Ellipse(CPoint StartPoint);
		Ellipse(CPoint StartPoint, CPoint EndPoint);

		// Implementation
	public:
		void Init();
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
	};
}