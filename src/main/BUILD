load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        "//src/lib:graphLib",
        "//src/lib/loader:loaderLib",
        "//src/lib/algorithms:algorithmsLib",
    ],
    linkopts = ["-pthread"],
)
