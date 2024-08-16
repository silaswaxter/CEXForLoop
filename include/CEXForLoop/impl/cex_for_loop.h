// ABOUT: This file contains the implementation for the constexpr for loop.
//        Inspired by Michael Gonzonda's work
//        (https://www.codeproject.com/Articles/857354/Compile-Time-Loops-with-Cplusplus-Creating-a-Gener)
//        particularly the N-tree expansion for subverting instantiation depth
//        limits
#ifndef IMPL_CEX_FOR_LOOP_H
#define IMPL_CEX_FOR_LOOP_H

#include <tuple>
#include <type_traits>

#include "../bool_expression_functors.h"
#include "linear_cex_for_loop.h"

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

// A exponentially expanding (via recursion) constexpr for loop implementation.
// Expansion along an N-ary Tree
// (https://en.wikipedia.org/wiki/M-ary_tree)
template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor,
          IType PrevTemplateDepth>
struct ExponentialCEXForFunctor {
  using FunctorData = typename BodyFunctor::Data;
  using FunctorOutputType = typename BodyFunctor::OutputType;

  // Magic Numbers
  // -----
  static constexpr IType kNChildren = 8;

  // Calculate some values for each instantiation of this functor
  // -----
  static constexpr IType kThisExpFunctorTemplateDepth =
      PrevTemplateDepth + 2;  // account for this template instantiation (both
                              // the functor struct and the function)
  static constexpr IType kRemainingTemplateDepth =
      static_cast<IType>(kMaxTemplateDepth) - kThisExpFunctorTemplateDepth;
  static constexpr IType kParentEnd = Start + (kRemainingTemplateDepth * Inc);

  template <IType StartLocal = Start, IType EndLocal = End,
            IType IncLocal = Inc>
  static constexpr IType iteration_count() {
    constexpr IType kIterationCount = (EndLocal - StartLocal) / IncLocal;
    static_assert(kIterationCount >= 0,
                  "Cannot iterate a negative number of times.");
    return kIterationCount;
  }

  // I vs N:  In this code you will see I and N referenced. I is the name of the
  //          iteration variable used by CEXForLoop. Since ChildExpMetaFunctor
  //          is instantiated using LinearCEXFor, the Ith child is the
  //          zero-based indexing child. However, the data structure used is
  //          called an N-Tree where N is the number of branches. So, the Nth
  //          child is the one-based indexing child.
  struct ChildExpMetaFunctor {
    // Helper constexpr ceil function. see https://stackoverflow.com/a/66146159
    static constexpr IType ceil(float value_floating) {
      const IType return_value = static_cast<int>(value_floating);
      return value_floating > return_value ? return_value + 1 : return_value;
    }

    static constexpr IType child_end(IType nth_child) {
      // Get the number of iterations that these children are responsible for
      IType children_iteration_count = (End - kParentEnd) / Inc;

      // Get the number of iterations each child is responsible for rounded up
      IType child_iteration_count =
          ceil(static_cast<float>(children_iteration_count) /
               static_cast<float>(kNChildren));

      IType child_end_calculated =
          kParentEnd + (Inc * nth_child * child_iteration_count);

      // since we rounded up, the calculated end might be past the overall End,
      // so we limit the child_end to this value.
      if (BoolExpressionFunctor::template WithType<IType>::func(
              child_end_calculated, End)) {
        return child_end_calculated;
      }
      return End;
    }

    using OutputType = std::tuple<FunctorData>;

    template <IType I>
    static constexpr auto func(FunctorData initial_data) ->
        typename std::enable_if_t<BoolExpressionFunctor::template WithType<
                                      IType>::func((child_end(I) + Inc), End),
                                  OutputType> {
      constexpr IType kRemainingTemplateDepth =
          kThisExpFunctorTemplateDepth +
          I +  // Since LinearCEXFor is used, each child increases
               // current template depth by 1.
          1;   // Account for child meta function instantiation.
      return ExponentialCEXForFunctor<
          IType, child_end(I) + Inc, child_end((I + 1)), Inc,
          BoolExpressionFunctor, BodyFunctor,
          kRemainingTemplateDepth>::func(initial_data);
    };

    template <IType I>
    static constexpr auto func(FunctorData initial_data) ->
        typename std::enable_if_t<!BoolExpressionFunctor::template WithType<
                                      IType>::func((child_end(I) + Inc), End),
                                  OutputType> {
      return {initial_data};
    };
  };

  // linearly expand if able to without reaching the maximum template depth
  template <IType StartLocal = Start, IType EndLocal = End,
            IType IncLocal = Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if_t<
          (iteration_count<StartLocal, EndLocal, IncLocal>() <
           kRemainingTemplateDepth),
          FunctorData> {
    return LinearCEXForFunctor<IType, StartLocal, EndLocal, IncLocal,
                               BoolExpressionFunctor,
                               BodyFunctor>::template func(initial_data);
  }

  // exponentially expand to avoid hitting maximum template depth
  template <IType StartLocal = Start, IType EndLocal = End,
            IType IncLocal = Inc>
  static constexpr auto func(FunctorData initial_data) ->
      typename std::enable_if_t<
          !(iteration_count<StartLocal, EndLocal, IncLocal>() <
            kRemainingTemplateDepth),
          FunctorData> {
    // Its helpful to think of this path as the root node of the tree. A tree
    // is composed of smaller trees.
    //
    // Since each node on the tree is responsible for part of the iteration,
    // do your responsible part
    initial_data = LinearCEXForFunctor<IType, StartLocal, kParentEnd, IncLocal,
                                       BoolExpressionFunctor,
                                       BodyFunctor>::func(initial_data);

    // Create N children w/ each an approximately (integer math rounding
    // required) 1/Nth share of remaining iterations Use our existing linear
    // CEX for loop implementation, but use a meta function that is responsible
    // for instantiating the iterations for each child.
    return LinearCEXForFunctor<IType, 0, kNChildren, 1,
                               BoolExpressionFunctor_LT,
                               ChildExpMetaFunctor>::func(initial_data);
  }
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // IMPL_CEX_FOR_LOOP_H
