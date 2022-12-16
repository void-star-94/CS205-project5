//
// Created by void-star on 2022/12/17.
//

#ifndef PROJECT5_FORWARDDECLARATIONS_H
#define PROJECT5_FORWARDDECLARATIONS_H

#include <concepts>
#include <cmath>


#ifndef CHECK_INPUT
#define CHECK_INPUT 1
#endif


#define Log(message) throw std::runtime_error(message)
#define Warning(message) std::cout << (message)

template<typename T>
concept Element_t = std::is_arithmetic_v<T>;

using Index = uint64_t;

template<typename T>
struct scalar_trait;

template<typename T>
struct derived_trait;

template<typename Derived>
class Base;

template<typename Derived>
class MatBase;

template<typename T> requires Element_t<T>
class Matrix;

template<typename T> requires Element_t<T>
class Matrix_View;

template<typename Content, typename Functor>
class UnaryOP;

template<typename LHS, typename RHS, typename Functor>
class BinaryOP;

template<typename Content, typename Functor>
class ScalarOP_l;

template<typename Content, typename Functor>
class ScalarOP_r;

#define unary_functor(name)  struct unary_functor_##name;

#define binary_functor(name) struct binary_functor_##name;

unary_functor(sin)
unary_functor(cos)
unary_functor(tan)
unary_functor(abs)
unary_functor(sqrt)
unary_functor(exp)
unary_functor(exp2)
unary_functor(log)
unary_functor(log2)
unary_functor(log10)
unary_functor(floor)
unary_functor(ceil)

binary_functor(max)
binary_functor(min)
binary_functor(add)
binary_functor(subtract)
binary_functor(multiply)
binary_functor(divide)


#endif //PROJECT5_FORWARDDECLARATIONS_H
