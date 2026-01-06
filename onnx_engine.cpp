#include "../include/onnx_engine.h"
#include <onnxruntime_cxx_api.h>
#include <vector>
#include <cmath>

int run_onnx_inference(const SystemMetrics& m)
{
    static Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "sysdoctor");

    static Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(1);
    session_options.SetGraphOptimizationLevel(
        GraphOptimizationLevel::ORT_ENABLE_BASIC
    );

    static Ort::Session session(
        env,
        "model/sysdoctor_model.onnx",
        session_options
    );

    Ort::AllocatorWithDefaultOptions allocator;

    /* -------- Input / Output Names -------- */
    Ort::AllocatedStringPtr input_name =
        session.GetInputNameAllocated(0, allocator);

    Ort::AllocatedStringPtr output_name =
        session.GetOutputNameAllocated(0, allocator);

    const char* input_names[]  = { input_name.get() };
    const char* output_names[] = { output_name.get() };

    /* -------- Feature Vector (explicit float cast) -------- */
    std::vector<float> input = {
        static_cast<float>(m.cpu_usage)    / 100.0f,
        static_cast<float>(m.cpu_temp)     / 100.0f,
        static_cast<float>(m.ram_usage)    / 100.0f,
        static_cast<float>(m.disk_usage)   / 100.0f,
        static_cast<float>(std::log1p(m.load_1min)),
        static_cast<float>(m.uptime_hours) / 1000.0f
    };

    std::vector<int64_t> shape = { 1, static_cast<int64_t>(input.size()) };

    /* -------- Tensor Memory Info (REQUIRED) -------- */
    Ort::MemoryInfo mem_info =
        Ort::MemoryInfo::CreateCpu(
            OrtArenaAllocator,
            OrtMemTypeDefault
        );

    /* -------- Create Tensor (CORRECT overload) -------- */
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        mem_info,
        input.data(),
        input.size(),
        shape.data(),
        shape.size()
    );

    /* -------- Run Inference -------- */
    auto output_tensors = session.Run(
        Ort::RunOptions{ nullptr },
        input_names,
        &input_tensor,
        1,
        output_names,
        1
    );

    float* output =
        output_tensors[0].GetTensorMutableData<float>();

    int predicted_class =
        static_cast<int>(std::round(output[0]));

    return predicted_class;
}

