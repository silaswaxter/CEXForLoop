#include <gtest/gtest.h>

#include <array>

#include "include/cex_for_loop.h"

struct TestFunctor {
  // typedef std::tuple<int, char> FunctorData;
  struct Data {
    std::array<int, 5> i_tracker;
    int foo;
  };

  template <long long i>
  static constexpr Data func(Data input_data) {
    std::get<i>(input_data.i_tracker) += i;
    input_data.foo = i;
    return input_data;
  };
};

TEST(ConstexprFor, ZeroToNMinusOne) {
  constexpr TestFunctor::Data test_initial_values = {{0, 0, 0, 0, 0}, 0};

  constexpr auto result =
      CEXForLoop::constexpr_for<0, test_initial_values.i_tracker.size(), 1,
                                TestFunctor>(test_initial_values);

  constexpr std::array<int, 5> expected_i_tracker{0, 1, 2, 3, 4};
  for(int i = 0; i < expected_i_tracker.size(); i++){
    ASSERT_EQ(result.i_tracker[i], expected_i_tracker[i]);
  }
  ASSERT_EQ(result.foo, 4);
}
