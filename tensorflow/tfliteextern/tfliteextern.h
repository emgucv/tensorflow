#ifndef  TFAPI_EXPORTS
#define TFAPI_EXPORTS
#endif

#if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__) && defined TFAPI_EXPORTS
#  define TF_EXPORTS __declspec(dllexport)
#elif defined __GNUC__ && __GNUC__ >= 4
#  define TF_EXPORTS __attribute__ ((visibility ("default")))
#else
#  define TF_EXPORTS
#endif

#ifndef TF_EXTERN_C
#  ifdef __cplusplus
#    define TF_EXTERN_C extern "C"
#  else
#    define TF_EXTERN_C
#  endif
#endif

#if defined WIN32 || defined _WIN32
#  define TF_CDECL __cdecl
#  define TF_STDCALL __stdcall
#else
#  define TF_CDECL
#  define TF_STDCALL
#endif

#ifndef TFAPI
#  define TFAPI(rettype) TF_EXTERN_C TF_EXPORTS rettype TF_CDECL
#endif

//#include <stddef.h>
//#include <stdint.h>
#include <cstdlib>
#include <cstring>

#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/string_util.h"
#include "tensorflow/core/public/version.h"

//#ifdef __ANDROID__
//#include "tensorflow/lite/delegates/nnapi/nnapi_delegate.h"
#include "tensorflow/lite/nnapi_delegate.h"
//#endif

//#include "tensorflow/lite/tools/mutable_op_resolver.h"

TFAPI(tflite::FlatBufferModel*) tfeFlatBufferModelBuildFromFile(char* filename);
TFAPI(tflite::FlatBufferModel*) tfeFlatBufferModelBuildFromBuffer(char* buffer, int bufferSize);
//TFAPI(tflite::FlatBufferModel*) tfeFlatBufferModelBuildFromModel(tflite::FlatBufferModel* other);
TFAPI(bool) tfeFlatBufferModelInitialized(tflite::FlatBufferModel* model);
TFAPI(bool) tfeFlatBufferModelCheckModelIdentifier(tflite::FlatBufferModel* model);
TFAPI(void) tfeFlatBufferModelRelease(tflite::FlatBufferModel** model);

TFAPI(tflite::ops::builtin::BuiltinOpResolver*) tfeBuiltinOpResolverCreate(tflite::OpResolver** opResolver);
TFAPI(void) tfeBuiltinOpResolverRelease(tflite::ops::builtin::BuiltinOpResolver** resolver);

TFAPI(tflite::Interpreter*) tfeInterpreterCreate();
TFAPI(tflite::Interpreter*) tfeInterpreterCreateFromModel(tflite::FlatBufferModel* model, tflite::OpResolver* opResolver);
TFAPI(int) tfeInterpreterAllocateTensors(tflite::Interpreter* interpreter);
TFAPI(int) tfeInterpreterInvoke(tflite::Interpreter* interpreter);
//TFAPI(char*) tfeInterpreterInputTensor(tflite::Interpreter* interpreter, int index);
//TFAPI(char*) tfeInterpreterOuputTensor(tflite::Interpreter* interpreter, int index);
TFAPI(TfLiteTensor*) tfeInterpreterGetTensor(tflite::Interpreter* interpreter, int index);
TFAPI(int) tfeInterpreterTensorSize(tflite::Interpreter* interpreter);
TFAPI(int) tfeInterpreterNodesSize(tflite::Interpreter* interpreter);
TFAPI(int) tfeInterpreterGetInputSize(tflite::Interpreter* interpreter);
TFAPI(void) tfeInterpreterGetInput(tflite::Interpreter* interpreter, int* input);
TFAPI(const char*) tfeInterpreterGetInputName(tflite::Interpreter* interpreter, int index);
TFAPI(int) tfeInterpreterGetOutputSize(tflite::Interpreter* interpreter);
TFAPI(int) tfeInterpreterGetOutput(tflite::Interpreter* interpreter, int* output);
TFAPI(const char*) tfeInterpreterGetOutputName(tflite::Interpreter* interpreter, int index);
TFAPI(void) tfeInterpreterUseNNAPI(tflite::Interpreter* interpreter, bool enable);
TFAPI(void) tfeInterpreterSetNumThreads(tflite::Interpreter* interpreter, int numThreads);
TFAPI(void) tfeInterpreterRelease(tflite::Interpreter** interpreter);
TFAPI(int) tfeInterpreterModifyGraphWithDelegate(tflite::Interpreter* interpreter, TfLiteDelegate* delegate);

TFAPI(tflite::InterpreterBuilder*) tfeInterpreterBuilderCreate(tflite::FlatBufferModel* model, tflite::OpResolver* opResolver);
TFAPI(void) tfeInterpreterBuilderRelease(tflite::InterpreterBuilder** builder);
TFAPI(int) tfeInterpreterBuilderBuild(tflite::InterpreterBuilder* builder, tflite::Interpreter* interpreter);

TFAPI(int) tfeTensorGetType(TfLiteTensor* tensor);
TFAPI(char*) tfeTensorGetData(TfLiteTensor* tensor);
TFAPI(void) tfeTensorGetQuantizationParams(TfLiteTensor* tensor, TfLiteQuantizationParams* params);
TFAPI(int) tfeTensorGetAllocationType(TfLiteTensor* tensor);
TFAPI(int) tfeTensorGetByteSize(TfLiteTensor* tensor);
TFAPI(const char*) tfeTensorGetName(TfLiteTensor* tensor);
TFAPI(TfLiteIntArray*) tfeTensorGetDims(TfLiteTensor* tensor);
TFAPI(bool) tfeTensorIsVariable(TfLiteTensor* tensor);
TFAPI(void) tfeMemcpy(void* dst, void* src, int length);

TFAPI(tflite::DynamicBuffer*) tfeDynamicBufferCreate();
TFAPI(void) tfeDynamicBufferRelease(tflite::DynamicBuffer** buffer);
TFAPI(void) tfeDynamicBufferAddString(tflite::DynamicBuffer* buffer, char* str, int len);
TFAPI(void) tfeDynamicBufferWriteToTensor(tflite::DynamicBuffer* buffer, TfLiteTensor* tensor);


TFAPI(TfLiteIntArray*) tfeIntArrayCreate(int size);
TFAPI(int) tfeIntArrayGetSize(TfLiteIntArray* v);
TFAPI(int*) tfeIntArrayGetData(TfLiteIntArray* v);
TFAPI(void) tfeIntArrayRelease(TfLiteIntArray** v);

TFAPI(tflite::NNAPIDelegate*) tfeNNAPIDelegateCreate();
TFAPI(void) tfeNNAPIDelegateRelease(tflite::NNAPIDelegate** delegate);
TFAPI(bool) tfeNNAPIDelegateIsSupported(tflite::NNAPIDelegate* delegate);
TFAPI(TfLiteDelegate*) tfeNNAPIDelegateGetDelegate();


//TFAPI(tflite::MutableOpResolver*) tfeMutableOpResolverCreate(tflite::OpResolver** opResolver); 
//TFAPI(void) tfeMutableOpResolverRelease(tflite::MutableOpResolver** resolver);

TFAPI(const char*) tfeGetLiteVersion();

namespace tflite
{
  extern "C" typedef int (*ErrorCallback)( int status, const char* err_msg);
  
  // An error reporter that simplify writes the message to stderr.
  struct TfliteErrReporter : public ErrorReporter {
    int Report(const char* format, va_list args) override;
  };

  ErrorReporter* CallbackErrorReporter();
}

TFAPI(void) tfeRedirectError( tflite::ErrorCallback errCallback);
