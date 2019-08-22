//
// Created by ierturk on 16/08/2019.
//


#include "SSDNet.h"
#include <QtCore/QFile>
#include <QtCore/QJsonParseError>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>

SSDNet::SSDNet()= default;;
SSDNet::~SSDNet()= default;;

void SSDNet::init(const char* model_path) {
    module = torch::jit::load(model_path);
    module.eval();

    QFile inFile("/home/ierturk/Work/REPOs/ssd/yoloData/clk/train.json");
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr{};
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        // qDebug() << "Parse failed";
    }

    QJsonObject rootObj = doc.object();
    QJsonArray ptsArray = rootObj.value("categories").toArray();
    foreach(const QJsonValue & val, ptsArray) {
        classes.emplace_back(val.toObject().value("name").toString().toUtf8().constData());
    }

}

void SSDNet::setInput(QImage& image) {
    cv::Mat cv_blob;
    torch::Tensor torch_blob;

    frame =
            cv::Mat(
            image.height(),
            image.width(),
            CV_8UC4,
            image.bits(),
            image.bytesPerLine())
            .clone();

    cv_blob = cv::dnn::blobFromImage(
            frame,
            1.0,
            cv::Size(320,320),
            cv::Scalar(123, 117, 104),
            true,
            false,
            CV_32F);

    torch_blob =
            torch::from_blob(
                    cv_blob.data,
                    {1, 3, input_width, input_height});

    input.emplace_back(torch_blob);
}

void SSDNet::forward() {
    torch::NoGradGuard no_grad;

    if(input.empty())
        return;

    output = module.forward(input);
    input.clear();
    // postProcess();
}

QImage SSDNet::getOut() {
    return QImage(
            frame.data,
            frame.cols,
            frame.rows,
            frame.step,
            QImage::Format_ARGB32
            ).copy();
}

void SSDNet::postProcess() {
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;

    auto out_tuple = output.toTuple();
    torch::Tensor ssd_scores = out_tuple->elements()[0].toTensor();
    torch::Tensor ssd_boxes = out_tuple->elements()[1].toTensor();

    auto score = ssd_scores.accessor<float, 3>();
    auto box = ssd_boxes.accessor<float, 3>();


    for (size_t i = 0; i < 3234; i++) {
        for (size_t j = 1; j < 78; j++) {
            float confidence = score[0][i][j];
            if (confidence > confThreshold)
            {
                int left = (int)(box[0][i][0] * frame.cols);
                int top = (int)(box[0][i][1] * frame.rows);
                int right = (int)(box[0][i][2] * frame.cols);
                int bottom = (int)(box[0][i][3] * frame.rows);
                int width = right - left + 1;
                int height = bottom - top + 1;

                classIds.push_back((int)j - 1);;
                confidences.push_back((float)confidence);
                boxes.emplace_back(left, top, width, height);
            }
        }
    }

    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (int idx : indices)
    {
        cv::Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height);
    }
}

void SSDNet::drawPred(int classId, float conf, int left, int top, int right, int bottom) {
        rectangle(frame, cv::Point(left, top), cv::Point(right, bottom), cv::Scalar(0, 255, 0));

        std::string label = cv::format("%.2f", conf);
        if (!classes.empty()) {
            CV_Assert(classId < (int)classes.size());
            label = classes[classId] + ": " + label;
        }

        int baseLine;
        cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

        top = cv::max(top, labelSize.height);
        rectangle(frame, cv::Point(left, top - labelSize.height),
                  cv::Point(left + labelSize.width, top + baseLine), cv::Scalar::all(255), cv::FILLED);
        putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar());
}

