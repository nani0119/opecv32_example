#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"
using namespace std;


void FastFeatureDetector_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR "/16/checkerboard.jpg");
    if (img.empty())
    {
        cout << "img is empty" << endl;
        return;
    }

    //cv::GaussianBlur(img, img, cv::Size(5,5), 3);

    //cv::imshow("img", img);

    //cv::Mat imgGray;
    //cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
   // cv::Mat imgGray = img.clone();

    int threshold = 30;
    bool nonmaxSuppression = true;
    //int type = cv::FastFeatureDetector::TYPE_9_16;
    cv::FastFeatureDetector::DetectorType type = cv::FastFeatureDetector::TYPE_9_16;
    cv::Ptr<cv::FastFeatureDetector> detector = cv::FastFeatureDetector::create(threshold, nonmaxSuppression, type);

    vector<cv::KeyPoint> keypoints;
    detector->detect(img, keypoints, cv::noArray());

    for (vector<cv::KeyPoint>::iterator it = keypoints.begin(); it != keypoints.end(); ++it)
    {
        cv::circle(img, it->pt, 3, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    }

    cout << "descriptorSize:" << detector->descriptorSize() << endl;
    cout << "descriptorType:" << detector->descriptorType() << endl;
    cout << "defaultNorm:" << detector->defaultNorm() << endl;
    cv::imshow("keypoints", img);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    FastFeatureDetector_example();
    return 0;
}
