#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char const *argv[])
{
    cv::Mat img = cv::imread(argv[1]);
    if(img.empty())
    {
        std::cout << "not find image" << std::endl;
        return -1;
    }
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example", img);
    cv::waitKey(0);
    cv::destroyWindow("Example");
    return 0;
}
