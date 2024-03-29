// OOP2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Parallelogram.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "ru");
	POINT *ppt = new POINT[4];
	POINT *pptin = new POINT[4];
	POINT scr[4];
	HWND hwnd = FindWindowA("Notepad", NULL);
	HDC hdc = GetDC(hwnd);
	RECT rt;
	GetClientRect(hwnd, &rt);

	int mode;// 1 - незакр, 2 - закрашенный, 3 - фигура в фигуре

	int linestyle;
	int linethick;
	int linecolor;

	int fillstyle;
	int fillcolor;

	ifstream myfile("Text.txt");
	try
	{
		if (myfile.is_open() != true) throw 1;

		myfile >> mode;

		for (int i = 0; i < 4; i++)
		{
			myfile >> ppt[i].x;
			myfile >> ppt[i].y;
		}

		Parallelogram outer(ppt);

		if (mode == 3)
		{
			for (int i = 0; i < 4; i++)
			{
				myfile >> pptin[i].x;
				myfile >> pptin[i].y;
			}
		}
		Parallelogram inner(pptin);
		myfile >> linestyle;
		myfile >> linethick;
		myfile >> linecolor;
		outer.set_linestyle(linestyle);
		outer.set_linecolor(linecolor);
		outer.set_linethick(linethick);

		if (mode != 1)
		{
			myfile >> fillstyle;
			myfile >> fillcolor;
			outer.set_fillstyle(fillstyle);
			outer.set_fillcolor(fillcolor);
		}

		
		outer.check_parall(); //Проверка параллельности сторон
		
		
		if (mode == 3)
		{
			inner.check_parall();
			outer.check_nesting(pptin);
		}

		switch (mode)
		{
		case 1:
			outer.print_1();
		case 2:
			outer.print_2();
		case 3:
		{	
			outer.print_2();
			inner.print_1(); 
		}
		}	
		myfile.close();

		cout << "нажимайте на клавиши, чтобы двигать фигуру. Нажмите 0, чтобы выйти" << endl;
		char reply;
		cin >> reply;

		scr[0].y = (rt.bottom - 1);
		scr[0].x = 1;

		scr[1].y = 1; //создаётся параллелограмм размером с окно
		scr[1].x = 1;//и поле рисования закрывается им

		scr[2].y = 1;
		scr[2].x = (rt.right - 1);

		scr[3].y = (rt.bottom - 1);
		scr[3].x = (rt.right - 1);

		Parallelogram screen(scr);

		while (reply != '0')
		{
			screen.print_1();
			outer.move(reply);
			//проверка на вхождение в экран
				
		
			switch (mode)
			{
			case 1:
				outer.print_1();
				break;
			case 2:
				outer.print_2();
				break;
			case 3:
			{	outer.print_2();
			inner.move(reply);
			inner.print_1();
			break;
			}
			}
			cin >> reply;

			ofstream results("result.txt");
			results << mode<<endl;
			POINT* temp = outer.get_coord();
			for (int i = 0; i < 4; i++)
			{
				results << temp[i].x << ' ';
				results << temp[i].y << endl;
			}

			if (mode == 3)
			{
				POINT* temp = inner.get_coord();
				for (int i = 0; i < 4; i++)
				{
					results << temp[i].x << ' ';
					results << temp[i].y << endl;
				}
			}
			results << outer.get_linestyle() << ' ';
			results << outer.get_linethick() << ' ';
			results << outer.get_linecolor() << endl;
			if (mode != 1)
			{
				results << outer.get_fillstyle() << ' ';
				results << outer.get_fillcolor() << endl;
			}

		}

	}
		catch (int a)
		{
			switch (a)
			{
			case 1:
			{
				cout << "File not found" << endl;
				break;
			}
			case 2:
			{
				cout << "Заданная фигура вне окна" << endl;
				break;
			}
			case 3:

			{
				cout << "Внутренний параллелограмм не входит во внешний" << endl;
				break;
			}

			case 4:
			{
				cout << "Заданная фигура - не параллелограмм" << endl;
				break;
			}
			}
		}
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
