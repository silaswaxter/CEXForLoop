# CEXForLoop

![image depicting a full n-ary tree where n = 5 and the tree height is
3](nary_tree_cex_for_loop_expansion.png)

**CEXForLoop** is a powerful C++ header-only library designed to bring the
performance and flexibility of constexpr iteration to your code. Built with
advanced template metaprogramming techniques, it transforms traditional loop
iteration into a recursive n-ary tree structure, achieving remarkable
compile-time efficiency and unlocking new possibilities for constexpr
programming.

## Key Features

- **Requires C++14 or Higher**: CEXForLoop is fully compatible with modern C++
  standards, taking advantage of constexpr capabilities available from C++14
  onwards.
- **Constexpr Iteration Variable**: Iterate over arrays and other data
  structures in a fully constexpr manner, enabling complex compile-time
  computations and optimizations that would be impossible with standard runtime
  loops.
- **Optimized Template Depth**: By converting iteration into a recursive n-ary
  tree, CEXForLoop significantly reduces the required template depth, allowing
  it to scale efficiently. This approach achieves an O(log(n)) growth in
  template depth relative to iteration count, making it suitable for large
  compile-time loops that would otherwise hit compiler limits.
- **Extensive Parameter Passing**: Supports passing up to 50 non-template type
  parameters (i.e. constexpr values) to the loop body function, enabling highly
  customizable and flexible iteration logic. Parameters are passed to each
  successive iteration, allowing them to be modified along the way for dynamic
  and adaptable computations.

## A Simple Example

Here is a basic example (run-able with Godbolt here) in which a constexpr 
`std::array` of length 100 is created. A for loop from 0 to 199 by 1 is called
with CEXForLoop. Starting from the beginning of the array, the iteration 
variable is written to the array; when the "AppendIndex" surpasses the array
length, its set to the first index.

#include <array>
```cpp
#include <array>

#include <CEXForLoop/cex_for_loop.h>
#include <CEXForLoop/bool_expression_functors.h>

struct MyFunctorWithNTTP1 {
  struct NonConstexprData {
    std::array<std::size_t, 100> i_tracker;
  };

  using IType = std::size_t;
  using OutputType = std::tuple<NonConstexprData, std::size_t>;

  template <IType I, std::size_t AppendIndex>
  static constexpr OutputType func(NonConstexprData data) {
    std::get<AppendIndex>(data.i_tracker) = I;

    // if its the last index of the array go to the start
    constexpr std::size_t UpdatedAppendIndex =
            (AppendIndex == (data.i_tracker.size() - 1)) ?
            0 :
            AppendIndex + 1;

    return { data, UpdatedAppendIndex };
  };

  struct TypeEncodedInitialValue {
    static constexpr NonConstexprData
        // zero-initialize the array
        value = {{}};
  };

  using InitialNTTPs = cex_for_loop::TypeEncodedNTTPs<
        MyFunctorWithNTTP1>::template type<0>;
};

constexpr auto kData = cex_for_loop::func<
    MyFunctorWithNTTP1::IType, 0, 
    cex_for_loop::BoolExpressionFunctor_LT, 200,
    1, MyFunctorWithNTTP1, 
    MyFunctorWithNTTP1::InitialNTTPs,
    MyFunctorWithNTTP1::TypeEncodedInitialValue>();

static_assert(std::get<0>(kData.i_tracker) == 100, 
    "This should be true");
static_assert(std::get<99>(kData.i_tracker) == 199, 
    "This should be true");
```  

## Table of Contents

