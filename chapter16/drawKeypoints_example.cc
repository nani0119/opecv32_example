#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"
using namespace std;

void myTrackbar0Callback(int pos, void* param)
{
    cv::Mat img(400, 400, CV_8UC3, cv::Scalar(225, 255, 255));
    cv::Mat imgKp;
    cv::KeyPoint kp1;
    kp1.pt = cv::Point2d(200, 200);
    kp1.size = 100;
    kp1.angle = pos;
    std::vector<cv::KeyPoint> keypoints;

    keypoints.push_back(kp1);
    cv::drawKeypoints(img, keypoints, imgKp, cv::Scalar(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("display-keypoint", imgKp);
}

void drawKeypoints_example()
{
    int angel = 0;


    cv::namedWindow("display-keypoint");
    cv::setTrackbarMin("angle", "display-keypoint", 0);
    cv::setTrackbarMax("angle", "display-keypoint", 360);
    cv::createTrackbar("angle", "display-keypoint", &angel, 360, myTrackbar0Callback);

    myTrackbar0Callback(0, nullptr);

    while(1)
    {
        char key =(char)cv::waitKey(0);
        if(key == 'q')
        {
            break;
        }
    }
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    drawKeypoints_example();
    return 0;
}
