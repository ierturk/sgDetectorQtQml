//
// Created by ierturk on 16/08/2019.
//

#include "SSDNet.h"

SSDNet::SSDNet()= default;
SSDNet::~SSDNet()= default;

void SSDNet::init(const char* model_path) {
    module = torch::jit::load(model_path);
    module.eval();
}

void SSDNet::setInput(QImage& image) {

    QImage image_scaled = image.scaled(
                320, 320,
                Qt::AspectRatioMode::IgnoreAspectRatio);

    auto in = torch::from_blob(image.data_ptr(), {1,3, 320, 320});
    input.emplace_back(in);
}

void SSDNet::forward(float* frame) {
    torch::NoGradGuard no_grad;
    // torch::jit::setGraphExecutorOptimize(true);
    auto input = std::vector<torch::jit::IValue>();
    auto in_blob = torch::from_blob(frame, {1, 3, 320, 320});
    input.emplace_back(in_blob);
    output = module.forward(input);
}

c10::IValue SSDNet::getOut() {
    return output;
}
