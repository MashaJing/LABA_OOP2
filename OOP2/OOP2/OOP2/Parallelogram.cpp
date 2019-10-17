#include "pch.h"
#include "Parallelogram.h"

	float Parallelogram::len_between(const POINT a, const POINT b)
	{
		return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));// длина прямой между точками
	}

	int Parallelogram::check_window_location(const RECT &rt)
	{
		int n = 4;

		int xmax = ppt[0].x;
		int ymax = ppt[0].y;
		for (int i = 0; i < n; i++)
		{
			if (ppt[i].x < 0 || ppt[i].y < 0) throw 2;
			if (ppt[i].x > xmax) xmax = ppt[i].x; // находим максимальный x и y, чтобы сравнить их с границами окна
			if (ppt[i].y > ymax) ymax = ppt[i].y;

		}

		if (xmax <= rt.right && ymax <= rt.bottom) return 1; else throw 2;
	}

	
	Parallelogram::Parallelogram()
	{};
	Parallelogram::Parallelogram(POINT *ppt)
	{
		this->ppt = ppt;
	};

	void Parallelogram::move(char reply)
	{
		switch (reply)
		{
		case 'a':
		{	for (int i = 0; i < 4; i++)
		{
			this->ppt[i].x -= 20;
		}

		break;		}
		case 's':
		{	for (int i = 0; i < 4; i++)
			{
				this->ppt[i].y += 20;
			}

		break; }
		case 'w':
		{	for (int i = 0; i < 4; i++)
		{
			this->ppt[i].y -= 20;
		}

		break; }
		case 'd':
		{for (int i = 0; i < 4; i++)
		{
			this->ppt[i].x += 20;
		}

		break;
		}
		}
		}
	void Parallelogram::set_coord(POINT *ppt)
	{
		this->ppt = ppt;
	}
	void Parallelogram::set_linethick(int linethick)
	{
		this->linethick = linethick;
	}
	void Parallelogram::set_linestyle(int linestyle)
	{
		this->linestyle = linestyle;
	}
	void Parallelogram::set_linecolor(int linecolor)
	{
		this->linecolor = linecolor;
	}
	void Parallelogram::set_fillcolor(int fillcolor)
	{
		this->fillcolor = fillcolor;
	}
	void Parallelogram::set_fillstyle(int fillstyle)
	{
		this->fillstyle = fillstyle;
	}
	
	POINT* Parallelogram::get_coord()
	{
		return (this->ppt);
	}
	int Parallelogram::get_linethick()
	{
		return (this->linethick);
	}
	int Parallelogram::get_linestyle()
	{
		return (this->linestyle);
	}
	int Parallelogram::get_linecolor()
	{
		return (this->linecolor);
	}
	int Parallelogram::get_fillcolor()
	{
		return (this->fillcolor);
	}
	int Parallelogram::get_fillstyle()
	{
		return (this->fillstyle);
	}
	int Parallelogram::check_parall()
	{

		if (len_between(this->ppt[0], this->ppt[1]) == len_between(this->ppt[2], this->ppt[3]))
		{
			if (len_between(this->ppt[1], this->ppt[2]) == len_between(this->ppt[3], this->ppt[0]))
				return 1;
		}
		else 	throw 4;
	}

	int Parallelogram::check_nesting(const POINT *pptin)
	{

		float k1, k2, k3;
		float x, y, x1, y1, x2, y2, x3, y3;

		x1 = this->ppt[0].x; y1 = this->ppt[0].y;
		x2 = this->ppt[2].x; y2 = this->ppt[2].y;
		for (int i = 0; i < 4; i++)
		{
			x3 = this->ppt[1].x; y3 = this->ppt[1].y; // x1,x2,x3 - координаты вершин 1ого из треугольников, полученного делением параллелограмма пополам
			x = pptin[i].x; y = pptin[i].y; //координаты проверяемой точки
			k1 = (x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y);
			k2 = (x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y);
			k3 = (x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y);
			if (!((k1 >= 0 && k2 >= 0 && k3 >= 0) || (k1 <= 0 && k2 <= 0 && k3 <= 0)))
			{
				x3 = this->ppt[3].x; y3 = this->ppt[3].y; //x1,x2,новое x3 - координаты вершин 2ого из треугольников, полученного делением параллелограмма пополам
				k1 = (x1 - x) * (y2 - y1) - (x2 - x1) * (y1 - y);
				k2 = (x2 - x) * (y3 - y2) - (x3 - x2) * (y2 - y);
				k3 = (x3 - x) * (y1 - y3) - (x1 - x3) * (y3 - y);
				if (!((k1 >= 0 && k2 >= 0 && k3 >= 0) || (k1 <= 0 && k2 <= 0 && k3 <= 0))) throw 3;
			}
		}
		return 1;

	}

	int Parallelogram::print_1()
	{
		COLORREF color;
		HWND hwnd = FindWindowA("Notepad", NULL);
		HDC hdc = GetDC(hwnd);
		RECT rt;
		BOOL bxt;
		GetClientRect(hwnd, &rt);
		check_window_location(rt);

		switch (this->linecolor)
		{
		case 0:
			color = black;
			break;
		case 1:
			color = red;
			break;
		case 2:
			color = green;
			break;
		case 3:
			color = blue;
			break;
		}


		HPEN hBlackPen = GetStockPen(BLACK_PEN);
		HPEN hUserPen = CreatePen(this->linestyle, this->linethick, color);
		SelectPen(hdc, hUserPen);

		bxt = Polygon(hdc, this->ppt, 4);

		SelectPen(hdc, hBlackPen);
		DeletePen(hUserPen);
		ReleaseDC(hwnd, hdc);

		return 1;
	}

	int Parallelogram::print_2()
	{
		HWND hwnd = FindWindowA("Notepad", NULL);
		HDC hdc = GetDC(hwnd);
		RECT rt;
		BOOL bxt;
		COLORREF lcolor;
		COLORREF bcolor;
		GetClientRect(hwnd, &rt);
		check_window_location(rt);

		switch (this->linecolor)
		{
		case 0:
			lcolor = black;
			break;
		case 1:
			lcolor = red;
			break;
		case 2:
			lcolor = green;
			break;
		case 3:
			lcolor = blue;
			break;
		}

		switch (this->fillcolor)
		{
		case 0:
			bcolor = black;
			break;
		case 1:
			bcolor = red;
			break;
		case 2:
			bcolor = green;
			break;
		case 3:
			bcolor = blue;
			break;
		}

		HPEN hBlackPen = GetStockPen(BLACK_PEN);
		HPEN hUserPen = CreatePen(this->linestyle, this->linethick, lcolor);
		SelectPen(hdc, hUserPen);

		HBRUSH hOldBrush = GetStockBrush(WHITE_BRUSH);
		if (this->fillstyle == 0)
		{
			HBRUSH hUserBrush = CreateSolidBrush(bcolor);
			SelectBrush(hdc, hUserBrush);
		}
		else
		{
			HBRUSH hUserBrush = CreateHatchBrush(this->fillstyle, bcolor);
			SelectBrush(hdc, hUserBrush);
		}

		bxt = Polygon(hdc, this->ppt, 4);


		SelectPen(hdc, hBlackPen);
		DeletePen(hUserPen);
		SelectBrush(hdc, hOldBrush);
		ReleaseDC(hwnd, hdc);

		return 1;
	}