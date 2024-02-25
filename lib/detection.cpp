#include "detection.hpp"

void detection(const Mat &input, Mat &output)
{
    input.convertTo(output, CV_8UC3);
    Mat1i integral = integralImage(input);
    // TODO implement detection
    vector<Rect> detections;

    // Test detection
    detections.emplace_back(output.cols / 2 - 25, output.rows / 2 - 25, 50, 50);

    // Draw detections
    for (auto &detection : detections)
        rectangle(output, detection, cv::Scalar(255, 255, 255), 2);
}
