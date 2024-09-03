import torch
if __name__ == "__main__":
    vec = torch.tensor([-2, -1, 0, 1, 2], dtype=torch.float32)
    print("vec: ", vec)
    
    # 1. Sigmoid
    sigmoid_res = torch.nn.functional.sigmoid(vec)
    print("Sigmoid: ", sigmoid_res)
    
    # 2. ReLU
    relu_res = torch.nn.functional.relu(vec)
    print("ReLU: ", relu_res)
    
    # 3. Leaky ReLU
    leaky_relu_res = torch.nn.functional.leaky_relu(
        vec, negative_slope=0.1
    )
    print("Leaky ReLU: ", leaky_relu_res)