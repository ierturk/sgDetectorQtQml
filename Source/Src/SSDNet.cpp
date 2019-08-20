//
// Created by ierturk on 16/08/2019.
//

#include "SSDNet.h"

SSDNet::SSDNet()= default;
SSDNet::~SSDNet()= default;

void SSDNet::Init(const char* model_path) {
    torch::NoGradGuard no_grad;
    // torch::jit::setGraphExecutorOptimize(false);

    module = torch::jit::load(model_path);
    module.eval();
}

/*
void SSDNet::forward(const cv::Mat& frame) {
    torch::NoGradGuard no_grad;
    // torch::jit::setGraphExecutorOptimize(true);


    std::vector<torch::jit::IValue> input = std::vector<torch::jit::IValue>();

    input.emplace_back(torch::from_blob(
            cv::dnn::blobFromImage(
                    frame,
                    1.0,
                    cv::Size(input_width,input_height),
                    cv::Scalar(123, 117, 104),
                    true,
                    false,
                    CV_32F).data,
                    {1, 3, input_width, input_height}));

    output = module.forward(input);
}
*/

c10::IValue SSDNet::getOut() {
    return output;
}
