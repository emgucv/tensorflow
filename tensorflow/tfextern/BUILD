package(default_visibility = ["//visibility:public"])

load(
    "//tensorflow:tensorflow.bzl",
    "tf_copts",
    "tf_opts_nortti_if_android",
    "if_android",
    "tf_cc_shared_object",
)

#cc_binary(
tf_cc_shared_object(
    name = "libtfextern.so",
    srcs = ["tfextern.cc",
        "tfextern.h"
    ],
   copts = tf_copts() + [ 
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
	#"-Wl,-install_name,@rpath/libtfextern.dylib"
    ],
	"//conditions:default": ["-lm"],
    }),
    #linkshared = 1,
    linkstatic = 1,
    tags = [
        "manual",
        "notap",
    ],
    deps = select({
        "//tensorflow:android": [
            "//tensorflow/c:c_api",
            #"//tensorflow/core:core_cpu",
            "//tensorflow/core:android_tensorflow_lib"
        ],
        "//conditions:default": [
	    "//tensorflow/c:c_api",
            "//tensorflow/cc:cc_ops",
            "//tensorflow/core:framework_internal",
	    "//tensorflow/core:framework",
            "//tensorflow/core:tensorflow",
        ],
    }),
)