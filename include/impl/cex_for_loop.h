#ifndef IMPL_CEX_FOR_LOOP_H
#define IMPL_CEX_FOR_LOOP_H

#include <cstddef>
#include <type_traits>

namespace CEXForLoop {
namespace impl {

template <typename Functor>
struct Thing {
  using FunctorData = typename Functor::Data;

  template <long long start, long long end, long long inc>
  static constexpr auto constexpr_for(FunctorData initial_data) ->
      typename std::enable_if<(start != end), FunctorData>::type {
    return constexpr_for<start + inc, end, inc>(
        Functor::template func<start>(initial_data));
  };

  template <long long start, long long end, long long inc>
  static constexpr auto constexpr_for(FunctorData initial_data) ->
      typename std::enable_if<(start == end), FunctorData>::type {
    return initial_data;
  };
};

}  // namespace impl
}  // namespace CEXForLoop

#endif  // IMPL_CEX_FOR_LOOP_H
