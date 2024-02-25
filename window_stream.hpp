#ifndef OBJECT_DETECTION_WINDOW_H
#define OBJECT_DETECTION_WINDOW_H

#define PREVIEW_WINDOW_NAME "Preview"

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <chrono>
#include "lib/detection.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

using cv::Mat;

enum OutputMode {
    INPUT, GREY_SCALE, DETECTION, INTEGRAL_IMAGE
};

enum Action {
    ACTION_QUIT = 'q', ACTION_ORIGINAL = 'o', ACTION_GREY_SCALE = 'g', ACTION_DETECTION = 'd', ACTION_INTEGRAL = 'i'
};

/**
 * @brief Prints the window controls
 */
void printHelp();

/**
 * @brief Updates a window with an image.
 *
 * @param name The name of the window.
 * @param image The image to be shown in the window.
 */
void updateWindow(const string& name, const Mat &image);

/**
 * @brief Gets the default video input.
 *
 * @return cv::VideoCapture
 */
cv::VideoCapture getVideoInput();

/**
 * @brief Converts integral 1-channel integer matrix into a 3-channel float matrix
 * @param integral Input matrix
 * @param output Output Mat3f
 */
void convertIntegralImageToDisplayableFrame(const Mat1i &integral, Mat &output);

/**
 * @brief Starts the video streaming from the default camera, captures frames, and displays them in a window.
 */
void startStream();

#endif
