#include <array>
#include <gtest/gtest.h>

#include "include/cex_for_loop.h"

struct TestFunctor {
  // typedef std::tuple<int, char> FunctorData;
  struct Data {
    std::array<int, 10> i_tracker;
    int foo;
  };

  template <std::size_t i>
  static constexpr Data func(Data input_data) {
    input_data.foo = i;
    std::get<i>(input_data.i_tracker) = i;
    return input_data;
  };
};

TEST(ConstexprFor, basic_iteration) {
  constexpr TestFunctor::Data test_initial_values = {0, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, 5, 1, TestFunctor>(test_initial_values);

  ASSERT_EQ(result.foo, 4);
  ASSERT_EQ(std::get<0>(result.i_tracker), 0);
  ASSERT_EQ(std::get<1>(result.i_tracker), 1);
  ASSERT_EQ(std::get<2>(result.i_tracker), 2);
  ASSERT_EQ(std::get<3>(result.i_tracker), 3);
}
