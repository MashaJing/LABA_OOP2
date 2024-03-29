// OOP2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"


using namespace std;
class Parallelogram
{

private:
	int linestyle;
	int linethick;
	int linecolor;

	int fillstyle;
	int fillcolor;


	float len_between(const POINT a, const POINT b)
	{
		return sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));// длина прямой между точками
	}

	int check_window_location(const RECT &rt)
	{
		int n = 4;
		int xmax = ppt[0].x;
		int ymax = ppt[0].y;
		for (int i = 0; i < n; i++)
		{
			if (ppt[i].x < 0 || ppt[i].y < 0) return 0;
			if (ppt[i].x > xmax) xmax = ppt[i].x; // находим максимальный x и y, чтобы сравнить их с границами окна
			if (ppt[i].y > ymax) ymax = ppt[i].y;
		}

		if (xmax <= rt.right && ymax <= rt.bottom) return 1; else return 0;
	}

public:

	POINT *ppt;

	Parallelogram()
	{
	}

	Parallelogram(POINT *ppt)
	{
		this->ppt = ppt;
	}

	void set_coord(POINT *ppt)
	{
		this->ppt = ppt;
	}
	void set_linethick(int linethick)
	{
		this->linethick = linethick;
	}
	void set_linestyle(int linestyle)
	{
		this->linestyle = linestyle;
	}
	void set_linecolor(int linecolor)
	{
		this->linecolor = linecolor;
	}
	void set_fillcolor(int fillcolor)
	{
		this->fillcolor = fillcolor;
	}
	void set_fillstyle(int fillstyle)
	{
		this->fillstyle = fillstyle;
	}
	int check_parall()
	{

		if (len_between(this->ppt[0], this->ppt[1]) == len_between(this->ppt[2], this->ppt[3]))
		{
			if (len_between(this->ppt[1], this->ppt[2]) == len_between(this->ppt[3], this->ppt[0]))
				return 1;
		}
		else return 0;
	}

	int check_nesting(const POINT *pptin)
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
				if (!((k1 >= 0 && k2 >= 0 && k3 >= 0) || (k1 <= 0 && k2 <= 0 && k3 <= 0))) return 0;
			}
		}
		return 1;

	}

	int print_1()
	{
		COLORREF color;
		HWND hwnd = FindWindowA("Notepad", NULL);
		HDC hdc = GetDC(hwnd);
		RECT rt;
		POINT pt;
		BOOL bxt;
		GetClientRect(hwnd, &rt);

		if (check_window_location(rt) == 0)
		{
			cout << "вне области рисования" << endl;
			return 0;
		}

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

	int print_2()
	{
		HWND hwnd = FindWindowA("Notepad", NULL);
		HDC hdc = GetDC(hwnd);
		RECT rt;
		POINT pt;
		BOOL bxt;
		COLORREF lcolor;
		COLORREF bcolor;
		GetClientRect(hwnd, &rt);

		if (check_window_location(rt) == 0)
		{
			cout << "вне области рисования" << endl;
			return 0;
		}

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

};

FILE *fl;
int main()
{
	setlocale(LC_ALL, "ru");
	POINT *ppt = new POINT[4];
	POINT *pptin = new POINT[4];

	int mode;// 1 - незакр, 2 - закрашенный, 3 - фигура в фигуре

	int linestyle;
	int linethick;
	int linecolor;

	int fillstyle;
	int fillcolor;
	errno_t err;
	err = fopen_s(&fl, "Text6.txt", "r");
	if (err == 0)
	{

		fscanf_s(fl, "%d", &mode);
		if (mode != 1)
		{
			fscanf_s(fl, "%d", &fillstyle);
			fscanf_s(fl, "%d", &fillcolor);
		}

		for (int i = 0; i < 4; i++)
		{
			fscanf_s(fl, "%d %d", &ppt[i].x, &ppt[i].y);
		}
		Parallelogram outer(ppt);

		fscanf_s(fl, "%d", &linestyle);
		fscanf_s(fl, "%d", &linethick);
		fscanf_s(fl, "%d", &linecolor);
		outer.set_linestyle(linestyle);
		outer.set_linecolor(linecolor);
		outer.set_linethick(linethick);
		if (mode != 1)
		{
			outer.set_fillstyle(fillstyle);
			outer.set_fillcolor(fillcolor);
		}
		if (outer.check_parall() == 0)
		{
			cout << "1-ая заданная фигура не параллелограмм"<<endl;
			system("pause");
			return 1;
		}


		switch (mode)
		{
		case 1:
			outer.print_1();
			break;
		case 2:
			outer.print_2();
			break;
		case 3:
		{

			for (int i = 0; i < 4; i++)
			{
				fscanf_s(fl, "%d %d", &pptin[i].x, &pptin[i].y);
			}
			Parallelogram inner(pptin);
			
			if (inner.check_parall() == 0)
			{
				cout << "2-ая заданная фигура не параллелограмм";
				return 1;
			}
			if (outer.check_nesting(pptin) == 0)
			{
				cout << "заданные точки не вложены в 1-ый параллелограмм"<<endl;
				system("pause");
				return 1;
			}
			outer.print_2();
			inner.print_1();
		}
		}
		fclose(fl);
	}
	else cout << "файл не найден" << endl;
	system("pause");
	return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
