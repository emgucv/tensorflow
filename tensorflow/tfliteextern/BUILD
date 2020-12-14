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
    name = "tfliteextern.a",
    hdrs = ["tfliteextern.h"],
    srcs = ["tfliteextern.cc"],
    copts = tflite_copts(),
    deps = select(
		{
        "//tensorflow:android": [
	    "//tensorflow/lite:framework",
	    "//tensorflow/lite:context",
	    "//tensorflow/lite:string",
	    "//tensorflow/lite:string_util",
	    "//tensorflow/lite:schema_fbs_version",
	    "//tensorflow/lite/kernels:builtin_ops",
		"//tensorflow/core:version_lib",
		"//tensorflow/lite/delegates/gpu:delegate",
		],
        "//conditions:default": [
	    "//tensorflow/lite:framework",
	    "//tensorflow/lite:context",
	    "//tensorflow/lite:string",
	    "//tensorflow/lite:string_util",
	    "//tensorflow/lite:schema_fbs_version",
	    "//tensorflow/lite/kernels:builtin_ops",
		"//tensorflow/core:version_lib",
        ]}
	)
)

cc_library(
    name = "tfliteextern.ios.a",
    hdrs = ["tfliteextern.h"],
    srcs = ["tfliteextern.cc"],
    copts = tflite_copts(),
    deps = ["//tensorflow/lite/c:c_api"]
)

cc_binary(
    name = "libtfliteextern.so",
    srcs = ["tfliteextern.cc",
        "tfliteextern.h"
    ],
   copts = tflite_copts() + [ 
        "-ffunction-sections",
        "-fdata-sections",
    ],
    linkopts =  select({
        "//tensorflow:android": [
        "-landroid",
        "-llog",
        "-lm",
        "-z defs",
        "-s",
        "-Wl,--gc-sections",
    ],  "//tensorflow:macos": [
    	"-lm",
	"-lpthread",
	#"-Wl,-install_name,@rpath/libtfliteextern.dylib"
    ],
	"//conditions:default": ["-lm"],
    }),
    linkshared = 1,
    linkstatic = 1,
    tags = [
        "manual",
        "notap",
    ],
    deps = select(
		{
        "//tensorflow:android": [
	    "//tensorflow/lite:framework",
	    "//tensorflow/lite:context",
	    "//tensorflow/lite:string",
	    "//tensorflow/lite:string_util",
	    "//tensorflow/lite:schema_fbs_version",
	    "//tensorflow/lite/kernels:builtin_ops",
		"//tensorflow/core:version_lib",
		"//tensorflow/lite/delegates/gpu:delegate",
		],
        "//conditions:default": [
	    "//tensorflow/lite:framework",
	    "//tensorflow/lite:context",
	    "//tensorflow/lite:string",
	    "//tensorflow/lite:string_util",
	    "//tensorflow/lite:schema_fbs_version",
	    "//tensorflow/lite/kernels:builtin_ops",
		"//tensorflow/core:version_lib",
	    #"//tensorflow/lite/tools:mutable_op_resolver"
	    #"//tensorflow/c:c_api",
        #"//tensorflow/cc:cc_ops",
        #"//tensorflow/core:framework_internal",
	    #"//tensorflow/core:framework",
        #"//tensorflow/core:tensorflow",
        ]}
    ),
)