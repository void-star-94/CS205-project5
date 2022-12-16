//
// Created by void-star on 2022/12/16.
//

#ifndef PROJECT5_MATBASE_H
#define PROJECT5_MATBASE_H

#include <concepts>
#include <cstdint>
#include <memory>

#ifndef CHECK_INPUT
#define CHECK_INPUT 1
#endif


template<typename T>
concept Element_t = std::is_arithmetic_v<T>;

template<typename T> requires Element_t<T>
class MatBase {
public:
    using Scalar = T;
    using Index = uint64_t;

    virtual const Scalar &operator[](Index i, Index j) const = 0;

    virtual Scalar &operator[](Index i, Index j) = 0;


};

#endif //PROJECT5_MATBASE_H
