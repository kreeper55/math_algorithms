#include "polynom.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

double func(double x) {
    //return sin(x);
    //return -x*x*x - x*x + 3 * x + 1;
    //return cos(PI * x / 2);
    //return abs(x - 0.001 * sqrt(2));
    return 1 / (25 * x * x + 1);
    //return cos(x);
    //return log(x * x + cos(x));
}

constexpr int loading = 50;
constexpr int N = 11;

int main() {
    polynom pol(func);
    int n = 2 * N + 2;   // number of terms
    double a = -0.1;     //   start  segment
    double b = 0.1;      //   end segment
    double max_norm = 2.22507e-308;
    double step = (b - a) / (n);

    std::vector<double> array_x(n, 1);
    double x = a + step / 2;
    for (int i = 0; i < n; i++) {
        array_x[i] = x;
        x += step;
    }


    pol.init((abs(b) - abs(a)) / 2, n, step);

    std::ofstream fout("file.dat");
    std::ofstream middle_point("middle_point.dat");

    double diff = 0.0;
    double r = a, result = 0.0;
    std::cout << "compute.." << std::endl;
    for(int i = 0; i <= n; i++){
        std::system("cls");
        std::cout << "|";
        for(int j = 0; j < i * loading / n; j++)
            std::cout<<"*";
        for(int j = 0; j < loading - i * loading / n; j++)
            std::cout<<"_";
        std::cout << "|\n";

        diff = abs(func(array_x[i]) - pol(array_x[i]));
        if (diff > max_norm) {
            max_norm = diff;
        }

        middle_point << array_x[i] << "\t" << pol(array_x[i]) << "\n";
        fout << r << "\t" << pol(r) << "\n";

        r += step;
    }

    std::cout << std::endl << "norm : " << max_norm << std::endl;
}

/*int main() {
    polynom pol(func);
    int n = 10;          // number of terms
    double a = -1.0;     //   start  segment
    double b = 1.0;     //   end segment
    int count = 49;     // number of points
    double r, result = 0.0;
    double max_norm = 2.22507e-308;
    double step = (b - a)/(2 * n);

    std::vector<double> array_x(count, 1);
    double x = a + step / 2;
    for (int i = 0; i < count; i++) {
        array_x[i] = x;
        x += step;
    }


    pol.init((abs(b) - abs(a)) / 2, n, step);

    std::cout << "enter key " ;
    std::cin >> r;

    std::ofstream fout("file.dat");

    double diff = 0.0;
    for(int i = 0; i < count; i++){
        std::system("cls");
        std::cout << "|";
        for(int j = 0; j < i * loading / count; j++)
            std::cout<<"*";
        for(int j = 0; j < loading - i * loading / count; j++)
            std::cout<<"_";
        std::cout << "|\n";

        r = a + (b - a) * double(i) / count;
        result = pol(r);
        diff = abs(func(array_x[i]) - pol(array_x[i]));
        if (diff > max_norm) {
            max_norm = diff;
        }

        fout << r << "\t" << result << "\n";
    }

    std::cout << std::endl << "norm : " << max_norm << std::endl;
}
*/
