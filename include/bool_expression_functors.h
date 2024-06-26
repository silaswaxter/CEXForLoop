#ifndef BOOL_EXPRESSION_FUNCTORS_H
#define BOOL_EXPRESSION_FUNCTORS_H

namespace cex_for_loop {

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_EQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs == rhs;
  }
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_NEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs != rhs;
  }
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_LT {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs < rhs;
  }
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_LEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs <= rhs;
  }
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_GT {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs > rhs;
  }
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_GEQ {
  inline static constexpr bool func(long long lhs, long long rhs) {
    return lhs >= rhs;
  }
};

}  // namespace cex_for_loop

#endif  // BOOL_EXPRESSION_FUNCTORS_H
