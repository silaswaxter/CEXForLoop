#ifndef IMPL_CEX_FOR_LOOP_H
#define IMPL_CEX_FOR_LOOP_H

#include <type_traits>

#include "include/bool_expression_functors.h"

// Define a user override-able constant that limits the maximum template depth
// for this library. This library guarantees that it will not instantiate itself
// past this number. Note that use of the library in a templated context can
// lead to a total template depth greater than this value.
#ifndef CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH
#define CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH 100
constexpr std::size_t max_template_depth = CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH;
#endif  // CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH

namespace CEXForLoop {
namespace impl {

// A linearly expanding (via recursion) constexpr for loop implementation
template <typename BoolExpressionFunctor, typename BodyFunctor>
struct LinearCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;

  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<BoolExpressionFunctor::func(start, end),
                              FunctorData>::type {
    return func<start + inc, end, inc>(
        BodyFunctor::template func<start>(initial_data));
  }

  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<!BoolExpressionFunctor::func(start, end),
                              FunctorData>::type {
    return initial_data;
  }
};

// A exponentially expanding (via recursion) constexpr for loop implementation.
// Expansion along an N-ary Tree
// (https://en.wikipedia.org/wiki/M-ary_tree)
template <typename BoolExpressionFunctor, typename BodyFunctor, long long start,
          long long end, long long inc, std::size_t prev_template_depth>
struct ExponentialCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;
  // account for this template instantiation (both the functor struct and the
  // function)
  static constexpr std::size_t parent_current_template_depth =
      prev_template_depth + 2;
  static constexpr std::size_t remaining_template_depth =
      max_template_depth - parent_current_template_depth;

  // for access by the MetaFunctor
  static constexpr long long parent_end =
      start + remaining_template_depth * inc;

  template <long long start_ = start, long long end_ = end,
            long long inc_ = inc>
  static constexpr std::size_t iteration_count() {
    constexpr auto iteration_count = (end_ - start_) / inc_;
    static_assert(iteration_count >= 0,
                  "Cannot iterate a negative number of times.");
    return iteration_count;
  }

  static constexpr long long child_end(long long first_child_start,
                                       std::size_t child_number) {
    auto calculated_child =
        first_child_start +
        ((child_number * (end - first_child_start)) / 8 /* N in n_tree */) *
            inc;
    if (BoolExpressionFunctor::func(calculated_child, end)) {
      return calculated_child;
    } else {
      return end;
    }
  };

  struct ChildExpMetaFunctor {
    using Data = FunctorData;

    static constexpr auto first_child_start = parent_end + inc;

    template <long long i>
    static constexpr auto func(Data initial_data) ->
        typename std::enable_if<child_end(first_child_start, i) != end,
                                Data>::type {
      // account for this template instantiation (the LinearCEXFor and the
      // function)
      constexpr auto child_current_template_depth =
          parent_current_template_depth +
          (i + 1) +  // for each instantiation of the meta function
          1;         // for the base case in LinearCEXFor recursion
      initial_data = ExponentialCEXForFunctor<
          BoolExpressionFunctor, BodyFunctor, child_end(first_child_start, i),
          child_end(first_child_start, (i + 1)), inc,
          child_current_template_depth>::func(initial_data);
      return initial_data;
    };

    template <long long i>
    static constexpr auto func(Data initial_data) ->
        typename std::enable_if<child_end(first_child_start, i) == end,
                                Data>::type {
      return initial_data;
    };
  };

  // linearly expand if able to without reaching the maximum template depth
  template <long long start_ = start, long long end_ = end,
            long long inc_ = inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<(iteration_count<start_, end_, inc_>() <
                               remaining_template_depth),
                              FunctorData>::type {
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            start_, end_, inc_>(initial_data);
    return initial_data;
  }

  // exponentially expand to avoid hitting maximum template depth
  template <long long start_ = start, long long end_ = end,
            long long inc_ = inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<!(iteration_count<start_, end_, inc_>() <
                                remaining_template_depth),
                              FunctorData>::type {
    // Its helpful to think of this path as the root node of the tree. A tree
    // is composed of smaller trees.
    //
    // Since each node on the tree is responsible for part of the iteration,
    // do your responsible part
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            start_, parent_end, inc_>(initial_data);

    // Create 8 children w/ each a (1/8)th share of remaining iterations
    // Use our existing linear CEX for loop implementation, but for use a meta
    // function that is responsible for instantiating the iterations for each
    // child.
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor_LT, ChildExpMetaFunctor>::
            template func<0, 8, 1>(initial_data);

    return initial_data;
  }
};

}  // namespace impl
}  // namespace CEXForLoop

#endif  // IMPL_CEX_FOR_LOOP_H
