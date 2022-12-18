//
// Created by void-star on 2022/12/13.
//

#ifndef PROJECT5_MATRIX_H
#define PROJECT5_MATRIX_H

#include "MatBase.h"

template<typename T>
struct scalar_trait<Matrix<T>> {
    using type = T;
};

template<typename T>
struct derived_trait {
    using type = T;
};

template<typename T> requires Element_t<T>
class Matrix : public MatBase<Matrix<T>> {
    using Scalar = T;
public:
    explicit Matrix(uint64_t row = 1, uint64_t col = 1, Scalar fill = 0) : MatBase<Matrix<T>>(row, col) {
#ifdef SHOW_CONSTRUCT
        std::cout << "construct!\n";
#endif

#if CHECK_INPUT
        if (!this->m_rows || !this->m_cols)Log("Matrix size zero\ndo not change the dimension of the matrix!");
        if (UINT64_MAX / this->m_rows < this->m_cols)
            Log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
        Scalar *tmp = nullptr;
        tmp = new(std::nothrow) Scalar[this->m_rows * this->m_cols];
        if (!tmp)Log("m_data allocate failed");
        m_data = std::unique_ptr<Scalar[]>(tmp);
        for (uint64_t i = 0; i < this->m_rows * this->m_cols; ++i) {
            m_data[i] = fill;
        }
    }

    Matrix(uint64_t row, uint64_t col, Scalar *data) : MatBase<Matrix<T>>(row, col),
                                                       m_data(std::unique_ptr<Scalar[]>(data)) {
#ifdef SHOW_CONSTRUCT
        std::cout << "construct!\n";
#endif
    }

    ~Matrix() = default;

    template<typename V>
    Matrix(const Base<V> &other) {/*NOLINT*/
#ifdef SHOW_CONSTRUCT
        std::cout << "construct!\n";
#endif
        this->m_rows = other.rows();
        this->m_cols = other.cols();
#if CHECK_INPUT
        if (!this->m_rows || !this->m_cols)Log("Matrix size zero\ndo not change the dimension of the matrix!");
        if (UINT64_MAX / this->m_rows < this->m_cols)
            Log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
        Scalar *tmp = nullptr;
        tmp = new(std::nothrow) Scalar[this->m_rows * this->m_cols];
        if (!tmp)Log("m_data allocate failed");
        m_data = std::unique_ptr<Scalar[]>(tmp);
        for (int i = 0; i < this->m_rows * this->m_cols; ++i) {
            m_data[i] = other[i];
        }
    }


    Matrix(Matrix &&other) noexcept = default;

    template<typename V>
    Matrix &operator=(const Base<V> &other) {
        this->m_rows = other.rows();
        this->m_cols = other.cols();
#if CHECK_INPUT
        if (!this->m_rows || !this->m_cols)Log("Matrix size zero\ndo not change the dimension of the matrix!");
        if (UINT64_MAX / this->m_rows < this->m_cols)
            Log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
        Scalar *tmp = nullptr;
        tmp = new(std::nothrow) Scalar[this->m_rows * this->m_cols];
        if (!tmp)Log("m_data allocate failed");
        m_data = std::unique_ptr<Scalar[]>(tmp);
        for (int i = 0; i < this->m_rows * this->m_cols; ++i) {
            m_data[i] = other[i];
        }
        return *this;
    }

    Matrix &operator=(const Matrix &other) {
        this->m_rows = other.rows();
        this->m_cols = other.cols();
#if CHECK_INPUT
        if (!this->m_rows || !this->m_cols)Log("Matrix size zero\ndo not change the dimension of the matrix!");
        if (UINT64_MAX / this->m_rows < this->m_cols)
            Log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
        Scalar *tmp = nullptr;
        tmp = new(std::nothrow) Scalar[this->m_rows * this->m_cols];
        if (!tmp)Log("m_data allocate failed");
        m_data = std::unique_ptr<Scalar[]>(tmp);
        for (Index i = 0; i < this->m_rows * this->m_cols; ++i) {
            m_data[i] = other[i];
        }
        return *this;
    }

