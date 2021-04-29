#include "tfliteextern.h"

tflite::FlatBufferModel* tfeFlatBufferModelBuildFromFile(char* filename)
{
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(filename, tflite::CallbackErrorReporter()); 
  return model.release();
}

tflite::FlatBufferModel* tfeFlatBufferModelBuildFromBuffer(char* buffer, int bufferSize)
{
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromBuffer(buffer, bufferSize, tflite::CallbackErrorReporter()); 
  return model.release();
}

/*
tflite::FlatBufferModel* tfeFlatBufferModelBuildFromModel(tflite::FlatBufferModel* other)
{
  std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromModel(other);
  return model.release();
}
*/

bool tfeFlatBufferModelInitialized(tflite::FlatBufferModel* model)
{
  return model->initialized();
}
bool tfeFlatBufferModelCheckModelIdentifier(tflite::FlatBufferModel* model)
{
  return model->CheckModelIdentifier();
}

void tfeFlatBufferModelRelease(tflite::FlatBufferModel** model)
{
  delete *model;
  *model = 0;
}

tflite::ops::builtin::BuiltinOpResolver* tfeBuiltinOpResolverCreate(tflite::OpResolver** opResolver)
{
   tflite::ops::builtin::BuiltinOpResolver* builtinOpResolver = new tflite::ops::builtin::BuiltinOpResolver();
   *opResolver = dynamic_cast<tflite::OpResolver*>(builtinOpResolver);
   return builtinOpResolver;
}
void tfeBuiltinOpResolverRelease(tflite::ops::builtin::BuiltinOpResolver** resolver)
{
  delete * resolver;
  *resolver = 0;
}
tflite::Interpreter* tfeInterpreterCreate()
{
  return new tflite::Interpreter();
}
void tfeInterpreterCreateFromModel(tflite::Interpreter** interpreter, tflite::FlatBufferModel* model, tflite::OpResolver* opResolver)
{
  //std::unique_ptr<tflite::Interpreter> interpreterPtr(interpreter, [](tflite::Interpreter*){});
  std::unique_ptr<tflite::Interpreter> interpreterPtr(*interpreter);
  //std::unique_ptr<tflite::Interpreter, std::function<void(tflite::Interpreter*)>> interpreterPtr(interpreter, [](tflite::Interpreter* ptr) {} );
  //std::unique_ptr<tflite::Interpreter> interpreterPtr(interpreter, [](tflite::Interpreter) {});
  tflite::InterpreterBuilder(*model, *opResolver)(&interpreterPtr);
  *interpreter = interpreterPtr.release();
}
int tfeInterpreterAllocateTensors(tflite::Interpreter* interpreter)
{
  return interpreter->AllocateTensors();
}
int tfeInterpreterInvoke(tflite::Interpreter* interpreter)
{
  return interpreter->Invoke();
}
/*
char* tfeInterpreterInputTensor(tflite::Interpreter* interpreter, int index)
{
  return interpreter->typed_input_tensor<char>(index);
}
char* tfeInterpreterOutputTensor(tflite::Interpreter* interpreter, int index)
{
  return interpreter->typed_output_tensor<char>(index);
}
*/
TfLiteTensor* tfeInterpreterGetTensor(tflite::Interpreter* interpreter, int index)
{
  return interpreter->tensor(index);
}
int tfeInterpreterTensorSize(tflite::Interpreter* interpreter)
{
  return interpreter->tensors_size();
}
int tfeInterpreterNodesSize(tflite::Interpreter* interpreter)
{
  return interpreter->nodes_size();
}
int tfeInterpreterGetInputSize(tflite::Interpreter* interpreter)
{
  return interpreter->inputs().size();
}
void tfeInterpreterGetInput(tflite::Interpreter* interpreter, int* input)
{
  std::vector<int> ivec = interpreter->inputs();
  memcpy(input, &ivec[0], ivec.size() * sizeof(int));
}
const char* tfeInterpreterGetInputName(tflite::Interpreter* interpreter, int index)
{
  return interpreter->GetInputName(index);
}
int tfeInterpreterGetOutputSize(tflite::Interpreter* interpreter)
{
  return interpreter->outputs().size();
}
int tfeInterpreterGetOutput(tflite::Interpreter* interpreter, int* output)
{
  std::vector<int> ovec = interpreter->outputs();
  memcpy(output, &ovec[0], ovec.size() * sizeof(int));
  return ovec.size();
}
const char* tfeInterpreterGetOutputName(tflite::Interpreter* interpreter, int index)
{
  return interpreter->GetOutputName(index);
}

