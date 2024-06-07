#include <gtest/gtest.h>

#include <array>

#include "include/bool_expression_functors.h"
#include "include/cex_for_loop.h"

struct TestFunctorAdd {
  struct Data {
    std::array<int, 5> i_tracker;
    int last_i_value;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<i>(input_data.i_tracker) += i;
    input_data.last_i_value = i;
    return input_data;
  };
};

struct TestFunctorSet {
  struct Data {
    std::array<int, 5> i_tracker;
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
  constexpr TestFunctorAdd::Data test_initial_values = {{0, 0, 0, 0, 0}, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_initial_values.i_tracker.size(), 1,
                                CEXForLoop::BoolExpressionFunctor_LT,
                                TestFunctorAdd>(test_initial_values);

  constexpr std::array<int, 5> expected_i_tracker{0, 1, 2, 3, 4};
  for (std::size_t i = 0; i < expected_i_tracker.size(); i++) {
    ASSERT_EQ(result.i_tracker[i], expected_i_tracker[i]);
  }
  ASSERT_EQ(result.last_i_value, 4);
}

TEST(ConstexprFor, NMinusOneToZero) {
  constexpr TestFunctorSet::Data test_initial_values = {
      {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<test_initial_values.i_tracker.size() - 1, 0, -1,
                                CEXForLoop::BoolExpressionFunctor_GEQ,
                                TestFunctorSet>(test_initial_values);

  constexpr std::array<int, 5> expected_i_tracker{0, 1, 2, 3, 4};
  for (std::size_t i = 0; i < expected_i_tracker.size(); i++) {
    ASSERT_EQ(result.i_tracker[i], expected_i_tracker[i]);
  }
  ASSERT_EQ(result.last_i_value, 0);
}
