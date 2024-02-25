cmake_minimum_required(VERSION 3.27)
project(object_detection)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

# Lib : OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Lib : argparse
include(FetchContent)
FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Lib : GTest
find_package(GTest QUIET)
include_directories(${GTEST_INCLUDE_DIRS})

# Executables
set(MAIN_EXEC main)
FOREACH (FILE ${MAIN_EXEC})
    add_executable(${FILE} ${FILE}.cpp window_stream.cpp lib/integral_image.cpp lib/detection.cpp lib/training.cpp lib/classifier.cpp)
    target_link_libraries(${FILE} ${OpenCV_LIBS} argparse)
ENDFOREACH (FILE)

# Tests
if(GTest_FOUND)
    enable_testing()
    set(TEST_EXEC test_lib)
    add_executable(${TEST_EXEC} tests/test_lib.cpp lib/integral_image.cpp lib/detection.cpp lib/training.cpp lib/classifier.cpp)
    target_link_libraries(${TEST_EXEC} ${GTEST_LIBRARIES} ${OpenCV_LIBS} argparse)

    add_test(NAME ${TEST_EXEC} COMMAND ${TEST_EXEC})
else()
    message(STATUS "GTest not found. Skipping tests.")
endif()
