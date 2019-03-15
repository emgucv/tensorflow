#include "tfextern.h"

const char* tfeGetVersion()
{
	return TF_Version();
}

TF_Tensor* tfeAllocateTensor(int tfDataType, int* dims, int numDims, int len)
{
	void* v = malloc(sizeof(int64_t) * numDims);
	int64_t* d = static_cast<int64_t*>(v);
	for (int i = 0; i < numDims; i++)
		d[i] = dims[i];
	TF_Tensor* result = TF_AllocateTensor((TF_DataType)tfDataType, d, numDims, len);
	free(v);
	return result;
}

void tfeDeleteTensor(TF_Tensor** tensor)
{
	TF_DeleteTensor(*tensor);
	*tensor = 0;
}

void* tfeTensorData(TF_Tensor* tensor)
{
	return TF_TensorData(tensor);
}

int tfeTensorByteSize(TF_Tensor* tensor)
{
	return static_cast<int>(TF_TensorByteSize(tensor));
}

TF_DataType tfeTensorType(TF_Tensor* tensor)
{
	return TF_TensorType(tensor);
}
int tfeNumDims(TF_Tensor* tensor)
{
	return TF_NumDims(tensor);
}
void tfeGetDim(TF_Tensor* tensor, int* dims, int numDims)
{
	for (int i = 0; i < numDims; i++)
		dims[i] = TF_Dim(tensor, i);
}


TF_Session* tfeNewSession(TF_Graph* graph, const TF_SessionOptions* opts, TF_Status* status)
{
	if (opts == 0)
	{
		TF_SessionOptions* optsNew = TF_NewSessionOptions();
		TF_Session* session = TF_NewSession(graph, optsNew, status);
		TF_DeleteSessionOptions(optsNew);
		return session;
	}
	else
		return TF_NewSession(graph, opts, status);
}
void tfeDeleteSession(TF_Session** session, TF_Status* status)
{
	TF_DeleteSession(*session, status);
	*session = 0;
}
void tfeSessionRun(
	TF_Session* session, const TF_Buffer* run_options,
	TF_Operation** inputOps, int* inputIdx, TF_Tensor* const* input_values, int ninputs,
	TF_Operation** outputOps, int* outputIdx, TF_Tensor** output_values, int noutputs,
	const TF_Operation* const* target_opers, int ntargets,
	TF_Buffer* run_metadata, TF_Status* status)
{
	void* dataIn = malloc(sizeof(TF_Output)*ninputs);
	TF_Output* inputs = static_cast<TF_Output*>(dataIn);
	for (int i = 0; i < ninputs; i++)
	{
		inputs[i].oper = inputOps[i];
		inputs[i].index = inputIdx[i];
	}

	void* dataOut = malloc(sizeof(TF_Output)*noutputs);
	TF_Output* outputs = static_cast<TF_Output*>(dataOut);
	for (int i = 0; i < noutputs; i++)
	{
		outputs[i].oper = outputOps[i];
		outputs[i].index = outputIdx[i];
	}

	TF_SessionRun(session, run_options, inputs, input_values, ninputs, outputs, output_values, noutputs, target_opers, ntargets, run_metadata, status);
	free(dataIn);
	free(dataOut);

}

void tfeSessionListDevices(TF_Session* session, char* nameBuffer, char* typeBuffer, long long* memorySizeBuffer, TF_Status* status)
{
	TF_DeviceList* deviceList = TF_SessionListDevices(session, status);

	int namePosition = 0, typePosition = 0;
	int deviceCount = TF_DeviceListCount(deviceList);
	int i;
	for (i = 0; i < deviceCount; i++)
	{
		const char* deviceName = TF_DeviceListName(deviceList, i, status);
		int deviceNameLength = strlen(deviceName);
		memcpy(nameBuffer + namePosition, deviceName, deviceNameLength);
		namePosition += deviceNameLength;
		nameBuffer[namePosition] = '\n';
		namePosition += 1;

		const char* deviceType = TF_DeviceListType(deviceList, i, status);
		int deviceTypeLength = strlen(deviceType);
		memcpy(typeBuffer + typePosition, deviceType, deviceTypeLength);
		typePosition += deviceTypeLength;
		typeBuffer[typePosition] = '\n';
		typePosition += 1;

		*(memorySizeBuffer + i) = TF_DeviceListMemoryBytes(deviceList, i, status);
	}
	nameBuffer[namePosition] = '\0';
	typeBuffer[typePosition] = '\0';
	//memorySizeBuffer[i] = 0;
	TF_DeleteDeviceList(deviceList);
}

