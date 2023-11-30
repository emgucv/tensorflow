package(default_visibility = ["//visibility:public"])

load(
    "//tensorflow:tensorflow.bzl",
    "tf_copts",
    "tf_opts_nortti_if_android",
    "if_android",
    "tf_cc_shared_object",
    "tf_cc_test",
)


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
    ], "//tensorflow:linux_aarch64": [
        "-lm", 
    	"-Wl,--stub-group-size=1048576"
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
            #"//tensorflow/c:c_api",
            #"//tensorflow/core:core_cpu",
            "//tensorflow/core:portable_tensorflow_lib",
			"//tensorflow/imgproc:imgproc",
        ],
        "//conditions:default": [
	        "//tensorflow/c:c_api",
            "//tensorflow/cc:cc_ops",
            "//tensorflow/core:framework_internal",
	        "//tensorflow/core:framework",
            "//tensorflow/core:tensorflow",
			"//tensorflow/imgproc:imgproc",
        ],
    }),
)

# -----------------------------------------------------------------------------
# Tests

tf_cc_test(
    name = "tfextern_test",
    srcs = ["tfextern_test.cc",
            "tfextern_test.h",
            "tfextern.cc",
            "tfextern.h"],
    deps = select({
            "//tensorflow:android": [
                #":libtfextern.so",
                #"//tensorflow/c:c_api",
                #"//tensorflow/core:core_cpu",
                "//tensorflow/core:portable_tensorflow_lib",
    			"//tensorflow/imgproc:imgproc",
            ],
            "//conditions:default": [
                #":libtfextern.so",
    	        "//tensorflow/c:c_api",
                "//tensorflow/cc:cc_ops",
                "//tensorflow/core:framework_internal",
    	        "//tensorflow/core:framework",
                "//tensorflow/core:tensorflow",
    			"//tensorflow/imgproc:imgproc",
            ],
        }),
    #extra_copts = ["-std=c11"],
    #deps = [
    #    ":libtfextern.so",
    #],
)