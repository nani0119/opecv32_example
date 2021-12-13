#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void equalizeHist_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    std::vector<cv::Mat> plane(3);
    std::vector<cv::Mat> dstPlane(3);
    cv::split(img, plane);


    for(int channel = 0; channel < 3;channel++)
    {
        cv::equalizeHist(plane[channel], dstPlane[channel]);
    }
    cv::Mat dst;
    cv::merge(dstPlane, dst);

    cv::imshow("img", img);
    cv::imshow("dst", dst);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    equalizeHist_example();
    return 0;
}
