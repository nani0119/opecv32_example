#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void filter2D_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);

    cv::Mat kx, ky;
    cv::getDerivKernels(kx, ky, 1, 1, 5);

    cv::Mat kernel = ky*kx.t();
    std::cout << "kernel:" << kernel << std::endl;

    cv::Mat dst;
    cv::filter2D(img, dst, CV_32F, kernel);

    cv::namedWindow("filter2D", CV_WINDOW_AUTOSIZE);
    cv::imshow("filter2D", dst);

    cv::Mat sepDst;
    cv::sepFilter2D(img, sepDst, CV_32F, kx, ky);

    cv::namedWindow("sepfilter2D", CV_WINDOW_AUTOSIZE);
    cv::imshow("sepfilter2D", sepDst);

    cv::Mat gaussianK = cv::getGaussianKernel(5, 1.);
    cv::Mat gaussianKernel = gaussianK*gaussianK.t();
    std::cout << "gaussian kernel:" << gaussianKernel << std::endl;
    cv::Mat gaussianDst;
    cv::filter2D(img, gaussianDst, CV_32F, gaussianKernel);

    cv::normalize(gaussianDst, gaussianDst, 0., 1.,cv::NORM_MINMAX, CV_32F);
    cv::namedWindow("gaussianfilter2D", CV_WINDOW_AUTOSIZE);
    cv::imshow("gaussianfilter2D", gaussianDst);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    filter2D_example();
    return 0;
}
