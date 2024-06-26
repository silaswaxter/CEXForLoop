#ifndef CEX_FOR_LOOP_H
#define CEX_FOR_LOOP_H

#include "impl/cex_for_loop.h"

namespace cex_for_loop {

template <long long Start, long long End, long long Inc,
          typename BoolExpressionFunctor, typename BodyFunctor>
constexpr typename BodyFunctor::Data constexpr_for(
    typename BodyFunctor::Data initial_values) {
  return impl::ExponentialCEXForFunctor<BoolExpressionFunctor, BodyFunctor,
                                        Start, End, Inc,
                                        1>::func(initial_values);
};

}  // namespace cex_for_loop

#endif  // CEX_FOR_LOOP_H
