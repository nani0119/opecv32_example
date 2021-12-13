#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void canny_edage_dect_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/lena.bmp", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::imshow("img", img);

    cv::Mat imgBlur;
    cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 5);

    cv::imshow("imgblur", imgBlur);

    cv::Mat imgEdage;
    cv::Canny(imgBlur, imgEdage, 50, 150);

    cv::imshow("imgEdage", imgEdage);


    cv::waitKey(0);
    cv::destroyAllWindows();
}



int main(int argc, char const *argv[])
{
    canny_edage_dect_example();
    return 0;
}
