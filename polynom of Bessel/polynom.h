#include "math.h"
#include <vector>
#include <functional>

/*class Polynom {
private:
    double _a;
    double _b;
    double _step;
    //std::vector<double> _polynom_coef;
    double _polynom_coef;
    std::vector<double> _y; // f(x) = y, [x - n * _step, x + n * _step]
    int _size;
    double _x0;

    double delta(int y_i_1, int y_i, int nesting_level) {
        if (nesting_level == 0) return _y[y_i_1] - _y[y_i];

        return delta(y_i_1, y_i, nesting_level - 1);
    }

    double qu(double x) {
        return (x - _x0) / _step;
    }

    double func(double x) {
        //return sin(x);
        //return -x*x*x - x*x + 3 * x + 1;
        //return cos(PI * x / 2);
        //return abs(x - 0.001 * sqrt(2));
        //return 1 / (25 * x * x + 1);
        return cos(x);
    }

public:
    Polynom(double a, double b, int n) : _a(a), _b(b), _size(2 * n + 2) {
        _step = abs(_a - _b) / (_size - 1);
        _x0 = func(_a);
        //_polynom_coef.resize(_size);
        _y.resize(_size + 1);
        //_polynom_coef[_size / 2 - 1] = (func(_a) + func(_a + _step)) / 2;
        _polynom_coef = (func(_a) + func(_a + _step)) / 2;

        _y[_size / 2] = func(_x0);
        double h = _x0;
        for (int i = _size / 2 + 1, j = _size / 2 - 1; i < _size + 1 && j > 0; i++, j--) {
            _y[i] = func(h + _step);
            _y[j] = func(h - (i - j) * _step);
            h += _step;
        }
    }

    double polynom(double x) {
        double temp_qu = 0.0;
        unsigned long long factorial_even = 1;
        unsigned long long factorial_not_even = 1;
        for (int i = 0; i < _size - 1; i++) {
            temp_qu = qu(x);
            if (i % 2 == 0) {
                temp_qu -= 0.5;
                factorial_not_even *= (i + 1);
                for (int j = 0; j < i / 2; j++) {
                    temp_qu *= qu(x - j);
                    temp_qu *= qu(x + j - 1);
                }
                _polynom_coef += (temp_qu / factorial_not_even) * delta(_size / 2 + 1 - i, _size / 2 - i, i);
            } else {
                factorial_even *= (i + 1);
                for (int j = 0; j < i / 2 + 1; j++) {
                    temp_qu *= qu(x - j);
                    temp_qu *= qu(x + j - 1);
                }
                _polynom_coef += (temp_qu / factorial_even)  *
                    ((delta(_size / 2 - i, _size / 2 - 1 - i, i) + delta(_size / 2 + 1 - i, _size / 2 - i, i)) / 2);
            }
            //if ((i - 1) % 2 == 0) {
                //_polynom[_size / 2 - 1 + i] = qu(_a + _step * i) - 0.5)* delta();
            //} else {
            //}
        }
        return _polynom_coef;
    }
};*/

class polynom
{
private:
    std::function<double(double)> func;
    std::vector<double> coeff;
    double h, x0;
    int n;

    unsigned long long fact(int x)
    {
        unsigned long long res = 1;
        for(int i = 2;i <= x; i++)
            res *= i;
        return res;
    }

    double f(int i)
    {
        return func(x0 - (n - i) * h);
    }

public:
    double delta(int k, int i)
    {
        if(k == 1) return f(i + 1) - f(i);
        return delta(k - 1, i + 1) - delta(k - 1, i);
    }

    polynom(double(*func)(double))
    {
        this->func = func;
    }

    void init(double x0, int n, double h){
        this->x0 = x0;
        this->n = n;
        this->h = h;
        coeff.resize(n);
        coeff[0] = (f(n) + f(n + 1)) / 2;
        for (int i = 1; i < n; i++) {
            if (i % 2 == 1) {
                coeff[i] = delta(i, n - i / 2);
            } else {
                coeff[i] = (delta(i, n - i / 2) + delta(i, n - i / 2 + 1)) / 2;
            }
            coeff[i] /= fact(i);
        }
    }

    double operator()(double x){
        double t = (x - x0) / h;
        double res = coeff[0], k = 1.0;
        for(int i = 1; i < n; i++)
        {
            k = 1.0;
            for (int j = 1; j <= i / 2; j++) {
                k *= (t - j) * (t + j - 1);
            }

            if (i % 2 == 1) {
                k *= (t - 0.5) * coeff[i];
            }
            else {
                k *= coeff[i];
            }

            res += k;
        }
        return res;
    }
};
/*class polynom
{
private:
    std::function<double(double)> func;
    double h, x0;
    int n;

    unsigned long long fact(int x)
    {
        unsigned long long res = 1;
        for(int i = 2;i <= x;i++)
            res *= i;
        return res;
    }

    double f(int i)
    {
        return func(x0 - (n - i) * h);
    }

public:
    double delta(int k, int i)
    {
        if(k == 1) return f(i + 1) - f(i);
        return delta(k - 1, i + 1) - delta(k - 1, i);
    }

    polynom(double(*func)(double))
    {
        this->func = func;
    }

    void init(double x0, int n, double h){
        this->x0 = x0;
        this->n = n;
        this->h = h;
    }

    double operator()(double x){
        double t = (x - x0) / h;
        double res = 0.0;
        for(int i = 1; i < 2 * n + 2; i++)
        {
            double k = 1.0;
            for(int j = 1; j <= i / 2; j++)
                k *= (t - j) * (t + j - 1);

            if(i % 2 == 1) {
                k *= (t - 0.5) * delta(i, n - i / 2);
            }
            else {
                k *= (delta(i, n - i / 2) + delta(i, n - i / 2 + 1)) / 2;
            }

            k /= fact(i);
            res += k;

        }
        return res + (f(n) + f(n + 1)) / 2;
    }
};
*/
