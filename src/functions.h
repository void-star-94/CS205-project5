//
// Created by void-star on 2022/12/17.
//

#ifndef PROJECT5_FUNCTIONS_H
#define PROJECT5_FUNCTIONS_H

#include "ForwardDeclarations.h"

#define unary_func(name) template<typename Content>\
UnaryOP<Base<Content>, unary_functor_##name> name(const Base<Content> &content) {\
    return UnaryOP<Base<Content>, unary_functor_##name>(content);\
}

unary_func(sin)

unary_func(cos)

unary_func(tan)

unary_func(abs)

unary_func(sqrt)

unary_func(exp)

unary_func(exp2)

unary_func(log)

unary_func(log2)

unary_func(log10)

unary_func(floor)

unary_func(ceil)


template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_add> operator+(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_add>(lhs, rhs);
}

template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_subtract> operator-(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_subtract>(lhs, rhs);
}

template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_multiply> multiply_EWise(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_multiply>(lhs, rhs);
}

template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_divide> divide_EWise(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_divide>(lhs, rhs);
}

template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_max> max(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_max>(lhs, rhs);
}

template<typename LHS, typename RHS>
BinaryOP<Base<LHS>, Base<RHS>, binary_functor_min> min(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
#endif
    return BinaryOP<Base<LHS>, Base<RHS>, binary_functor_min>(lhs, rhs);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_l<Base<Content>, binary_functor_add> operator+(const Number &number, const Base<Content> &content) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_l<Base<Content>, binary_functor_add>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_r<Base<Content>, binary_functor_add> operator+(const Base<Content> &content, const Number &number) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_r<Base<Content>, binary_functor_add>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_l<Base<Content>, binary_functor_subtract> operator-(const Number &number, const Base<Content> &content) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_l<Base<Content>, binary_functor_subtract>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_r<Base<Content>, binary_functor_subtract> operator-(const Base<Content> &content, const Number &number) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_r<Base<Content>, binary_functor_subtract>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_l<Base<Content>, binary_functor_multiply> operator*(const Number &number, const Base<Content> &content) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_l<Base<Content>, binary_functor_multiply>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_r<Base<Content>, binary_functor_multiply> operator*(const Base<Content> &content, const Number &number) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_r<Base<Content>, binary_functor_multiply>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_r<Base<Content>, binary_functor_divide> operator/(const Base<Content> &content, const Number &number) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_r<Base<Content>, binary_functor_divide>(content, scalar);
}

template<typename Content, typename Number>
requires Element_t<Number>
ScalarOP_l<Base<Content>, binary_functor_divide> divide_EWise(const Number &number, const Base<Content> &content) {
    using Scalar = typename scalar_trait<Content>::type;
    auto scalar = (Scalar) number;
    return ScalarOP_l<Base<Content>, binary_functor_divide>(content, scalar);
}

/// todo: faster multiply

template<typename LHS, typename RHS>
Matrix<typename scalar_trait<LHS>::type> operator*(const Base<LHS> &lhs, const Base<RHS> &rhs) {
#if CHECK_INPUT
    if (!std::is_same_v<typename scalar_trait<LHS>::type, typename scalar_trait<RHS>::type>)Log("input type mismatch");
    if (lhs.cols() != rhs.rows())Log("dimension mismatch");
#endif
    Matrix<typename scalar_trait<LHS>::type> re(lhs.rows(), rhs.cols());
    for (int i = 0; i < re.rows(); ++i) {
        for (int j = 0; j < re.cols(); ++j) {
            typename scalar_trait<LHS>::type tmp = 0;
            for (int k = 0; k < lhs.cols(); ++k) {
                tmp += lhs[i, k] * rhs[k, j];
            }
            re[i, j] = tmp;
        }
    }
    return re;
}


#endif //PROJECT5_FUNCTIONS_H
