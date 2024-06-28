// ABOUT: This file contains the implementation for the constexpr for loop.
//        Inspired by Michael Gonzonda's work
//        (https://www.codeproject.com/Articles/857354/Compile-Time-Loops-with-Cplusplus-Creating-a-Gener)
//        particularly the N-tree expansion for subverting instantiation depth
//        limits
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
constexpr std::size_t kMaxTemplateDepth = CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH;
#endif  // CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH

namespace cex_for_loop {
namespace impl {

// A linearly expanding (via recursion) constexpr for loop implementation
template <typename BoolExpressionFunctor, typename BodyFunctor>
struct LinearCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;

  template <long long Start, long long End, long long Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<BoolExpressionFunctor::func(Start, End),
                              FunctorData>::type {
    return func<Start + Inc, End, Inc>(
        BodyFunctor::template func<Start>(initial_data));
  }

  template <long long Start, long long End, long long Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<!BoolExpressionFunctor::func(Start, End),
                              FunctorData>::type {
    return initial_data;
  }
};

// A exponentially expanding (via recursion) constexpr for loop implementation.
// Expansion along an N-ary Tree
// (https://en.wikipedia.org/wiki/M-ary_tree)
template <typename BoolExpressionFunctor, typename BodyFunctor, long long Start,
          long long End, long long Inc, std::size_t PrevTemplateDepth>
struct ExponentialCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;
  // account for this template instantiation (both the functor struct and the
  // function)
  static constexpr std::size_t kParentCurrentTemplateDepth =
      PrevTemplateDepth + 2;
  static constexpr std::size_t kRemainingTemplateDepth =
      kMaxTemplateDepth - kParentCurrentTemplateDepth;

  // for access by the MetaFunctor
  static constexpr long long kNChildren = 8;
  static constexpr long long kParentEnd = Start + kRemainingTemplateDepth * Inc;

  template <long long StartLocal = Start, long long EndLocal = End,
            long long IncLocal = Inc>
  static constexpr std::size_t iteration_count() {
    constexpr auto kIterationCount = (EndLocal - StartLocal) / IncLocal;
    static_assert(kIterationCount >= 0,
                  "Cannot iterate a negative number of times.");
    return kIterationCount;
  }

  static constexpr long long child_end(long long first_child_start,
                                       std::size_t child_number) {
    long long calculated_child =
        first_child_start +
        ((child_number * (End - first_child_start)) / kNChildren) * Inc;
    if (BoolExpressionFunctor::func(calculated_child, End)) {
      return calculated_child;
    }
    return End;
  };

  struct ChildExpMetaFunctor {
    using Data = FunctorData;

    static constexpr auto kFirstChildStart = kParentEnd + Inc;

    template <long long I>
    static constexpr auto func(Data initial_data) ->
        typename std::enable_if<child_end(kFirstChildStart, I) != End,
                                Data>::type {
      // account for this template instantiation (the LinearCEXFor and the
      // function)
      constexpr auto kChildCurrentTemplateDepth =
          kParentCurrentTemplateDepth +
          (I + 1) +  // for each instantiation of the meta function
          1;         // for the base case in LinearCEXFor recursion
      initial_data = ExponentialCEXForFunctor<
          BoolExpressionFunctor, BodyFunctor, child_end(kFirstChildStart, I),
          child_end(kFirstChildStart, (I + 1)), Inc,
          kChildCurrentTemplateDepth>::func(initial_data);
      return initial_data;
    };

    template <long long I>
    static constexpr auto func(Data initial_data) ->
        typename std::enable_if<child_end(kFirstChildStart, I) == End,
                                Data>::type {
      return initial_data;
    };
  };

  // linearly expand if able to without reaching the maximum template depth
  template <long long StartLocal = Start, long long EndLocal = End,
            long long IncLocal = Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<
          (iteration_count<StartLocal, EndLocal, IncLocal>() <
           kRemainingTemplateDepth),
          FunctorData>::type {
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            StartLocal, EndLocal, IncLocal>(initial_data);
    return initial_data;
  }

  // exponentially expand to avoid hitting maximum template depth
  template <long long StartLocal = Start, long long EndLocal = End,
            long long IncLocal = Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if<
          !(iteration_count<StartLocal, EndLocal, IncLocal>() <
            kRemainingTemplateDepth),
          FunctorData>::type {
    // Its helpful to think of this path as the root node of the tree. A tree
    // is composed of smaller trees.
    //
    // Since each node on the tree is responsible for part of the iteration,
    // do your responsible part
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor, BodyFunctor>::template func<
            StartLocal, kParentEnd, IncLocal>(initial_data);

    // Create n_children children w/ each a (1/n_children)th share of remaining
    // iterations Use our existing linear CEX for loop implementation, but for
    // use a meta function that is responsible for instantiating the iterations
    // for each child.
    initial_data =
        LinearCEXForFunctor<BoolExpressionFunctor_LT, ChildExpMetaFunctor>::
            template func<0, kNChildren, 1>(initial_data);

    return initial_data;
  }
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // IMPL_CEX_FOR_LOOP_H
