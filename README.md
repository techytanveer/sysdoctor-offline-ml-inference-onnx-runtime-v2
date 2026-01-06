#  SysDoctor (ONNX Version)

SysDoctor is a **Linux system diagnostics tool written in C++** that combines:

* **Rule‑Based AI** (deterministic, configurable)
* **Offline ML Inference (ONNX Runtime)**

This version uses an **ONNX machine‑learning model** to detect system health patterns **offline**, without Python or cloud dependencies at runtime.

---

##  Key Features

*  Native **C++ Linux application**
*  **Hybrid AI architecture** (Rules + ML)
*  **JSON‑based configuration** (no recompilation needed)
*  **Offline inference** using ONNX Runtime
*  No telemetry, no cloud, no runtime training

---

##  Architecture Overview

```
System Metrics
     ↓
Rule Engine (Option A)
     ↓
ONNX ML Inference (Option B)
     ↓
Diagnosis Aggregation
     ↓
Human‑Readable Output
```

### Design Principles

* **Rules are authoritative** (safety & determinism)
* **ML is advisory** (pattern recognition)
* **LLMs (future)** explain results, never decide

---

##  Project Structure

```
sysdoctoronnx/
├── src/
│   ├── main.cpp
│   ├── metrics.cpp
│   ├── ai_engine.cpp
│   ├── onnx_engine.cpp
│   └── ...
├── include/
│   └── *.h
├── model/
│   └── sysdoctor_model.onnx
├── rules.json
├── CMakeLists.txt
└── README.md
```

---

##  ONNX Model Details

### Model File

```
model/sysdoctor_model.onnx
```

### Input Tensor

* **Shape:** `[1, 6]`
* **Type:** `float32`

| Index | Feature         | Description               |
| ----: | --------------- | ------------------------- |
|     0 | CPU usage       | Normalized (0–1)          |
|     1 | CPU temperature | Normalized (0–1)          |
|     2 | RAM usage       | Normalized (0–1)          |
|     3 | Disk usage      | Normalized (0–1)          |
|     4 | Load average    | `log1p(load_1min)`        |
|     5 | Uptime          | Normalized (hours / 1000) |

### Output

Single float value interpreted as a **class label**:

| Label | Meaning           |
| ----: | ----------------- |
|     0 | System healthy    |
|     1 | High load pattern |
|     2 | Overheating risk  |
|     3 | Disk pressure     |

>  Output semantics are defined by SysDoctor, not ONNX.

---

##  Building SysDoctor

### 1️ Dependencies

* C++17 compiler (GCC / Clang)
* CMake ≥ 3.10
* ONNX Runtime (prebuilt)
* nlohmann/json

### 2️ Install ONNX Runtime (CPU)

```bash
wget https://github.com/microsoft/onnxruntime/releases/download/v1.17.3/onnxruntime-linux-x64-1.17.3.tgz
tar -xvf onnxruntime-linux-x64-1.17.3.tgz
sudo mkdir -p /usr/local/onnxruntime
sudo cp -r onnxruntime-linux-x64-1.17.3/include /usr/local/onnxruntime/
sudo cp -r onnxruntime-linux-x64-1.17.3/lib /usr/local/onnxruntime/

echo "/usr/local/onnxruntime/lib" | sudo tee /etc/ld.so.conf.d/onnxruntime.conf
sudo ldconfig
```

---

### 3️ Build

```bash
mkdir build
cd build
cmake ..
make -j
```

---

##  Running

```bash
./sysdoctor
```

> ⚠️ Do **not** use `sudo` unless required. Relative paths may fail under `sudo`.

---

##  Configuration (rules.json)

Rules are loaded from `rules.json` at runtime.

Example:

```json
{
  "cpu_temp_critical": 85,
  "cpu_usage_high": 80,
  "ram_usage_high": 85,
  "disk_usage_high": 80,
  "disk_usage_critical": 90,
  "load_avg_high": 4.0,
  "uptime_reboot_hours": 720
}
```

This allows tuning system behavior **without recompiling**.

---

##  Training the ONNX Model

The ONNX model is **not generated automatically**.

It is trained separately using Python and exported to ONNX.

See:

```
train_sysdoctor_model.py
```

Frameworks used:

* scikit‑learn
* skl2onnx

At runtime, **Python is NOT required**.

---

##  Security & Privacy

* ✔ Fully offline
* ✔ No telemetry
* ✔ No cloud calls
* ✔ Deterministic execution

Safe for:

* Servers
* Air‑gapped systems
* Enterprise environments

---

##  Roadmap

* [v3] LLM explanations (llama.cpp)

---

##  License

MIT / Apache‑2.0 (choose as appropriate)

---

## 👤 Author

Tanveer Ahmed
Linux C++ | Systems Engineering | Hybrid AI

---

##  Final Note

SysDoctor demonstrates **how AI should be built in system software**:

> Rules first. ML assists. Humans stay in control.

This is intentional, safe, and production‑ready.
