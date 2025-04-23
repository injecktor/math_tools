#include <vector>
#include <cstdio>
#include <cassert>
#include <string>

#define VEC2TOVEC1(row, column, columns_count) (row * columns_count + column)

#define MATRIX_FOR(rows_count, columns_count) \
    for (size_t row = 0; row < rows_count; row++) \
        for (size_t column = 0; column < columns_count; column++)

namespace math_tools {

template <class T>
class matrix_t {
public:
    matrix_t() = default;
    // Square matrix
    matrix_t(size_t a_side);
    matrix_t(size_t a_rows_count, size_t a_columns_count);
    matrix_t(size_t a_rows_count, size_t a_columns_count, std::vector<T> a_values);

    bool fill(std::vector<T> a_values);
    bool change_row(size_t a_row, std::vector<T> a_values);
    bool change_column(size_t a_column, std::vector<T> a_values);

    bool append_row();
    bool append_row(std::vector<T> a_values);

    bool append_column();
    bool append_column(std::vector<T> a_values);

    T det();
    size_t rank();
    matrix_t<T> transpose();
    matrix_t<T> minor();
    matrix_t<T> cofactors();
    matrix_t<T> adjugate();
    matrix_t<T> reciprocal();
    bool is_invertible() {
        return det() != static_cast<T>(0);
    }

    std::string get_matrix_to_print();

    size_t get_rows_count() {
        return rows_count;
    }

    size_t get_columns_count() {
        return columns_count;
    }

    template<typename I_T>
    std::vector<T>& operator[](I_T a_row) {
        return values[a_row];
    }

    matrix_t operator+(matrix_t a_other);
    matrix_t operator-(matrix_t a_other);
    matrix_t operator*(matrix_t a_other);
    matrix_t operator*(T a_number);
    matrix_t operator/(T a_number);
    matrix_t operator+=(matrix_t a_other);
    matrix_t operator-=(matrix_t a_other);
    matrix_t operator*=(matrix_t a_other);
    matrix_t operator*=(T a_number);
    matrix_t operator/=(T a_number);

private:
    size_t rows_count, columns_count;
    std::vector<std::vector<T>> values;
};

template <class T>
matrix_t<T>::matrix_t(size_t a_rows_count, size_t a_columns_count) 
    : rows_count(a_rows_count), columns_count(a_columns_count) {
    values.resize(rows_count);
    for (size_t i = 0; i < rows_count; i++) {
        values[i].resize(columns_count);
    }
}

template <class T>
matrix_t<T>::matrix_t(size_t a_rows_count, size_t a_columns_count, std::vector<T> a_values)
    : matrix_t(a_rows_count, a_columns_count) {
    assert(fill(a_values) && "Fill failed");
}

template <class T>
bool matrix_t<T>::fill(std::vector<T> a_values) {
    if (a_values.size() != rows_count * columns_count) {
        return false;
    }
    MATRIX_FOR(rows_count, columns_count) {
        values[row][column] = a_values[VEC2TOVEC1(row, column, columns_count)];
    }
    return true;
}

template <class T>
bool matrix_t<T>::change_row(size_t a_row, std::vector<T> a_values) {
    if (a_row >= rows_count || a_values.size() != columns_count) {
        return false;
    }
    for (size_t i = 0; i < columns_count; i++) {
        values[a_row][i] = a_values[i];
    }
    return true;
}

template <class T>
bool matrix_t<T>::change_column(size_t a_column, std::vector<T> a_values) {
    if (a_column >= columns_count || a_values.size() != rows_count) {
        return false;
    }
    for (size_t i = 0; i < columns_count; i++) {
        values[i][a_column] = a_values[i];
    }
    return true;
}

template <class T>
bool matrix_t<T>::append_row() {
    std::vector<T> tmp_row;
    tmp_row.resize(columns_count);
    return append_row(tmp_row);
}

template <class T>
bool matrix_t<T>::append_row(std::vector<T> a_values) {
    if (a_values.size() != columns_count) {
        return false;
    }
    values.emplace_back(a_values);
    rows_count++;
    return true;
}

template <class T>
bool matrix_t<T>::append_column() {
    std::vector<T> tmp_column;
    tmp_column.resize(rows_count);
    return append_row(tmp_column);
}

template <class T>
bool matrix_t<T>::append_column(std::vector<T> a_values) {
    if (a_values.size() != rows_count) {
        return false;
    }
    for (size_t i = 0; i < values.size(); i++) {
        values[i].emplace_back(a_values[i]);
    }
    columns_count++;
    return true;
}

template <class T>
T matrix_t<T>::det() {
    if (rows_count != columns_count) {
        assert(false && "Impossible to evaluate determinant for not square matrix\n");
    }
    if (rows_count == 1) {
        return (*this)[0][0];
    }
    if (rows_count == 2) {
        return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];
    }
    T result = 0;
    for (size_t i = 0; i < columns_count; i++) {
        matrix_t<T> tmp(rows_count - 1, columns_count - 1);
        for (size_t row = 0; row < rows_count - 1; row++) {
            T minus = 0;
            for (size_t column = 0; column < columns_count; column++) {
                if (column == i) {
                    minus = 1;
                    continue;
                }
                tmp[row][column - minus] = values[row + 1][column];
            }
        }
        if (i & 0b1) {
            result -= values[0][i] * tmp.det();
        } else {
            result += values[0][i] * tmp.det();
        }
    }
    return result;
}

