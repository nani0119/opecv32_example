#include <opencv2/opencv.hpp>
#include <iostream>

#define RESOURCE_DIR "../resource/"

void morphology_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout <<"img is empty" << std::endl;
        return;
    }

    cv::imshow("origin", img);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(5, 5));
    std::cout << "kernel:" << kernel << std::endl;

    cv::Mat dst;
    cv::erode(img, dst, kernel);
    cv::imshow("erode", dst);

    cv::dilate(img, dst, kernel);
    cv::imshow("dilate", dst);

    cv::morphologyEx(img, dst, cv::MORPH_OPEN, kernel);
    cv::imshow("open", dst);

    cv::morphologyEx(img, dst, cv::MORPH_CLOSE, kernel);
    cv::imshow("close", dst);

    cv::morphologyEx(img, dst, cv::MORPH_TOPHAT, kernel);
    cv::imshow("tophat", dst);

    cv::morphologyEx(img, dst, cv::MORPH_BLACKHAT, kernel);
    cv::imshow("blackhat", dst);

    cv::morphologyEx(img, dst, cv::MORPH_GRADIENT, kernel);
    cv::imshow("gradient", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    morphology_example();
    return 0;
}