TF_Status* tfeNewStatus()
{
	return TF_NewStatus();
}
void tfeDeleteStatus(TF_Status** status)
{
	TF_DeleteStatus(*status);
	*status = 0;
}
int tfeGetCode(TF_Status* s)
{
	return TF_GetCode(s);
}
const char* tfeMessage(TF_Status* s)
{
	return TF_Message(s);
}

TF_SessionOptions* tfeNewSessionOptions()
{
	return TF_NewSessionOptions();
}
void tfeDeleteSessionOptions(TF_SessionOptions** session_options)
{
	TF_DeleteSessionOptions(*session_options);
	*session_options = 0;
}
void tfeCloseSession(TF_Session* session, TF_Status* status)
{
	TF_CloseSession(session, status);
}
void tfeSetConfig(TF_SessionOptions* options, const void* proto, int proto_len, TF_Status* status)
{
	TF_SetConfig(options, proto, proto_len, status);
}
void tfeSetTarget(TF_SessionOptions* options, const char* target)
{
	TF_SetTarget(options, target);
}

TF_ImportGraphDefOptions* tfeNewImportGraphDefOptions()
{
	return TF_NewImportGraphDefOptions();
}
void tfeDeleteImportGraphDefOptions(TF_ImportGraphDefOptions** opts)
{
	TF_DeleteImportGraphDefOptions(*opts);
	*opts = 0;
}
void tfeImportGraphDefOptionsSetPrefix(TF_ImportGraphDefOptions* opts, const char* prefix)
{
	TF_ImportGraphDefOptionsSetPrefix(opts, prefix);
}
void tfeImportGraphDefOptionsAddInputMapping(
	TF_ImportGraphDefOptions* opts,
	const char* src_name,
	int src_index,
	TF_Operation* dstOp,
	int dstOpIdx)
{
	TF_Output dst;
	dst.oper = dstOp;
	dst.index = dstOpIdx;
	TF_ImportGraphDefOptionsAddInputMapping(
		opts,
		src_name,
		src_index,
		dst);
}
void tfeImportGraphDefOptionsRemapControlDependency(
	TF_ImportGraphDefOptions* opts,
	const char* src_name,
	TF_Operation* dst)
{
	TF_ImportGraphDefOptionsRemapControlDependency(opts, src_name, dst);
}
void tfeImportGraphDefOptionsAddControlDependency(
	TF_ImportGraphDefOptions* opts, TF_Operation* oper)
{
	TF_ImportGraphDefOptionsAddControlDependency(opts, oper);
}
void tfeImportGraphDefOptionsAddReturnOutput(
	TF_ImportGraphDefOptions* opts, const char* oper_name, int index)
{
	TF_ImportGraphDefOptionsAddReturnOutput(opts, oper_name, index);
}
int tfeImportGraphDefOptionsNumReturnOutputs(TF_ImportGraphDefOptions* opts)
{
	return TF_ImportGraphDefOptionsNumReturnOutputs(opts);
}

TF_Graph* tfeNewGraph()
{
	return TF_NewGraph();
}
void tfeDeleteGraph(TF_Graph** graph)
{
	TF_DeleteGraph(*graph);
	*graph = 0;
}
void tfeGraphImportGraphDef(TF_Graph* graph, const TF_Buffer* graph_def, const TF_ImportGraphDefOptions* options, TF_Status* status)
{
	TF_GraphImportGraphDef(graph, graph_def, options, status);
}
TF_Operation* tfeGraphOperationByName(TF_Graph* graph, const char* oper_name)
{
	return TF_GraphOperationByName(graph, oper_name);
}
TF_Operation* tfeGraphNextOperation(TF_Graph* graph, size_t* pos)
{
	return TF_GraphNextOperation(graph, pos);
}
void tfeGraphToGraphDef(TF_Graph* graph, TF_Buffer* output_graph_def, TF_Status* status)
{
	TF_GraphToGraphDef(graph, output_graph_def, status);
}
void tfeGraphSetTensorShape(TF_Graph* graph, TF_Operation* outputOperation, int idx, const int* dims, const int num_dims, TF_Status* status)
{
	int64_t* dimsTF = static_cast<int64_t*>(malloc(sizeof(int64_t) * num_dims));
	for (int i = 0; i < num_dims; i++)
		dimsTF[i] = dims[i];
	TF_Output output;
	output.oper = outputOperation;
	output.index = idx;
	TF_GraphSetTensorShape(graph, output, dimsTF, num_dims, status);
	free(dimsTF);
}
int tfeGraphGetTensorNumDims(TF_Graph* graph, TF_Operation* outputOperation, int idx, TF_Status* status)
{
	TF_Output output;
	output.oper = outputOperation;
	output.index = idx;
	return TF_GraphGetTensorNumDims(graph, output, status);
}
void tfeGraphGetTensorShape(TF_Graph* graph, TF_Operation* outputOperation, int idx, int* dims, int num_dims, TF_Status* status)
{
	int64_t* dimsTF = static_cast<int64_t*>(malloc(sizeof(int64_t) * num_dims));
	TF_Output output;
	output.oper = outputOperation;
	output.index = idx;

	TF_GraphGetTensorShape(graph, output, dimsTF, num_dims, status);
	for (int i = 0; i < num_dims; i++)
		dims[i] = static_cast<int>(dimsTF[i]);
	free(dimsTF);
}
TF_Buffer* tfeGraphVersions(TF_Graph* graph, TF_Status* status)
{
	TF_Buffer* output_version_def = new TF_Buffer();
	TF_GraphVersions(graph, output_version_def, status);
	return output_version_def;
}