template <class T>
size_t matrix_t<T>::rank() {
    if (rows_count != columns_count) {
        assert(false && "Inpossible to evaluate rank of non square matrix");
    }
    return rows_count;
}

template <class T>
matrix_t<T> matrix_t<T>::transpose() {
    matrix_t<T> result(columns_count, rows_count);
    MATRIX_FOR(rows_count, columns_count) {
        result[column][row] = values[row][column];
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::minor() {
    matrix_t<T> result(rows_count, columns_count);
    if (rows_count != columns_count) {
        assert(false && "Impossible to evaluate minor for not square matrix\n");
    }
    for (size_t i = 0; i < rows_count; i++) {
        for (size_t j = 0; j < columns_count; j++) {
            matrix_t<T> tmp(rows_count - 1, columns_count - 1);
            T row_minus = 0, column_minus = 0;
            MATRIX_FOR(rows_count, columns_count) {
                if (row == i) {
                    row_minus = 1;
                    continue;
                }
                if (column == j) {
                    column_minus = 1;
                    continue;
                }
                tmp[row - row_minus][column - column_minus] = values[row][column];
            }
            result[i][j] = tmp.det();
        }
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::cofactors() {
    matrix_t<T> result(rows_count, columns_count);
    result = minor();
    MATRIX_FOR(rows_count, columns_count) {
        if ((row + column) & 0b1) {
            result[row][column] *= -1;
        }
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::adjugate() {
    matrix_t<T> result(*this);
    return result.cofactors().transpose();
}

template <class T>
matrix_t<T> matrix_t<T>::reciprocal() {
    T det_value = det();
    if (det_value == 0) {
        assert(false && "Matrix is not invertable");
    }
    matrix_t<T> result(*this);
    result = adjugate();
    return result / det_value;
}

template <class T>
std::string matrix_t<T>::get_matrix_to_print() {
    std::string result;
    for (size_t row = 0; row < rows_count; row++) {
        result += "( ";
        for (size_t column = 0; column < columns_count; column++) {
            if (column != 0) {
                result += "\t";
            }
            result += std::to_string(values[row][column]);
        }
        result += " )\n";
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator+(matrix_t a_other) {
    if (rows_count != a_other.get_rows_count() 
        || columns_count != a_other.get_columns_count()) {
        assert(false && "Can't add matrixes with different sizes");
    }
    matrix_t result(rows_count, columns_count);
    MATRIX_FOR(rows_count, columns_count) {
        result[row][column] = (*this)[row][column] + a_other[row][column];
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator-(matrix_t a_other) {
    if (rows_count != a_other.get_rows_count() 
        || columns_count != a_other.get_columns_count()) {
        assert(false && "Can't add matrixes with different sizes");
    }
    matrix_t result(rows_count, columns_count);
    MATRIX_FOR(rows_count, columns_count) {
        result[row][column] = (*this)[row][column] - a_other[row][column];
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator*(matrix_t a_other) {
    if (columns_count != a_other.get_rows_count()) {
        assert(false && "Can't multiply matrix with incorrect sizes");
    }
    matrix_t result(rows_count, a_other.get_columns_count());
    for (size_t i = 0; i < rows_count; i++) {
        for (size_t j = 0; j < a_other.get_columns_count(); j++) {
            for (size_t k = 0; k < columns_count; k++) {
                result[i][j] += values[i][k] * a_other[k][j];
            }
        }
    }
    
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator*(T a_number) {
    matrix_t result(rows_count, columns_count);
    MATRIX_FOR(rows_count, columns_count) {
        values[row][column] *= a_number;
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator/(T a_number) {
    matrix_t result(*this);
    MATRIX_FOR(rows_count, columns_count) {
        result[row][column] /= a_number;
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator+=(matrix_t a_other) {
    *this = *this + a_other;
}

template <class T>
matrix_t<T> matrix_t<T>::operator-=(matrix_t a_other) {
    *this = *this - a_other;
}

template <class T>
matrix_t<T> matrix_t<T>::operator*=(matrix_t a_other) {
    *this = *this * a_other;
}

template <class T>
matrix_t<T> matrix_t<T>::operator*=(T a_value) {
    *this = *this * a_value;
}

template <class T>
matrix_t<T> matrix_t<T>::operator/=(T a_value) {
    *this = *this / a_value;
}

}