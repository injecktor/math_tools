#include <vector>
#include <cstdio>
#include <cassert>
#include <string>

#define VEC2TOVEC1(row, column, columns_count) (row * columns_count + column)

#define MATRIX_FOR \
    for (size_t row = 0; row < rows_count; row++) \
        for (size_t column = 0; column < columns_count; column++)

using namespace std;

template <class T>
class matrix_t {
public:
    // Square matrix
    matrix_t() {};
    matrix_t(size_t a_side);
    matrix_t(size_t a_rows_count, size_t a_columns_count);
    matrix_t(size_t a_rows_count, size_t a_columns_count, vector<T> a_values);

    bool fill(vector<T> a_values);
    bool change_row(size_t a_row, vector<T> a_values);
    bool change_column(size_t a_column, vector<T> a_values);

    bool append_row();
    bool append_row(vector<T> a_values);

    bool append_column();
    bool append_column(vector<T> a_values);

    template<typename I_T>
    vector<T>& operator[](I_T a_row) {
        return values[a_row];
    }

    string get_matrix_to_print();

    size_t get_rows_count() {
        return rows_count;
    }

    size_t get_columns_count() {
        return columns_count;
    }

    matrix_t operator+(matrix_t other);
    matrix_t operator-(matrix_t other);

private:
    size_t rows_count, columns_count;
    vector<vector<T>> values;
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
matrix_t<T>::matrix_t(size_t a_rows_count, size_t a_columns_count, vector<T> a_values)
    : matrix_t(a_rows_count, a_columns_count) {
    assert(fill(a_values) && "Fill failed");
}

template <class T>
bool matrix_t<T>::fill(vector<T> a_values) {
    if (a_values.size() != rows_count * columns_count) {
        return false;
    }
    MATRIX_FOR {
        values[row][column] = a_values[VEC2TOVEC1(row, column, columns_count)];
    }
    return true;
}

template <class T>
bool matrix_t<T>::change_row(size_t a_row, vector<T> a_values) {
    if (a_row >= rows_count || a_values.size() != columns_count) {
        return false;
    }
    for (size_t i = 0; i < columns_count; i++) {
        values[a_row][i] = a_values[i];
    }
    return true;
}

template <class T>
bool matrix_t<T>::change_column(size_t a_column, vector<T> a_values) {
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
    vector<T> tmp_row;
    tmp_row.resize(columns_count);
    return append_row(tmp_row);
}

template <class T>
bool matrix_t<T>::append_row(vector<T> a_values) {
    if (a_values.size() != columns_count) {
        return false;
    }
    values.emplace_back(a_values);
    rows_count++;
    return true;
}

template <class T>
bool matrix_t<T>::append_column() {
    vector<T> tmp_column;
    tmp_column.resize(rows_count);
    return append_row(tmp_column);
}

template <class T>
bool matrix_t<T>::append_column(vector<T> a_values) {
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
string matrix_t<T>::get_matrix_to_print() {
    string result;
    for (size_t row = 0; row < rows_count; row++) {
        result += "( ";
        for (size_t column = 0; column < columns_count; column++) {
            if (column != 0) {
                result += "\t";
            }
            result += to_string(values[row][column]);
        }
        result += " )\n";
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator+(matrix_t other) {
    if (rows_count != other.get_rows_count() 
        || columns_count != other.get_columns_count()) {
        assert(false && "Can't add matrixes with different sizes");
    }
    matrix_t result(rows_count, columns_count);
    MATRIX_FOR {
        result[row][column] = (*this)[row][column] + other[row][column];
    }
    return result;
}

template <class T>
matrix_t<T> matrix_t<T>::operator-(matrix_t other) {
    if (rows_count != other.get_rows_count() 
        || columns_count != other.get_columns_count()) {
        assert(false && "Can't add matrixes with different sizes");
    }
    matrix_t result(rows_count, columns_count);
    MATRIX_FOR {
        result[row][column] = (*this)[row][column] - other[row][column];
    }
    return result;
}