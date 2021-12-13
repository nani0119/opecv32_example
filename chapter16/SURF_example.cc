#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <opencv2/xfeatures2d.hpp>

#define RESOURCE_DIR "../resource/"
using namespace std;

void SURF_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/16/checkerboard.jpg");
    if(img.empty())
    {
        cout << "img is empty" << endl;
        return;
    }

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SURF::create();
    std::vector<cv::KeyPoint> keypoint;
    f2d->detect(imgGray,keypoint);
    cv::Mat image_with_kp;
    cv::Mat descriptor;
    f2d->compute(imgGray,keypoint,descriptor);
    cv::drawKeypoints(imgGray, keypoint, image_with_kp, cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    cv::imshow("SURF keypoints", image_with_kp);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char *argv[])
{
    SURF_example();
    return 0;
}