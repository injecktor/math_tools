#include "matrix.hpp"

int main() {
    matrix_t<size_t> matrix(2, 2, vector<size_t>{4, 3, 2, 1});
    matrix_t<size_t> matrix1(2, 2, vector<size_t>{8, 7, 6, 5});
    matrix_t<size_t> matrix2;
    matrix2 = matrix1 - matrix;
    printf("%s\n", matrix2.get_matrix_to_print().c_str());
    return 0;
}