void tfeGraphGetOpDef(TF_Graph* graph, const char* opName, TF_Buffer* outputOpDef, TF_Status* status)
{
	TF_GraphGetOpDef(graph, opName, outputOpDef, status);
}

int tfeGraphNumFunctions(TF_Graph* g)
{
	return TF_GraphNumFunctions(g);
}

TF_OperationDescription* tfeNewOperation(TF_Graph* graph, char* op_type, char* oper_name)
{
	return TF_NewOperation(graph, op_type, oper_name);
}
TF_Operation* tfeFinishOperation(TF_OperationDescription* desc, TF_Status* status)
{
	return TF_FinishOperation(desc, status);
}

const char* tfeOperationName(TF_Operation* oper)
{
	return  TF_OperationName(oper);
}
const char* tfeOperationOpType(TF_Operation* oper)
{
	return TF_OperationOpType(oper);
}
const char* tfeOperationDevice(TF_Operation* oper)
{
	return TF_OperationDevice(oper);
}
int tfeOperationNumOutputs(TF_Operation* oper)
{
	return TF_OperationNumOutputs(oper);
}
TF_DataType tfeOperationOutputType(TF_Operation* oper, int idx)
{
	TF_Output out;
	out.oper = oper;
	out.index = idx;
	return TF_OperationOutputType(out);
}
int tfeOperationOutputNumConsumers(TF_Operation* oper, int idx)
{
	TF_Output out;
	out.oper = oper;
	out.index = idx;
	return TF_OperationOutputNumConsumers(out);
}

int tfeOperationOutputConsumers(TF_Operation* operOut, int outIdx, TF_Operation** consumers, int* inputIdx, int maxConsumers)
{
	TF_Output outOp;
	outOp.oper = operOut;
	outOp.index = outIdx;
	TF_Input* inputs = static_cast<TF_Input*>(malloc(sizeof(TF_Input) * maxConsumers));
	int count = TF_OperationOutputConsumers(outOp, inputs, maxConsumers);

	for (int i = 0; i < maxConsumers; i++)
	{
		consumers[i] = inputs[i].oper;
		inputIdx[i] = inputs[i].index;
	}
	free(inputs);
	return count;
}

int tfeOperationNumInputs(TF_Operation* oper)
{
	return TF_OperationNumInputs(oper);
}
int tfeOperationNumControlInputs(TF_Operation* oper)
{
	return TF_OperationNumControlInputs(oper);
}
int tfeOperationGetControlInputs(TF_Operation* oper, TF_Operation** controlInputs, int maxControlInputs)
{
	return TF_OperationGetControlInputs(oper, controlInputs, maxControlInputs);
}
int tfeOperationNumControlOutputs(TF_Operation* oper)
{
	return TF_OperationNumControlOutputs(oper);
}
int tfeOperationGetControlOutputs(TF_Operation* oper, TF_Operation** controlOutputs, int maxControlOutputs)
{
	return TF_OperationGetControlOutputs(oper, controlOutputs, maxControlOutputs);
}

TF_DataType tfeOperationInputType(TF_Operation* oper, int idx)
{
	TF_Input input;
	input.oper = oper;
	input.index = idx;
	return TF_OperationInputType(input);
}

void tfeOperationGetAttrMetadata(TF_Operation* oper, const char* attrName, TF_AttrMetadata* meta, TF_Status* status)
{
	TF_AttrMetadata m = TF_OperationGetAttrMetadata(oper, attrName, status);
	memcpy(meta, &m, sizeof(TF_AttrMetadata));
}

