//
// Created by void-star on 2022/12/17.
//

#ifndef PROJECT5_FUNCTORS_H
#define PROJECT5_FUNCTORS_H

#include "ForwardDeclarations.h"

#define Unary_functor_std(func)                                  \
struct unary_functor_##func{                                     \
    auto operator()(const auto& scalar)const { return std::func(scalar); }    \
};

Unary_functor_std(sin)

Unary_functor_std(cos)

Unary_functor_std(tan)

Unary_functor_std(abs)

Unary_functor_std(sqrt)

Unary_functor_std(exp)

Unary_functor_std(exp2)

Unary_functor_std(log)

Unary_functor_std(log2)

Unary_functor_std(log10)

Unary_functor_std(floor)

Unary_functor_std(ceil)

#define Binary_functor_std(func)                                                            \
struct binary_functor_##func{                                                               \
    auto operator()(const auto& scalar1, const auto& scalar2)const{ return std::func(scalar1, scalar2); }      \
};

Binary_functor_std(max)

Binary_functor_std(min)

#define Binary_functor(func, code) \
struct binary_functor_##func{                                                               \
    auto operator()(const auto& scalar1, const auto& scalar2)const{ code }      \
};


Binary_functor(add, return scalar1 + scalar2;)

Binary_functor(subtract, return scalar1 - scalar2;)

Binary_functor(multiply, return scalar1 * scalar2;)

Binary_functor(divide, return scalar1 / scalar2;)


#endif //PROJECT5_FUNCTORS_H
