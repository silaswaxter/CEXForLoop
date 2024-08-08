#ifndef CEX_FOR_LOOP_H
#define CEX_FOR_LOOP_H

#include <array>
#include <cstdint>

#include "impl/cex_for_loop.h"
#include "impl/cex_for_loop_functional.h"
#include "impl/template_metaprogramming_helpers.h"

namespace cex_for_loop {

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor>
constexpr typename BodyFunctor::Data constexpr_for(
    typename BodyFunctor::Data initial_values) {
  static_assert(!static_cast<bool>(std::is_const<IType>().value),
                "User provided type may NOT be const qualified.");
  static_assert(!static_cast<bool>(std::is_volatile<IType>().value),
                "User provided type may NOT be volatile qualified.");
  static_assert(
      std::is_integral<IType>().value && not std::is_same<IType, bool>(),
      "User provided type must be an integer type (no bools allowed).");
  static_assert(std::is_signed<IType>().value,
                "User provided type must be signed integer.");
  return impl::ExponentialCEXForFunctor<IType, Start, End, Inc,
                                        BoolExpressionFunctor, BodyFunctor,
                                        1>::func(initial_values);
};

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor>
constexpr typename BodyFunctor::Data constexpr_for_functional(
    const typename BodyFunctor::Data& initial_value) {
  static_assert(!static_cast<bool>(std::is_const<IType>().value),
                "User provided type may NOT be const qualified.");
  static_assert(!static_cast<bool>(std::is_volatile<IType>().value),
                "User provided type may NOT be volatile qualified.");
  static_assert(
      std::is_integral<IType>().value && not std::is_same<IType, bool>(),
      "User provided type must be an integer type (no bools allowed).");
  static_assert(std::is_signed<IType>().value,
                "User provided type must be signed integer.");

  return BodyFunctor::template func<0>(initial_value);
  // return impl::functional::ExponentialCEXForFunctor<
  //     IType, Start, End, Inc, BoolExpressionFunctor, BodyFunctor,
  //     1>::func(initial_value);
};

}  // namespace cex_for_loop

#endif  // CEX_FOR_LOOP_H
