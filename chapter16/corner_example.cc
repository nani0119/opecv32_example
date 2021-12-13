#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"

using namespace std;

void corner_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/16/checkerboard.jpg");
    if(img.empty())
    {
        cout << "img is empty" << endl;
        return;
    }

    //cv::GaussianBlur(img, img, cv::Size(5,5), 3);

    //cv::imshow("img", img);

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Point2f> corners;
    int maxCorners = 2000;
    double qualityLevel = 0.01;
    double minDistance = 10;
    int blockSize = 3;
    double k = 0.04;
    cv::goodFeaturesToTrack(imgGray, corners, maxCorners, qualityLevel,minDistance, cv::noArray(), blockSize, false, k);

    for(vector<cv::Point2f>::iterator it = corners.begin(); it != corners.end(); ++it)
    {
        cv::circle(img, *it, 5, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
    }
    cv::imshow("goodFeaturesToTrack", img);

    cv::Size winSize(4, 4);
    cv::Size zeroZone(-1, -1);
    //cv::TermCriteria criteria = cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 40, 0.01);
    cv::TermCriteria criteria = cv::TermCriteria(CV_TERMCRIT_EPS, 0, 0.01);
    cv::cornerSubPix(imgGray, corners, winSize, zeroZone, criteria);

    for(vector<cv::Point2f>::iterator it = corners.begin(); it != corners.end(); ++it)
    {
        cv::circle(img, *it, 5, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    }
    cv::imshow("cornerSubPix", img);
    cv::waitKey(0);
    cv::destroyAllWindows();

}


int main(int argc, char const *argv[])
{
    corner_example();
    return 0;
}
