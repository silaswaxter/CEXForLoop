#include <gtest/gtest.h>

#include <array>

#include "include/bool_expression_functors.h"
#include "include/cex_for_loop.h"

struct TestFunctorSetSmallIteration {
  struct Data {
    std::array<int, 250> i_tracker;
    int last_i_value;
  };

  template <long long I>
  static constexpr Data func(Data input_data) {
    std::get<I>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

struct TestFunctorAdd {
  struct Data {
    long long kResult;
  };

  template <long long I>
  static constexpr Data func(Data input_data) {
    input_data.kResult += I;
    return input_data;
  };
};

struct TestFunctorSetForNegative2IncNegative2Start {
  struct Data {
    std::array<int, 200> i_tracker;
  };

  template <long long I>
  static constexpr Data func(Data input_data) {
    std::get<(-1 * I / 2) - 1>(input_data.i_tracker) = I;
    return input_data;
  };
};

struct TestFunctorSetLargeIterationIncBy3WithNegative1700Start {
  struct Data {
    std::array<int, 1'000'000> i_tracker;
    int last_i_value;
  };

  template <long long I>
  static constexpr Data func(Data input_data) {
    std::get<(I - 300) / -3>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

struct TestFunctorSetLargeIteration {
  struct Data {
    std::array<int, 1'000'000> i_tracker;
    int last_i_value;
  };

  template <long long I>
  static constexpr Data func(Data input_data) {
    std::get<I>(input_data.i_tracker) = I;
    input_data.last_i_value = I;
    return input_data;
  };
};

TEST(ConstexprFor, ZeroToPositiveNumber) {
  constexpr long long kTestTemplateDepth = 5;
  constexpr TestFunctorSetSmallIteration::Data kTestInitialValues = {
      {0, 0, 0, 0, 0}, 0};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<0, kTestTemplateDepth, 1,
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
  for (std::size_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
}

TEST(ConstexprFor, PositiveNumberToZero) {
  constexpr long long kTestTemplateDepth = 5;
  constexpr TestFunctorSetSmallIteration::Data kTestInitialValues = {
      {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 0};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<kTestTemplateDepth, 0, -1,
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

  for (std::size_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
  ASSERT_EQ(kResult.last_i_value, 0);
}

TEST(ConstexprFor, ZeroToNegativeNumber) {
  constexpr long long kTestTemplateDepth = 5;
  constexpr TestFunctorAdd::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<0, -kTestTemplateDepth, -1,
                                  cex_for_loop::BoolExpressionFunctor_GT,
                                  TestFunctorAdd>(kTestInitialValues);
  ASSERT_EQ(0 - 1 - 2 - 3 - 4, kResult.kResult);
}

TEST(ConstexprFor, NegativeNumberToZero) {
  constexpr long long kTestTemplateDepth = 5;
  constexpr TestFunctorAdd::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<-kTestTemplateDepth + 1, 0, 1,
                                  cex_for_loop::BoolExpressionFunctor_LEQ,
                                  TestFunctorAdd>(kTestInitialValues);
  ASSERT_EQ(-4 - 3 - 2 - 1 - 0, kResult.kResult);
}

TEST(ConstexprFor, NegativeNumberToNegativeNumber) {
  constexpr TestFunctorSetForNegative2IncNegative2Start::Data
      kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<-2, -202, -2,
                                  cex_for_loop::BoolExpressionFunctor_GEQ,
                                  TestFunctorSetForNegative2IncNegative2Start>(
          kTestInitialValues);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kResult.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(kResult.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  std::array<int, 101> expected_i_tracker = {};
  for (int i = 0; i < 101; i++) {
    expected_i_tracker[i] = -2 * i - 2;
  }
  for (std::size_t i = 0; i < 101; i++) {
    ASSERT_EQ(kResult.i_tracker[i], expected_i_tracker[i]);
  }
}

TEST(ConstexprFor, NegativeNumberToPositiveNumberBy3s) {
  constexpr TestFunctorAdd::Data kTestInitialValues = {};

  constexpr auto kResult = cex_for_loop::constexpr_for<
      -15, 15, 3, cex_for_loop::BoolExpressionFunctor_LEQ, TestFunctorAdd>(
      kTestInitialValues);

  ASSERT_EQ(kResult.kResult, 0);
}

TEST(ConstexprFor, TemplateInstantiationDepth2000) {
  constexpr long long kTestTemplateDepth = 2000;
  constexpr TestFunctorSetLargeIterationIncBy3WithNegative1700Start::Data
      kTestInitialValues = {};

  constexpr auto kResult = cex_for_loop::constexpr_for<
      (-3 * kTestTemplateDepth) + 300, 300, 3,
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
  constexpr long long kTestTemplateDepth = 10'000;
  constexpr TestFunctorSetLargeIteration::Data kTestInitialValues = {};

  constexpr auto kResult =
      cex_for_loop::constexpr_for<1, kTestTemplateDepth, 1,
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
  for (std::size_t i = 0; i < kTestTemplateDepth; i++) {
    ASSERT_EQ(kResult.i_tracker[i], i);
  }
}
