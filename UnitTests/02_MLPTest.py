import torch

if __name__ == "__main__":
    # Set a fixed seed for reproducibility
    torch.manual_seed(0)
    our_mlp = torch.nn.Linear(4, 4)
    #print("Our MLP:", our_mlp.state_dict())
    
    weight = our_mlp.state_dict()["weight"]
    bias = our_mlp.state_dict()["bias"]
    #print("Weight:", weight)
    #print("Bias:", bias)
    
    test_input = torch.arange(4, dtype=torch.float32)
    print("Input:", test_input)
    
    # Forward pass
    output = our_mlp(test_input)
    print("Output:", output)
