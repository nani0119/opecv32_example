#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <opencv2/xfeatures2d.hpp>

#define RESOURCE_DIR "../resource/"
using namespace std;


void extracte_sift(cv::Mat input,std::vector<cv::KeyPoint> &keypoint,cv::Mat &descriptor, string tag){
    cv::Ptr<cv::Feature2D> f2d = cv::xfeatures2d::SIFT::create();
    f2d->detect(input,keypoint);
    cv::Mat image_with_kp;
    f2d->compute(input,keypoint,descriptor);
    cv::drawKeypoints(input, keypoint, image_with_kp, cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow(tag + "_sift"+std::to_string(keypoint.size())+".png",image_with_kp);
}

void match_two_image(cv::Mat image1,cv::Mat image2, std::vector<cv::KeyPoint> keypoint1,std::vector<cv::KeyPoint> keypoint2,cv::Mat descriptor1,cv::Mat descriptor2){
    cv::FlannBasedMatcher matcher;
    std::vector<cv::DMatch> matches, goodmatches;
    matcher.match(descriptor1,descriptor2, matches);
    cv::Mat  good_matches_image;

    double max_dist = 0; double min_dist = 100;
#if 0
    for (int i = 0; i < descriptor1.rows; i++) {
        if (matches[i].distance > max_dist) {
            max_dist = matches[i].distance;
        }
        if (matches[i].distance < min_dist) {
            min_dist = matches[i].distance;
        }
    }
#endif
    for (int i = 0; i < descriptor1.rows; i++) {
        if (matches[i].distance < 4 * min_dist) {
            goodmatches.push_back(matches[i]);
        }
    }
    cout << min_dist << endl;

    cv::drawMatches(image1, keypoint1, image2, keypoint2,
                    goodmatches, good_matches_image, cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("good_matches_image.png",good_matches_image);

    {
        std::vector <cv::KeyPoint> RAN_KP1, RAN_KP2;
        std::vector<cv::Point2f> keypoints1, keypoints2;
        for (int i = 0; i < goodmatches.size(); i++) {
            keypoints1.push_back(keypoint1[goodmatches[i].queryIdx].pt);
            keypoints2.push_back(keypoint2[goodmatches[i].trainIdx].pt);
            RAN_KP1.push_back(keypoint1[goodmatches[i].queryIdx]);
            RAN_KP2.push_back(keypoint2[goodmatches[i].trainIdx]);
        }

        std::vector<uchar> RansacStatus;
        cv::Mat p1(keypoints1.size(), 2, CV_32F);
        for(int i = 0; i < keypoints1.size(); i++)
        {
            p1.at<float>(i, 0) = keypoints1[i].x;
            p1.at<float>(i, 1) = keypoints1[i].y;
        }

        cv::Mat p2(keypoints2.size(), 2, CV_32F);
        for(int i = 0; i < keypoints2.size(); i++)
        {
            p2.at<float>(i, 0) = keypoints2[i].x;
            p2.at<float>(i, 1) = keypoints2[i].y;
        }

        cv::findFundamentalMat(p1, p2, RansacStatus, cv::FM_RANSAC);

        std::vector <cv::KeyPoint> ransac_keypoints1, ransac_keypoints2;
        std::vector <cv::DMatch> ransac_matches;
        int index = 0;
        for (size_t i = 0; i < goodmatches.size(); i++)
        {
            if (RansacStatus[i] != 0)
            {
                ransac_keypoints1.push_back(RAN_KP1[i]);
                ransac_keypoints2.push_back(RAN_KP2[i]);
                goodmatches[i].queryIdx = index;
                goodmatches[i].trainIdx = index;
                ransac_matches.push_back(goodmatches[i]);
                index++;
            }
        }
        cv::Mat after_ransac_sift_match;
        cv::drawMatches(image1, ransac_keypoints1, image2, ransac_keypoints2,
                        ransac_matches, after_ransac_sift_match, cv::Scalar::all(-1), cv::Scalar::all(-1),
                        std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        cv::imshow("after_ransac_sift_match.png",after_ransac_sift_match);
    }
}

int main(int argc, char *argv[])
{
    cv::Mat image1 = cv::imread(RESOURCE_DIR"/16/box_in_scene.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread(RESOURCE_DIR"/16/box.png", cv::IMREAD_GRAYSCALE);
    std::vector<cv::KeyPoint> keypoint1,keypoint2;
    cv::Mat descriptor1, descriptor2;
    extracte_sift(image1,keypoint1,descriptor1, "img1");
    extracte_sift(image2,keypoint2,descriptor2, "img2");
    match_two_image(image1,image2,keypoint1,keypoint2,descriptor1,descriptor2);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}