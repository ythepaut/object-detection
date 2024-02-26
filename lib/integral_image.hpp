#ifndef OBJECT_DETECTION_INTEGRAL_IMAGE_HPP
#define OBJECT_DETECTION_INTEGRAL_IMAGE_HPP

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>

using cv::Mat;
using cv::Mat1b;
using cv::Mat1i;
using cv::Rect;
using std::vector;

/**
 * @brief Converts an image to grayscale.
 *
 * @param image The input image.
 * @return The grayscale image.
 */
Mat1b greyScale(const Mat &image);

/**
 * @brief Computes the integral image of the input image.
 *
 * The integral image is a two-dimensional matrix where each element represents the sum of the
 * pixels of the input image from the top left corner to the corresponding position.
 *
 * @param image The input image.
 * @return The computed integral image.
 */
Mat1i integralImage(const Mat &image);

/**
 * @brief Calculates the sum of the areas within a given region of a 2D matrix.
 *
 * @param integral The integral image matrix.
 * @param x1 The x-coordinate of the top-left corner of the region.
 * @param y1 The y-coordinate of the top-left corner of the region.
 * @param x2 The x-coordinate of the bottom-right corner of the region.
 * @param y2 The y-coordinate of the bottom-right corner of the region.
 * @return The sum of the areas within the specified region.
 */
int areaSum(const Mat1i &integral, int x1, int y1, int x2, int y2);

/**
 * @brief Compute Harr-like features for a given region in an integral image.
 *
 * @param integral The integral image containing the sums of pixel intensities.
 * @param region The rectangular region for which features need to be computed.
 *
 * @return A vector of float values representing the computed features.
 */
vector<float> computeFeatures(const Mat1i &integral, const Rect &region);

#endif
