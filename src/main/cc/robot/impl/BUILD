cc_library(
    name = "impl",
    hdrs = [
    	"RobotImpl.h",
    ],
    srcs = [
    	"RobotImpl.cc",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "//src/main/cc/maze/cell",
        "//src/main/cc/maze",
        "//src/main/cc/robot",
    ],
    copts = ["-isystemsrc/main/cc"],
    linkopts = [
        "-std=c++11",
        "-Isrc/main/cc",
    ],
)
