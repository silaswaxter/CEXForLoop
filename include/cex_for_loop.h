#ifndef CEX_FOR_LOOP_H
#define CEX_FOR_LOOP_H

#include "impl/cex_for_loop.h"

namespace CEXForLoop {

template <long long start, long long end, long long inc,
          typename BoolExpressionFunctor, typename BodyFunctor>
constexpr typename BodyFunctor::Data constexpr_for(
    typename BodyFunctor::Data initial_values) {
  return impl::ExponentialCEXForFunctor<BoolExpressionFunctor, BodyFunctor,
                                        start, end, inc,
                                        1>::func(initial_values);
};

}  // namespace CEXForLoop

#endif  // CEX_FOR_LOOP_H
