#include "matrix.h"
#include "gen.h"
#include <iostream>


#define N 60
#define ALPHA 1.e-1
#define BETA 1.e+0

using std::cout;
using std::endl;

template <typename type, size_t size>
matrix<double, size, size> reflected_matrix(matrix<type, size, size>& m)
{
    matrix<int, size, size> E('E');
    matrix<double, size, size> m_U, res_E('E');
    matrix<double, size, 1> m_W;
    for (int i = 0; i < size; i++)
        res_E[i][i] = 1;

    for (int i = 0; i < size - 1; i++) {
        matrix<double, size, 1> s_column = m.get_column(i);
        matrix<int, size, 1> l_column = E.get_column(i);
        for (int j = 0; j < i; j++) {
            s_column[j][0] = 0;
        }

        double alpha = sqrt(s_column.to_vector() * s_column.to_vector());
        double s_l = s_column.to_vector() * l_column.to_vector();
        alpha = (s_l < 0 ? alpha : alpha * -1);

        double ro = sqrt(2 * pow(abs(alpha), 2) + 2 * abs(alpha) * abs(s_l));

        m_W = (1./ro) * (s_column - alpha * l_column);

        m_U = E - 2 * (m_W * m_W.get_transposed());
        m = m_U * m;
        res_E = m_U * res_E;
    }
    return res_E;
}

template <typename type, size_t size>
mvector<type, size> solve_equation(const matrix<type, size, size>& m, const matrix<type, size, 1>& m_B) {
    mvector<double, size> res;

    for(int i = size - 1; i >= 0; i--){
        res[i] = m_B[i][0];
        for(int j = i + 1; j < size; j++)
            res[i] -= res[j] * m[i][j];
        res[i] /= m[i][i];
    }
    return res;
}

template <typename type, size_t size>
void reflect_triangle(matrix<type, size, size>& triangle_matrix) {
    double sum = 0;

    for (int i = size - 1; i >= 0; i--) {
        for (int j = size - 1; j >= i; j--) {
            if (i == j) {
                triangle_matrix[i][j] = 1 / triangle_matrix[i][j];
            }
            else {
                sum = 0;
                for (int k = j; k > i; k--) {
                    sum += triangle_matrix[i][k] * triangle_matrix[k][j];
                }
                triangle_matrix[i][j] = ((-1. * sum) / triangle_matrix[i][i]);
            }
        }
    }
}


int main() {
	const int n = N;
	double **a = new double* [n];
	for(int i = 0; i < n; i++)
		a[i] = new double [n];

	double **a_inv = new double* [n];
	for(int i = 0; i < n; i++ )
		a_inv[i] = new double [n];

	double alpha = ALPHA;
	double beta = BETA;

	mygen(a, a_inv, n, alpha, beta, 1, 2, 0, 1); // симметричная*/
	//matrix<double, n, n> A(a), A_INV(a_inv);
	//A = a;
	//a_inv = A_INV;
	//cout << endl << "a : \n" << endl << A << endl;
	//cout << endl << "a_inv : \n" << endl << A_INV << endl;
	//mygen ( a, a_inv, n, alpha, beta, 1, 2, 1, 1 ); //проостой структуры
	//mygen ( a, a_inv, n, alpha, beta, 0, 0, 2, 1 ); //жорданова клетка

/*	cout << "a:" << endl;
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ ) cout << " " << a[i][j];
		cout << endl;
	}
	cout << "a_inv:" << endl;
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ ) cout << " " << a_inv[i][j];
		cout << endl;
	}

*/
	//char ch;  cin >> ch;
    //matrix<double, n, n> m_inverse(a_inv

    cout << endl;

	matrix<double, n, n> m_matrix(a), m_inverse(a_inv), E('E');
	auto copy_matrix = m_matrix;

    auto H = reflected_matrix(m_matrix);
    auto answer = m_matrix;
    //cout << "method : reflected matrix (A = Ui * A)\n" << m_matrix << endl;
    reflect_triangle(m_matrix);
    //cout << "method : reflect triangle ()\n " << m_matrix << endl;

    answer = m_matrix * H;
    //cout << endl << endl << "(reflect) H : " << endl << H;
    //cout << endl << endl << endl << "my answer inverse matrix (U^-1 * H)\n" << answer;
    auto ans_diff = m_inverse - answer;
    //cout << endl << endl << endl << "a_inverse etalon matrix\n" << m_inverse;
    //cout << endl << "diff (matrix inverse - my answer) :\n" << ans_diff;

    answer = copy_matrix * answer;
    //cout << "\n\n\nt.e. matrix * matrix_inverse == E :\n" << answer;

    auto norm_z = ans_diff.norm();
    auto dzeta = norm_z / m_inverse.norm();
    auto norm_ro = (answer - E).norm();
    cout << "alpha = " << alpha << " \t";
    cout << "beta = " << beta << " \t";
    cout << "||A|| = " << copy_matrix.norm() << " \t";
    cout << "||A^-1|| = " << m_inverse.norm() << " \t";
    cout << "||z|| = " << norm_z << " \t";
    cout << "||dzeta|| = " << dzeta << " \t";
    cout << "||r|| = " << norm_ro << " \t";
}
