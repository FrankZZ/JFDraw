#pragma once


namespace Fraint
{

	class Square : public Shape
	{
		// Construction
	public:
		Square(CPoint StartPoint);
		Square(CPoint StartPoint, CPoint EndPoint);

		// Implementation
	public:
		void Init();
		void Draw(CDC *pDC);
		void DrawTo(CDC *pDC, CPoint ToPoint);
		void SetEndPoint(CPoint point);
	};
}