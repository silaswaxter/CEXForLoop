#ifndef CEX_FOR_LOOP_H
#define CEX_FOR_LOOP_H

#include "impl/nary_tree_cex_for_loop.h"
#include "type_encoded_nttps_helper.h"

namespace cex_for_loop {

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor,
          typename InitialTupleWithTypeEncodedNTTPs,
          typename InitialNonCEXDataFunctor>
constexpr typename BodyFunctor::NonConstexprData func() {
  static_assert(!static_cast<bool>(std::is_const<IType>().value),
                "User provided type may NOT be const qualified.");
  static_assert(!static_cast<bool>(std::is_volatile<IType>().value),
                "User provided type may NOT be volatile qualified.");
  static_assert(
      std::is_integral<IType>().value && not std::is_same<IType, bool>(),
      "User provided type must be an integer type (excludes bool).");
  // static_assert(std::is_signed<IType>().value,
  //               "User provided type must be signed integer.");

  return std::get<0>(
      impl::NAryTreeCEXForLoop<BodyFunctor>::template With<
          IType, Start, End, Inc, BoolExpressionFunctor,
          InitialTupleWithTypeEncodedNTTPs, InitialNonCEXDataFunctor>::func());
};

}  // namespace cex_for_loop

#endif  // CEX_FOR_LOOP_H
