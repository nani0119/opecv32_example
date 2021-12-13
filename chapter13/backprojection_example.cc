#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void backprojection_example()
{
    cv::Mat grass = cv::imread(RESOURCE_DIR"/13/grass.png");
    if(grass.empty())
    {
        std::cout << "grass img is empty" << std::endl;
        return;
    }
    cv::imshow("grass", grass);

    cv::Mat grass_hsv;
    cv::cvtColor(grass, grass_hsv, cv::COLOR_BGR2HSV);

    int h_bins = 8;
    int s_bins = 8;
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 255};


    cv::Mat grass_hist;
    int grass_channel[] = {0, 1};

    int grass_hist_size[] = {h_bins, s_bins};
    const float* grass_ranges[] = {h_ranges, s_ranges};
    cv::calcHist(&grass_hsv, 1, grass_channel, cv::noArray(), grass_hist, 2, grass_hist_size, grass_ranges);

    cv::Mat messi = cv::imread(RESOURCE_DIR"/13/messi.png");
    if(messi.empty())
    {
        std::cout << "messi img is empty" << std::endl;
        return;
    }
    cv::imshow("messi", messi);

    cv::Mat messi_hsv;
    cv::Mat backproject;
    cv::cvtColor(messi, messi_hsv, cv::COLOR_BGR2HSV);
    int messi_channel[] = {0, 1};
    const float* messi_ranges[] = {h_ranges, s_ranges};
    cv::calcBackProject(&messi_hsv, 1, messi_channel, grass_hist, backproject, messi_ranges);


    cv::imshow("backprojection", backproject);

    cv::Mat backprojectInv;
    cv::threshold(backproject, backprojectInv, 255/2, 255, cv::THRESH_BINARY_INV);
    cv::imshow("backprojection-inv", backprojectInv);


    cv::Mat grassImg (messi.size(), messi.type(), cv::Scalar(255,255,255));
    cv::Mat messiImg (messi.size(), messi.type(), cv::Scalar(255,255,255));

    messi.copyTo(grassImg, backproject);
    messi.copyTo(messiImg, backprojectInv);

    cv::imshow("messiImg", messiImg);
    cv::imshow("grassImg", grassImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    backprojection_example();
    return 0;
}