    Matrix(const Matrix &other) {
        this->m_rows = other.rows();
        this->m_cols = other.cols();
#if CHECK_INPUT
        if (!this->m_rows || !this->m_cols)Log("Matrix size zero\ndo not change the dimension of the matrix!");
        if (UINT64_MAX / this->m_rows < this->m_cols)
            Log("Matrix size too large\ndo not change the dimension of the matrix!");
#endif
        Scalar *tmp = nullptr;
        tmp = new(std::nothrow) Scalar[this->m_rows * this->m_cols];
        if (!tmp)Log("m_data allocate failed");
        m_data = std::unique_ptr<Scalar[]>(tmp);
        for (Index i = 0; i < this->m_rows * this->m_cols; ++i) {
            m_data[i] = other[i];
        }
    }

    Matrix &operator=(Matrix &&other) noexcept = default;

    Scalar &at(Index i, Index j) {
#if CHECK_INPUT
        if (i >= this->m_rows || j >= this->m_cols)Log("Index out of range");
#endif
        return m_data[j * this->m_rows + i];
    }

    Scalar at(Index i, Index j) const {
#if CHECK_INPUT
        if (i >= this->m_rows || j >= this->m_cols)Log("Index out of range");
#endif
        return m_data[j * this->m_rows + i];
    }

    Scalar &at(Index i) {
#if CHECK_INPUT
        if (i >= this->m_rows * this->m_cols)Log("Index out of range");
#endif
        return m_data[i];
    }

    Scalar at(Index i) const {
#if CHECK_INPUT
        if (i >= this->m_rows * this->m_cols)Log("Index out of range");
#endif
        return m_data[i];
    }

    Scalar *data() const { return m_data.get(); }

    Matrix &reshape(Index rows, Index cols) {
        {
#if CHECK_INPUT
            if (rows * cols != this->m_rows * this->m_cols)Log("dimension invalid");
#endif
            this->m_rows = rows;
            this->m_cols = cols;
            return *this;
        }
    }

    Matrix_View<T> block(Index start_row, Index start_col, Index rows, Index cols) {
#if CHECK_INPUT
        if (UINT64_MAX - rows < start_row || UINT64_MAX - cols < start_col)Log("Index overflow");
        if (start_row + rows > this->m_rows || start_col + cols > this->m_cols)Log("Block position invalid");
#endif
        return Matrix_View<T>(*this, start_row, start_col, rows, cols);
    }

    Matrix_View<T> col(Index i) {
#if CHECK_INPUT
        if (i >= this->m_cols)Log("Column number invalid");
#endif
        return Matrix_View<T>(*this, 0, i, this->m_rows, 1);
    }

    Matrix_View<T> row(Index i) {
#if CHECK_INPUT
        if (i >= this->m_rows)Log("Row number invalid");
#endif
        return Matrix_View<T>(*this, i, 0, 1, this->m_cols);
    }

    bool operator==(const Matrix &other) const {
        if (this->m_rows != other.m_rows || this->m_cols != other.m_cols)return false;
        if (m_data.get() == other.m_data.get())
            return true;
        for (int i = 0; i < this->m_rows * this->m_cols; ++i)
            if (m_data[i] != other[i])return false;
        return true;
    }

private:
    std::unique_ptr<Scalar[]> m_data;
};


template<typename T>
struct scalar_trait<Matrix_View<T>> {
    using type = T;
};




template<typename T> requires Element_t<T>
class Matrix_View : public MatBase<Matrix_View<T>> {
public:
    using Scalar = T;

    Matrix_View(Matrix<T> &mat, Index start_row, Index start_col, Index rows, Index cols) : matrix(mat),
                                                                                            m_start_row(
                                                                                                    start_row),
                                                                                            m_start_col(
                                                                                                    start_col),
                                                                                            MatBase<Matrix_View<T>>(
                                                                                                    rows, cols),
                                                                                            m_rows_(mat.rows()),
                                                                                            m_cols_(mat.cols()) {}

    Matrix_View(Matrix_View &&) noexcept = delete;

