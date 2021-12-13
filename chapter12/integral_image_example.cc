#include <iostream>
#include <opencv2/opencv.hpp>
#define RESOURCE_DIR "../resource/"

void integral_image_example()
{
    cv::Mat m = (cv::Mat_<unsigned char>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 3);

    cv::Mat sum;
    cv::integral(m, sum);
    std::cout << "sum:" << std::endl << sum << std::endl;

    cv::Mat squaredSum;
    cv::integral(m, sum, squaredSum, CV_32F);
    std::cout << "sum:" << std::endl << sum << std::endl;
    std::cout << "sumsquaredSum:" << std::endl << squaredSum << std::endl;

    cv::Mat tiltedSum;
    cv::integral(m, sum, squaredSum, tiltedSum, CV_32F);
    std::cout << "sum:" << std::endl << sum << std::endl;
    std::cout << "sumsquaredSum:" << std::endl << squaredSum << std::endl;
    std::cout << "tiltedSum:" << std::endl << tiltedSum << std::endl;

    //=====================================================================

    cv::Mat img = cv::imread(RESOURCE_DIR"/12/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::normalize(img, img, 0, 1, cv::NORM_MINMAX, CV_32F);

    cv::Mat sumImg;
    cv::Mat squaredSumImg;
    cv::Mat tiltedSumImg;
    cv::integral(img, sumImg, squaredSumImg, tiltedSumImg);

    cv::normalize(sumImg, sumImg, 0, 1, cv::NORM_MINMAX, CV_32F);
    cv::normalize(squaredSumImg, squaredSumImg, 0, 1, cv::NORM_MINMAX, CV_32F);
    cv::normalize(tiltedSumImg, tiltedSumImg, 0, 1, cv::NORM_MINMAX, CV_32F);

    cv::imshow("sum", sumImg);
    cv::imshow("squaredSumImg", squaredSumImg);
    cv::imshow("titledSumImg", tiltedSumImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}



int main(int argc, char const *argv[])
{
    integral_image_example();
    return 0;
}
