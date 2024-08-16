load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")

cc_library(
    name = "CEXForLoop",
    srcs = glob(["include/CEXForLoop/impl/*.h"]),
    hdrs = [
        "include/CEXForLoop/bool_expression_functors.h",
        "include/CEXForLoop/cex_for_loop.h",
    ],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

# Generate compile_commands.json
# note: This is not an ideal solution; it violates single-source-of-truth
#       because targets and their flags must be duplicated here. Additionally,
#       it requires the developer to specifically run this bazel target in order
#       to update. These problems could be solved if this was a service
#       subscribed to bazel build events.
refresh_compile_commands(
    name = "refresh_compile_commands",

    # Specify the targets of interest; specify a dict of targets and any flags
    # required to build them. No need to add flags already in .bazelrc. They're
    # automatically picked up. If you don't need flags, a list of targets is
    # also okay, as is a single target string. Wildcard patterns, like //... for
    # everything, *are* allowed here, just like a build. As are additional
    # targets (+) and subtractions (-), like in bazel query
    # https://docs.bazel.build/versions/main/query.html#expressions
    targets = {
        "//test:all": "--config=clang_config",
    },
)
