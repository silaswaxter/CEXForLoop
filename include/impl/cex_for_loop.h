#ifndef IMPL_CEX_FOR_LOOP_H
#define IMPL_CEX_FOR_LOOP_H

#include <type_traits>

namespace CEXForLoop {
namespace impl {

template <typename BoolExpressionFunctor, typename BodyFunctor>
struct ConstexprFor {
  using FunctorData = typename BodyFunctor::Data;

  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<BoolExpressionFunctor::func(start, end),
                              FunctorData>::type {
    return func<start + inc, end, inc>(
        BodyFunctor::template func<start>(initial_data));
  };

  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<!BoolExpressionFunctor::func(start, end),
                              FunctorData>::type {
    return initial_data;
  };
};

}  // namespace impl
}  // namespace CEXForLoop

#endif  // IMPL_CEX_FOR_LOOP_H
