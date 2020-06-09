#include "TensorFlowLite.h"
#include "tensorflow/lite/experimental/micro/kernels/micro_ops.h"
#include "tensorflow/lite/experimental/micro/micro_error_reporter.h"
#include "tensorflow/lite/experimental/micro/micro_interpreter.h"
#include "tensorflow/lite/experimental/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"
#include "eye_gestures_quantized.h"

#define DEBUG 0


namespace {
  tflite::ErrorReporter* error_reporter = nullptr;
  const tflite::Model* model = nullptr;
  tflite::MicroInterpreter* interpreter = nullptr;
  TfLiteTensor* model_input = nullptr;
  TfLiteTensor* model_output = nullptr;
  constexpr int tensor_arena_size = 93 * 1024;
  uint8_t tensor_arena[tensor_arena_size];

}
void setup() {
#if DEBUG
  while(!Serial);
#endif
  
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;
  model = tflite::GetModel(eye_gestures_quantized);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model version does not match");
  }
  //static tflite::ops::micro::AllOpsResolver resolver;
  static tflite::MicroMutableOpResolver resolver;
  resolver.AddBuiltin(
    tflite::BuiltinOperator_DEPTHWISE_CONV_2D,
    tflite::ops::micro::Register_DEPTHWISE_CONV_2D(),
    1,3);
  resolver.AddBuiltin(
    tflite::BuiltinOperator_CONV_2D,
    tflite::ops::micro::Register_CONV_2D(),
    1,3);
  resolver.AddBuiltin(
    tflite::BuiltinOperator_MAX_POOL_2D,
    tflite::ops::micro::Register_MAX_POOL_2D(),
    1,3);
  resolver.AddBuiltin(
    tflite::BuiltinOperator_FULLY_CONNECTED,
    tflite::ops::micro::Register_FULLY_CONNECTED(),
    1,3);
  
  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena,
                                       tensor_arena_size, error_reporter);
                               
  interpreter = &static_interpreter;
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk){
    error_reporter->Report("AllocateTensors() failed");
    while(1);
  }
  model_input = interpreter->input(0);
  model_output = interpreter->output(0);
  Serial.print("Number of dimensions: ");
  Serial.println(model_input->dims->size);
  Serial.println(model_input->dims->data[0]);
  Serial.println(model_input->dims->data[1]);
  Serial.println(model_input->dims->data[2]);
  Serial.println(model_input->dims->data[3]);
  Serial.print("Input type: ");
  Serial.println(model_input->type);

}

void loop() {
  uint8_t mt[30000];
  
  const uint8_t* image_data = mt;
  for (int i = 0; i < model_input->bytes; ++i) {
    model_input->data.uint8[i] = image_data[i];
  }
  TfLiteStatus invoke_status = interpreter->Invoke();
  if (invoke_status != kTfLiteOk) {
    error_reporter->Report("invoke failed");
  }
  float y_val = model_output->data.f[0];

  Serial.println(y_val);

  delay(1000);
  

}
