load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "progressbarlib",
    hdrs = ["progressbar.h"],
)

cc_binary(
    name = "sample",
    srcs = ["main.cc"],
    deps = [
        ":progressbarlib",
    ],
)
