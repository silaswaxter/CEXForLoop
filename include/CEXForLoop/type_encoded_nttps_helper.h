// This file is generated by a python script. It provides a convienient helper
// that encodes NTTP as std::integral_constants types. This is especially
// helpful when there are a large number of NTTPs.

#ifndef TYPE_ENCODED_NTTPS_HELPER_IMPL_H
#define TYPE_ENCODED_NTTPS_HELPER_IMPL_H

#include <tuple>

namespace cex_for_loop {
template <typename BodyFunctor,
          std::size_t NTTPCount =
              std::tuple_size<typename BodyFunctor::OutputType>::value - 1>
struct TypeEncodedNTTPs;

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 0> {
  using type = std::tuple<>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 1> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 2> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 3> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 4> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 5> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 6> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 7> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 8> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 9> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 10> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 11> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9,
    std::tuple_element_t<11, typename BodyFunctor::OutputType>
        InitialNTTPValue10>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>,
      std::integral_constant<decltype(InitialNTTPValue10), InitialNTTPValue10>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 12> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9,
    std::tuple_element_t<11, typename BodyFunctor::OutputType>
        InitialNTTPValue10,
    std::tuple_element_t<12, typename BodyFunctor::OutputType>
        InitialNTTPValue11>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>,
      std::integral_constant<decltype(InitialNTTPValue10), InitialNTTPValue10>,
      std::integral_constant<decltype(InitialNTTPValue11), InitialNTTPValue11>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 13> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9,
    std::tuple_element_t<11, typename BodyFunctor::OutputType>
        InitialNTTPValue10,
    std::tuple_element_t<12, typename BodyFunctor::OutputType>
        InitialNTTPValue11,
    std::tuple_element_t<13, typename BodyFunctor::OutputType>
        InitialNTTPValue12>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>,
      std::integral_constant<decltype(InitialNTTPValue10), InitialNTTPValue10>,
      std::integral_constant<decltype(InitialNTTPValue11), InitialNTTPValue11>,
      std::integral_constant<decltype(InitialNTTPValue12), InitialNTTPValue12>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 14> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9,
    std::tuple_element_t<11, typename BodyFunctor::OutputType>
        InitialNTTPValue10,
    std::tuple_element_t<12, typename BodyFunctor::OutputType>
        InitialNTTPValue11,
    std::tuple_element_t<13, typename BodyFunctor::OutputType>
        InitialNTTPValue12,
    std::tuple_element_t<14, typename BodyFunctor::OutputType>
        InitialNTTPValue13>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>,
      std::integral_constant<decltype(InitialNTTPValue10), InitialNTTPValue10>,
      std::integral_constant<decltype(InitialNTTPValue11), InitialNTTPValue11>,
      std::integral_constant<decltype(InitialNTTPValue12), InitialNTTPValue12>,
      std::integral_constant<decltype(InitialNTTPValue13), InitialNTTPValue13>>;
};

template <typename BodyFunctor>
struct TypeEncodedNTTPs<BodyFunctor, 15> {
  template <
      // clang-format off
    std::tuple_element_t<1, typename BodyFunctor::OutputType>
        InitialNTTPValue0,
    std::tuple_element_t<2, typename BodyFunctor::OutputType>
        InitialNTTPValue1,
    std::tuple_element_t<3, typename BodyFunctor::OutputType>
        InitialNTTPValue2,
    std::tuple_element_t<4, typename BodyFunctor::OutputType>
        InitialNTTPValue3,
    std::tuple_element_t<5, typename BodyFunctor::OutputType>
        InitialNTTPValue4,
    std::tuple_element_t<6, typename BodyFunctor::OutputType>
        InitialNTTPValue5,
    std::tuple_element_t<7, typename BodyFunctor::OutputType>
        InitialNTTPValue6,
    std::tuple_element_t<8, typename BodyFunctor::OutputType>
        InitialNTTPValue7,
    std::tuple_element_t<9, typename BodyFunctor::OutputType>
        InitialNTTPValue8,
    std::tuple_element_t<10, typename BodyFunctor::OutputType>
        InitialNTTPValue9,
    std::tuple_element_t<11, typename BodyFunctor::OutputType>
        InitialNTTPValue10,
    std::tuple_element_t<12, typename BodyFunctor::OutputType>
        InitialNTTPValue11,
    std::tuple_element_t<13, typename BodyFunctor::OutputType>
        InitialNTTPValue12,
    std::tuple_element_t<14, typename BodyFunctor::OutputType>
        InitialNTTPValue13,
    std::tuple_element_t<15, typename BodyFunctor::OutputType>
        InitialNTTPValue14>
  // clang-format on
  using type = std::tuple<
      std::integral_constant<decltype(InitialNTTPValue0), InitialNTTPValue0>,
      std::integral_constant<decltype(InitialNTTPValue1), InitialNTTPValue1>,
      std::integral_constant<decltype(InitialNTTPValue2), InitialNTTPValue2>,
      std::integral_constant<decltype(InitialNTTPValue3), InitialNTTPValue3>,
      std::integral_constant<decltype(InitialNTTPValue4), InitialNTTPValue4>,
      std::integral_constant<decltype(InitialNTTPValue5), InitialNTTPValue5>,
      std::integral_constant<decltype(InitialNTTPValue6), InitialNTTPValue6>,
      std::integral_constant<decltype(InitialNTTPValue7), InitialNTTPValue7>,
      std::integral_constant<decltype(InitialNTTPValue8), InitialNTTPValue8>,
      std::integral_constant<decltype(InitialNTTPValue9), InitialNTTPValue9>,
      std::integral_constant<decltype(InitialNTTPValue10), InitialNTTPValue10>,
      std::integral_constant<decltype(InitialNTTPValue11), InitialNTTPValue11>,
      std::integral_constant<decltype(InitialNTTPValue12), InitialNTTPValue12>,
      std::integral_constant<decltype(InitialNTTPValue13), InitialNTTPValue13>,
      std::integral_constant<decltype(InitialNTTPValue14), InitialNTTPValue14>>;
};

}  // namespace cex_for_loop

#endif  // TYPE_ENCODED_NTTPS_HELPER_IMPL_H
