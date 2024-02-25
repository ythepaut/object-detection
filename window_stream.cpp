#include "window_stream.hpp"

void printHelp()
{
    cout << endl << "Preview controls :" << endl;
    cout << "d : Show detection" << endl;
    cout << "o : Show original input stream" << endl;
    cout << "g : Show greyscale input stream" << endl;
    cout << "i : Show integral image" << endl;
    cout << "q : Quit" << endl;
    cout << endl;
}

void updateWindow(const string &name, const Mat &image)
{
    cv::namedWindow(name, cv::WINDOW_NORMAL);
    cv::imshow(name, image);
}

cv::VideoCapture getVideoInput()
{
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cerr << "Error: Could not start video capture." << endl;
        exit(1);
    }
    return cap;
}

void convertIntegralImageToDisplayableFrame(const Mat1i &integral, Mat &output)
{
    // Crop into original frame dimension
    Mat1i integralCropped = integral(cv::Rect(1, 1, integral.cols - 1, integral.rows - 1));

    // Normalize
    double min, max;
    cv::minMaxLoc(integralCropped, &min, &max);
    integralCropped.convertTo(output, CV_8UC3, 255.0 / (max - min), -min * 255.0 / (max - min));
}

void startStream()
{
    cv::VideoCapture cap = getVideoInput();
    printHelp();

    Mat frame;
    OutputMode mode = INTEGRAL_IMAGE;
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    char key;
    while (true)
    {
        // Capture frame
        cap >> frame;
        if (frame.empty()) break;

        // Compute output
        Mat output;
        switch (mode)
        {
            case INPUT:
                output = frame;
                break;
            case GREY_SCALE:
                cv::cvtColor(frame, output, cv::COLOR_BGR2GRAY);
                break;
            case DETECTION:
                detection(frame, output);
                break;
            case INTEGRAL_IMAGE:
                Mat1i integral = integralImage(frame);
                output.create(integral.rows - 1, integral.cols - 1, CV_8UC3);
                convertIntegralImageToDisplayableFrame(integral, output);
                break;
        }

        // Display
        updateWindow(PREVIEW_WINDOW_NAME, output);

        // Performance
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        counter++;
        if (elapsed.count() > 1.0)
        {
            double fps = counter / elapsed.count();
            std::cout << "\rFPS : " << fps << "\tMODE : " << mode << std::flush;
            start = std::chrono::high_resolution_clock::now();
            counter = 0;
        }

        // Actions
        key = (char) cv::waitKey(1);
        if (key == ACTION_QUIT) break;
        if (key == ACTION_ORIGINAL) mode = INPUT;
        if (key == ACTION_GREY_SCALE) mode = GREY_SCALE;
        if (key == ACTION_DETECTION) mode = DETECTION;
        if (key == ACTION_INTEGRAL) mode = INTEGRAL_IMAGE;
    }

    cap.release();
    cv::destroyWindow(PREVIEW_WINDOW_NAME);
}
