#ifndef OBJECT_DETECTION_DETECTION_HPP
#define OBJECT_DETECTION_DETECTION_HPP

#include <opencv2/core/mat.hpp>
#include "integral_image.hpp"

using cv::Mat;
using cv::Mat_;
using cv::Mat1b;
using cv::Mat1f;
using cv::Mat3b;
using cv::Mat3f;

/**
 * @brief Detects objects in an image.
 *
 * @param input The input image.
 * @param output Copy of the input image with the detected objects highlighted.
 */
void detection(const Mat &input, Mat &output);

#endif