<!--toc:start-->
- [CEXForLoop](#cexforloop)
  - [Key Features](#key-features)
  - [Table of Contents](#table-of-contents)
  - [How to Use?](#how-to-use)
    - [Writing a Functor](#writing-a-functor)
    - [Calling CEXForLoop with a Functor](#calling-cexforloop-with-a-functor)
    - [Illustrative Examples](#illustrative-examples)
  - [FAQs and Debugging](#faqs-and-debugging)
  - [How it works](#how-it-works)
  - [Library Requirements](#library-requirements)
  - [Installing](#installing)
  - [Contributing](#contributing)
    - [Standards](#standards)
    - [Setup the Test Environment](#setup-the-test-environment)
      - [Prerequisites](#prerequisites)
      - [Commands](#commands)
  - [License](#license)
<!--toc:end-->

## How to Use?

1. **Include the Required Headers**:

   - Add the top-level header: `include/cex_for_loop.h`.
   - Include `include/bool_expression_functors.h` if using a standard boolean
     expression.

2. **Define a Functor for the Loop Body**:

   - This functor will serve as the internal body of your for loop.
   - See [Writing a Functor](#writing-a-functor) below for more details.

3. **Call the Constexpr For Loop Function**:
   - Pass the necessary arguments:
     - The type of the iteration variable.
     - Start, end, and increment values of the iteration.
     - The boolean expression to determine loop termination.
     - The previously defined body functor.
     - Initial values for user-provided non-template type parameters (NTTP) and
       any non-constexpr data.

### Writing a Functor

If this section is a bit too daunting to read, consider looking at the example
section first.

1. **Create a New Struct Definition**:

   - Name the struct something sensible that reflects its purpose.

2. **Define a Struct Named `NonConstexprData` Inside Your Functor**:

   - This struct holds the data the for loop operates on. Although the data is
     **not constexpr** within the loop body, the overall for loop returns this
     type as a constexpr value. Each iteration returns a tuple containing a
     constexpr value of this type—refer to step 4.

3. **(Optional) Create an Alias for the Iteration Variable Type**:

   - This allows you to adhere to the single-source-of-truth principle by
     defining the type in one place, reducing repetition and improving
     maintainability.

4. **Define an Alias Called `OutputType`**:

   - Create an alias as follows:

     ```cpp
     using OutputType = std::tuple<NonConstexprData, /*your NTTP types in order here*/>
     ```

     This is the return value of your functor function, allowing you and
     (`CEXForLoop` internals) to capture any modifications made to
     `NonConstexprData` and the NTTPs.

5. **Define a Templated Function**:

   - The function template must have at least one parameter, the type of which
     should match what is passed to the `CEXForLoop` interface at the call site.
     If you defined an alias in step 3, use it to avoid duplicate information.
   - Up to 50 NTTPs can follow the iterated variable as long as their types are
     listed in order in the `OutputType` alias.
   - Define the function with the signature:

     ```cpp
     static constexpr OutputType func(NonConstexprData input_data){
       // your implementation...
     }
     ```

     - Its helpful when defining the function, to consider it in the context of
       a **functional programming paradigm**.

6. **(Optional) Define the Initial Value Encoded Type Inside the Functor**:

   - _Context:_ `CEXForLoop` requires an initial `NonConstexprData` value to be
     passed to the loop on the first iteration. Since the `NonConstexprData`
     value passed to your `func` must be constexpr (from within `CEXForLoop`'s
     implementation), the value needs to be encoded as a type and passed as a
     template parameter. (In C++14, user-defined NTTPs are not allowed, so
     encoding your initial value as a type is the workaround.)
   - _Optional:_ If your initial value is constant, define the encoded struct
     type within the functor for better locality and maintainability.

### Calling CEXForLoop with a Functor

The interface for `CEXForLoop` is a constexpr templated function that takes no
function parameters and returns the `NonConstexprData` value from the final
iteration. (Note that the `NonConstexprData` name comes from the fact that the
data is _not constexpr_ from within the for loop body--its result, however, is).
The template parameter order mimics a traditional for loop:

1. The type of the iteration variable.
2. The initial value of the iteration variable
3. The boolean expression functor (type encoded function) that stops further
   iteration; the function inside the boolean functor takes two values, the
   current iteration value (`rhs` parameter) and the end value (`lhs`
   parameter)--see next step. Standard boolean expression functors are provided
   inside `include/CEXForLoop/bool_expression_functors.h`, however custom
   boolean functors of the same signature are allowed.
4. The end value for the iteration variable which is used as the left-hand side
   parameter in the boolean expression--see prior step.
5. The increment value for the iteration variable, ie the value that is added to
   the iteration variable at the end of each iteration.
6. The functor type that makes up the body of the for loop.
7. The doubly type encoded (sounds intimidating but you won't have to worry
   about it) initial values for the user NTTPs. Required regardless of the
   number of user NTTPs, this parameter is:

   ```cpp
   std::tuple<
     /*for the nth user NTTP in user NTTP count:*/
     std::integral_constant</*nth user NTTP type*/, /*nth user NTTP initial value*/>
   >
   ```

   This is **gross**! So, a helper was created that allows you to pass the
   constexpr values you want, and it will encode them correctly using the
   `BodyFunctor` `OutputType`:

   - _For 0 user NTTPs:_

     ```cpp
     cex_for_loop::TypeEncodedNTTPs<Passes0NTTPsFunctor>::type
     ```

   - _For 1 or more user NTTPs:_

     ```cpp
     cex_for_loop::TypeEncodedNTTPs<Passes0NTTPsFunctor>::template type<
         /*comma separated initial values in order*/>
     ```

8. The type encoded initial value for `NonConstexprData`. See the last step of
   [Writing a Functor](#writing-a-functor) for details.

### Illustrative Examples

Usage is simple. This following example code is **live** at
[this compiler explorer](https://godbolt.org/z/5W6r4r5nG). See
`test/constexpr_for_test.cc` for more examples.

First, we include the necessary headers:

```cpp
#include "include/CEXForLoop/cex_for_loop.h"
#include "include/CEXForLoop/bool_expression_functors.h"
```

Then we define a functor that describes the for loop we are going to call:

```cpp
struct MyFunctorWithNTTP1 {
  // This is the data that will be returned by this functor. Its modifiable in
  // the context of this functor.
  struct NonConstexprData {
    int foo;
    char bar;
    std::array<std::size_t, 100> arr;
  };

  // The type for I
  using IType = std::size_t;
  // The output type for func. The first element is the output data--i.e. the
  // result of whatever work was done on the input data. The remaining elements
  // are the template nontype parameters that will be passed to func on each
  // call. These parameters are constexpr by definition.
  using OutputType = std::tuple<NonConstexprData, std::size_t>;

  template <IType I, std::size_t AppendIndex>
  static constexpr OutputType func(NonConstexprData input_data) {
    NonConstexprData output_data = input_data;
    std::get<AppendIndex>(output_data.arr) = I;

    constexpr std::size_t UpdatedAppendIndex =
            (AppendIndex == (output_data.arr.size() - 1)) ?
            0 :
            AppendIndex + 1;

    OutputType return_value = {output_data, UpdatedAppendIndex};
    return return_value;
  };

  struct TestInitialDataTypeEncoded {
    static constexpr NonConstexprData
        // NOLINTNEXTLINE(readability-identifier-naming)
        value = {4, 3, {}};
  };
};
```

Next we call the `CEXForLoop` public interface function and capture its result:

```cpp
constexpr auto kData = cex_for_loop::func<
    MyFunctorWithNTTP1::IType, 0, cex_for_loop::BoolExpressionFunctor_LT, 200,
    1, MyFunctorWithNTTP1,
    cex_for_loop::TypeEncodedNTTPs<MyFunctorWithNTTP1>::template type<0>,
    MyFunctorWithNTTP1::TestInitialDataTypeEncoded>();
```

Finally, we can access the constexpr resultant data:

```cpp
constexpr std::array<int, std::get<99>(kData.arr)> kExample = {};
```

## FAQs and Debugging

**Q: My function call failed and the compiler error is hard to read; What do I
do?**  
A: While writing the library I (Silas) ran into this issue many times. The
strategy that works best is to search through the compilation error from the top
down for the word `error`. This can happen from a variety of issues, most
commonly:

- A static assert is failing from inside one of the iterations--eg accessing an
  out of bounds index in an `std::array`.
  - Check that your using the correct boolean expression.
- There is a mismatch in user NTTPs at:
  - call-site initial values
  - `OutputType` definition
  - `func` template list
  - return value from the function

**Q: What is the required template depth for \_\_ number iterations?**  
A: You can expect to get about 500 iterations for 100 templates deep and about
40,000 iterations for 150 templates deep. An approximate (recorded with a
slightly diffferent implementation that is off by a couple of templates) graph
can be found [here](https://www.desmos.com/calculator/f3sedir5ez).

> [!NOTE]
>
> This only matters if your calling `CEXForLoop` from within a context that is
> already of hundreds of templates deep or if your compiler's template depth is
> set lower (gcc and clang default 900).

**Q: Why is my compile time so long?** A: If your iteration count is at all
significant (>1000) expect to wait at least 5 seconds. In short, the compiler is
doing a lot. Each iteration is at least a function call and template
instantiation.

## How it works

<!-- Insert Blog/Article Link once complete -->

## Library Requirements

- C++ Version >= C++14

## Installing

Your compiler must be pointed at the installation location of `CEXForLoop` (eg
`-I<location-of-this-library>/include/CEXForLoop/`)

## Contributing

Use this GitHub repo for issues, PRs, etc. The following subsections describe
collaboration processes in terms of writing code and project direction.

1. Enable custom git hooks by running
   `git config --local include.path ../.gitconfig`.
   - These git hooks will run the python generator scripts automatically on
     pre-commit to ensure the generated files are in sync with the generation
     code

### Standards

This project follows these standards:

- [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
  - `clang-format` formatting (see `.clang-format` for config details)
  - `clang-tidy` linting (see `.clang-tidy` for config details)

### Setup the Test Environment

#### Prerequisites

- Bazel (preferably [Bazelisk](https://github.com/bazelbuild/bazelisk))
  installed.
  - Bazelisk installs and executes bazel for you; it manages the version of
    bazel installed--important for truly reproducible builds across machines.
    LittlePP "lives at the head" in terms of bazel version so by using Bazelisk,
    the latest version of bazel will be used whenever its invoked.

#### Commands

- All tests are run with `bazelisk test --test_output=all //test:all`
- `compile_commands.json` can be generated by running
  `bazelisk run //:refresh_compile_commands`
  - This file is consumed by tools such as `clang-tidy`. Read more
    [here](https://github.com/hedronvision/bazel-compile-commands-extractor)

## License

Distributed under the [The MIT License](https://opensource.org/license/mit/).