TF_DataType tfeOperationGetAttrType(TF_Operation* oper, const char* attrName, TF_Status* status)
{
	TF_DataType t;
	TF_OperationGetAttrType(oper, attrName, &t, status);
	return t;
}

void tfeOperationGetAttrString(TF_Operation* oper, const char* attrName, void* value, int maxLength, TF_Status* status)
{
	TF_OperationGetAttrString(oper, attrName, value, maxLength, status);
}

bool tfeOperationGetAttrBool(TF_Operation* oper, const char* attrName, TF_Status* status)
{
	unsigned char value;
	TF_OperationGetAttrBool(oper, attrName, &value, status);
	return (value != 0);
}

void tfeOperationGetAttrShape(TF_Operation* oper, const char* attrName, int64_t* value, int numDims, TF_Status* status)
{
	TF_OperationGetAttrShape(oper, attrName, value, numDims, status);
}

void tfeOperationGetAttrTensorShapeProto(TF_Operation* oper, const char* attrName, TF_Buffer* value, TF_Status* status)
{
	TF_OperationGetAttrTensorShapeProto(oper, attrName, value, status);
}

void tfeOperationGetAttrValueProto(TF_Operation* oper, const char* attrName, TF_Buffer* outputAttrValue, TF_Status* status)
{
	TF_OperationGetAttrValueProto(oper, attrName, outputAttrValue, status);
}

TF_Tensor* tfeOperationGetAttrTensor(TF_Operation* oper, const char* attrName, TF_Status* status)
{
	TF_Tensor* ptr;
	TF_OperationGetAttrTensor(oper, attrName, &ptr, status);
	return ptr;
}

void tfeOperationGetAttrIntList(TF_Operation* oper, const char* attrName, int64_t* values, int maxValues, TF_Status* status)
{
	TF_OperationGetAttrIntList(oper, attrName, values, maxValues, status);
}

//Function
TF_Function* tfeFunctionImportFunctionDef(const void* proto, int proto_len, TF_Status* status)
{
	return TF_FunctionImportFunctionDef(proto, proto_len, status);
}
void tfeDeleteFunction(TF_Function** func)
{
	TF_DeleteFunction(*func);
	*func = 0;
}
void tfeFunctionToFunctionDef(TF_Function* func, TF_Buffer* output_func_def, TF_Status* status)
{
	TF_FunctionToFunctionDef(func, output_func_def, status);
}

//OperationDescription
void tfeAddInput(TF_OperationDescription* desc, TF_Operation* oper, int index)
{
	TF_Output out;
	out.oper = oper;
	out.index = index;
	TF_AddInput(desc, out);
}
void tfeSetAttrInt(TF_OperationDescription* desc, const char* attr_name, int64_t value)
{
	TF_SetAttrInt(desc, attr_name, value);
}
void tfeSetAttrIntList(TF_OperationDescription* desc, const char* attr_name, const int64_t* values, int num_values)
{
	TF_SetAttrIntList(desc, attr_name, values, num_values);
}
void tfeSetAttrBool(TF_OperationDescription* desc, const char* attr_name, bool value)
{
	TF_SetAttrBool(desc, attr_name, value ? 255 : 0);
}
void tfeSetAttrBoolList(TF_OperationDescription* desc, const char* attr_name, const unsigned char* values, int num_values)
{
	TF_SetAttrBoolList(desc, attr_name, values, num_values);
}
void tfeSetAttrFloat(TF_OperationDescription* desc, const char* attr_name, float value)
{
	TF_SetAttrFloat(desc, attr_name, value);
}
void tfeSetAttrFloatList(TF_OperationDescription* desc, const char* attr_name, const float* values, int num_values)
{
	TF_SetAttrFloatList(desc, attr_name, values, num_values);
}
void tfeSetAttrString(TF_OperationDescription* desc, const char* attr_name, const void* value, int length)
{
	TF_SetAttrString(desc, attr_name, value, length);
}
void tfeSetAttrStringList(TF_OperationDescription* desc, const char* attr_name, const void** values, size_t* lengths, int numValues)
{
	TF_SetAttrStringList(desc, attr_name, values, lengths, numValues);
}
void tfeSetAttrType(TF_OperationDescription* desc, const char* attr_name, TF_DataType value)
{
	TF_SetAttrType(desc, attr_name, value);
}
void tfeSetAttrTypeList(TF_OperationDescription* desc, const char* attr_name, const TF_DataType* values, int num_values)
{
	TF_SetAttrTypeList(desc, attr_name, values, num_values);
}
void tfeSetAttrShape(TF_OperationDescription* desc, const char* attr_name, const int64_t* dims, int num_dims)
{
	TF_SetAttrShape(desc, attr_name, dims, num_dims);
}
void tfeSetAttrShapeList(TF_OperationDescription* desc, const char* attr_name, const int64_t* const* dims, const int* num_dims, int num_shapes)
{
	TF_SetAttrShapeList(desc, attr_name, dims, num_dims, num_shapes);
}
void tfeSetAttrTensor(TF_OperationDescription* desc, const char* attr_name, TF_Tensor* value, TF_Status* status)
{
	TF_SetAttrTensor(desc, attr_name, value, status);
}
void tfeSetDevice(TF_OperationDescription* desc, const char* device)
{
	TF_SetDevice(desc, device);
}
void tfeAddInputList(TF_OperationDescription* desc, TF_Operation** inputOps, int* indices, int num_inputs)
{
	TF_Output* inputs = static_cast<TF_Output*>(malloc(sizeof(TF_Output) * num_inputs));
	for (int i = 0; i < num_inputs; i++)
	{
		inputs[i].oper = inputOps[i];
		inputs[i].index = indices[i];
	}
	TF_AddInputList(desc, inputs, num_inputs);
	free(inputs);
}
void tfeAddControlInput(TF_OperationDescription* desc, TF_Operation* input)
{
	TF_AddControlInput(desc, input);
}

