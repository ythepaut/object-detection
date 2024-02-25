#ifndef OBJECT_DETECTION_MAIN_HPP
#define OBJECT_DETECTION_MAIN_HPP

#define PROGRAM_NAME "object_detection"

#include <iostream>
#include <argparse/argparse.hpp>
#include "window_stream.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

/**
 * @brief Initialize the argument parser with the specified options.
 *
 * @param parser The argparse::ArgumentParser object to be initialized.
 * @return void
 */
void initialiseArgumentParser(argparse::ArgumentParser &parser);

/**
 * @brief Parses command line arguments and populates variables.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of command line arguments.
 * @param parser The `argparse::ArgumentParser` object used for parsing.
 * @param usingStream A boolean variable to store the value of the `--stream` option.
 * @param inputImage A string variable to store the value of the `--input` option.
 * @param outputImage A string variable to store the value of the `--output` option.
 *
 * @return void
 * @throws std::runtime_error If an error occurs during parsing or if any required option is missing.
 */
void parseArguments(int argc, char *argv[], argparse::ArgumentParser &parser, bool &usingStream, string &inputImage,
                    string &outputImage);

int main(int argc, char *argv[]);

#endif
