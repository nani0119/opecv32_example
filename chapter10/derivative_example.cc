#include <opencv2/opencv.hpp>
#include <iostream>
#define RESOURCE_DIR "../resource/"

void derivative_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout <<"img is empty" << std::endl;
        return;
    }

    cv::imshow("originImg", img);
    cv::Mat dst;


    cv::Sobel(img, dst, CV_32F, 1, 0);
    cv::imshow("sobel-dx1dy0", dst);

    cv::Sobel(img, dst, CV_32F, 0, 1);
    cv::imshow("sobel-dx0dy1", dst);

    cv::Sobel(img, dst, CV_32F, 1, 1);
    cv::imshow("sobel-dx1dy1", dst);


    cv::Laplacian(img, dst, CV_32F, 3);
    cv::imshow("Laplacian-dx2dy2", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    derivative_example();
    return 0;
}
