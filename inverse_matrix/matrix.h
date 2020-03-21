#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "m_vector.h"

template <typename Type, size_t sizeY, size_t sizeX, class Enable = void>
class matrix {};

template <typename Type, size_t sizeY, size_t sizeX>
class matrix<Type, sizeY, sizeX>
{
private:
	class proxy_variable;
	class proxy_const;
	template<typename lhs, typename rhs>
	static constexpr bool combined = is_same<lhs, rhs>::value ||
		is_convertible<lhs, rhs>::value;
    static constexpr size_t max_size = sizeX > sizeY ? sizeX : sizeY;
	const size_t _size = sizeY * sizeX;
	array<Type, sizeX * sizeY> values;

public:
	template<typename lhs, typename rhs>
	using enable_type_combined = typename enable_if<combined<lhs, rhs>, void>::type;
    //using enable_vector = typename enable_if<sizeY == 1||sizeX==1, void>::type;
	using eneble_type_square = typename enable_if<true, void>::type;

	matrix();
	matrix(char type_name);
	matrix(double** arr) {
        for (int i = 0; i < sizeY; i++)
            for (int j = 0; j < sizeX; j++)
                (*this)[i][j] = arr[i][j];
	}
	~matrix();

	proxy_variable operator[](const size_t& index);
	proxy_const operator[](const size_t& index)const;

	matrix<Type, sizeY, sizeX>& operator=(const matrix<Type, sizeY, sizeX>& exemp);

	template<typename other_type, typename temp = enable_type_combined<Type, other_type>>
	matrix<Type, sizeY, sizeX>& operator=(const matrix<other_type, sizeY, sizeX>& exemp);

	template<typename other_type, typename temp = enable_type_combined<Type, other_type>>
	matrix<Type, sizeY, sizeX>& operator+=(const matrix<other_type, sizeY, sizeX>& exemp);

	template<typename other_type, typename temp = enable_type_combined<Type, other_type>>
	matrix<Type, sizeY, sizeX>& operator-=(const matrix<other_type, sizeY, sizeX>& exemp);

	template<typename other_type, typename temp = enable_type_combined<Type, other_type>>
	matrix<Type, sizeY, sizeX>& operator/=(const other_type& exemp);

	template<typename other_type, typename temp = enable_type_combined<Type, other_type>>
	matrix<Type, sizeY, sizeX>& operator*=(const other_type& exemp);

	template<typename T, size_t Y, size_t X>
	friend istream& operator>>(istream& in, matrix<T, Y, X>& exemp);

