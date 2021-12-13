#include <opencv2/opencv.hpp>
#include <iostream>

#define RESOURCE_DIR "../resource/"

void threshold_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout <<"img is empty" << std::endl;
        return;
    }

    cv::imshow("originImg", img);
    cv::Mat binThresholdImg;
    double fixed_threshold = 100;
    int threshold_type = cv::THRESH_BINARY;
    cv::threshold(img, binThresholdImg, fixed_threshold, 255, threshold_type);
    cv::imshow("binary threshold", binThresholdImg);

    int adaptive_method = cv::ADAPTIVE_THRESH_MEAN_C;
    int block_size = 15;
    double offset = 10;
    cv::adaptiveThreshold(img, binThresholdImg, 255, adaptive_method, threshold_type, block_size, 0);
    cv::imshow("adaptive threshold", binThresholdImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    threshold_example();
    return 0;
}
