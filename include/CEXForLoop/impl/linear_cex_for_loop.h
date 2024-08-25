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

template <typename IType>
constexpr IType IntegralPow(IType Base, IType Exponent) {
  return Exponent == 0 ? 1 : Base * IntegralPow(Base, Exponent - 1);
}

template <typename IType, IType LocalStart, IType Inc,
          IType LinearExpansionIndex, IType I>
constexpr IType GetExpansionStart() {
  constexpr IType kIStepSize =
      IntegralPow(static_cast<IType>(5), LinearExpansionIndex);

  return LocalStart + (I * kIStepSize * Inc);
}

template <typename IType, IType LocalStart, IType LocalEnd, IType Inc,
          IType LinearExpansionIndex, IType I>
constexpr IType GetExpansionEnd() {
  constexpr IType kCalculatedEnd =
      GetExpansionStart<IType, LocalStart, Inc, LinearExpansionIndex, I>() +
      (5 * Inc);
  return (LocalEnd > kCalculatedEnd) ? kCalculatedEnd : LocalEnd;
}

template <std::size_t N, typename TupleType>
using NthTypeOfTuple = typename std::tuple_element<N, TupleType>::type;

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor,
          typename TupleWithTypeEncodedNTTPs, typename InitialDataFunctor>
struct LinearCEXForFunctor {
  using FunctorData = typename BodyFunctor::NonConstexprData;
  using FunctorOutputType = typename BodyFunctor::OutputType;

  // clang-format off
  template <NthTypeOfTuple<1, FunctorOutputType> NTTP0Value>
  using NextTupleWithTypeEncodedNTTPs = std::tuple<
      std::integral_constant<NthTypeOfTuple<1, FunctorOutputType>, NTTP0Value>
      >;
  // clang-format on

  template <IType LocalStart, IType LocalEnd,
            typename LocalTupleWithTypeEncodedNTTPs,
            typename LocalInitialDataFunctor>
  struct LinearExpansion0 {
    static constexpr IType kLocalIterationCount =
        GetIterationCount<IType, LocalStart, LocalEnd, Inc,
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
    struct INone<UnusedType,
                 std::enable_if_t<kLocalIterationCount == 0, void>> {
      static constexpr FunctorOutputType kPriorOutput = {
          LocalInitialDataFunctor::value,
          NthTypeOfTuple<0, LocalTupleWithTypeEncodedNTTPs>::value};

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue = kPriorOutput;
    };
    template <typename UnusedType>
    struct I0<UnusedType, std::enable_if_t<kLocalIterationCount >= 1, void>> {
      static constexpr FunctorOutputType kPriorOutput = {
          LocalInitialDataFunctor::value,
          NthTypeOfTuple<0, LocalTupleWithTypeEncodedNTTPs>::value};

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue =
          BodyFunctor::template func<(LocalStart + 0),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };

    template <typename UnusedType>
    struct I1<UnusedType, std::enable_if_t<kLocalIterationCount >= 2, void>> {
      static constexpr FunctorOutputType kPriorOutput = I0<>::kValue;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue =
          BodyFunctor::template func<(LocalStart + 1),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I2<UnusedType, std::enable_if_t<kLocalIterationCount >= 3, void>> {
      static constexpr FunctorOutputType kPriorOutput = I1<>::kValue;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue =
          BodyFunctor::template func<(LocalStart + 2),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I3<UnusedType, std::enable_if_t<kLocalIterationCount >= 4, void>> {
      static constexpr FunctorOutputType kPriorOutput = I2<>::kValue;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue =
          BodyFunctor::template func<(LocalStart + 3),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };
    template <typename UnusedType>
    struct I4<UnusedType, std::enable_if_t<kLocalIterationCount >= 5, void>> {
      static constexpr FunctorOutputType kPriorOutput = I3<>::kValue;

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue =
          BodyFunctor::template func<(LocalStart + 4),
                                     std::get<1>(kPriorOutput)>(
              std::get<0>(kPriorOutput));
    };

    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 0, FunctorOutputType> {
      return INone<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 1, FunctorOutputType> {
      return I0<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 2, FunctorOutputType> {
      return I1<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 3, FunctorOutputType> {
      return I2<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 4, FunctorOutputType> {
      return I3<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<LocalLocalIterationCount == 5, FunctorOutputType> {
      return I4<>::kValue;
    }
  };

  template <IType LocalStart, IType LocalEnd,
            typename LocalTupleWithTypeEncodedNTTPs,
            typename LocalInitialDataFunctor>
  struct LinearExpansion1 {
    static constexpr IType kLocalIterationCount =
        GetIterationCount<IType, LocalStart, LocalEnd, Inc,
                          BoolExpressionFunctor>();

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
    struct I0<UnusedType, std::enable_if_t<(kLocalIterationCount >= 0), void>> {
      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue = LinearExpansion0<
          GetExpansionStart<IType, LocalStart, Inc, 1, 0>(),
          GetExpansionEnd<IType, LocalStart, LocalEnd, Inc, 1, 0>(),
          LocalTupleWithTypeEncodedNTTPs, LocalInitialDataFunctor>::func();
    };

    template <typename UnusedType>
    struct I1<UnusedType, std::enable_if_t<(kLocalIterationCount > 5), void>> {
      static constexpr FunctorOutputType kPriorOutput = I0<>::kValue;

      struct NextInitialDataFunctor {
        // NOLINTNEXTLINE(readability-identifier-naming)
        static constexpr FunctorData value = std::get<0>(kPriorOutput);
      };

      // NOLINTNEXTLINE(readability-identifier-naming)
      static constexpr auto kValue = LinearExpansion0<
          GetExpansionStart<IType, LocalStart, Inc, 1, 1>(),
          GetExpansionEnd<IType, LocalStart, LocalEnd, Inc, 1, 1>(),
          NextTupleWithTypeEncodedNTTPs<std::get<1>(kPriorOutput)>,
          NextInitialDataFunctor>::func();
    };

    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<(LocalLocalIterationCount >= 0) &&
                                (LocalLocalIterationCount < 6),
                            FunctorOutputType> {
      return I0<>::kValue;
    }
    template <IType LocalLocalIterationCount = kLocalIterationCount>
    static constexpr auto func()
        -> std::enable_if_t<(LocalLocalIterationCount >= 6) &&
                                (LocalLocalIterationCount < 11),
                            FunctorOutputType> {
      return I1<>::kValue;
    }
  };
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // LINEAR_CEX_FOR_LOOP_H
