#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "../lib/integral_image.hpp"

TEST(IntegralImageTest, IntegralImage)
{
    // Given
    Mat input = (cv::Mat_<ushort>(5, 5) <<
            1, 7, 4, 2, 9,
            7, 2, 3, 8, 2,
            1, 8, 7, 9, 1,
            3, 2, 3, 1, 5,
            2, 9, 5, 6, 6);
    Mat expectedIntegral = (cv::Mat_<ushort>(6, 6) <<
            0, 0, 0, 0, 0, 0,
            0, 1, 8, 12, 14, 23,
            0, 8, 17, 24, 34, 45,
            0, 9, 26, 40, 59, 71,
            0, 12, 31, 48, 68, 85,
            0, 14, 42, 64, 90, 113);

    // When
    Mat1i integral = integralImage(input);

    // Then
    for (int row = 0; row < integral.rows; ++row)
        for (int col = 0; col < integral.cols; ++col)
            EXPECT_EQ(integral(row, col), expectedIntegral.at<ushort>(row, col));
}

TEST(IntegralImageTest, AreaSum)
{
    // Given
    Mat input = (cv::Mat_<ushort>(5, 5) <<
            1, 7, 4, 2, 9,
            7, 2, 3, 8, 2,
            1, 8, 7, 9, 1,
            3, 2, 3, 1, 5,
            2, 9, 5, 6, 6);
    Mat1i integral = integralImage(input);

    // When
    int sum1 = areaSum(integral, 0, 0, 3, 3);
    int sum2 = areaSum(integral, 3, 3, 4, 4);
    int sum3 = areaSum(integral, 2, 3, 2, 3);
    int sum4 = areaSum(integral, 2, 0, 3, 3);

    // Then
    EXPECT_EQ(sum1, 68);
    EXPECT_EQ(sum2, 18);
    EXPECT_EQ(sum3, 9);
    EXPECT_EQ(sum4, 34);
}
