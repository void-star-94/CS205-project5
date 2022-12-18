//
// Created by void-star on 2022/12/17.
//

#ifndef PROJECT5_EXPR_H
#define PROJECT5_EXPR_H

#include "MatBase.h"





template<typename Content, typename Functor>
class UnaryOP : public Base<UnaryOP<Content, Functor>> {
public:
    using Scalar = typename scalar_trait<Content>::type;

    explicit UnaryOP(const Content &content) : content(content),
                                               Base<UnaryOP<Content, Functor>>(content.rows(), content.cols()) {}

    UnaryOP(const UnaryOP &) = delete;

    UnaryOP(UnaryOP &&)  noexcept = default;

    UnaryOP &operator=(const UnaryOP &) = delete;

    UnaryOP &operator=(UnaryOP &&)  noexcept = default;

    ~UnaryOP() = default;

    inline Scalar at(Index i, Index j) const { return functor(content[i, j]); }

    inline Scalar at(Index i) const { return functor(content[i]); }


private:
    const Content &content;
    Functor functor{};
};




template<typename LHS, typename RHS, typename Functor>
class BinaryOP : public Base<BinaryOP<LHS, RHS, Functor>> {
public:
    using Scalar = typename scalar_trait<LHS>::type;

    explicit BinaryOP(const LHS &lhs, const RHS &rhs) : lhs(lhs), rhs(rhs),
                                                        Base<BinaryOP<LHS, RHS, Functor>>(lhs.rows(),
                                                                                          lhs.cols()) {
#if CHECK_INPUT
        if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols())Log("dimension mismatch");
#endif
    }

    BinaryOP(const BinaryOP &) = delete;

    BinaryOP(BinaryOP &&)  noexcept = default;

    BinaryOP &operator=(const BinaryOP &) = delete;

    BinaryOP &operator=(BinaryOP &&)  noexcept = default;

    ~BinaryOP() = default;

    inline Scalar at(Index i, Index j) const { return functor(lhs[i, j], rhs[i, j]); }

    inline Scalar at(Index i) const { return functor(lhs[i], rhs[i]); }


private:
    const LHS &lhs;
    const RHS &rhs;
    Functor functor{};
};




template<typename Content, typename Functor>
class ScalarOP_l : public Base<ScalarOP_l<Content, Functor>> {
public:
    using Scalar = typename scalar_trait<Content>::type;

    explicit ScalarOP_l(const Content &content, const Scalar &scalar) : content(content), scalar(scalar),
                                                                        Base<ScalarOP_l<Content, Functor>>(
                                                                                content.rows(), content.cols()) {}

    ScalarOP_l(const ScalarOP_l &) = delete;

    ScalarOP_l(ScalarOP_l &&)  noexcept = default;

    ScalarOP_l &operator=(const ScalarOP_l &) = delete;

    ScalarOP_l &operator=(ScalarOP_l &&)  noexcept = default;

    ~ScalarOP_l() = default;

    inline Scalar at(Index i, Index j) const { return functor(scalar, content[i, j]); }

    inline Scalar at(Index i) const { return functor(scalar, content[i]); }


private:
    const Content &content;
    const Scalar scalar;
    Functor functor{};
};



template<typename Content, typename Functor>
class ScalarOP_r : public Base<ScalarOP_r<Content, Functor>> {
public:
    using Scalar = typename scalar_trait<Content>::type;

    explicit ScalarOP_r(const Content &content, const Scalar &scalar) : content(content), scalar(scalar),
                                                                        Base<ScalarOP_r<Content, Functor>>(
                                                                                content.rows(), content.cols()) {}

    ScalarOP_r(const ScalarOP_r &) = delete;

    ScalarOP_r(ScalarOP_r &&)  noexcept = default;

    ScalarOP_r &operator=(const ScalarOP_r &) = delete;

    ScalarOP_r &operator=(ScalarOP_r &&)  noexcept = default;

    ~ScalarOP_r() = default;

    inline Scalar at(Index i, Index j) const { return functor(content[i, j], scalar); }

    inline Scalar at(Index i) const { return functor(content[i], scalar); }

private:
    const Content &content;
    const Scalar scalar;
    Functor functor{};
};


#endif //PROJECT5_EXPR_H
