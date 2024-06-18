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

TEST(ConstexprFor, ZeroToNMinusOne) {
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

TEST(ConstexprFor, NMinusOneToZero) {
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

TEST(ConstexprFor, TemplateInstantiationDepth150) {
  constexpr long long test_template_depth = 150;
  constexpr TestFunctorSet_SmallIteration::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_template_depth, 1,
                                CEXForLoop::BoolExpressionFunctor_LEQ,
                                TestFunctorSet_SmallIteration>(
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

TEST(ConstexprFor, TemplateInstantiationDepth2000) {
  constexpr long long test_template_depth = 2000;
  constexpr TestFunctorSet_LargeIteration::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_template_depth, 1,
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

TEST(ConstexprFor, TemplateInstantiationDepth10000) {
  constexpr long long test_template_depth = 10000;
  constexpr TestFunctorSet_LargeIteration::Data test_initial_values = {};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_template_depth, 1,
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
