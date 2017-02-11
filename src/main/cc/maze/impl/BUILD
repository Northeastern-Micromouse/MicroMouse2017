cc_library(
    name = "impl",
    hdrs = [
    	"MazeImpl.h",
    ],
    srcs = [
    	"MazeImpl.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/main/cc/maze/cell",
        "//src/main/cc/maze",
    ],
    copts = ["-isystemsrc/main/cc"],
    linkopts = [
        "-std=c++11",
        "-Isrc/main/cc",
    ],
)
