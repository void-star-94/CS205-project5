//
// Created by void-star on 2022/12/13.
//

#ifndef PROJECT5_MATRIX_H
#define PROJECT5_MATRIX_H

#include "MatBase.h"

#define log(message) throw std::runtime_error(message)

template<typename T> requires Element_t<T>
class Matrix {
    using Scalar = T;
    using Index = uint64_t;
public:
    explicit Matrix(uint64_t row = 1, uint64_t col = 1, Scalar fill = 0);

    Matrix(uint64_t row, uint64_t col, Scalar *data);

    ~Matrix() = default;

    Matrix(const Matrix &);

    Matrix(Matrix &&) noexcept = default;

    Matrix &operator=(const Matrix &other) {
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
        return *this;
    }

    Matrix &operator=(Matrix &&) noexcept = default;

private:
    const Index rows;
    const Index cols;
    std::unique_ptr<Scalar[]> data;
};


#endif //PROJECT5_MATRIX_H
