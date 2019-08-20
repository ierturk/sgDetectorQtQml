#include <torch/script.h>
#include <torch/torch.h>
#include <iostream>
#include <memory>

using namespace std::chrono;


void testTorch() {
    torch::NoGradGuard no_grad;

	torch::Tensor tensor = torch::rand({1, 4, 5});
	std::cout << tensor << std::endl;
	std::cout << tensor[0].slice(1, 4, 5) << '\n';


	torch::jit::script::Module module = torch::jit::load(
	        "/home/ierturk/Work/REPOs/ssd/ssdIE/outputs/mobilenet_v2_ssd320_clk_trainval2019/jit_model_040000.pt"
	        );
	
	// Create a vector of inputs.
	std::vector<torch::jit::IValue> inputs;
    torch::Tensor in = torch::rand({1, 3, 320, 320});
    inputs.emplace_back(in);
	
	for (int k = 0; k < 10; k++) {
		auto start = std::chrono::high_resolution_clock::now();
		auto outputs = module.forward(inputs).toTuple();
		// at::Tensor output = module.forward(inputs).toTensor();
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(end - start);
		std::cout << "inference taken : " << duration.count() << " ms" << '\n';

		// std::cout << output.slice(/*dim=*/1, /*start=*/0, /*end=*/5) << '\n';

		torch::Tensor out1 = outputs->elements()[0].toTensor();
		torch::Tensor out2 = outputs->elements()[1].toTensor();

		std::cout
			<< out1.size(0) << ", "
			<< out1.size(1) << ", "
			<< out1.size(2) << '\n';

		for (int i = 0; i < 3234; i++) {
			for (int j = 1; j < 78; j++) {
				if (out1[0][i][j].item<std::float_t>() > 0.2f) {
					std::cout << i << ", " << j << '\n';
				}
			}
		}

		std::cout << "ok "<< k << '\n';
	}
}
