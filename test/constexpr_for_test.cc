#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <CEXForLoop/cex_for_loop.h>
#include <CEXForLoop/bool_expression_functors.h>

struct TestFunctorSetSmallIteration {
  struct Data {
    std::array<uint32_t, 250> i_tracker;
    int last_i_value;
  };

  template <uint32_t I>
  static constexpr Data func(Data input_data) {
    std::get<I>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

struct TestFunctorAdd {
  struct Data {
    int64_t kResult;
  };

  template <int64_t I>
  static constexpr Data func(Data input_data) {
    input_data.kResult += I;
    return input_data;
  };
};

struct TestFunctorSetForNegative2IncNegative2Start {
  using NumericType = int16_t;
  struct Data {
    std::array<int16_t, 200> i_tracker;
  };

  template <int16_t I>
  static constexpr Data func(Data input_data) {
    std::get<(-1 * I / 2) - 1>(input_data.i_tracker) = I;
    return input_data;
  };
};

struct TestFunctorSetLargeIterationIncBy3WithNegative1700Start {
  struct Data {
    std::array<int64_t, 10'100> i_tracker;
    int last_i_value;
  };

  template <int64_t I>
  static constexpr Data func(Data input_data) {
    std::get<(I - 300) / -3>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

struct TestFunctorSetLargeIteration {
  struct Data {
    std::array<uint64_t, 10'100> i_tracker;
    uint64_t last_i_value;
  };

  template <uint64_t I>
  static constexpr Data func(Data input_data) {
    std::get<I>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

TEST(ConstexprFor, ZeroToPositiveNumber) {
  constexpr uint32_t kTestTemplateDepth = 5;
  constexpr TestFunctorSetSmallIteration::Data kTestInitialValues = {
      {0, 0, 0, 0, 0}, 0};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int32_t, 0, kTestTemplateDepth, 1,
                                  cex_for_loop::BoolExpressionFunctor_LT,
                                  TestFunctorSetSmallIteration>(
          kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kResult.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(kResult.last_i_value, kTestTemplateDepth - 1);
  for (uint32_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
}

TEST(ConstexprFor, PositiveNumberToZero) {
  constexpr uint32_t kTestTemplateDepth = 5;
  constexpr TestFunctorSetSmallIteration::Data kTestInitialValues = {
      {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 0};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int32_t, kTestTemplateDepth - 1, 0, -1,
                                  cex_for_loop::BoolExpressionFunctor_GEQ,
                                  TestFunctorSetSmallIteration>(
          kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kResult.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  for (uint32_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
  ASSERT_EQ(kResult.last_i_value, 0);
}

TEST(ConstexprFor, ZeroToNegativeNumber) {
  constexpr int64_t kTestTemplateDepth = 5;
  constexpr TestFunctorAdd::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int64_t, 0, -kTestTemplateDepth, -1,
                                  cex_for_loop::BoolExpressionFunctor_GT,
                                  TestFunctorAdd>(kTestInitialValues);
  ASSERT_EQ(0 - 1 - 2 - 3 - 4, kResult.kResult);
}

TEST(ConstexprFor, NegativeNumberToZero) {
  constexpr int64_t kTesttemplatedepth = 5;
  constexpr TestFunctorAdd::Data kTestinitialvalues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int64_t, -kTesttemplatedepth + 1, 0, 1,
                                  cex_for_loop::BoolExpressionFunctor_LEQ,
                                  TestFunctorAdd>(kTestinitialvalues);
  ASSERT_EQ(-4 - 3 - 2 - 1 - 0, kResult.kResult);
}

TEST(ConstexprFor, NegativeNumberToNegativeNumber) {
  using UserProvidedType =
      TestFunctorSetForNegative2IncNegative2Start::NumericType;
  constexpr UserProvidedType kTestStart = -2;
  constexpr UserProvidedType kTestEnd = -202;
  constexpr UserProvidedType kTestInc = -2;

  constexpr TestFunctorSetForNegative2IncNegative2Start::Data
      kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<UserProvidedType, kTestStart, kTestEnd,
                                  kTestInc,
                                  cex_for_loop::BoolExpressionFunctor_GEQ,
                                  TestFunctorSetForNegative2IncNegative2Start>(
          kTestInitialValues);

  std::array<UserProvidedType, 200> expected_i_tracker = {};
  auto expected_i_inc = 0;
  for (UserProvidedType i = kTestStart; i >= kTestEnd; i += kTestInc) {
    // NOLINTNEXTLINE(bugprone-narrowing-conversions)
    expected_i_tracker[expected_i_inc] = i;
    expected_i_inc++;
  }

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (UserProvidedType value : kResult.i_tracker) {
  //   print_string.append(std::to_string(value) + ", ");
  // }
  // ADD_FAILURE() << print_string

  for (int i = 0; i < expected_i_inc; i++) {
    ASSERT_EQ(kResult.i_tracker[i], expected_i_tracker[i]) << i;
  }
}

TEST(ConstexprFor, NegativeNumberToPositiveNumberBy3s) {
  constexpr TestFunctorAdd::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int64_t, -15, 15, 3,
                                  cex_for_loop::BoolExpressionFunctor_LEQ,
                                  TestFunctorAdd>(kTestInitialValues);

  ASSERT_EQ(kResult.kResult, 0);
}

TEST(ConstexprFor, TemplateInstantiationDepth2000) {
  constexpr int64_t kTestTemplateDepth = 2000;
  constexpr TestFunctorSetLargeIterationIncBy3WithNegative1700Start::Data
      kTestInitialValues = {};

  constexpr auto kResult = cex_for_loop::constexpr_for<
      int64_t, (-3 * kTestTemplateDepth) + 300, 300, 3,
      cex_for_loop::BoolExpressionFunctor_LEQ,
      TestFunctorSetLargeIterationIncBy3WithNegative1700Start>(
      kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kTestTemplateDepth; i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(kResult.last_i_value, 300);
}

TEST(ConstexprFor, TemplateInstantiationDepth10000) {
  constexpr uint64_t kTestTemplateDepth = 10'000;
  constexpr TestFunctorSetLargeIteration::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<int64_t, 1, kTestTemplateDepth, 1,
                                  cex_for_loop::BoolExpressionFunctor_LEQ,
                                  TestFunctorSetLargeIteration>(
          kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kTestTemplateDepth; i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(kResult.last_i_value, kTestTemplateDepth);
  for (uint64_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
}
