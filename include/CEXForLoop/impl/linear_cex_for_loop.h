#ifndef LINEAR_CEX_FOR_LOOP_H
#define LINEAR_CEX_FOR_LOOP_H

#include <cstddef>
#include <tuple>
#include <type_traits>

#include "../bool_expression_functors.h"
namespace cex_for_loop {
namespace impl {

template <std::size_t N, typename... Ts>
using NthTypeOf = typename std::tuple_element<N, std::tuple<Ts...>>::type;

template <typename IType, IType Start, IType End, IType Inc,
          typename BoolExpressionFunctor, typename BodyFunctor>
struct LinearCEXForFunctor {
  using FunctorData = typename BodyFunctor::NonConstexprData;
  using FunctorOutputType = typename BodyFunctor::OutputType;

  static constexpr IType ceil_division(IType num, IType den) {
    return (num + (num % den)) / den;
  }

  static constexpr IType floor_division(IType num, IType den) {
    return (num - (num % den)) / den;
  }

  template <typename LocalBoolExpressionFunctor = BoolExpressionFunctor>
  static constexpr auto GetIterationCount()
      -> std::enable_if_t<
          (std::is_same<LocalBoolExpressionFunctor,
                        cex_for_loop::BoolExpressionFunctor_LT>::value) ||
              (std::is_same<LocalBoolExpressionFunctor,
                            cex_for_loop::BoolExpressionFunctor_GT>::value),
          std::size_t> {
    return floor_division((End - Start), Inc);
  }

  template <typename LocalBoolExpressionFunctor = BoolExpressionFunctor>
  static constexpr auto GetIterationCount()
      -> std::enable_if_t<
          (std::is_same<LocalBoolExpressionFunctor,
                        cex_for_loop::BoolExpressionFunctor_LEQ>::value) ||
              (std::is_same<LocalBoolExpressionFunctor,
                            cex_for_loop::BoolExpressionFunctor_GEQ>::value),
          std::size_t> {
    return ceil_division((End - Start), Inc);
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 0),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    return kOutput0;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 1),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    return kOutput1;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 2),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    return kOutput2;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 3),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    return kOutput3;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 4),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    return kOutput4;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 5),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    constexpr IType kI5 = kI4 + Inc;
    constexpr auto kOutput5 =
        BodyFunctor::template func<kI5, std::get<1>(kOutput4)>(
            std::get<0>(kOutput4));
    return kOutput5;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 6),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    constexpr IType kI5 = kI4 + Inc;
    constexpr auto kOutput5 =
        BodyFunctor::template func<kI5, std::get<1>(kOutput4)>(
            std::get<0>(kOutput4));
    constexpr IType kI6 = kI5 + Inc;
    constexpr auto kOutput6 =
        BodyFunctor::template func<kI6, std::get<1>(kOutput5)>(
            std::get<0>(kOutput5));
    return kOutput6;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 7),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    constexpr IType kI5 = kI4 + Inc;
    constexpr auto kOutput5 =
        BodyFunctor::template func<kI5, std::get<1>(kOutput4)>(
            std::get<0>(kOutput4));
    constexpr IType kI6 = kI5 + Inc;
    constexpr auto kOutput6 =
        BodyFunctor::template func<kI6, std::get<1>(kOutput5)>(
            std::get<0>(kOutput5));
    constexpr IType kI7 = kI6 + Inc;
    constexpr auto kOutput7 =
        BodyFunctor::template func<kI7, std::get<1>(kOutput6)>(
            std::get<0>(kOutput6));
    return kOutput7;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 8),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    constexpr IType kI5 = kI4 + Inc;
    constexpr auto kOutput5 =
        BodyFunctor::template func<kI5, std::get<1>(kOutput4)>(
            std::get<0>(kOutput4));
    constexpr IType kI6 = kI5 + Inc;
    constexpr auto kOutput6 =
        BodyFunctor::template func<kI6, std::get<1>(kOutput5)>(
            std::get<0>(kOutput5));
    constexpr IType kI7 = kI6 + Inc;
    constexpr auto kOutput7 =
        BodyFunctor::template func<kI7, std::get<1>(kOutput6)>(
            std::get<0>(kOutput6));
    constexpr IType kI8 = kI7 + Inc;
    constexpr auto kOutput8 =
        BodyFunctor::template func<kI8, std::get<1>(kOutput7)>(
            std::get<0>(kOutput7));
    return kOutput8;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 9),
          FunctorOutputType> {
    constexpr IType kI0 = Start;
    constexpr auto kOutput0 = BodyFunctor::template func<
        kI0, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(
        InitialDataFunctor::value);
    constexpr IType kI1 = kI0 + Inc;
    constexpr auto kOutput1 =
        BodyFunctor::template func<kI1, std::get<1>(kOutput0)>(
            std::get<0>(kOutput0));
    constexpr IType kI2 = kI1 + Inc;
    constexpr auto kOutput2 =
        BodyFunctor::template func<kI2, std::get<1>(kOutput1)>(
            std::get<0>(kOutput1));
    constexpr IType kI3 = kI2 + Inc;
    constexpr auto kOutput3 =
        BodyFunctor::template func<kI3, std::get<1>(kOutput2)>(
            std::get<0>(kOutput2));
    constexpr IType kI4 = kI3 + Inc;
    constexpr auto kOutput4 =
        BodyFunctor::template func<kI4, std::get<1>(kOutput3)>(
            std::get<0>(kOutput3));
    constexpr IType kI5 = kI4 + Inc;
    constexpr auto kOutput5 =
        BodyFunctor::template func<kI5, std::get<1>(kOutput4)>(
            std::get<0>(kOutput4));
    constexpr IType kI6 = kI5 + Inc;
    constexpr auto kOutput6 =
        BodyFunctor::template func<kI6, std::get<1>(kOutput5)>(
            std::get<0>(kOutput5));
    constexpr IType kI7 = kI6 + Inc;
    constexpr auto kOutput7 =
        BodyFunctor::template func<kI7, std::get<1>(kOutput6)>(
            std::get<0>(kOutput6));
    constexpr IType kI8 = kI7 + Inc;
    constexpr auto kOutput8 =
        BodyFunctor::template func<kI8, std::get<1>(kOutput7)>(
            std::get<0>(kOutput7));
    constexpr IType kI9 = kI8 + Inc;
    constexpr auto kOutput9 =
        BodyFunctor::template func<kI9, std::get<1>(kOutput8)>(
            std::get<0>(kOutput8));
    return kOutput9;
  }
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // LINEAR_CEX_FOR_LOOP_H
