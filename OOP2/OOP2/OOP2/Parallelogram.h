#ifndef __PARALLELOGRAM_H
#define __PARALLELOGRAM_H
using namespace std;
class Parallelogram {

private:

	POINT *ppt;
	int linestyle;
	int linethick;
	int linecolor;

	int fillstyle;
	int fillcolor;
	int check_window_location(const RECT &rt);
	float len_between(const POINT a, const POINT b);
	
public:
	Parallelogram();
	Parallelogram(POINT *ppt);
	
	void move(char reply);
	void set_coord(POINT *ppt);
	void set_linethick(int linethick);
	void set_linestyle(int linestyle);
	void set_linecolor(int linecolor);
	void set_fillcolor(int fillcolor);
	void set_fillstyle(int fillstyle);
	

	POINT* get_coord();
	int get_linethick();
	int get_linestyle();
	int get_linecolor();
	int get_fillcolor();
	int get_fillstyle();
	
	int check_parall();
	int check_nesting(const POINT *pptin);
	int print_1();
	int print_2();
};
// TODO: add headers that you want to pre-compile here

#endif