//
// Created by void-star on 2022/12/13.
//

#include "Matrix.h"


template<typename T>
requires Element_t<T> Matrix<T>::Matrix(uint64_t row, uint64_t col, Scalar fill):rows(row), cols(col) {
#if CHECK_INPUT
    if (!rows || !cols)log("Matrix size zero");
    if (UINT64_MAX / rows < cols)log("Matrix size too large");
#endif
    Scalar *tmp = nullptr;
    tmp = new(std::nothrow) Scalar[rows * cols];
    if (!tmp)log("data allocate failed");
    data = std::make_unique(tmp);
    for (uint64_t i = 0; i < rows * cols; ++i) {
        data[i] = fill;
    }
}

template<typename T>
requires Element_t<T>
Matrix<T>::Matrix(uint64_t row, uint64_t col, Scalar *data):rows(row), cols(col), data(std::make_unique(data)) {
#if CHECK_INPUT
    if (!rows || !cols)log("Matrix size zero");
    if (UINT64_MAX / rows < cols)log("Matrix size too large");
#endif
}

template<typename T>
requires Element_t<T> Matrix<T>::Matrix(const Matrix &other) {
    rows = other.rows;
    cols = other.cols;
#if CHECK_INPUT
    if (!rows || !cols)log("Matrix size zero\ndo not change the dimension of the matrix!");
    if (UINT64_MAX / rows < cols)log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
    Scalar *tmp = nullptr;
    tmp = new(std::nothrow) Scalar[rows * cols];
    if (!tmp)log("data allocate failed");
    data = std::make_unique(tmp);
}


