#ifndef TEMPLATE_METAPROGRAMMING_HELPERS
#define TEMPLATE_METAPROGRAMMING_HELPERS

#include <cstddef>
#include <cstdint>
#include <tuple>
#include <type_traits>
namespace tmp_helpers {

// Primary template: handles the summation for multiple types
template <typename... Types>
struct SizeOfAllVariadicTemplateParameters;

// Specialization for the case where there is at least one type
template <typename T, typename... Rest>
struct SizeOfAllVariadicTemplateParameters<T, Rest...> {
  // NOLINTNEXTLINE(readability-identifier-naming)
  static constexpr size_t value =
      sizeof(T) + SizeOfAllVariadicTemplateParameters<Rest...>::value;
};

// Specialization for the base case: no types left
template <>
struct SizeOfAllVariadicTemplateParameters<> {
  // NOLINTNEXTLINE(readability-identifier-naming)
  static constexpr size_t value = 0;
};

//------------------------------------------------------------------------------
// Reference: https://stackoverflow.com/a/10615119
//------------------------------------------------------------------------------
template <int... Indices>
struct IndicesType {
  using next = IndicesType<Indices..., sizeof...(Indices)>;
};

template <int Size>
struct BuildIndices {
  using type = typename BuildIndices<Size - 1>::type::next;
};

template <>
struct BuildIndices<0> {
  using type = IndicesType<>;
};

template <typename T>
using Bare =
    typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename Tuple>
constexpr typename BuildIndices<std::tuple_size<Bare<Tuple>>::value>::type
make_indices() {
  return {};
}

template <typename Tuple, int... Indices>
constexpr std::array<typename std::tuple_element<0, Bare<Tuple>>::type,
                     std::tuple_size<Bare<Tuple>>::value>
// NOLINTNEXTLINE(readability-named-parameter)
TupleToArray(Tuple&& tuple, IndicesType<Indices...>) {
  return {{std::get<Indices>(std::forward<Tuple>(tuple))...}};
}

template <typename Tuple>
constexpr auto TupleToArray(Tuple&& tuple)
    -> decltype(TupleToArray(std::declval<Tuple>(), make_indices<Tuple>())) {
  return TupleToArray(std::forward<Tuple>(tuple), make_indices<Tuple>());
}
//------------------------------------------------------------------------------
// Reference: https://stackoverflow.com/a/10615119
//------------------------------------------------------------------------------

template <uint8_t... Bytes>
constexpr std::array<uint8_t, sizeof...(Bytes)> Uint8tParameterPackToArray() {
  return TupleToArray(std::make_tuple(Bytes...));
}

//------------------------------------------------------------------------------
template<std::size_t I, typename... Types>
struct NthType {
    using type = decltype(std::get<I>(std::tuple<Types...>()));
};

template<std::size_t I, typename... Types>
using NthType_t = typename NthType<I, Types...>::type;
//------------------------------------------------------------------------------


}  // namespace tmp_helpers

#endif  // TEMPLATE_METAPROGRAMMING_HELPERS
