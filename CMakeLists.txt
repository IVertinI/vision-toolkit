cmake_minimum_required(VERSION 3.10)
project(VisionToolkit)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS})

add_library(vision_toolkit STATIC
    src/filters.cpp
    src/transforms.cpp
)

target_link_libraries(vision_toolkit ${OpenCV_LIBS})

add_executable(app src/filters.cpp)
add_executable(demo examples/demo.cpp)
target_link_libraries(demo vision_toolkit)
target_link_libraries(app vision_toolkit)

# 测试
enable_testing()
find_package(GTest)
if(GTEST_FOUND)
    add_executable(test_filters tests/test_filters.cpp)
    target_link_libraries(test_filters vision_toolkit GTest::GTest GTest::Main)
    add_test(NAME FilterTests COMMAND test_filters)
endif()