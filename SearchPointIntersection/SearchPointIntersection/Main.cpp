#include <iostream>
#include <iomanip>
#include <functional>
#include <fstream>
#include <math.h>

#include <list>
#include <map>
#include <chrono>

#include "Point2D.h"
#include "Function.h"
#include "Curve.h"

using std::list;
using std::function;
using std::map;

//	���������� ����� �� �����, ��� ������, ��� ������ �������
//	��� ������� ���-�� ������ ������� ������ �����
constexpr unsigned short cells = 500;

//	��������� �����, �������� ������� ��� ������ �������
struct Grid {
	double u1, u2, v1, v2;
	Grid(double u1, double u2, double v1, double v2) :
		u1(u1), u2(u2),
		v1(v1), v2(v2) {}

	Grid(const Grid& grid) :
		u1(grid.u1), u2(grid.u2),
		v1(grid.v1), v2(grid.v2) {}

	Grid() {
		u1 = u2 = v1 = v2 = 0;
	}
};

//	����������� �������� ������ ����� �����������
//	������������ ���������� ��������� �� ����� � �������� cells � �������� ������ h
list<double> search_for_intersection_points(
			IFunction &f1, const double &u1, const double &u2,
			IFunction &f2, const double &v1, const double &v2, 
			const double &epsilon = 1e-2, const double &h = 1., //	�������� �� ���������
			unsigned short count = 0) {
	//	������������ ���������� ����������� �������
	if (count > 10) { return list<double>(); }

	unsigned short t_count = count;			//	������� ��� ��������							
	double interval1 = (u2 - u1) / cells;	//	��������� �� ���������(���), �� ������� ����� ����������� ������
	double interval2 = (v2 - v1) / cells;
	double t_h = h, temp = 0;				

	map<double, Point2D> mapPoints1;	//	���� ��� �������� ��������� ������, � ������� ������ ��� �������	
	map<double, Point2D> mapPoints2;
	list<double> results;				//	���� ���������� (����������)
	Grid grid(u1, u2, v1, v2);			//	��������������� �����
	Point2D p;							//	��������������� �����

	//	��� ���� ������ ���������� ������� ������� � ������������ ���������� � ����������
	//	���������� ������������� � ����������� ����, ����� ������, � ����� ��������� ����� ������ �������� ����� �������
	for (int i = 0; i <= cells; i++) {
		temp = u1 + interval1 * i;	
		mapPoints1[temp] = Point2D(floor(f1.get_X(temp) / h), floor(f1.get_Y(temp) / h));

		temp = v1 + interval2 * i;
		mapPoints2[temp] = Point2D(floor(f2.get_X(temp) / h), floor(f2.get_Y(temp) / h));
	}

	//	��������� �� ������� ���������� ���������
	for (auto it1 = mapPoints1.begin(); it1 != mapPoints1.end(); ++it1) {
		for (auto it2 = mapPoints2.begin(); it2 != mapPoints2.end(); ++it2) {
			if (it1->second == it2->second) {
				//	���� ���������� �������, ����������� ��������� ����� ����� ������������
				double delta_x = f1.get_X(it1->first) - f2.get_X(it2->first);
				double delta_y = f1.get_Y(it1->first) - f2.get_Y(it2->first);
				//	���� ��� ������ ��������� eps, �� ��������� ��� ����� � ����
				if (sqrt(pow(delta_x, 2) + pow(delta_y, 2)) < epsilon) { 
					results.push_back(it1->first);
					p = it1->second;
					while (it1 != --mapPoints1.end() && p == it1->second) { ++it1; }	//	���������� ��� ����������
					while (it2 != --mapPoints2.end() && p == it2->second) { ++it2; }	//	� ����������� ������������
				}
				else {	//	���� �������� �������������������
					grid.u1 = it1->first - interval1;	//	���������� ������ ����������
					grid.v1 = it2->first - interval2;	//	������ ����� ������ � ��������� ���
					p = it1->second;

					while (it1 != --mapPoints1.end() && p == it1->second ) { ++it1; }	//	���� ��������� ����������
					grid.u2 = it1->first + interval1;									//	�� ������ �����������

					while (it2 != --mapPoints2.end() && p == it2->second) { ++it2; }
					grid.v2 = it2->first + interval2;

					t_h *= 0.1;	//	��������� ���
					t_count++;	//	������� ������ ��������
					
					results.merge(search_for_intersection_points(
						f1, grid.u1, grid.u2,
						f2, grid.v1, grid.v2,
						epsilon, t_h, t_count
					));	//	����������� ����� � ���������� ����������� � ����

					t_h *= 10;	//	���������� ������ ��������
					t_count--;	//	����� ������ �� ��������
				}
			}
		}
	}
	mapPoints1.clear();	
	mapPoints2.clear();

	return results;
}

