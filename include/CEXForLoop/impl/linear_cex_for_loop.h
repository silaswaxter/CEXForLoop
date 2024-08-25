#ifndef LINEAR_CEX_FOR_LOOP_H
#define LINEAR_CEX_FOR_LOOP_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "../bool_expression_functors.h"
namespace cex_for_loop {
namespace impl {

template <typename T>
struct RemoveFirstTypeOfTuple {};

template <typename T, typename... Ts>
struct RemoveFirstTypeOfTuple<std::tuple<T, Ts...>> {
  using type = std::tuple<Ts...>;
};

template <typename IType>
static constexpr IType ceil_division(IType num, IType den) {
  return (num + (num % den)) / den;
}

template <typename IType>
static constexpr IType floor_division(IType num, IType den) {
  return (num - (num % den)) / den;
}

template <typename IType, IType Start, IType End, IType Inc,
          typename LocalBoolExpressionFunctor>
static constexpr auto GetIterationCount()
    -> std::enable_if_t<
        (std::is_same<LocalBoolExpressionFunctor,
                      cex_for_loop::BoolExpressionFunctor_LT>::value) ||
            (std::is_same<LocalBoolExpressionFunctor,
                          cex_for_loop::BoolExpressionFunctor_GT>::value),
        IType> {
  return floor_division((End - Start), Inc);
}

template <typename IType, IType Start, IType End, IType Inc,
          typename LocalBoolExpressionFunctor>
static constexpr auto GetIterationCount()
    -> std::enable_if_t<
        (std::is_same<LocalBoolExpressionFunctor,
                      cex_for_loop::BoolExpressionFunctor_LEQ>::value) ||
            (std::is_same<LocalBoolExpressionFunctor,
                          cex_for_loop::BoolExpressionFunctor_GEQ>::value),
        IType> {
  return ceil_division((End - Start), Inc);
}

template <std::size_t N, typename TupleType>
using NthTypeOfTuple = typename std::tuple_element<N, TupleType>::type;

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor,
          typename TupleWithTypeEncodedNTTPs, typename InitialDataFunctor>
struct LinearCEXForFunctor {
  using FunctorData = typename BodyFunctor::NonConstexprData;
  using FunctorOutputType = typename BodyFunctor::OutputType;

  template <IType LocalStart, IType LocalEnd, IType LocalInc,
            typename LocalTupleWithTypeEncodedNTTPs,
            typename LocalInitialDataFunctor>
  struct LinearExpansion0 {
    static constexpr IType kLocalIterationCount =
        GetIterationCount<IType, LocalStart, LocalEnd, LocalInc,
                          BoolExpressionFunctor>();

    template <typename UnusedType = void, typename Picker = void>
    struct INone;
    template <typename UnusedType = void, typename Picker = void>
    struct I0;
    template <typename UnusedType = void, typename Picker = void>
    struct I1;
    template <typename UnusedType = void, typename Picker = void>
    struct I2;
    template <typename UnusedType = void, typename Picker = void>
    struct I3;
    template <typename UnusedType = void, typename Picker = void>
    struct I4;

    template <typename UnusedType>
    struct INone<UnusedType, std::enable_if_t<kLocalIterationCount == 0, void>> {
      static constexpr FunctorOutputType kPriorOutput = {
          LocalInitialDataFunctor::value,
          NthTypeOfTuple<0, LocalTupleWithTypeEncodedNTTPs>::value};

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value = kPriorOutput;
    };
    template <typename UnusedType>
    struct I0<UnusedType, std::enable_if_t<kLocalIterationCount >= 1, void>> {
      static constexpr FunctorOutputType kPriorOutput = {
          LocalInitialDataFunctor::value,
          NthTypeOfTuple<0, LocalTupleWithTypeEncodedNTTPs>::value};

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value =
          BodyFunctor::template func<(LocalStart + 0),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };

    template <typename UnusedType>
    struct I1<UnusedType, std::enable_if_t<kLocalIterationCount >= 2, void>> {
      static constexpr FunctorOutputType kPriorOutput = I0<>::value;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value =
          BodyFunctor::template func<(LocalStart + 1),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I2<UnusedType, std::enable_if_t<kLocalIterationCount >= 3, void>> {
      static constexpr FunctorOutputType kPriorOutput = I1<>::value;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value =
          BodyFunctor::template func<(LocalStart + 2),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I3<UnusedType, std::enable_if_t<kLocalIterationCount >= 4, void>> {
      static constexpr FunctorOutputType kPriorOutput = I2<>::value;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value =
          BodyFunctor::template func<(LocalStart + 3),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I4<UnusedType, std::enable_if_t<kLocalIterationCount >= 5, void>> {
      static constexpr FunctorOutputType kPriorOutput = I3<>::value;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto value =
          BodyFunctor::template func<(LocalStart + 4),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };

    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 0, FunctorOutputType> {
      return INone<>::value;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 1, FunctorOutputType> {
      return I0<>::value;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 2, FunctorOutputType> {
      return I1<>::value;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 3, FunctorOutputType> {
      return I2<>::value;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 4, FunctorOutputType> {
      return I3<>::value;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 5, FunctorOutputType> {
      return I4<>::value;
    }
  };
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // LINEAR_CEX_FOR_LOOP_H
