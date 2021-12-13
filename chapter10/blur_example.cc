#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void blur_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);

    cv::Mat simpleBlurDst;
    cv::namedWindow("simple-blur", CV_WINDOW_AUTOSIZE);
    cv::blur(img, simpleBlurDst, cv::Size(5,5));
    cv::imshow("simple-blur", simpleBlurDst);

    cv::Mat boxFilterDst;
    cv::namedWindow("box-blur", CV_WINDOW_AUTOSIZE);
    cv::boxFilter(img, boxFilterDst, -1, cv::Size(5, 5));
    cv::imshow("box-blur", boxFilterDst);

    cv::Mat medianFilterDst;
    cv::namedWindow("median-blur", CV_WINDOW_AUTOSIZE);
    cv::medianBlur(img, medianFilterDst, 5);
    cv::imshow("median-blur", medianFilterDst);


    cv::Mat gaussianFilterDst;
    cv::GaussianBlur(img, gaussianFilterDst, cv::Size(5,5), 1., 1.);
    cv::namedWindow("gaussian-blur", CV_WINDOW_AUTOSIZE);
    cv::imshow("gaussian-blur", gaussianFilterDst);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


int g_d = 15;
int g_sigmaColor = 20;
int g_sigmaSpace = 50;


void on_Trackbar(int pos, void* param)
{
    if(param == nullptr)
    {
        std::cout << "param is null" << std::endl;
        return;
    }
    cv::Mat& img = *((cv::Mat*)param);

    cv::Mat bilaterFilterDst;
    cv::bilateralFilter(img, bilaterFilterDst, g_d, g_sigmaColor, g_sigmaSpace);
    cv::imshow("bilaterFilter", bilaterFilterDst);

}

void bilateralFilter_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/10/checkerboard.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);

    cv::Mat bilaterFilterDst;
    cv::bilateralFilter(img, bilaterFilterDst, g_d, g_sigmaColor, g_sigmaSpace);

    cv::namedWindow("bilaterFilter", CV_WINDOW_AUTOSIZE);
    cv::createTrackbar("d","bilaterFilter", &g_d, 50, on_Trackbar, (void*)&img);
    cv::createTrackbar("sigma-color","bilaterFilter", &g_sigmaColor, 100, on_Trackbar, (void*)&img);
    cv::createTrackbar("sigma-space","bilaterFilter", &g_sigmaSpace, 100, on_Trackbar, (void*)&img);

    cv::imshow("bilaterFilter", bilaterFilterDst);


    cv::waitKey(0);
    cv::destroyAllWindows();


}

int main(int argc, char const *argv[])
{
    blur_example();
    bilateralFilter_example();
    return 0;
}
