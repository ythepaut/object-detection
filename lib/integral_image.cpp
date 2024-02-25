#include "integral_image.hpp"

Mat1b greyScale(const Mat &image)
{
    if (image.channels() == 1)
        return image.clone();
    Mat1b greyScaled;
    cvtColor(image, greyScaled, cv::COLOR_BGR2GRAY, 0);
    return greyScaled;
}

Mat1i integralImage(const Mat &image)
{
    Mat1b grey = greyScale(image);
    Mat1i integral;
    integral.create(grey.rows + 1, grey.cols + 1);
    integral.setTo(0);

    for (int row = 1; row <= grey.rows; ++row)
        for (int col = 1; col <= grey.cols; ++col)
            integral(row, col) = grey(row - 1, col - 1) + integral(row - 1, col) + integral(row, col - 1) -
                                 integral(row - 1, col - 1);

    return integral;
}

int areaSum(const Mat1i &integral, int x1, int y1, int x2, int y2)
{
    return integral(x2, y2) - integral(x1 - 1, y2) - integral(x2, y1 - 1) + integral(x1 - 1, y1 - 1);
}

vector<float> computeFeatures(const Mat1i &integral, const Rect &region)
{
    vector<float> features;

    for (int i = region.x; i < region.x + region.width; i += 2)
    {
        for (int j = region.y; j < region.y + region.height; j += 2)
        {
            if (i <= 0 || i >= integral.rows - 3) continue;
            if (j <= 0 || j >= integral.cols - 3) continue;

            // Compute the sum of pixel intensities within specified window for Harr-like features
            int totalIntensity = areaSum(integral, i, j, i + 2, j + 2);
            if (totalIntensity == 0) continue;

            // Compute the Harr-like features
            // Feature 1 : difference between sum of intensities of two vertical regions.
            int feature1 = areaSum(integral, i, j, i + 1, j + 2) - areaSum(integral, i + 1, j, i + 2, j + 2);
            // Feature 2 : difference between sum of intensities of two horizontal regions.
            int feature2 = areaSum(integral, i, j, i + 2, j + 1) - areaSum(integral, i, j + 1, i + 2, j + 2);
            // Feature 3 : Three-rectangle feature (horizontal)
            int feature3 = areaSum(integral, i, j, i + 2, j + 1) - 2 * areaSum(integral, i, j + 1, i + 2, j + 2) +
                           areaSum(integral, i, j + 2, i + 2, j + 3);
            // Feature 4 : Three-rectangle feature (vertical)
            int feature4 = areaSum(integral, i, j, i + 1, j + 2) - 2 * areaSum(integral, i + 1, j, i + 2, j + 2) +
                           areaSum(integral, i + 2, j, i + 3, j + 2);
            // Feature 5 : Four-rectangle feature
            int feature5 = areaSum(integral, i, j, i + 1, j + 1) - areaSum(integral, i + 1, j, i + 2, j + 1) -
                           areaSum(integral, i, j + 1, i + 1, j + 2) +
                           areaSum(integral, i + 1, j + 1, i + 2, j + 2);
            // Feature 6 : Four-rectangle feature (alternate arrangement)
            int feature6 = areaSum(integral, i + 1, j + 1, i + 2, j + 2) - areaSum(integral, i, j + 1, i + 1, j + 2) -
                           areaSum(integral, i + 1, j, i + 2, j + 1) +
                           areaSum(integral, i, j, i + 1, j + 1);
            // Feature 7 : Center-surround feature
            int feature7 =
                    4 * areaSum(integral, i + 1, j + 1, i + 2, j + 2) -
                    2 * (areaSum(integral, i, j + 1, i + 1, j + 2) + areaSum(integral, i + 1, j, i + 2, j + 1) +
                         areaSum(integral, i + 2, j + 1, i + 3, j + 2) +
                         areaSum(integral, i + 1, j + 2, i + 2, j + 3)) +
                    areaSum(integral, i, j, i + 1, j + 1) + areaSum(integral, i + 2, j, i + 3, j + 1) +
                    areaSum(integral, i, j + 2, i + 1, j + 3) + areaSum(integral, i + 2, j + 2, i + 3, j + 3);

            // Normalize the features by total intensity of the region and push into the vector
            features.push_back(static_cast<float>(feature1) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature2) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature3) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature4) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature5) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature6) / (float) totalIntensity);
            features.push_back(static_cast<float>(feature7) / (float) totalIntensity);
        }
    }
    return features;
}


