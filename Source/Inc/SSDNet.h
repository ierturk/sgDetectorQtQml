//
// Created by ierturk on 16/08/2019.
//

#ifndef SG_DETECTOR_SSDNET_H
#define SG_DETECTOR_SSDNET_H

#include <torch/torch.h>
#include <torch/script.h>
#include <QVideoFrame>

class SSDNet {
public:
    SSDNet(const char* model_path);
    ~SSDNet();

    void init(const char* model_path);
    void setInput(QImage& image);
    void forward(float* frame);
    c10::IValue getOut();

private:
    unsigned int input_width = 320;
    unsigned int input_height = 320;
    torch::jit::script::Module module;
    std::vector<torch::jit::IValue> input;
    c10::IValue output;
};


#endif //SG_DETECTOR_SSDNET_H
