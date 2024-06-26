#include <gtest/gtest.h>

#include <array>

#include "include/bool_expression_functors.h"
#include "include/cex_for_loop.h"

struct TestFunctorSet_SmallIteration {
  struct Data {
    std::array<int, 250> i_tracker;
    int last_i_value;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<i>(input_data.i_tracker) = i;
    input_data.last_i_value = i;
    return input_data;
  };
};

struct TestFunctorAdd {
  struct Data {
    long long result;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    input_data.result += i;
    return input_data;
  };
};

struct TestFunctorSet_ForNegative2IncNegative2Start {
  struct Data {
    std::array<int, 200> i_tracker;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<(-1 * i / 2) - 1>(input_data.i_tracker) = i;
    return input_data;
  };
};

struct TestFunctorSet_LargeIterationIncBy3WithNegative1700Start {
  struct Data {
    std::array<int, 1'000'000> i_tracker;
    int last_i_value;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<(i - 300) / -3>(input_data.i_tracker) = i;
    input_data.last_i_value = i;
    return input_data;
  };
};

struct TestFunctorSet_LargeIteration {
  struct Data {
    std::array<int, 1'000'000> i_tracker;
    int last_i_value;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<i>(input_data.i_tracker) = i;
    input_data.last_i_value = i;
    return input_data;
  };
};

TEST(ConstexprFor, ZeroToPositiveNumber) {
  constexpr long long test_template_depth = 5;
  constexpr TestFunctorSet_SmallIteration::Data test_initial_values = {
      {0, 0, 0, 0, 0}, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_template_depth, 1,
                                CEXForLoop::BoolExpressionFunctor_LT,
                                TestFunctorSet_SmallIteration>(
          test_initial_values);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < result.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(result.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(result.last_i_value, test_template_depth - 1);
  for (std::size_t i = 0; i < test_template_depth; i++) {
    ASSERT_EQ(result.i_tracker[i], i);
  }
}

TEST(ConstexprFor, PositiveNumberToZero) {
  constexpr long long test_template_depth = 5;
  constexpr TestFunctorSet_SmallIteration::Data test_initial_values = {
      {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<test_template_depth, 0, -1,
                                CEXForLoop::BoolExpressionFunctor_GEQ,
                                TestFunctorSet_SmallIteration>(
          test_initial_values);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < result.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(result.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  for (std::size_t i = 0; i < test_template_depth; i++) {
    ASSERT_EQ(result.i_tracker[i], i);
  }
  ASSERT_EQ(result.last_i_value, 0);
}

TEST(ConstexprFor, ZeroToNegativeNumber) {
  constexpr long long test_template_depth = 5;
  constexpr TestFunctorAdd::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, -test_template_depth, -1,
                                CEXForLoop::BoolExpressionFunctor_GT,
                                TestFunctorAdd>(test_initial_values);
  ASSERT_EQ(0 - 1 - 2 - 3 - 4, result.result);
}

TEST(ConstexprFor, NegativeNumberToZero) {
  constexpr long long test_template_depth = 5;
  constexpr TestFunctorAdd::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<-test_template_depth + 1, 0, 1,
                                CEXForLoop::BoolExpressionFunctor_LEQ,
                                TestFunctorAdd>(test_initial_values);
  ASSERT_EQ(-4 - 3 - 2 - 1 - 0, result.result);
}

TEST(ConstexprFor, NegativeNumberToNegativeNumber) {
  constexpr TestFunctorSet_ForNegative2IncNegative2Start::Data
      test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<-2, -202, -2,
                                CEXForLoop::BoolExpressionFunctor_GEQ,
                                TestFunctorSet_ForNegative2IncNegative2Start>(
          test_initial_values);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < result.i_tracker.size(); i++) {
  //   print_string.append(std::to_string(result.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  std::array<int, 101> expected_i_tracker = {};
  for (std::size_t i = 0; i < 101; i++) {
    expected_i_tracker[i] = -2 * i - 2;
  }
  for (std::size_t i = 0; i < 101; i++) {
    ASSERT_EQ(result.i_tracker[i], expected_i_tracker[i]);
  }
}

TEST(ConstexprFor, NegativeNumberToPositiveNumberBy3s) {
  constexpr TestFunctorAdd::Data test_initial_values = {};

  constexpr auto result = CEXForLoop::constexpr_for<
      -15, 15, 3, CEXForLoop::BoolExpressionFunctor_LEQ, TestFunctorAdd>(
      test_initial_values);

  ASSERT_EQ(result.result, 0);
}

TEST(ConstexprFor, TemplateInstantiationDepth2000) {
  constexpr long long test_template_depth = 2000;
  constexpr TestFunctorSet_LargeIterationIncBy3WithNegative1700Start::Data
      test_initial_values = {};

  constexpr auto result = CEXForLoop::constexpr_for<
      (-3 * test_template_depth) + 300, 300, 3,
      CEXForLoop::BoolExpressionFunctor_LEQ,
      TestFunctorSet_LargeIterationIncBy3WithNegative1700Start>(
      test_initial_values);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < test_template_depth; i++) {
  //   print_string.append(std::to_string(result.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(result.last_i_value, 300);
}

TEST(ConstexprFor, TemplateInstantiationDepth10000) {
  constexpr long long test_template_depth = 10'000;
  constexpr TestFunctorSet_LargeIteration::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<1, test_template_depth, 1,
                                CEXForLoop::BoolExpressionFunctor_LEQ,
                                TestFunctorSet_LargeIteration>(
          test_initial_values);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < test_template_depth; i++) {
  //   print_string.append(std::to_string(result.i_tracker[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  ASSERT_EQ(result.last_i_value, test_template_depth);
  for (std::size_t i = 0; i < test_template_depth; i++) {
    ASSERT_EQ(result.i_tracker[i], i);
  }
}
