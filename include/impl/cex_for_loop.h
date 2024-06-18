#ifndef IMPL_CEX_FOR_LOOP_H
#define IMPL_CEX_FOR_LOOP_H

#include <type_traits>

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
template <typename BoolExpressionFunctor, typename BodyFunctor,
          std::size_t prev_template_depth>
struct ExponentialCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;
  // account for this template instantiation
  static constexpr std::size_t current_template_depth = prev_template_depth + 1;
  static constexpr std::size_t remaining_template_depth =
      max_template_depth - current_template_depth;

  template <long long start, long long end, long long inc>
  static constexpr std::size_t iteration_count() {
    constexpr auto iteration_count = (end - start) / inc;
    static_assert(iteration_count >= 0,
                  "Cannot iterate a negative number of times.");
    return iteration_count;
  }

  static constexpr long long child_end(long long end, long long inc,
                                       long long first_child_start,
                                       std::size_t child_number) {
    return first_child_start +
           ((child_number * (end - first_child_start)) / 8 /* N in n_tree */) *
               inc;
  };

  // linearly expand if able to without reaching the maximum template depth
  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<(iteration_count<start, end, inc>() <
                               remaining_template_depth),
                              FunctorData>::type {
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            start, end, inc>(initial_data);
    return initial_data;
  }

  // exponentially expand to avoid hitting maximum template depth
  template <long long start, long long end, long long inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<!(iteration_count<start, end, inc>() <
                                remaining_template_depth),
                              FunctorData>::type {
    // Its helpful to think of this path as the root node of the tree. A tree
    // is composed of smaller trees.
    //
    // Since each node on the tree is responsible for part of the iteration,
    // do your responsible part
    constexpr long long parent_end = remaining_template_depth * inc + start;
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            start, parent_end, inc>(initial_data);

    // Create 8 children w/ each a (1/8)th share of remaining iterations
    using ChildExpFunctor =
        ExponentialCEXForFunctor<BoolExpressionFunctor, BodyFunctor,
                                 current_template_depth>;

    constexpr auto first_child_start = parent_end + inc;
    initial_data = ChildExpFunctor::template func<
        first_child_start, child_end(end, inc, first_child_start, 1), inc>(
        initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 1) + inc,
        child_end(end, inc, first_child_start, 2), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 2) + inc,
        child_end(end, inc, first_child_start, 3), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 3) + inc,
        child_end(end, inc, first_child_start, 4), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 4) + inc,
        child_end(end, inc, first_child_start, 5), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 5) + inc,
        child_end(end, inc, first_child_start, 6), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 6) + inc,
        child_end(end, inc, first_child_start, 7), inc>(initial_data);
    initial_data = ChildExpFunctor::template func<
        child_end(end, inc, first_child_start, 7) + inc, end, inc>(
        initial_data);

    return initial_data;
  }
};

}  // namespace impl
}  // namespace CEXForLoop

#endif  // IMPL_CEX_FOR_LOOP_H
