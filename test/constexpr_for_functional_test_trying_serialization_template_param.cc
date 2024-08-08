#include <CEXForLoop/bool_expression_functors.h>
#include <CEXForLoop/cex_for_loop.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

// TODO:
//  1. Write serialization method
//  2. Write Deserialization method

// Define as a functor so that reused data only has to be instantiated once
template <typename... FuncParameterTypes>
struct FunctorParameterDeserializer {
  template <uint8_t... FuncParameterBytes>
  struct WithBytes {
    // static constexpr auto kBytes =
    //     tmp_helpers::Uint8tParameterPackToArray<FuncParameterBytes...>();

    static constexpr auto kTypes = std::tuple<FuncParameterTypes...>();

    // returns an array where each index is the ith functor parameter type
    // and the value is the types front index (i.e. where its data starts)
    static constexpr std::array<std::size_t, sizeof...(FuncParameterTypes)>
        kByteFront = {};

    template <std::size_t I>
    static constexpr int
    // tmp_helpers::NthType_t<I, FuncParameterTypes...>
    GetIthParam() {
      // When I > 0, ensure that the Ith parameter offset was written in a call
      // to GetIthParam<I-1>();
      // static_assert(std::get<I - 1>(kByteFront) != 0,
      //               "You must retreieve Functor Parameters in order.");
      // update the I+1 parameter offset
      // std::get<I + 1>(kByteFront) = sizeof(std::get<I>(kTypes));

      // tmp_helpers::NthType_t<I, FuncParameterTypes...> return_value = {};
      // tmp_helpers::NthType_t<I, FuncParameterTypes...> return_value = {};

      constexpr auto kBytes =
          tmp_helpers::Uint8tParameterPackToArray<FuncParameterBytes...>();

      int return_value = {};
      auto *return_value_ptr = reinterpret_cast<uint8_t *>(&return_value);
      for (std::size_t i = 0; i < sizeof(return_value); i++) {
        return_value_ptr[i] = kBytes[i];
      }
      return return_value;
    }
    //
    // template <>
    // static constexpr tmp_helpers::NthType_t<0, FuncParameterTypes...>
    // GetIthParam<0>() {
    //   tmp_helpers::NthType_t<0, FuncParameterTypes...> return_value;
    //   uint8_t* return_value_ptr = &return_value;
    //   for (int i = 0; i < sizeof(return_value); i++) {
    //     return_value_ptr[i] = kBytes[i];
    //   }
    //
    //   std::get<1>(kByteFront) = sizeof(std::get<0>(kTypes));
    //
    //   return return_value;
    // }
  };
};

struct TestFunctorSetLargeIteration {
  struct NonConstexprData {
    std::array<uint64_t, 10'100> i_tracker;
    uint64_t last_i_value;
  };

  template <typename... FuncParameterTypes>
  struct FuncingFunctor {
    template <uint64_t I, uint8_t... FuncParameterBytes>
    static constexpr std::array<
        uint8_t, tmp_helpers::SizeOfAllVariadicTemplateParameters<
                     FuncParameterTypes...>::value>
    func(NonConstexprData non_constexpr_data) {
      /*Deserialize Method on `DataBytes`*/
      // The user is going to document the parameter types above and then
      // expect them here.

      constexpr int kFirstVar = FunctorParameterDeserializer<
          FuncParameterTypes...>::template WithBytes<FuncParameterBytes...>::
          template GetIthParam<0>();

      static_assert(kFirstVar == 0);

      // auto second_var = 9;
      // auto non_existant_var = 10; /* static assert should fail */

      // -----Custom Content-----
      std::get<I>(non_constexpr_data.i_tracker) = I;
      non_constexpr_data.last_i_value = I;
      // -----Custom Content-----

      /*Serilize Method on `input_data`*/
      return std::array<uint8_t,
                        tmp_helpers::SizeOfAllVariadicTemplateParameters<
                            FuncParameterTypes...>::value>();
    };
  };
};

TEST(ConstexprFor, ZeroToPositiveNumber) {
  // constexpr uint32_t kTestTemplateDepth = 5;
  constexpr TestFunctorSetLargeIteration::NonConstexprData kTestInitialValues =
      {{0, 0, 0, 0, 0}, 0};

  auto thing = TestFunctorSetLargeIteration::FuncingFunctor<int>::func<
      0, static_cast<uint8_t>(0x00), static_cast<uint8_t>(0x00),
      static_cast<uint8_t>(0x00), static_cast<uint8_t>(0x00)>(
      kTestInitialValues);

  // TestFunctorSetLargeIteration::FunctorFunctor <

  // constexpr auto kResult =
  //     cex_for_loop::constexpr_for<int32_t, 0, kTestTemplateDepth, 1,
  //                                 cex_for_loop::BoolExpressionFunctor_LT,
  //                                 TestFunctorSetLargeIteration>(
  //         kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kResult.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;
  //
  // ASSERT_EQ(kResult.last_i_value, kTestTemplateDepth - 1);
  // for (uint32_t i = 0; i < kTestTemplateDepth; i++) {
  //   ASSERT_EQ(kResult.i_tracker[i], i);
  // }
}
