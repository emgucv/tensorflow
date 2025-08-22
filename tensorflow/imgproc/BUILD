package(default_visibility = ["//visibility:public"])

load(
    #"//tensorflow:tensorflow.bzl",
    "//tensorflow/lite:build_def.bzl",
    "tflite_copts",
    #"tf_opts_nortti_if_android",
    #"if_android",
    #"tf_cc_shared_object",
    "gen_selected_ops"
)

cc_library(
    name = "imgproc",
    hdrs = ["imgproc.h"],
    srcs = ["imgproc.cc"],
    copts = tflite_copts(),
)


