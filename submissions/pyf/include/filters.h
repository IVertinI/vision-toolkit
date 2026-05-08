#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>

namespace vision {

// 灰度化
cv::Mat toGrayscale(const cv::Mat& image);

// 高斯模糊
cv::Mat gaussianBlur(const cv::Mat& image, int kernelSize = 5, double sigma = 1.0);

// Sobel边缘检测
cv::Mat sobelEdgeDetection(const cv::Mat& image);

// Canny边缘检测
cv::Mat cannyEdgeDetection(const cv::Mat& image, double threshold1 = 50, double threshold2 = 150);

} // namespace vision

#endif