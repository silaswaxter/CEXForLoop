#ifndef CEX_FOR_LOOP_H
#define CEX_FOR_LOOP_H

#include <cstddef>
#include <type_traits>

#include "impl/cex_for_loop.h"

namespace CEXForLoop {

template <long long start, long long end, long long inc, typename Functor>
constexpr typename Functor::Data constexpr_for(
    typename Functor::Data initial_values) {
  return impl::Thing<Functor>::template constexpr_for<start, end, inc>(
      initial_values);
};

}  // namespace CEXForLoop

#endif  // CEX_FOR_LOOP_H