//void tfeInterpreterUseNNAPI(tflite::Interpreter* interpreter, bool enable)
//{
//	interpreter->UseNNAPI(enable);
//}
void tfeInterpreterSetNumThreads(tflite::Interpreter* interpreter, int numThreads)
{
	interpreter->SetNumThreads(numThreads);
}


void tfeInterpreterRelease(tflite::Interpreter** interpreter)
{
  delete * interpreter;
  *interpreter = 0;
}

int tfeInterpreterModifyGraphWithDelegate(tflite::Interpreter* interpreter, TfLiteDelegate* delegate)
{
	return (int) interpreter->ModifyGraphWithDelegate(delegate);
}
	

tflite::InterpreterBuilder* tfeInterpreterBuilderCreate(tflite::FlatBufferModel* model, tflite::OpResolver* opResolver)
{
  return new tflite::InterpreterBuilder(*model, *opResolver);
}

void tfeInterpreterBuilderRelease(tflite::InterpreterBuilder** builder)
{
  delete * builder;
  *builder = 0;
}
int tfeInterpreterBuilderBuild(tflite::InterpreterBuilder* builder, tflite::Interpreter* interpreter)
{
  std::unique_ptr<tflite::Interpreter> ptr(interpreter);
  int status = (*builder)(&ptr);
  ptr.release();
  return status;
}

int tfeTensorGetType(TfLiteTensor* tensor)
{
  return tensor->type;
}

char* tfeTensorGetData(TfLiteTensor* tensor)
{
  return tensor->data.raw;
}

void tfeTensorGetQuantizationParams(TfLiteTensor* tensor, TfLiteQuantizationParams* params)
{
  memcpy(params, &(tensor->params), sizeof(TfLiteQuantizationParams));
}

int tfeTensorGetAllocationType(TfLiteTensor* tensor)
{
  return tensor->allocation_type;
}
int tfeTensorGetByteSize(TfLiteTensor* tensor)
{
  return (int)tensor->bytes;
}
const char* tfeTensorGetName(TfLiteTensor* tensor)
{
  return tensor->name;
}
TfLiteIntArray* tfeTensorGetDims(TfLiteTensor* tensor)
{
	return tensor->dims;
}
bool tfeTensorIsVariable(TfLiteTensor* tensor)
{
	return tensor->is_variable;
}


void tfeMemcpy(void* dst, void* src, int length)
{
  memcpy(dst, src, length);
}

tflite::DynamicBuffer* tfeDynamicBufferCreate()
{
  return new tflite::DynamicBuffer();
}
void tfeDynamicBufferRelease(tflite::DynamicBuffer** buffer)
{
  delete *buffer;
  *buffer = 0;
}
void tfeDynamicBufferAddString(tflite::DynamicBuffer* buffer, char* str, int len)
{
  buffer->AddString(str, len);
}
void tfeDynamicBufferWriteToTensor(tflite::DynamicBuffer* buffer, TfLiteTensor* tensor, TfLiteIntArray* newShape)
{
  buffer->WriteToTensor(tensor, newShape);
}

TfLiteIntArray* tfeIntArrayCreate(int size)
{
	return TfLiteIntArrayCreate(size);
}
int tfeIntArrayGetSize(TfLiteIntArray* v)
{
	return v->size;
}
int* tfeIntArrayGetData(TfLiteIntArray* v)
{
	return v->data;
}
void tfeIntArrayRelease(TfLiteIntArray** v)
{
	TfLiteIntArrayFree(*v);
	*v = 0;
}


tflite::StatefulNnApiDelegate* tfeStatefulNnApiDelegateCreate(TfLiteDelegate** tfLiteDelegate)
{
	tflite::StatefulNnApiDelegate* d = new tflite::StatefulNnApiDelegate();
    *tfLiteDelegate = static_cast<TfLiteDelegate*>(d);
    return d;
}
void tfeStatefulNnApiDelegateRelease(tflite::StatefulNnApiDelegate** delegate)
{
	delete *delegate;
	*delegate = 0;
}

