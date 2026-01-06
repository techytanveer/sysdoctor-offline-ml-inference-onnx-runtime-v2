import numpy as np
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline
from skl2onnx import convert_sklearn
from skl2onnx.common.data_types import FloatTensorType

# -----------------------------
# Training data (EXAMPLE)
# Replace with real data later
# -----------------------------
# Features:
# [cpu_usage, cpu_temp, ram_usage, disk_usage, log(load_1min), uptime_hours]
X = np.array([
    [0.20, 0.40, 0.30, 0.50, 0.10, 0.10],  # healthy
    [0.85, 0.70, 0.80, 0.60, 0.90, 0.30],  # high load
    [0.60, 0.95, 0.50, 0.40, 0.60, 0.20],  # overheating
    [0.40, 0.50, 0.60, 0.95, 0.40, 0.50],  # disk pressure
])

# Labels:
# 0 = healthy
# 1 = high load
# 2 = overheating
# 3 = disk pressure
y = np.array([0, 1, 2, 3])

# -----------------------------
# ML Pipeline
# -----------------------------
pipeline = Pipeline([
    ("scaler", StandardScaler()),
    ("clf", LogisticRegression(
        max_iter=500
    ))
])

pipeline.fit(X, y)

# -----------------------------
# Export to ONNX
# -----------------------------
initial_type = [
    ("input", FloatTensorType([None, 6]))
]

onnx_model = convert_sklearn(
    pipeline,
    initial_types=initial_type,
    target_opset=13
)

with open("sysdoctor_model.onnx", "wb") as f:
    f.write(onnx_model.SerializeToString())

print("✅ sysdoctor_model.onnx created successfully")

