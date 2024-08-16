import sys
import os

def generate_header_file(file_path, max_iteration_count):
    file_name = os.path.basename(file_path)
    header_guard = file_name.upper().replace(".", "_")

    with open(file_path, "w") as f:
        # Write the header guard
        f.write(f"#ifndef {header_guard}\n")
        f.write(f"#define {header_guard}\n\n")

        # Write the includes
        f.write("#include <cstddef>\n")
        f.write("#include <tuple>\n")
        f.write("#include <type_traits>\n\n")
        f.write("#include \"../bool_expression_functors.h\"\n")

        # Write the namespaces
        f.write("namespace cex_for_loop {\n")
        f.write("namespace impl {\n\n")

        # Write the struct and its content

        f.write("template <std::size_t N, typename... Ts>\n")
        f.write("using NthTypeOf = typename std::tuple_element<N, std::tuple<Ts...>>::type;\n\n")

        f.write("template <typename IType, IType Start, IType End, IType Inc,\n")
        f.write("          typename BoolExpressionFunctor, typename BodyFunctor>\n")
        f.write("struct LinearCEXForFunctor {\n")
        f.write("  using FunctorData = typename BodyFunctor::NonConstexprData;\n")
        f.write("  using FunctorOutputType = typename BodyFunctor::OutputType;\n\n")

        f.write("  static constexpr IType ceil_division(IType num, IType den) {\n")
        f.write("    return (num + (num % den)) / den;\n")
        f.write("  }\n\n")

        f.write("  static constexpr IType floor_division(IType num, IType den) {\n")
        f.write("    return (num - (num % den)) / den;\n")
        f.write("  }\n\n")

        f.write("  template <typename LocalBoolExpressionFunctor = BoolExpressionFunctor>\n")
        f.write("  static constexpr auto GetIterationCount()\n")
        f.write("      -> std::enable_if_t<\n")
        f.write("          (std::is_same<LocalBoolExpressionFunctor,\n")
        f.write("                        cex_for_loop::BoolExpressionFunctor_LT>::value) ||\n")
        f.write("              (std::is_same<LocalBoolExpressionFunctor,\n")
        f.write("                            cex_for_loop::BoolExpressionFunctor_GT>::value),\n")
        f.write("          std::size_t> {\n")
        f.write("    return floor_division((End - Start), Inc);\n")
        f.write("  }\n\n")

        f.write("  template <typename LocalBoolExpressionFunctor = BoolExpressionFunctor>\n")
        f.write("  static constexpr auto GetIterationCount()\n")
        f.write("      -> std::enable_if_t<\n")
        f.write("          (std::is_same<LocalBoolExpressionFunctor,\n")
        f.write("                        cex_for_loop::BoolExpressionFunctor_LEQ>::value) ||\n")
        f.write("              (std::is_same<LocalBoolExpressionFunctor,\n")
        f.write("                            cex_for_loop::BoolExpressionFunctor_GEQ>::value),\n")
        f.write("          std::size_t> {\n")
        f.write("    return ceil_division((End - Start), Inc);\n")
        f.write("  }\n\n")

        for i in range(max_iteration_count):
            f.write("  template <typename InitialDataFunctor, typename... TypeEncodedFuncNTTPs>\n")
            f.write("  // NOLINTNEXTLINE(readability-function-cognitive-complexity)\n")
            f.write("  static constexpr auto func()\n")
            f.write("      -> std::enable_if_t<\n")
            f.write("          (std::tuple_size<std::tuple<TypeEncodedFuncNTTPs...>>::value == 1) &&\n")
            f.write(f"              (GetIterationCount() == {i}),\n")
            f.write("          FunctorOutputType> {\n")

            # Write the pattern
            for j in range(i + 1):
                f.write(f"    constexpr IType kI{j} = ")
                
                if j == 0:
                    f.write("Start;\n")
                    f.write(f"    constexpr auto kOutput{j} = BodyFunctor::template func<\n")
                    f.write(f"        kI{j}, NthTypeOf<0, TypeEncodedFuncNTTPs...>::value>(\n")
                    f.write("        InitialDataFunctor::value);\n")
                else:
                    f.write(f"kI{j-1} + Inc;\n")
                    f.write(f"    constexpr auto kOutput{j} =\n")
                    f.write(f"        BodyFunctor::template func<kI{j}, std::get<1>(kOutput{j-1})>(\n")
                    f.write(f"            std::get<0>(kOutput{j-1}));\n")
                
                if j == i:
                    f.write(f"    return kOutput{j};\n")
                    if i == (max_iteration_count - 1):
                        f.write("  }\n")
                    else:
                        f.write("  }\n\n")

        # Close the struct, namespaces, and header guard
        f.write("};\n\n")  # Close LinearCEXForFunctor
        f.write("}  // namespace impl\n")
        f.write("}  // namespace cex_for_loop\n\n")
        f.write(f"#endif  // {header_guard}\n")

# Process CLI passed args and make sure they are valid
passed_max_iteration_count = sys.argv[1]
assert(passed_max_iteration_count.isdigit())
passed_max_iteration_count = int(passed_max_iteration_count)

gen_file_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "linear_cex_for_loop.h")

generate_header_file(gen_file_path, passed_max_iteration_count)