int main() {
	system("start ../x64/Debug/Drawing.exe");
	system("pause");
	//std::cout << std::setprecision(15) << std::endl;
	//	������ ������� �������� ��������������
	//function<double(double)> f_x1 = [](double t) { return t * 0.6; };
	//function<double(double)> f_y1 = [](double t) { return std::sin(2 * t*t); };
	//function<double(double)> f_x2 = [](double t) { return 10 * std::cos(t); };
	//function<double(double)> f_y2 = [](double t) { return std::sin(t); };

	function<double(double)> f_x1 = [](double t) { return (t * 0.1 + 1)* std::cos(t * 5 + 1.5); };
	function<double(double)> f_y1 = [](double t) { return (t * 0.1 + 1) * std::sin(t * 5 + 1.5); };
	function<double(double)> f_x2 = [](double t) { return t; };
	function<double(double)> f_y2 = [](double t) { return sin(t * t * 2); };
	/*function<double(double)> f_x1 = [](double t) { return std::cos(t); };
	function<double(double)> f_y1 = [](double t) { return std::sin(t); };
	function<double(double)> f_x2 = [](double t) { return t; };
	function<double(double)> f_y2 = [](double t) { return (t * t); };*/


	IFunction *func1 = new Curve(f_x1, f_y1);	//	����� ������, � �������� ����� ��� ������-�������
	IFunction *func2 = new Curve(f_x2, f_y2);	//	������ ��������� ����������� ����� - �������
	
	double u1 = -30, u2 = 30;		//	������� ��� ������ �-��
	double v1 = -5, v2 = 5;	//	��� ������
	double eps = 1e-10;			//	��� �������� ���������� �����

	const unsigned amount_points = 10000;	//	��� ������ ����� ������� � ���� (� ���������� �� ���������)

	//	��� ������ � ����
	std::ofstream fout1;
	fout1.open("function1.dat");
	fout1 << "x\ty\n";
	for (double i = u1; i <= u2; i += (u2 - u1) / amount_points) {
		Point2D point1(func1->getPoint(i));
		fout1 << point1.to_string() << "\n";
	}
	fout1.close();

	std::ofstream fout2;
	fout2.open("function2.dat");
	fout2 << "x\ty\n";
	for (double i = v1; i <= v2; i += (v2 - v1) / amount_points) {
		Point2D point2(func2->getPoint(i));
		fout2 << point2.to_string() << "\n";
	}
	fout2.close();
	


	std::chrono::time_point<std::chrono::system_clock> start_t, end_t;
	start_t = std::chrono::system_clock::now();

	std::cout << "search intersection points..." << "\n";
	list<double> res = search_for_intersection_points(*func1, u1, u2, *func2, v1, v2, eps);

	std::ofstream fres;
	fres.open("result.dat");
	fres << "x\ty\n";

	std::cout << "points found:" << res.size() << "\n";
	while (!res.empty()) {
		std::cout << func1->getPoint(res.front()).to_string() << std::endl;
		fres << std::scientific << std::setprecision(15) << func1->get_X(res.front()) << "\t" << func1->get_Y(res.front()) << "\n";
		res.pop_front();
	}
	fres.close();

	end_t = std::chrono::system_clock::now();
	auto ellapsed_sec = std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_t).count();
	std::cout << "calculations are finished for " << ellapsed_sec / 1000 << "." << ellapsed_sec % 60 << " seconds\n";

	func1->~IFunction();
	func2->~IFunction();
	return 0;
}
