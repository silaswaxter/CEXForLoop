#include <CEXForLoop/bool_expression_functors.h>
#include <CEXForLoop/cex_for_loop.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

struct TestFunctorSetLargeIteration {
  struct Data {
    std::size_t append_index;
    std::array<uint64_t, 100> array;
  };

  template <std::size_t I>
  static constexpr Data func(const Data& input_data) {
    Data output_data = input_data;

    static_assert(input_data.append_index == 0, "no no no");
    // if(I % 3 == 0){
    //   std::get<input_data.append_index>(output_data.array) = I;
    // }

    return output_data;
  }
};

constexpr TestFunctorSetLargeIteration::Data kTestInitialValues = {0, {}};

TEST(ConstexprFor, ZeroToPositiveNumber) {
  constexpr uint32_t kTestTemplateDepth = 5;
  // constexpr TestFunctorSetLargeIteration::Data kTestInitialValues = {0, {}};

  constexpr auto kResult = cex_for_loop::constexpr_for_functional<
      int32_t, 0, kTestTemplateDepth, 1, cex_for_loop::BoolExpressionFunctor_LT,
      TestFunctorSetLargeIteration>(kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kResult.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  // ASSERT_EQ(kResult.last_i_value, kTestTemplateDepth - 1);
  // for (uint32_t i = 0; i < kTestTemplateDepth; i++) {
  //   ASSERT_EQ(kResult.i_tracker[i], i);
  // }
}
