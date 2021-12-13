#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"
using namespace std;

ostream &operator<<(ostream &o, cv::SimpleBlobDetector::Params &p)
{
    o << "minThreshold:" << p.minThreshold << endl;
    o << "maxThreshold:" << p.maxThreshold << endl;
    o << "thresholdStep:" << p.thresholdStep << endl;
    o << "minRepeatability:" << p.minRepeatability << endl;
    o << "minDistBetweenBlobs:" << p.minDistBetweenBlobs << endl;
    o << "filterByColor:" << p.filterByColor << ":" << (int)(p.blobColor) << endl;
    o << "filterByArea:" << p.filterByArea << ":" << p.minArea << ":" << p.maxArea << endl;
    o << "filterByCircularity:" << p.filterByCircularity << ":" << p.minCircularity << ":" << p.maxCircularity << endl;
    o << "filterByInertia:" << p.filterByInertia << ":" << p.minInertiaRatio << ":" << p.maxInertiaRatio << endl;
    o << "filterByConvexity:" << p.filterByConvexity << ":" << p.minConvexity << ":" << p.maxConvexity << endl;
    return o;
}

void SimpleBlobDetector_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR "/16/checkerboard.jpg");
    if (img.empty())
    {
        cout << "img is empty" << endl;
        return;
    }

    //cv::GaussianBlur(img, img, cv::Size(5,5), 3);

    //cv::imshow("img", img);

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    cv::SimpleBlobDetector::Params params;
    cout << "default params:" << endl;
    cout << params << endl;

    params.minThreshold = 50;
    params.maxThreshold = 220;
    params.thresholdStep = 10;
    params.minRepeatability = 3;
    params.minDistBetweenBlobs = 10;
    params.filterByColor = true;
    params.blobColor = 0;

    cout << "============================================" << endl;
    cout << "modify param" << endl;
    cout << params << endl;

    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);

    vector<cv::KeyPoint> keypoints;
    detector->detect(imgGray, keypoints, cv::noArray());

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
    SimpleBlobDetector_example();
    return 0;
}
