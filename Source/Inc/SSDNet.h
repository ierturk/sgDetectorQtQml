//
// Created by ierturk on 16/08/2019.
//

#ifndef SG_DETECTOR_SSDNET_H
#define SG_DETECTOR_SSDNET_H

#include <torch/torch.h>
#include <torch/script.h>
#include <QVideoFrame>
#include <opencv2/opencv.hpp>

class SSDNet {
public:
    SSDNet();
    ~SSDNet();

    void init(const char* model_path);
    void setInput(QImage& image);
    void forward();
    void postProcess();
    QImage getOut();
    bool isInitialized();
    bool isInProgress();
    void setInProgress(bool status);


private:
    bool initialized = false;
    unsigned int input_width = 320;
    unsigned int input_height = 320;
    float confThreshold = 0.5f;
    float nmsThreshold = 0.4f;
    torch::jit::script::Module module;
    cv::Mat frame;
    std::vector<torch::jit::IValue> input;
    c10::IValue output;

    bool inProgress = false;

    std::vector<std::string> classes;

    void drawPred(int classId, float conf, int left, int top, int right, int bottom);

};


#endif //SG_DETECTOR_SSDNET_H
