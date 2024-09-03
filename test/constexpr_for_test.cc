#include <CEXForLoop/bool_expression_functors.h>
#include <CEXForLoop/cex_for_loop.h>
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

static_assert(__cplusplus == 201402L,
              "Ensure your testing with the oldest supported c++ version.");

struct Passes0NTTPsFunctor {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    int foo;
    char bar;
    std::array<std::size_t, 1000> arr;
  };

  // The type for I
  using IType = std::size_t;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType = std::tuple<NonConstexprData>;

  template <IType I>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;
    std::get<I>(output_data.arr) = I;

    OutputType return_value = {output_data};
    return return_value;
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {4, 3, {}};
  };
};

TEST(ConstexprFor, NTTPCount0InitilizesAndReturnsData) {
  // this number is high because standard implementation for NTTP count = 0,
  // will be O(n) instead of O(log(n)) for required template depth versus
  // iteration count
  constexpr std::size_t kBoundaryValue = 1000;

  constexpr auto kData = cex_for_loop::func<
      Passes0NTTPsFunctor::IType, 0, kBoundaryValue, 1,
      cex_for_loop::BoolExpressionFunctor_LT, Passes0NTTPsFunctor,
      cex_for_loop::TypeEncodedNTTPs<Passes0NTTPsFunctor>::type,
      Passes0NTTPsFunctor::TestInitialDataTypeEncoded>();

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kData.arr.size(); i++) {
  //   print_string.append(std::to_string(kData.arr[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  // tests that NTTP passing works and that output_data from (n-1)th
  // iteration
  // is input_data for nth iteration
  ASSERT_EQ(0, std::get<0>(kData.arr));
  ASSERT_EQ(1, std::get<1>(kData.arr));
  ASSERT_EQ(kBoundaryValue - 1, std::get<kBoundaryValue - 1>(kData.arr));

  // test that initial data is pulled from the correct source and that
  // unmodified data persists
  ASSERT_EQ(4, kData.foo);
  ASSERT_EQ(3, kData.bar);
}

struct Passes1NTTPsFunctor {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    int foo;
    char bar;
    std::array<std::size_t, 1000> arr;
  };

  // The type for I
  using IType = std::size_t;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType = std::tuple<NonConstexprData, std::size_t>;

  template <IType I, std::size_t A>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;
    std::get<I>(output_data.arr) = I;

    OutputType return_value = {output_data, A};
    return return_value;
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {4, 3, {}};
  };
};

TEST(ConstexprFor, NTTPCount1InitilizesAndReturnsData) {
  constexpr std::size_t kBoundaryValue = 1000;

  constexpr auto kData = cex_for_loop::func<
      Passes1NTTPsFunctor::IType, 0, kBoundaryValue, 1,
      cex_for_loop::BoolExpressionFunctor_LT, Passes1NTTPsFunctor,
      cex_for_loop::TypeEncodedNTTPs<Passes1NTTPsFunctor>::template type<0>,
      Passes1NTTPsFunctor::TestInitialDataTypeEncoded>();

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kData.arr.size(); i++) {
  //   print_string.append(std::to_string(kData.arr[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  // tests that NTTP passing works and that output_data from (n-1)th
  // iteration
  // is input_data for nth iteration
  ASSERT_EQ(0, std::get<0>(kData.arr));
  ASSERT_EQ(1, std::get<1>(kData.arr));
  ASSERT_EQ(kBoundaryValue - 1, std::get<kBoundaryValue - 1>(kData.arr));

  // test that initial data is pulled from the correct source and that
  // unmodified data persists
  ASSERT_EQ(4, kData.foo);
  ASSERT_EQ(3, kData.bar);
}

struct Passes5NTTPsFunctor {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    int foo;
    char bar;
  };

  // The type for I
  using IType = std::size_t;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType =
      std::tuple<NonConstexprData, int64_t, char, unsigned long, uint32_t, int>;

  template <IType I, int64_t NTTP0, char NTTP1, unsigned long NTTP2,
            uint32_t NTTP3, int NTTP4>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;

    output_data.foo = NTTP4;
    output_data.bar = 0;

    OutputType return_value = {output_data, NTTP0, NTTP1,
                               NTTP2,       NTTP3, NTTP4 + 1};
    return return_value;
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {4, 3};
  };
};

TEST(ConstexprFor, Passes5NTTPs) {
  constexpr std::size_t kBoundaryValue = 1000;

  constexpr auto kData = cex_for_loop::func<
      Passes5NTTPsFunctor::IType, 0, kBoundaryValue, 1,
      cex_for_loop::BoolExpressionFunctor_LT, Passes5NTTPsFunctor,
      cex_for_loop::TypeEncodedNTTPs<Passes5NTTPsFunctor>::type<0, 0, 0, 0, 0>,
      Passes5NTTPsFunctor::TestInitialDataTypeEncoded>();

  // test that NTTPs value persists from prior iteration
  ASSERT_EQ(kBoundaryValue - 1, kData.foo);
  ASSERT_EQ(0, kData.bar);
}

struct CountsDownBy3Functor {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    int foo;
    char bar;
    std::array<int, 1001> arr;
  };

  // The type for I
  using IType = int;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType = std::tuple<NonConstexprData>;

  template <IType I>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;
    std::get<(I / 3)>(output_data.arr) = I;

    OutputType return_value = {output_data};
    return return_value;
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {4, 3, {}};
  };
};

TEST(ConstexprFor, Passes0NTTPsCountDownBy3WithGEQ) {
  constexpr int kBoundaryValue = 3000;

  constexpr auto kData = cex_for_loop::func<
      CountsDownBy3Functor::IType, kBoundaryValue, 0, -3,
      cex_for_loop::BoolExpressionFunctor_GEQ, CountsDownBy3Functor,
      cex_for_loop::TypeEncodedNTTPs<CountsDownBy3Functor>::type,
      CountsDownBy3Functor::TestInitialDataTypeEncoded>();

  // ASSERT_EQ(0, kData);

  // Uncomment to print i values in order
  // -----
  // std::string print_string;
  // for (int i = 0; i < kData.arr.size(); i++) {
  //   print_string.append(std::to_string(kData.arr[i]) + ", ");
  // }
  // ADD_FAILURE() << print_string;

  // tests that NTTP passing works and that output_data from (n-1)th
  // iteration is input_data for nth iteration
  ASSERT_EQ(0, std::get<0>(kData.arr));
  ASSERT_EQ(3, std::get<1>(kData.arr));
  ASSERT_EQ(3000, std::get<1000>(kData.arr));

  // test that initial data is pulled from the correct source and that
  // unmodified data persists
  ASSERT_EQ(4, kData.foo);
  ASSERT_EQ(3, kData.bar);
}

struct NoIterationTestFunctor {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    bool is_func_called;
  };

  // The type for I
  using IType = std::size_t;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType = std::tuple<NonConstexprData>;

  template <IType I>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;
    output_data.is_func_called = true;

    return {output_data};
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {false};
  };
};

TEST(ConstexprFor, NTTPCount0NoIterationReturnsWithoutExecutingFunc) {
  constexpr auto kData = cex_for_loop::func<
      NoIterationTestFunctor::IType, 0, 0, 1,
      cex_for_loop::BoolExpressionFunctor_LT, NoIterationTestFunctor,
      cex_for_loop::TypeEncodedNTTPs<NoIterationTestFunctor>::type,
      NoIterationTestFunctor::TestInitialDataTypeEncoded>();

  ASSERT_FALSE(kData.is_func_called);
}
