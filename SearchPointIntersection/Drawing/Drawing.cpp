// Drawing.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>

constexpr int Ox = 100;
constexpr int Oy = 100;
constexpr int size_point = 5;
constexpr int line_sickness = 3;

void show_line(const HDC& hdc, const int x0, const int y0, const int x1, const int y1) {
    MoveToEx(hdc, x0, y0, 0);
    LineTo(hdc, x1, y1);
}

void show_point(const HDC& hdc, const int x0, const int y0, const int x1, const int y1) {
    HBRUSH brush;
    brush = CreateSolidBrush(RGB(60, 60, 230)); //Создаём кисть определённого стиля и цвета
    SelectObject(hdc, brush); //Выбираем кисть
    Ellipse(hdc, x0, y0, x1, y1);
    DeleteObject(brush); //Очищаем память от созданной, но уже ненужной кисти
}

int main()
{
    std::cout << "kkk";
    HWND hwnd = GetConsoleWindow();
    wchar_t Title[1024];
    GetConsoleTitle(Title, 1024); // Узнаем имя окна
    //hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
    RECT window = {};
    GetWindowRect(hwnd, &window);
    HDC hdc = GetDC(hwnd);    // Получаем контекст для рисования
    HPEN p1, p2 = CreatePen(PS_SOLID, line_sickness, RGB(255, 0, 0)); // Создаем красное перо
    p1 = (HPEN)SelectObject(hdc, p2);  // Заносим красное перо в контекст рисования
    std::ifstream fin1;
    fin1.open("../SearchPointIntersection/function1.dat");
    //LONG x0 = window.left + 700, y0 = window.top + 470, 
      //  size_x = (window.right - window.left) / 10, size_y = 400;
    //std::cout << window.left << "\t" << window.top << "\t" << window.right << "\t" << window.bottom << "\n";
    char* kek = new char[10];
    double x, y, x0 = Ox, y0 = Oy;
    fin1 >> kek;
    fin1 >> kek;
    while (!fin1.eof()) {
        fin1 >> x;
        fin1 >> y;
        x = static_cast<int>(x);
        x = static_cast<int>(y);
        show_line(hdc, x0, y0, x, y);
        x0 = x;
        y0 = y;
        //std::cout << x << "\t" << y << "\n";
    }
    fin1.close();

   // SelectObject(hdc, p1);
   // ReleaseDC(hwnd, hdc);
    
    /*HPEN p3, p4 = CreatePen(PS_SOLID, 5, RGB(125, 125, 0)); // Создаем красное перо
    p3 = (HPEN)SelectObject(hdc, p4);  // Заносим красное перо в контекст рисования

    std::ifstream fin2;
    fin2.open("../SearchPointIntersection/function2.dat");

    fin1 >> kek;
    fin1 >> kek;
    while (!fin2.eof()) {
        fin1 >> x;
        fin1 >> y;
        x = static_cast<int>(x);
        x = static_cast<int>(y);
        show_line(hdc, x0, y0, x, y, lppt);
        lppt->x = x;
        lppt->y = y;
    }
    fin2.close();*/

    

    SelectObject(hdc, p1);   // Возвращаем старое перо
    DeleteObject(p1);       // Удаляем созданное перо
    SelectObject(hdc, p2);
    DeleteObject(p2);       // Удаляем созданное перо
   /* SelectObject(hdc, p3);
    DeleteObject(p3);       // Удаляем созданное перо
    SelectObject(hdc, p4);
    DeleteObject(p4);       // Удаляем созданное перо*/
	ReleaseDC(hwnd, hdc);
    std::cin.get();
}
