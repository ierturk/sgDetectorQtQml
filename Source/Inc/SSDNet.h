//
// Created by ierturk on 16/08/2019.
//

#ifndef SG_DETECTOR_SSDNET_H
#define SG_DETECTOR_SSDNET_H


#include <torch/torch.h>
#include <torch/script.h>

class SSDNet {

public:
    SSDNet();
    ~SSDNet();

    void Init(const char* model_path);
    // void setInput(const cv::Mat& frame);
    // void forward(const cv::Mat& frame);
    c10::IValue getOut();

private:
    unsigned int input_width = 320;
    unsigned int input_height = 320;
    torch::jit::script::Module module;
    c10::IValue output;
};


#endif //SG_DETECTOR_SSDNET_H
