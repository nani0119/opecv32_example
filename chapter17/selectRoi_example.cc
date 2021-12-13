#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

#define RESOURCE_DIR "../resource/"

int main(int argc, char const *argv[])
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/9/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return 1;
    }
    //cv::namedWindow("roi-img");
    bool fromCenter = false;
    bool showcrossair = false;
    cv::Rect2d rect = cv::selectROI("selectRoi", img, showcrossair, fromCenter);
    //cv::Rect2d rect = cv::selectROI(img,fromCenter);
    cv::imshow("roi-img", img(rect));
    std::cout <<"roi rect:"<< rect << std::endl;

    cv::waitKey(0);
    cv::destroyAllWindows();



    /* code */
    return 0;
}