void tfeColocateWith(TF_OperationDescription* desc, TF_Operation* op)
{
	TF_ColocateWith(desc, op);
}

TF_Buffer* tfeNewBuffer()
{
	return TF_NewBuffer();
}
TF_Buffer* tfeNewBufferFromString(const void* proto, int proto_len)
{
	return TF_NewBufferFromString(proto, proto_len);
}
void tfeDeleteBuffer(TF_Buffer** buffer)
{
	TF_DeleteBuffer(*buffer);
	*buffer = 0;
}
const void* tfeBufferGetData(TF_Buffer* buffer)
{
	return buffer->data;
}
int tfeBufferGetLength(TF_Buffer* buffer)
{
	return static_cast<int>(buffer->length);
}

int tfeDataTypeSize(TF_DataType dt)
{
	return static_cast<int>(TF_DataTypeSize(dt));
}


TF_Buffer* tfeGetAllOpList()
{
	return TF_GetAllOpList();
}

int tfeStringEncodedSize(int len)
{
	return static_cast<int>(TF_StringEncodedSize(len));
}
int tfeStringEncode(const char* src, int src_len, char* dst, int dst_len, TF_Status* status)
{
	return static_cast<int>(TF_StringEncode(src, src_len, dst, dst_len, status));
}

int tfeStringDecode(const char* src, int src_len, const char** dst, size_t* dst_len, TF_Status* status)
{
	return static_cast<int>(TF_StringDecode(src, src_len, dst, dst_len, status));
}

//Library
TF_Library* tfeLoadLibrary(const char* libraryFilename, TF_Status* status)
{
	return TF_LoadLibrary(libraryFilename, status);
}
TF_Buffer* tfeGetOpList(TF_Library* libHandle)
{
	return &(libHandle->op_list);
}
void tfeDeleteLibraryHandle(TF_Library** libHandle)
{
	TF_DeleteLibraryHandle(*libHandle);
	*libHandle = 0;
}

void tfeMemcpy(void* dst, void* src, int length)
{
	memcpy(dst, src, length);
}

bool tfeIsGoogleCudaEnabled()
{
	return tensorflow::IsGoogleCudaEnabled();
}

bool tfeOpIsRegistered(char* operationName)
{
	std::string s(operationName);
	std::vector<tensorflow::OpDef> op_defs;
	tensorflow::OpRegistry::Global()->GetRegisteredOps(&op_defs);
	for (std::vector<tensorflow::OpDef>::iterator it = op_defs.begin(); it != op_defs.end(); ++it)
	{
		if (it->name() == s)
			return true;
	}
	return false;
}

bool tfeOpHasKernel(char* operationName)
{
	std::string op_name(operationName);
	tensorflow::KernelList kl = tensorflow::GetAllRegisteredKernels();
	for (int i = 0; i < kl.kernel_size(); ++i)
	{
		tensorflow::KernelDef kd = kl.kernel(i);
		if (kd.op() == op_name)
			return true;
	}
	return false;
}