#ifndef BOOL_EXPRESSION_FUNCTORS_H
#define BOOL_EXPRESSION_FUNCTORS_H

namespace cex_for_loop {

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_EQ_uncontrolled_template_depth {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs == rhs;
    }
  };
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_NEQ_uncontrolled_template_depth {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs != rhs;
    }
  };
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_LT {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs < rhs;
    }
  };
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_LEQ {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs <= rhs;
    }
  };
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_GT {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs > rhs;
    }
  };
};

// NOLINTNEXTLINE(readability-identifier-naming)
struct BoolExpressionFunctor_GEQ {
  // The templated struct within allows user to pass this type without having
  // to pass the template parameter at the call-site meaning the CEXForLoop can
  // be "DRY" (Don't Repeat Yourself)
  template <typename IType>
  struct WithType {
    inline static constexpr bool func(IType lhs, IType rhs) {
      return lhs >= rhs;
    }
  };
};

}  // namespace cex_for_loop

#endif  // BOOL_EXPRESSION_FUNCTORS_H
