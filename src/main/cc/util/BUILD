cc_library(
    name = "util",
    hdrs = glob(["*.h"]),
    srcs = glob(["*.cc"]),
    visibility = ["//visibility:public"],
    copts = ["-isystemsrc/main/cc"],
    linkopts = [
        "-std=c++11",
        "-Isrc/main/cc",
    ],
)