//
// Created by void-star on 2022/12/16.
//

#ifndef PROJECT5_MATBASE_H
#define PROJECT5_MATBASE_H

#include <memory>
#include "ForwardDeclarations.h"


template<typename T>
struct scalar_trait {
    using type = typename T::Scalar;
};

template<typename T>
struct derived_trait {
    using type = T;
};

template<typename T>
struct derived_trait<Base<T>> {
    using type = typename T::derived;
};

template<typename Derived>
class Base {
public:
    using Scalar = typename scalar_trait<Derived>::type;
    using derived = typename derived_trait<Derived>::type;

    explicit Base(Index rows = 1, Index cols = 1) : m_rows(rows), m_cols(cols) {
#if CHECK_INPUT
        if (!rows || !cols)Log("Matrix size zero");
        if (UINT64_MAX / rows < cols)Log("Matrix size too large");
#endif
    }

    inline Scalar operator[](Index i, Index j) const {
//        std::cout << "base\n";
        return self.at(i, j);
    };

    inline Scalar operator[](Index i) const {
//        std::cout << "base\n";
        return self.at(i);
    };

    [[nodiscard]] Index rows() const { return m_rows; }

    [[nodiscard]] Index cols() const { return m_cols; }


protected:
    Index m_rows;
    Index m_cols;
    derived &self = static_cast<Derived &>(*this);
};


template<typename Derived>
std::ostream &operator<<(std::ostream &os, const Base<Derived> &matrix) {
    for (Index i = 0; i < matrix.rows(); ++i) {
        for (Index j = 0; j < matrix.cols(); ++j) {
            os << matrix[i, j] << "\t";
        }
        os << "\n";
    }
    return os;
}

template<typename T>
struct derived_trait<MatBase<T>> {
    using type = typename T::derived;
};

template<typename Derived>
class MatBase : public Base<Derived> {
public:
    using Scalar = typename scalar_trait<Derived>::type;
    using derived = typename derived_trait<Derived>::type;

    explicit MatBase(Index rows = 1, Index cols = 1) : Base<Derived>(rows, cols) {}

    inline Scalar &operator[](Index i, Index j) {
        return this->self.at(i, j);
    };

    inline Scalar &operator[](Index i) {
        return this->self.at(i);
    };

    inline Scalar operator[](Index i, Index j) const {
        return this->self.at(i, j);
    };

    inline Scalar operator[](Index i) const {
        return this->self.at(i);
    };

};

#endif //PROJECT5_MATBASE_H
