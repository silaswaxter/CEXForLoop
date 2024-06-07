#ifndef BOOL_EXPRESSION_FUNCTORS_H
#define BOOL_EXPRESSION_FUNCTORS_H

namespace CEXForLoop {

struct BoolExpressionFunctor_EQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs == rhs;
  }
};

struct BoolExpressionFunctor_NEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs != rhs;
  }
};

struct BoolExpressionFunctor_LT {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs < rhs;
  }
};

struct BoolExpressionFunctor_LEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs <= rhs;
  }
};

struct BoolExpressionFunctor_GT {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs > rhs;
  }
};

struct BoolExpressionFunctor_GEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs >= rhs;
  }
};

}  // namespace CEXForLoop

#endif  // BOOL_EXPRESSION_FUNCTORS_H
