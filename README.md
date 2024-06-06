# CEXForLoop

CEXForLoop is a header-only library for C++>14. It provides a for-loop mechanism
that is within a constexpr context meaning it can operate on constexpr data.

## Illustrative Examples

TODO

## Requirements

### Library Requirements

- C++ Version >= C++14

## Installing

1. Your compiler must be pointed at CEXForLoop (e.g.
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
