# CEXForLoop

CEXForLoop is a header-only library for C++>=14. It provides a constexpr
for-loop where the iteration variable is also constexpr. The library converts
iteration to recursion. The library subverts the compiler enforced template
instantiation depth so that iteration lengths can be larger than this limit;
expansions greater than user-override-able `CEX_FOR_LOOP_MAX_TEMPLATE_DEPTH`
(default = 100) take place along an N-tree where each node linearly recurses as
much as possible without violating the maximum template depth limit.

## Illustrative Examples

Usage is simple.

1. Include the top-level headers, `include/constexpr.h` and
   `include/bool_expression_functors.h`.
2. Define a function that will make up the body/statement of the for loop. There
   are some constraints on this definition like it must be within a struct known
   as a functor. An example is shown below:

```cpp
struct MyFunctor {
  // Must be called "Data"
  struct Data {
    // CUSTOM
    std::array<uint8_t, 10> foo;
    uint8_t bar;
  };

  // Must be called "func" and take this form
  template <long long i>
  static constexpr Data func(Data input_data) {
    // CUSTOM
    std::get<i>(input_data.foo) = std::get<i>(input_data.foo) + input_data.bar;
    return input_data;
  };
};
```

> [!NOTE] These are all of the constraints. This list is exhaustive, but if you
> copy and paste the definition and change only the `Data` and `func` internals
> you don't need to worry about these.
>
> - The function must be wrapped in a structure
> - The function must be named `func`
> - The functor (i.e. encapsulating struct) must also define a struct called
>   `Data`.
> - The function must be templated on **only** a `long long` variable (e.g.
>   `i`).
> - The function must only take and return the previously defined `Data` struct

3. Call the constexpr for loop. The iteration variable begins at the 1st
   template parameter and is incremented by the 3rd template parameter;
   iteration ends when the boolean expression functor (the 4th template
   parameter) returns false while comparing the iteration variable to the 2nd
   template parameter. The 5th template parameter is your custom functor type.
   The function parameter is the initial data of your custom functor `Data`
   type. Here is an example.

```cpp
constexpr MyFunctor::Data input_data = { {1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 12};
constexpr MyFunctor::Data result =
    CEXForLoop::constexpr_for<0, input_data.foo.size(), 1,
                              CEXForLoop::BoolExpressionFunctor_LT,
                              MyFunctor>(input_data);
```

> [!NOTE] All the standard boolean expressions are already defined in
> `include/bool_expression_functors.h`.

## Requirements

### Library Requirements

- C++ Version >= C++14

## Installing

Your compiler must be pointed at CEXForLoop (e.g.
`-I<location-of-this-library>/include`)

## Contributing

Use this GitHub repo for issues, PRs, etc. The following subsections describe
collaboration processes in terms of writing code and project direction.

### Standards

Some standards/best practices that are adhered to on a best-effort basis.

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
  - `clang-format` formatting (config file tracked)
- [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
  - `clang-tidy` linting (config file tracked)

### Setup the Test Environment

#### Prerequisites

- Unix Machine (see note below)
- Clang 16 Installed (see note below)
- Bazel (preferably [Bazelisk](https://github.com/bazelbuild/bazelisk))
  installed
  - Bazelisk installs and executes bazel for you; it manages the version of
    bazel installed--important for truly reproducible builds across machines.
    LittlePP "lives at the head" in terms of bazel version so by using Bazelisk,
    the latest version of bazel will be used whenever its invoked.

_note: The build system used for testing the library is Bazel. Since, at the
time of writing, Bazel's default C++ toolchain is for c++2011, and AFAIK there
isn't a way to override this without resorting to the `copts` in BUILD targets,
a basic c++ toolchain is constructed; currently, the hermeticity is violated
since this toolchain depends on clang 16 being installed on a Unix machine--my
setup. This should be fixed, but I didn't want to waste time making the build
system generic if I'm the only one using it._

#### Commands

- All tests are run with
  `bazelisk test --config=clang_config --test_output=all //test:all`
- `compile_commands.json` is generated with
  `bazelisk run --config=clang_config //:refresh_compile_commands`
  - This file is consumed by tools such as `clang-tidy`. Read more
    [here](https://github.com/hedronvision/bazel-compile-commands-extractor)

## License

Distributed under the [The MIT License](https://opensource.org/license/mit/).
