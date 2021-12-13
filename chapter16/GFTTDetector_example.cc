#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"
using namespace std;

void GFEEDetector_example()
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


    int maxCorners = 200;
    double qualityLevel = 0.1;
    double minDistance = 10;
    int blockSize = 3;
    bool useHarrisDetector = false;
    double k = 0.04;

    cv::Ptr<cv::GFTTDetector> detector =  cv::GFTTDetector::create(maxCorners, qualityLevel, minDistance, blockSize, useHarrisDetector, k);

    vector<cv::KeyPoint> keypoints;
    detector->detect(imgGray, keypoints, cv::noArray());

    for(vector<cv::KeyPoint>::iterator it = keypoints.begin(); it != keypoints.end(); ++it)
    {
        cv::circle(img, it->pt, 3, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
    }

    cout << "descriptorSize:" << detector->descriptorSize()<<endl;
    cout << "descriptorType:" << detector->descriptorType()<<endl;
    cout << "defaultNorm:" << detector->defaultNorm()<<endl;
    cv::imshow("keypoints", img);

    cv::Mat cornerHarrisDst;
    cv::cornerHarris(imgGray, cornerHarrisDst, blockSize, 5, k);
    cv::normalize(cornerHarrisDst, cornerHarrisDst,0,1, cv::NORM_MINMAX);
    cv::imshow("cornerHarrisDst", cornerHarrisDst);

    cv::Mat cornerMinEigenValDst;
    cv::cornerMinEigenVal(imgGray, cornerMinEigenValDst, blockSize, 5);
    cv::normalize(cornerMinEigenValDst, cornerMinEigenValDst,0,1, cv::NORM_MINMAX);
    cv::imshow("cornerMinEigenValDst", cornerMinEigenValDst);

    cv::Mat cornerEigenValsAndVecsDst;
    cv::cornerEigenValsAndVecs(imgGray, cornerEigenValsAndVecsDst, blockSize, 5);

    cv::waitKey(0);
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    GFEEDetector_example();
    return 0;
}