	template<typename T, size_t Y, size_t X>
	friend ostream& operator<<(ostream& out, matrix<T, Y, X>& exemp);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, Y, X>
		operator+(const matrix<lhs, Y, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, Y, X>
		operator-(const matrix<lhs, Y, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value);

	template<typename lhs, typename rhs, size_t lhs_Y, size_t lhs_X, size_t rhs_Y, size_t rhs_X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, lhs_Y, rhs_X>
		operator*(const matrix<lhs, lhs_Y, lhs_X>& lhs_value, const matrix<rhs, rhs_Y, rhs_X>& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend mvector<typename common_type<lhs, rhs>::type, Y>
		operator*(const matrix<lhs, Y, X>& lhs_value, const mvector<rhs, X>& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend mvector<typename common_type<lhs, rhs>::type, Y>
		operator*(const mvector<lhs, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, Y, X>
		operator*(const matrix<lhs, Y, X>& lhs_value, const rhs& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, Y, X>
		operator*(const lhs& lhs_value, const matrix<rhs, Y, X>& rhs_value);

	template<typename lhs, typename rhs, size_t Y, size_t X, typename temp>
	friend matrix<typename common_type<lhs, rhs>::type, Y, X>
		operator/(const matrix<lhs, Y, X>& lhs_value, const rhs& rhs_value);

	template<typename temp = eneble_type_square>
	void sample_of_main_diagonal_elements();

	template<typename temp = eneble_type_square>
	matrix<Type, sizeY, sizeX> get_sample_of_main_diagonal_elements();

	mvector<Type, max_size> to_vector() {
	    if(sizeX != 1 && sizeY != 1) throw "PLOXO!";
        mvector<Type, max_size> res;
        for (int i = 0; i < max_size; i++)
            res[i] = values[i];
        return res;
	}

	Type norm() {
        Type n = 0.0;
        Type sum = 0.0;
        for (int i = 0; i < sizeY; i++) {
            sum = 0.;
            for (int j = 0; j < sizeX; j++) {
                sum = sum + fabs(values[i * sizeX + j]);
            }
            if (sum > n) n = sum;
        }
        return n;
	}

	void trangle_view();

	matrix<Type, sizeY, sizeX> get_trangle_view();

	void transposed();

	matrix<Type, sizeX, sizeY> get_transposed();

	template<typename temp = eneble_type_square>
	void conversed();

	template<typename temp = eneble_type_square>
	matrix<Type, sizeY - 1, sizeX - 1> get_conversed();

	matrix<Type, sizeY, 1> get_column(size_t index);

	matrix<Type, 1, sizeX> get_line(size_t index);

	void set_column(mvector<Type, sizeY> exemp, size_t index);

	void set_line(mvector<Type, sizeX> exemp, size_t index);

	void swap_elements(size_t x1, size_t y1, size_t x2, size_t y2);
};

#endif



template <typename Type, size_t sizeY, size_t sizeX>
class matrix<Type, sizeY, sizeX>::proxy_variable
{
private:
	const size_t& point;
	matrix<Type, sizeY, sizeX>& _matrix;
public:
	proxy_variable();
	proxy_variable(matrix<Type, sizeY, sizeX>& exemp, const size_t& index) :_matrix(exemp), point(index) {}
	Type& operator[](const size_t& index)
	{
		try {
			if (point >= sizeY || index >= sizeX) throw 0;
		}
		catch (...) { cout << "index outside the array" << endl; }
		return this->_matrix.values[point * sizeX + index];
	}
};

template <typename Type, size_t sizeY, size_t sizeX>
class matrix<Type, sizeY, sizeX>::proxy_const
{
private:
	const size_t& point;
	const matrix<Type, sizeY, sizeX>& _matrix;
public:
	proxy_const();
	proxy_const(const matrix<Type, sizeY, sizeX>& exemp, const size_t& index) :_matrix(exemp), point(index) {}
	const Type& operator[](const size_t& index) const
	{
		try {
			if (point >= sizeY || index >= sizeX) throw 0;
		}
		catch (...) { cout << "index outside the array" << endl; }
		return this->_matrix.values[point * sizeX + index];
	}

};

template<typename Type, size_t sizeY, size_t sizeX>
typename matrix<Type, sizeY, sizeX>::proxy_variable matrix<Type, sizeY, sizeX>::operator[](const size_t& index)
{
	return typename matrix<Type, sizeY, sizeX>::proxy_variable(*this, index);
}

template<typename Type, size_t sizeY, size_t sizeX>
typename matrix<Type, sizeY, sizeX>::proxy_const matrix<Type, sizeY, sizeX>::operator[](const size_t& index)const
{
	return typename matrix<Type, sizeY, sizeX>::proxy_const(*this, index);
}


template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeY, sizeX>::matrix() {}

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeY, sizeX>::matrix(char type_name) {
	switch (type_name) {
	case 'E':
		if (sizeY == sizeX)
			for (int i = 0; i < sizeY * sizeY; i++)
				if ((i - i / sizeY) % sizeY == 0) values[i] = 1;
				else values[i] = 0;
		break;
	case 'Z':
		for (int i = 0; i < sizeY * sizeY; i++)
			values[i] = 0;
		break;
	}
}

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeY, sizeX>::~matrix() {};

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator=(const matrix<Type, sizeY, sizeX>& exemp)
{
	for (int i = 0; i < sizeY * sizeX; i++)
		this->values[i] = exemp.values[i];
	return *this;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename other_type, typename temp>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator=(const matrix<other_type, sizeY, sizeX>& exemp)
{
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
			(*this)[i][j] = exemp[i][j];
	return *this;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename other_type, typename temp>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator+=(const matrix<other_type, sizeY, sizeX>& exemp)
{
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
			(*this)[i][j] += exemp[i][j];
	return *this;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename other_type, typename temp>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator-=(const matrix<other_type, sizeY, sizeX>& exemp)
{
	for (int i = 0; i < sizeY; i++)
		for (int j = 0; j < sizeX; j++)
			* this[i][j] -= exemp[i][j];
	return *this;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename other_type, typename temp>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator*=(const other_type& exemp)
{
	for (int i = 0; i < this->_size; i++)
		this->values[i] *= static_cast<Type>(exemp);
	return *this;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename other_type, typename temp>
matrix<Type, sizeY, sizeX>& matrix<Type, sizeY, sizeX>::operator/=(const other_type& exemp)
{
	for (int i = 0; i < this->_size; i++)
		this->values[i] /= static_cast<Type>(exemp);
	return *this;
}


template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, Y, X>
	operator+(const matrix<lhs, Y, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, Y, X> result;
	for (int i = 0; i < Y * X; i++) {
		result.values[i] = lhs_value.values[i] + rhs_value.values[i];
	}
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, Y, X>
	operator-(const matrix<lhs, Y, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, Y, X> result;
	for (int i = 0; i < Y * X; i++)
		result.values[i] = lhs_value.values[i] - rhs_value.values[i];
	return result;
}

template<typename lhs, typename rhs, size_t lhs_Y, size_t lhs_X, size_t rhs_Y, size_t rhs_X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, lhs_Y, lhs_X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, lhs_Y, rhs_X>
	operator*(const matrix<lhs, lhs_Y, lhs_X>& lhs_value, const matrix<rhs, rhs_Y, rhs_X>& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, lhs_Y, rhs_X> result;
	typename common_type<lhs, rhs>::type summ;
	for (int i = 0; i < lhs_Y; i++)
		for (int j = 0; j < rhs_X; j++) {
			summ = 0;
			for (int k = 0; k < lhs_X; k++)
				summ += lhs_value.values[i * lhs_X + k] * rhs_value.values[rhs_X * k + j];
			result[i][j] = summ;
		}
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	mvector<typename common_type<lhs, rhs>::type, Y>
	operator*(const matrix<lhs, Y, X>& lhs_value, const mvector<rhs, X>& rhs_value)
{
	mvector<typename common_type<rhs, lhs>::type, X> result;
	typename common_type<lhs, rhs>::type summ;
	for (int i = 0; i < Y; i++) {
		summ = 0;
		for (int j = 0; j < X; j++)
			summ += lhs_value[i][j] * rhs_value[j];
		result[i] = summ;
	}
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	mvector<typename common_type<lhs, rhs>::type, Y>
	operator*(const mvector<lhs, X>& lhs_value, const matrix<rhs, Y, X>& rhs_value)
{
	mvector<typename common_type<rhs, lhs>::type, X> result;
	typename common_type<lhs, rhs>::type summ;
	for (int i = 0; i < Y; i++) {
		summ = 0;
		for (int j = 0; j < X; j++)
			summ += rhs_value[j][i] * lhs_value[j];
		result[i] = summ;
	}
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, Y, X>
	operator*(const matrix<lhs, Y, X>& lhs_value, const rhs& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, Y, X> result;
	result = lhs_value;
	for (int i = 0; i < Y * X; i++)
		result.values[i] *= rhs_value;
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, Y, X>
	operator*(const lhs& lhs_value, const matrix<rhs, Y, X>& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, Y, X> result;
	result = rhs_value;
	for (int i = 0; i < Y * X; i++)
		result.values[i] *= lhs_value;
	return result;
}

template<typename lhs, typename rhs, size_t Y, size_t X,
	typename temp = typename matrix<typename common_type<lhs, rhs>::type, Y, X>::
	template enable_type_combined<lhs, rhs>>
	matrix<typename common_type<lhs, rhs>::type, Y, X>
	operator/(const matrix<lhs, Y, X>& lhs_value, const rhs& rhs_value)
{
	matrix<typename common_type<lhs, rhs>::type, Y, X> result;
	for (int i = 0; i < Y * X; i++)
		result.values[i] /= rhs_value;
	return result;
}

template <typename T, size_t Y, size_t X>
std::istream& operator>>(std::istream& in, matrix<T, Y, X>& exemp)
{
	for (int i = 0; i < Y * X; i++)
		in >> exemp.values[i];
	return in;
}

template<typename T, size_t Y, size_t X>
ostream& operator<<(ostream& out, matrix<T, Y, X>& exemp)
{
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			out << exemp.values[i * X + j] << (exemp.values[i * X + j] > 0 ? "  " : "") << "\t";
		}
		out << std::endl;
	}
	return out;
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename temp>
void matrix<Type, sizeY, sizeX>::sample_of_main_diagonal_elements()
{
	int maxX, maxY;
	for (int i = 0; i < sizeY - 1; i++) {
		maxX = i, maxY = i;
		for (int j = i; j < sizeY; j++)
			for (int k = i; k < sizeY; k++)
				if (values[maxY * sizeX + maxX] < values[j * sizeX + k]) {
					maxY = j; maxX = k;
				}
		swap_elements(i, i, maxY, maxX);
	}
}

template <typename Type, size_t sizeY, size_t sizeX>
template <typename temp>
matrix<Type, sizeY, sizeX> matrix<Type, sizeY, sizeX>::get_sample_of_main_diagonal_elements() {
	matrix<Type, sizeY, sizeX> exemp;
	int maxX, maxY;

	for (int i = 0; i < sizeY - 1; i++) {
		maxX = i, maxY = i;
		for (int j = i; j < sizeY; j++)
			for (int k = i; k < sizeY; k++)
				if (exemp[maxY][maxX] < values[j][k]) {
					maxY = j; maxX = k;
				}
		exemp.swap_elements(i, i, maxY, maxX);
	}
	return exemp;
}

template <typename Type, size_t sizeY, size_t sizeX>
void matrix<Type, sizeY, sizeX>::swap_elements(size_t x1, size_t y1, size_t x2, size_t y2) {
	for (int i = 0; i < sizeY; i++)
		std::swap(values[i * sizeX + y1], values[i * sizeX + y2]);

	for (int i = 0; i < sizeY; i++)
		std::swap(values[x1 * sizeX + i], values[x2 * sizeX + i]);
}

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeY, 1> matrix<Type, sizeY, sizeX>::get_column(size_t index) {
	matrix<Type, sizeY, 1> res;
	for (int i = 0; i < sizeY; i++)
        res[i][0] = values[sizeX * i + index];
	return res;
}

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, 1, sizeX> matrix<Type, sizeY, sizeX>::get_line(size_t index) {
    matrix<Type, 1, sizeX> res;
    for(int i = 0; i < sizeX; i++)
        res[0][i] = values[sizeX * index + i];
	return res;
}

template <typename Type, size_t sizeY, size_t sizeX>
void matrix<Type, sizeY, sizeX>::set_column(mvector<Type, sizeY> exemp, size_t index) {
	for (int i = 0; i < sizeY; i++)
		values[sizeX * i + index] = exemp[i];
}

template <typename Type, size_t sizeY, size_t sizeX>
void matrix<Type, sizeY, sizeX>::set_line(mvector<Type, sizeX> exemp, size_t index) {
	for (int i = 0; i < sizeX; i++)
		values[sizeX * index + i] = exemp[i];
}

template <typename Type, size_t sizeY, size_t sizeX>
matrix<Type, sizeX, sizeY> matrix<Type, sizeY, sizeX>::get_transposed(){
    matrix<Type, sizeX, sizeY> res;
    for(int i = 0;i < sizeY;i++)
        for(int j = 0;j < sizeX;j++)
            res[j][i] = values[sizeX*i + j];
        return res;
}
