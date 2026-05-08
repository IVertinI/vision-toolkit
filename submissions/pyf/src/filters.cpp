#include "filters.h"

namespace vision {

cv::Mat toGrayscale(const cv::Mat& image) {
    if (image.channels() == 1) {
        return image.clone();
    }
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat gaussianBlur(const cv::Mat& image, int kernelSize, double sigma) {
    if (kernelSize % 2 == 0) {
        kernelSize += 1;
    }
    cv::Mat blurred;
    cv::GaussianBlur(image, blurred, cv::Size(kernelSize, kernelSize), sigma);
    return blurred;
}

cv::Mat sobelEdgeDetection(const cv::Mat& image) {
    cv::Mat gray = toGrayscale(image);
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    
    cv::Sobel(gray, grad_x, CV_16S, 1, 0, 3);
    cv::Sobel(gray, grad_y, CV_16S, 0, 1, 3);
    
    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    
    cv::Mat edges;
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, edges);
    
    return edges;
}

cv::Mat cannyEdgeDetection(const cv::Mat& image, double threshold1, double threshold2) {
    cv::Mat gray = toGrayscale(image);
    cv::Mat edges;
    cv::Canny(gray, edges, threshold1, threshold2);
    return edges;
}

} // namespace vision

int main()
{
    std::cout << "Vision Toolkit Test" << std::endl;
    
    // 创建测试图像
    cv::Mat testImage = cv::Mat::ones(100, 100, CV_8UC3) * 255;
    
    // 测试灰度转换
    cv::Mat gray = vision::toGrayscale(testImage);
    std::cout << "Grayscale image channels: " << gray.channels() << std::endl;
    
    // 测试高斯模糊
    cv::Mat blurred = vision::gaussianBlur(testImage, 5, 1.0);
    std::cout << "Blurred image size: " << blurred.size() << std::endl;
    
    // 测试边缘检测
    cv::Mat edges = vision::sobelEdgeDetection(testImage);
    std::cout << "Edges image size: " << edges.size() << std::endl;
    
    cv::Mat canny = vision::cannyEdgeDetection(testImage, 50, 150);
    std::cout << "Canny edges size: " << canny.size() << std::endl;
    std::cout<<"运行成功"<<std::endl;
    return 0;
}