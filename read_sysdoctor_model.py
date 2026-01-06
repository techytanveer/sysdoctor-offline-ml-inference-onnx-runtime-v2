import onnx

# Load the model
model = onnx.load("sysdoctor_model.onnx")

# Check that the model is well-formed
onnx.checker.check_model(model)

# Print the model's metadata and graph inputs
print(onnx.helper.printable_graph(model.graph))
