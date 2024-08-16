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

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 10),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    return kOutput10;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 11),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    return kOutput11;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 12),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    return kOutput12;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 13),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    return kOutput13;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 14),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    return kOutput14;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 15),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    return kOutput15;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 16),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    return kOutput16;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 17),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    return kOutput17;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 18),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    return kOutput18;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 19),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    return kOutput19;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 20),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    return kOutput20;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 21),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    return kOutput21;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 22),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    return kOutput22;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 23),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    return kOutput23;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 24),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    return kOutput24;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 25),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    return kOutput25;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 26),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    return kOutput26;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 27),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    return kOutput27;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 28),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    return kOutput28;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 29),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    return kOutput29;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 30),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    return kOutput30;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 31),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    return kOutput31;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 32),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    return kOutput32;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 33),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    return kOutput33;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 34),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    return kOutput34;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 35),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    return kOutput35;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 36),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    return kOutput36;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 37),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    return kOutput37;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 38),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    return kOutput38;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 39),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    return kOutput39;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 40),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    return kOutput40;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 41),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    return kOutput41;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 42),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    return kOutput42;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 43),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    return kOutput43;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 44),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    return kOutput44;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 45),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    return kOutput45;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 46),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    return kOutput46;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 47),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    return kOutput47;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 48),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    return kOutput48;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 49),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    return kOutput49;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 50),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    return kOutput50;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 51),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    return kOutput51;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 52),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    return kOutput52;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 53),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    return kOutput53;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 54),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    return kOutput54;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 55),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    return kOutput55;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 56),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    return kOutput56;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 57),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    return kOutput57;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 58),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    return kOutput58;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 59),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    return kOutput59;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 60),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    return kOutput60;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 61),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    return kOutput61;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 62),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    return kOutput62;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 63),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    return kOutput63;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 64),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    return kOutput64;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 65),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    return kOutput65;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 66),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    return kOutput66;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 67),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    return kOutput67;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 68),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    return kOutput68;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 69),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    return kOutput69;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 70),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    return kOutput70;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 71),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    return kOutput71;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 72),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    return kOutput72;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 73),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    return kOutput73;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 74),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    return kOutput74;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 75),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    return kOutput75;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 76),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    return kOutput76;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 77),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    return kOutput77;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 78),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    return kOutput78;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 79),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    return kOutput79;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 80),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    return kOutput80;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 81),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    return kOutput81;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 82),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    return kOutput82;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 83),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    return kOutput83;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 84),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    return kOutput84;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 85),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    return kOutput85;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 86),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    return kOutput86;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 87),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    return kOutput87;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 88),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    return kOutput88;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 89),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    return kOutput89;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 90),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    return kOutput90;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 91),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    return kOutput91;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 92),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    return kOutput92;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 93),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    return kOutput93;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 94),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    return kOutput94;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 95),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    constexpr IType kI95 = kI94 + Inc;
    constexpr auto kOutput95 =
        BodyFunctor::template func<kI95, std::get<1>(kOutput94)>(
            std::get<0>(kOutput94));
    return kOutput95;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 96),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    constexpr IType kI95 = kI94 + Inc;
    constexpr auto kOutput95 =
        BodyFunctor::template func<kI95, std::get<1>(kOutput94)>(
            std::get<0>(kOutput94));
    constexpr IType kI96 = kI95 + Inc;
    constexpr auto kOutput96 =
        BodyFunctor::template func<kI96, std::get<1>(kOutput95)>(
            std::get<0>(kOutput95));
    return kOutput96;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 97),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    constexpr IType kI95 = kI94 + Inc;
    constexpr auto kOutput95 =
        BodyFunctor::template func<kI95, std::get<1>(kOutput94)>(
            std::get<0>(kOutput94));
    constexpr IType kI96 = kI95 + Inc;
    constexpr auto kOutput96 =
        BodyFunctor::template func<kI96, std::get<1>(kOutput95)>(
            std::get<0>(kOutput95));
    constexpr IType kI97 = kI96 + Inc;
    constexpr auto kOutput97 =
        BodyFunctor::template func<kI97, std::get<1>(kOutput96)>(
            std::get<0>(kOutput96));
    return kOutput97;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 98),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    constexpr IType kI95 = kI94 + Inc;
    constexpr auto kOutput95 =
        BodyFunctor::template func<kI95, std::get<1>(kOutput94)>(
            std::get<0>(kOutput94));
    constexpr IType kI96 = kI95 + Inc;
    constexpr auto kOutput96 =
        BodyFunctor::template func<kI96, std::get<1>(kOutput95)>(
            std::get<0>(kOutput95));
    constexpr IType kI97 = kI96 + Inc;
    constexpr auto kOutput97 =
        BodyFunctor::template func<kI97, std::get<1>(kOutput96)>(
            std::get<0>(kOutput96));
    constexpr IType kI98 = kI97 + Inc;
    constexpr auto kOutput98 =
        BodyFunctor::template func<kI98, std::get<1>(kOutput97)>(
            std::get<0>(kOutput97));
    return kOutput98;
  }

  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>
  // NOLINTNEXTLINE(readability-function-cognitive-complexity)
  static constexpr auto func()
      -> std::enable_if_t<
          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&
              (GetIterationCount() == 99),
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
    constexpr IType kI10 = kI9 + Inc;
    constexpr auto kOutput10 =
        BodyFunctor::template func<kI10, std::get<1>(kOutput9)>(
            std::get<0>(kOutput9));
    constexpr IType kI11 = kI10 + Inc;
    constexpr auto kOutput11 =
        BodyFunctor::template func<kI11, std::get<1>(kOutput10)>(
            std::get<0>(kOutput10));
    constexpr IType kI12 = kI11 + Inc;
    constexpr auto kOutput12 =
        BodyFunctor::template func<kI12, std::get<1>(kOutput11)>(
            std::get<0>(kOutput11));
    constexpr IType kI13 = kI12 + Inc;
    constexpr auto kOutput13 =
        BodyFunctor::template func<kI13, std::get<1>(kOutput12)>(
            std::get<0>(kOutput12));
    constexpr IType kI14 = kI13 + Inc;
    constexpr auto kOutput14 =
        BodyFunctor::template func<kI14, std::get<1>(kOutput13)>(
            std::get<0>(kOutput13));
    constexpr IType kI15 = kI14 + Inc;
    constexpr auto kOutput15 =
        BodyFunctor::template func<kI15, std::get<1>(kOutput14)>(
            std::get<0>(kOutput14));
    constexpr IType kI16 = kI15 + Inc;
    constexpr auto kOutput16 =
        BodyFunctor::template func<kI16, std::get<1>(kOutput15)>(
            std::get<0>(kOutput15));
    constexpr IType kI17 = kI16 + Inc;
    constexpr auto kOutput17 =
        BodyFunctor::template func<kI17, std::get<1>(kOutput16)>(
            std::get<0>(kOutput16));
    constexpr IType kI18 = kI17 + Inc;
    constexpr auto kOutput18 =
        BodyFunctor::template func<kI18, std::get<1>(kOutput17)>(
            std::get<0>(kOutput17));
    constexpr IType kI19 = kI18 + Inc;
    constexpr auto kOutput19 =
        BodyFunctor::template func<kI19, std::get<1>(kOutput18)>(
            std::get<0>(kOutput18));
    constexpr IType kI20 = kI19 + Inc;
    constexpr auto kOutput20 =
        BodyFunctor::template func<kI20, std::get<1>(kOutput19)>(
            std::get<0>(kOutput19));
    constexpr IType kI21 = kI20 + Inc;
    constexpr auto kOutput21 =
        BodyFunctor::template func<kI21, std::get<1>(kOutput20)>(
            std::get<0>(kOutput20));
    constexpr IType kI22 = kI21 + Inc;
    constexpr auto kOutput22 =
        BodyFunctor::template func<kI22, std::get<1>(kOutput21)>(
            std::get<0>(kOutput21));
    constexpr IType kI23 = kI22 + Inc;
    constexpr auto kOutput23 =
        BodyFunctor::template func<kI23, std::get<1>(kOutput22)>(
            std::get<0>(kOutput22));
    constexpr IType kI24 = kI23 + Inc;
    constexpr auto kOutput24 =
        BodyFunctor::template func<kI24, std::get<1>(kOutput23)>(
            std::get<0>(kOutput23));
    constexpr IType kI25 = kI24 + Inc;
    constexpr auto kOutput25 =
        BodyFunctor::template func<kI25, std::get<1>(kOutput24)>(
            std::get<0>(kOutput24));
    constexpr IType kI26 = kI25 + Inc;
    constexpr auto kOutput26 =
        BodyFunctor::template func<kI26, std::get<1>(kOutput25)>(
            std::get<0>(kOutput25));
    constexpr IType kI27 = kI26 + Inc;
    constexpr auto kOutput27 =
        BodyFunctor::template func<kI27, std::get<1>(kOutput26)>(
            std::get<0>(kOutput26));
    constexpr IType kI28 = kI27 + Inc;
    constexpr auto kOutput28 =
        BodyFunctor::template func<kI28, std::get<1>(kOutput27)>(
            std::get<0>(kOutput27));
    constexpr IType kI29 = kI28 + Inc;
    constexpr auto kOutput29 =
        BodyFunctor::template func<kI29, std::get<1>(kOutput28)>(
            std::get<0>(kOutput28));
    constexpr IType kI30 = kI29 + Inc;
    constexpr auto kOutput30 =
        BodyFunctor::template func<kI30, std::get<1>(kOutput29)>(
            std::get<0>(kOutput29));
    constexpr IType kI31 = kI30 + Inc;
    constexpr auto kOutput31 =
        BodyFunctor::template func<kI31, std::get<1>(kOutput30)>(
            std::get<0>(kOutput30));
    constexpr IType kI32 = kI31 + Inc;
    constexpr auto kOutput32 =
        BodyFunctor::template func<kI32, std::get<1>(kOutput31)>(
            std::get<0>(kOutput31));
    constexpr IType kI33 = kI32 + Inc;
    constexpr auto kOutput33 =
        BodyFunctor::template func<kI33, std::get<1>(kOutput32)>(
            std::get<0>(kOutput32));
    constexpr IType kI34 = kI33 + Inc;
    constexpr auto kOutput34 =
        BodyFunctor::template func<kI34, std::get<1>(kOutput33)>(
            std::get<0>(kOutput33));
    constexpr IType kI35 = kI34 + Inc;
    constexpr auto kOutput35 =
        BodyFunctor::template func<kI35, std::get<1>(kOutput34)>(
            std::get<0>(kOutput34));
    constexpr IType kI36 = kI35 + Inc;
    constexpr auto kOutput36 =
        BodyFunctor::template func<kI36, std::get<1>(kOutput35)>(
            std::get<0>(kOutput35));
    constexpr IType kI37 = kI36 + Inc;
    constexpr auto kOutput37 =
        BodyFunctor::template func<kI37, std::get<1>(kOutput36)>(
            std::get<0>(kOutput36));
    constexpr IType kI38 = kI37 + Inc;
    constexpr auto kOutput38 =
        BodyFunctor::template func<kI38, std::get<1>(kOutput37)>(
            std::get<0>(kOutput37));
    constexpr IType kI39 = kI38 + Inc;
    constexpr auto kOutput39 =
        BodyFunctor::template func<kI39, std::get<1>(kOutput38)>(
            std::get<0>(kOutput38));
    constexpr IType kI40 = kI39 + Inc;
    constexpr auto kOutput40 =
        BodyFunctor::template func<kI40, std::get<1>(kOutput39)>(
            std::get<0>(kOutput39));
    constexpr IType kI41 = kI40 + Inc;
    constexpr auto kOutput41 =
        BodyFunctor::template func<kI41, std::get<1>(kOutput40)>(
            std::get<0>(kOutput40));
    constexpr IType kI42 = kI41 + Inc;
    constexpr auto kOutput42 =
        BodyFunctor::template func<kI42, std::get<1>(kOutput41)>(
            std::get<0>(kOutput41));
    constexpr IType kI43 = kI42 + Inc;
    constexpr auto kOutput43 =
        BodyFunctor::template func<kI43, std::get<1>(kOutput42)>(
            std::get<0>(kOutput42));
    constexpr IType kI44 = kI43 + Inc;
    constexpr auto kOutput44 =
        BodyFunctor::template func<kI44, std::get<1>(kOutput43)>(
            std::get<0>(kOutput43));
    constexpr IType kI45 = kI44 + Inc;
    constexpr auto kOutput45 =
        BodyFunctor::template func<kI45, std::get<1>(kOutput44)>(
            std::get<0>(kOutput44));
    constexpr IType kI46 = kI45 + Inc;
    constexpr auto kOutput46 =
        BodyFunctor::template func<kI46, std::get<1>(kOutput45)>(
            std::get<0>(kOutput45));
    constexpr IType kI47 = kI46 + Inc;
    constexpr auto kOutput47 =
        BodyFunctor::template func<kI47, std::get<1>(kOutput46)>(
            std::get<0>(kOutput46));
    constexpr IType kI48 = kI47 + Inc;
    constexpr auto kOutput48 =
        BodyFunctor::template func<kI48, std::get<1>(kOutput47)>(
            std::get<0>(kOutput47));
    constexpr IType kI49 = kI48 + Inc;
    constexpr auto kOutput49 =
        BodyFunctor::template func<kI49, std::get<1>(kOutput48)>(
            std::get<0>(kOutput48));
    constexpr IType kI50 = kI49 + Inc;
    constexpr auto kOutput50 =
        BodyFunctor::template func<kI50, std::get<1>(kOutput49)>(
            std::get<0>(kOutput49));
    constexpr IType kI51 = kI50 + Inc;
    constexpr auto kOutput51 =
        BodyFunctor::template func<kI51, std::get<1>(kOutput50)>(
            std::get<0>(kOutput50));
    constexpr IType kI52 = kI51 + Inc;
    constexpr auto kOutput52 =
        BodyFunctor::template func<kI52, std::get<1>(kOutput51)>(
            std::get<0>(kOutput51));
    constexpr IType kI53 = kI52 + Inc;
    constexpr auto kOutput53 =
        BodyFunctor::template func<kI53, std::get<1>(kOutput52)>(
            std::get<0>(kOutput52));
    constexpr IType kI54 = kI53 + Inc;
    constexpr auto kOutput54 =
        BodyFunctor::template func<kI54, std::get<1>(kOutput53)>(
            std::get<0>(kOutput53));
    constexpr IType kI55 = kI54 + Inc;
    constexpr auto kOutput55 =
        BodyFunctor::template func<kI55, std::get<1>(kOutput54)>(
            std::get<0>(kOutput54));
    constexpr IType kI56 = kI55 + Inc;
    constexpr auto kOutput56 =
        BodyFunctor::template func<kI56, std::get<1>(kOutput55)>(
            std::get<0>(kOutput55));
    constexpr IType kI57 = kI56 + Inc;
    constexpr auto kOutput57 =
        BodyFunctor::template func<kI57, std::get<1>(kOutput56)>(
            std::get<0>(kOutput56));
    constexpr IType kI58 = kI57 + Inc;
    constexpr auto kOutput58 =
        BodyFunctor::template func<kI58, std::get<1>(kOutput57)>(
            std::get<0>(kOutput57));
    constexpr IType kI59 = kI58 + Inc;
    constexpr auto kOutput59 =
        BodyFunctor::template func<kI59, std::get<1>(kOutput58)>(
            std::get<0>(kOutput58));
    constexpr IType kI60 = kI59 + Inc;
    constexpr auto kOutput60 =
        BodyFunctor::template func<kI60, std::get<1>(kOutput59)>(
            std::get<0>(kOutput59));
    constexpr IType kI61 = kI60 + Inc;
    constexpr auto kOutput61 =
        BodyFunctor::template func<kI61, std::get<1>(kOutput60)>(
            std::get<0>(kOutput60));
    constexpr IType kI62 = kI61 + Inc;
    constexpr auto kOutput62 =
        BodyFunctor::template func<kI62, std::get<1>(kOutput61)>(
            std::get<0>(kOutput61));
    constexpr IType kI63 = kI62 + Inc;
    constexpr auto kOutput63 =
        BodyFunctor::template func<kI63, std::get<1>(kOutput62)>(
            std::get<0>(kOutput62));
    constexpr IType kI64 = kI63 + Inc;
    constexpr auto kOutput64 =
        BodyFunctor::template func<kI64, std::get<1>(kOutput63)>(
            std::get<0>(kOutput63));
    constexpr IType kI65 = kI64 + Inc;
    constexpr auto kOutput65 =
        BodyFunctor::template func<kI65, std::get<1>(kOutput64)>(
            std::get<0>(kOutput64));
    constexpr IType kI66 = kI65 + Inc;
    constexpr auto kOutput66 =
        BodyFunctor::template func<kI66, std::get<1>(kOutput65)>(
            std::get<0>(kOutput65));
    constexpr IType kI67 = kI66 + Inc;
    constexpr auto kOutput67 =
        BodyFunctor::template func<kI67, std::get<1>(kOutput66)>(
            std::get<0>(kOutput66));
    constexpr IType kI68 = kI67 + Inc;
    constexpr auto kOutput68 =
        BodyFunctor::template func<kI68, std::get<1>(kOutput67)>(
            std::get<0>(kOutput67));
    constexpr IType kI69 = kI68 + Inc;
    constexpr auto kOutput69 =
        BodyFunctor::template func<kI69, std::get<1>(kOutput68)>(
            std::get<0>(kOutput68));
    constexpr IType kI70 = kI69 + Inc;
    constexpr auto kOutput70 =
        BodyFunctor::template func<kI70, std::get<1>(kOutput69)>(
            std::get<0>(kOutput69));
    constexpr IType kI71 = kI70 + Inc;
    constexpr auto kOutput71 =
        BodyFunctor::template func<kI71, std::get<1>(kOutput70)>(
            std::get<0>(kOutput70));
    constexpr IType kI72 = kI71 + Inc;
    constexpr auto kOutput72 =
        BodyFunctor::template func<kI72, std::get<1>(kOutput71)>(
            std::get<0>(kOutput71));
    constexpr IType kI73 = kI72 + Inc;
    constexpr auto kOutput73 =
        BodyFunctor::template func<kI73, std::get<1>(kOutput72)>(
            std::get<0>(kOutput72));
    constexpr IType kI74 = kI73 + Inc;
    constexpr auto kOutput74 =
        BodyFunctor::template func<kI74, std::get<1>(kOutput73)>(
            std::get<0>(kOutput73));
    constexpr IType kI75 = kI74 + Inc;
    constexpr auto kOutput75 =
        BodyFunctor::template func<kI75, std::get<1>(kOutput74)>(
            std::get<0>(kOutput74));
    constexpr IType kI76 = kI75 + Inc;
    constexpr auto kOutput76 =
        BodyFunctor::template func<kI76, std::get<1>(kOutput75)>(
            std::get<0>(kOutput75));
    constexpr IType kI77 = kI76 + Inc;
    constexpr auto kOutput77 =
        BodyFunctor::template func<kI77, std::get<1>(kOutput76)>(
            std::get<0>(kOutput76));
    constexpr IType kI78 = kI77 + Inc;
    constexpr auto kOutput78 =
        BodyFunctor::template func<kI78, std::get<1>(kOutput77)>(
            std::get<0>(kOutput77));
    constexpr IType kI79 = kI78 + Inc;
    constexpr auto kOutput79 =
        BodyFunctor::template func<kI79, std::get<1>(kOutput78)>(
            std::get<0>(kOutput78));
    constexpr IType kI80 = kI79 + Inc;
    constexpr auto kOutput80 =
        BodyFunctor::template func<kI80, std::get<1>(kOutput79)>(
            std::get<0>(kOutput79));
    constexpr IType kI81 = kI80 + Inc;
    constexpr auto kOutput81 =
        BodyFunctor::template func<kI81, std::get<1>(kOutput80)>(
            std::get<0>(kOutput80));
    constexpr IType kI82 = kI81 + Inc;
    constexpr auto kOutput82 =
        BodyFunctor::template func<kI82, std::get<1>(kOutput81)>(
            std::get<0>(kOutput81));
    constexpr IType kI83 = kI82 + Inc;
    constexpr auto kOutput83 =
        BodyFunctor::template func<kI83, std::get<1>(kOutput82)>(
            std::get<0>(kOutput82));
    constexpr IType kI84 = kI83 + Inc;
    constexpr auto kOutput84 =
        BodyFunctor::template func<kI84, std::get<1>(kOutput83)>(
            std::get<0>(kOutput83));
    constexpr IType kI85 = kI84 + Inc;
    constexpr auto kOutput85 =
        BodyFunctor::template func<kI85, std::get<1>(kOutput84)>(
            std::get<0>(kOutput84));
    constexpr IType kI86 = kI85 + Inc;
    constexpr auto kOutput86 =
        BodyFunctor::template func<kI86, std::get<1>(kOutput85)>(
            std::get<0>(kOutput85));
    constexpr IType kI87 = kI86 + Inc;
    constexpr auto kOutput87 =
        BodyFunctor::template func<kI87, std::get<1>(kOutput86)>(
            std::get<0>(kOutput86));
    constexpr IType kI88 = kI87 + Inc;
    constexpr auto kOutput88 =
        BodyFunctor::template func<kI88, std::get<1>(kOutput87)>(
            std::get<0>(kOutput87));
    constexpr IType kI89 = kI88 + Inc;
    constexpr auto kOutput89 =
        BodyFunctor::template func<kI89, std::get<1>(kOutput88)>(
            std::get<0>(kOutput88));
    constexpr IType kI90 = kI89 + Inc;
    constexpr auto kOutput90 =
        BodyFunctor::template func<kI90, std::get<1>(kOutput89)>(
            std::get<0>(kOutput89));
    constexpr IType kI91 = kI90 + Inc;
    constexpr auto kOutput91 =
        BodyFunctor::template func<kI91, std::get<1>(kOutput90)>(
            std::get<0>(kOutput90));
    constexpr IType kI92 = kI91 + Inc;
    constexpr auto kOutput92 =
        BodyFunctor::template func<kI92, std::get<1>(kOutput91)>(
            std::get<0>(kOutput91));
    constexpr IType kI93 = kI92 + Inc;
    constexpr auto kOutput93 =
        BodyFunctor::template func<kI93, std::get<1>(kOutput92)>(
            std::get<0>(kOutput92));
    constexpr IType kI94 = kI93 + Inc;
    constexpr auto kOutput94 =
        BodyFunctor::template func<kI94, std::get<1>(kOutput93)>(
            std::get<0>(kOutput93));
    constexpr IType kI95 = kI94 + Inc;
    constexpr auto kOutput95 =
        BodyFunctor::template func<kI95, std::get<1>(kOutput94)>(
            std::get<0>(kOutput94));
    constexpr IType kI96 = kI95 + Inc;
    constexpr auto kOutput96 =
        BodyFunctor::template func<kI96, std::get<1>(kOutput95)>(
            std::get<0>(kOutput95));
    constexpr IType kI97 = kI96 + Inc;
    constexpr auto kOutput97 =
        BodyFunctor::template func<kI97, std::get<1>(kOutput96)>(
            std::get<0>(kOutput96));
    constexpr IType kI98 = kI97 + Inc;
    constexpr auto kOutput98 =
        BodyFunctor::template func<kI98, std::get<1>(kOutput97)>(
            std::get<0>(kOutput97));
    constexpr IType kI99 = kI98 + Inc;
    constexpr auto kOutput99 =
        BodyFunctor::template func<kI99, std::get<1>(kOutput98)>(
            std::get<0>(kOutput98));
    return kOutput99;
  }
};

}  // namespace impl
}  // namespace cex_for_loop

#endif  // LINEAR_CEX_FOR_LOOP_H
