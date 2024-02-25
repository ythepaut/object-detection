#include "main.hpp"

void initialiseArgumentParser(argparse::ArgumentParser &parser)
{
    // Inputs mode (video stream / single image)
    auto &inputModeGroup = parser.add_mutually_exclusive_group(true);
    inputModeGroup.add_argument("-s", "--stream")
            .flag()
            .help("stream from webcam as input");

    inputModeGroup.add_argument("--in", "--input")
            .help("input image path");

    // Output (only for single image input)
    parser.add_argument("--out", "--output")
            .help("output image path");
}

void parseArguments(int argc, char *argv[], argparse::ArgumentParser &parser, bool &usingStream, string &inputImage,
                    string &outputImage)
{
    try
    {
        parser.parse_args(argc, argv);

        usingStream = parser.get<bool>("--stream");
        if (usingStream) return;

        inputImage = parser.get<string>("--input");
        outputImage = parser.get<string>("--output");
    }
    catch (std::runtime_error &err)
    {
        cerr << "Failed to parse arguments." << endl;
        cerr << err.what() << endl;
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    // Initialise argument parser
    argparse::ArgumentParser parser(PROGRAM_NAME);
    initialiseArgumentParser(parser);

    // Parse arguments
    bool usingStream;
    string inputImage;
    string outputImage;
    parseArguments(argc, argv, parser, usingStream, inputImage, outputImage);

    if (usingStream)
        startStream();
    else
        cout << "TODO" << endl;

    return 0;
}
