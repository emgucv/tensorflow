package(default_visibility = ["//visibility:public"])

load(
    #"//tensorflow:tensorflow.bzl",
    "//tensorflow/contrib/lite:build_def.bzl",
    "tflite_copts",
    #"tf_opts_nortti_if_android",
    #"if_android",
    #"tf_cc_shared_object",
    "gen_selected_ops"
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
    ],  "//tensorflow:darwin": [
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
    deps = select({
        "//conditions:default": [
	    "//tensorflow/contrib/lite:framework",
	    "//tensorflow/contrib/lite:context",
	    "//tensorflow/contrib/lite:string",
	    "//tensorflow/contrib/lite:string_util",
	    "//tensorflow/contrib/lite:schema_fbs_version",
	    "//tensorflow/contrib/lite/kernels:builtin_ops",
		"//tensorflow/core:version_lib",
	    #"//tensorflow/contrib/lite/tools:mutable_op_resolver"
	    #"//tensorflow/c:c_api",
        #"//tensorflow/cc:cc_ops",
        #"//tensorflow/core:framework_internal",
	    #"//tensorflow/core:framework",
        #"//tensorflow/core:tensorflow",
        ],
    }),
)