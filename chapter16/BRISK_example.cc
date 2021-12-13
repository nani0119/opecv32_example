#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <opencv2/xfeatures2d.hpp>

#define RESOURCE_DIR "../resource/"
using namespace std;

void BRISK_example()
{
    int thresh = 127;
    cv::Mat img1 = cv::imread(RESOURCE_DIR "/16/box.png");
    if (img1.empty())
    {
        cout << "img is empty" << endl;
        return;
    }
    cv::imshow("img1", img1);
    cv::Mat imgGray1;
    cv::cvtColor(img1, imgGray1, cv::COLOR_BGR2GRAY);

    cv::Mat img2 = cv::imread(RESOURCE_DIR "/16/box_in_scene.png");
    if (img2.empty())
    {
        cout << "img is empty" << endl;
        return;
    }
    cv::imshow("img2", img2);
    cv::Mat imgGray2;
    cv::cvtColor(img2, imgGray2, cv::COLOR_BGR2GRAY);

    // -- Step 1: Detect the keypoints
    cv::Ptr<cv::Feature2D> f2d1 = cv::BRISK::create(thresh);
    std::vector<cv::KeyPoint> keypoint1;
    f2d1->detect(imgGray1, keypoint1);

    cv::Ptr<cv::Feature2D> f2d2 = cv::BRISK::create(thresh);
    std::vector<cv::KeyPoint> keypoint2;
    f2d2->detect(imgGray1, keypoint2);

    // -- Stpe 2: Calculate descriptors (feature vectors)
    cv::Mat descriptor1;
    f2d1->compute(imgGray1, keypoint1, descriptor1);

    cv::Mat descriptor2;
    f2d2->compute(imgGray2, keypoint2, descriptor2);

    // -- Step3: draw keypoints
    cv::Mat image_with_kp1;
    cv::drawKeypoints(img1, keypoint1, image_with_kp1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("StartDetector keypoints 1", image_with_kp1);

    cv::Mat image_with_kp2;
    cv::drawKeypoints(img1, keypoint2, image_with_kp2, cv::Scalar::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("StartDetector keypoints 2", image_with_kp2);


    // -- Step 4: Matching descriptor vectors with a brute force matcher
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> mathces;
    matcher.match(descriptor1, descriptor2, mathces);

    // -- Step 5: dwaw matches
    cv::Mat img_mathes;
    drawMatches(img1, keypoint1, img2, keypoint2, mathces, img_mathes);
    imshow("Mathces", img_mathes);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char *argv[])
{
    BRISK_example();
    return 0;
}