TfLiteDelegate* tfeGpuDelegateV2Create()
{
#ifdef __ANDROID__
    return TfLiteGpuDelegateV2Create(nullptr);
#else
    return 0;
#endif
}
void tfeGpuDelegateV2Delete(TfLiteDelegate** delegate)
{
#ifdef __ANDROID__
    TfLiteGpuDelegateV2Delete(*delegate);
#endif
    *delegate = 0;
}


//TfLiteDelegate* tfeGpuDelegateCreate()
//{
//#ifdef __IOS__
//    return TFLGpuDelegateCreate(nullptr);
//#else
//    return 0;
//#endif
//}
//void tfeGpuDelegateDelete(TfLiteDelegate** delegate)
//{
//#ifdef __IOS__
//    TFLGpuDelegateDelete(*delegate);
//#endif
//    *delegate = 0;
//}


//void RegisterSelectedOps(tflite::MutableOpResolver* resolver);

/*
tflite::MutableOpResolver* tfeMutableOpResolverCreate(tflite::OpResolver** opResolver)
{
  tflite::MutableOpResolver* mutableOpResolver =  new tflite::MutableOpResolver();
  //RegisterSelectedOps(mutableOpResolver);
  *opResolver = dynamic_cast<tflite::OpResolver*>( mutableOpResolver );
  return mutableOpResolver;
}

void tfeMutableOpResolverRelease(tflite::MutableOpResolver** resolver)
{
  delete *resolver;
  *resolver = 0;
}*/

static const char* tflite_version = TF_VERSION_STRING;

const char* tfeGetLiteVersion()
{
  return tflite_version;
}


static tflite::ErrorCallback customErrorCallback = 0;

char errBuffer[2048]; 

int tflite::TfliteErrReporter::Report(const char* format, va_list args) {
  const int result = sprintf(errBuffer, format, args);
  if (customErrorCallback)
    customErrorCallback(result, errBuffer);
  return result;
}

void tfeRedirectError( tflite::ErrorCallback errCallback)
{
  customErrorCallback = errCallback;
}

tflite::ErrorReporter* tflite::CallbackErrorReporter() {
  static tflite::TfliteErrReporter* error_reporter = new tflite::TfliteErrReporter;
  return error_reporter;
}


template<class T>
void tfePixelsToTensor(
	unsigned char* pixels,
    int bytesInPixel,	
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	T* floatValues)
{
	int idx = 0;
	if (flipUpsideDown)
	{
		//handle flip upside down
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				unsigned char* val = &pixels[((height - i - 1) * width + j) * bytesInPixel];
				if (swapBR)
				{
					floatValues[idx++] = (T) ( *(val+2) - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+1) - inputMean) * scale;
					floatValues[idx++] = (T) ( *val - inputMean) * scale;
				}
				else
				{
					floatValues[idx++] = (T) ( *val - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+1) - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+2) - inputMean) * scale;
				}
			}
	}
	else
	{
		for (int i = 0; i < height*width; ++i)
		{
			unsigned char* val = &pixels[i * bytesInPixel];
			if (swapBR)
			{
				floatValues[idx++] = (T) (*(val+2) - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+1) - inputMean) * scale;
				floatValues[idx++] = (T) (*val - inputMean) * scale;
			}
			else
			{
				floatValues[idx++] = (T) (*val - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+1) - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+2) - inputMean) * scale;
			}
		}
	}
}

void tfePixel32ToPixelFloat(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	float* floatValues)
{
	tfePixelsToTensor<float>(pixels, 4, width, height, inputMean, scale, flipUpsideDown, swapBR, floatValues);
}

void tfePixel32ToPixelByte(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	unsigned char* result)
{
	tfePixelsToTensor<unsigned char>(pixels, 4, width, height, inputMean, scale, flipUpsideDown, swapBR, result);
}

void tfePixel24ToPixelFloat(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	float* floatValues)
{
	tfePixelsToTensor<float>(pixels, 3, width, height, inputMean, scale, flipUpsideDown, swapBR, floatValues);
}

void tfePixel24ToPixelByte(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	unsigned char* result)
{
	tfePixelsToTensor<unsigned char>(pixels, 3, width, height, inputMean, scale, flipUpsideDown, swapBR, result);
}