    Matrix_View(const Matrix_View &) = delete;

    Matrix_View &operator=(const Matrix_View &other) = delete;

    Matrix_View &operator=(Matrix_View &&other) noexcept {
#if CHECK_INPUT
        auto abs = [](Index a, Index b) {
            return a > b ? a - b : b - a;
        };
        if (this->m_rows_ != matrix.rows() || this->m_cols_ != matrix.cols()) {
            Warning("current block invalid!\nblock assign failed\n");
            goto END;
        }
        if (this->m_rows != other.m_rows || this->m_cols != other.m_cols) {
            Warning("block size mismatch!\nblock assign failed\n");
            goto END;
        }
        if (matrix == other.matrix) {
            if (m_rows_ != other.m_rows_ || m_cols_ != other.m_cols_) {
                Warning("Invalid block!\nblock assign failed\n");
                goto END;
            }
            if ((abs(m_start_row * 2 + this->m_rows, other.m_start_row * 2 - other.m_rows) <
                 this->m_rows + other.m_rows) &&
                abs(m_start_col * 2 + this->m_cols, other.m_start_col * 2 - other.m_cols) <
                this->m_cols + other.m_cols) {
                Warning("block area overlap!\nblock assign failed\n");
                goto END;
            }
        }
#endif
        for (Index i = 0; i < this->m_rows; ++i) {
            for (Index j = 0; j < this->m_cols; ++j) {
                at(i, j) = other[i, j];
            }
        }
        END:
        return *this;
    }

    Matrix_View &operator=(const Matrix<T> &other) {
#if CHECK_INPUT
        if (this->m_rows_ != matrix.rows() || this->m_cols_ != matrix.cols())
            Log("current block invalid!");
        if (this->m_rows != other.rows() || this->m_cols != other.cols())
            Log("dimension mismatch!");
#endif
        if (matrix.data() == other.data())return *this;
        for (Index i = 0; i < this->m_rows * this->m_cols; ++i) {
            at(i) = other[i];
        }
        return *this;
    }

    Scalar &at(Index i, Index j) {
#if CHECK_INPUT
        if (i >= this->m_rows || j >= this->m_cols)Log("Index out of range");
#endif
        return matrix[(m_start_col + j) * matrix.rows() + m_start_row + i];
    }

    Scalar at(Index i, Index j) const {
#if CHECK_INPUT
        if (i >= this->m_rows || j >= this->m_cols)Log("Index out of range");
#endif
        return matrix[(m_start_col + j) * matrix.rows() + m_start_row + i];
    }

    Scalar &at(Index i) {
#if CHECK_INPUT
        if (i >= this->m_rows * this->m_cols)Log("Index out of range");
#endif
        return at(i % this->m_rows, i / this->m_rows);
    }

    Scalar at(Index i) const {
#if CHECK_INPUT
        if (i >= this->m_rows * this->m_cols)Log("Index out of range");
#endif
        return at(i % this->m_rows, i / this->m_rows);
    }

    Matrix_View<T> block(Index start_row, Index start_col, Index rows, Index cols) const {
#if CHECK_INPUT
        if (UINT64_MAX - rows < start_row || UINT64_MAX - cols < start_col)Log("Index overflow");
        if (start_row + rows > this->m_rows || start_col + cols > this->m_cols)Log("Block position invalid");
#endif
        return Matrix_View<T>(matrix, start_row + m_start_row, start_col + m_start_col, rows, cols);
    }

    Matrix_View<T> col(Index i) {
#if CHECK_INPUT
        if (i >= this->m_cols)Log("Column number invalid");
#endif
        return block(0, i, this->m_rows, 1);
    }

    Matrix_View<T> row(Index i) {
#if CHECK_INPUT
        if (i >= this->m_rows)Log("Row number invalid");
#endif
        return block(i, 0, 1, this->m_cols);
    }

private:
    Matrix<T> &matrix;
    const Index m_start_row;
    const Index m_start_col;
    const Index m_rows_;
    const Index m_cols_;
};


#endif //PROJECT5_MATRIX_H
