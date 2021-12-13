#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <opencv2/xfeatures2d.hpp>

#define RESOURCE_DIR "../resource/"
using namespace std;


void extracte_freak(cv::Mat input,std::vector<cv::KeyPoint> &keypoint,cv::Mat &descriptor)
{
    //使用BRISK算法中的特征点检测算法检测特征点，存入kp1和kp2中
    cv::Ptr<cv::BRISK> f2d = cv::BRISK::create();
    f2d->detect(input,keypoint);
    //FREAK算法，得到特征点描述符，存入des1和des2中
    cv::Ptr<cv::xfeatures2d::FREAK> f2d_freak = cv::xfeatures2d::FREAK::create();
    cv::Mat image_with_kp;
    f2d_freak->compute(input,keypoint,descriptor);
    cv::drawKeypoints(input, keypoint, image_with_kp, cv::Scalar::all(-1),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("freak"+std::to_string(random())+".png",image_with_kp);
}


void match_two_image(cv::Mat image1,cv::Mat image2, std::vector<cv::KeyPoint> keypoint1,std::vector<cv::KeyPoint> keypoint2,cv::Mat descriptor1,cv::Mat descriptor2){
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector<cv::DMatch> matches;
    matcher.match(descriptor1,descriptor2, matches);
    cv::Mat good_matches_image;
    cv::drawMatches(image1, keypoint1, image2, keypoint2,
                    matches, good_matches_image, cv::Scalar::all(-1), cv::Scalar::all(-1),
                    std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("good_matches_image.png",good_matches_image);
    {
        std::vector <cv::KeyPoint> RAN_KP1, RAN_KP2;
        std::vector<cv::Point2f> keypoints1, keypoints2;
        for (int i = 0; i < matches.size(); i++) {
            keypoints1.push_back(keypoint1[matches[i].queryIdx].pt);
            keypoints2.push_back(keypoint2[matches[i].trainIdx].pt);
            RAN_KP1.push_back(keypoint1[matches[i].queryIdx]);
            RAN_KP2.push_back(keypoint2[matches[i].trainIdx]);
        }

        std::vector<uchar> RansacStatus;
        cv::findFundamentalMat(keypoints1, keypoints2, RansacStatus, cv::FM_RANSAC);
        std::vector <cv::KeyPoint> ransac_keypoints1, ransac_keypoints2;
        std::vector <cv::DMatch> ransac_matches;
        int index = 0;
        for (size_t i = 0; i < matches.size(); i++)
        {
            if (RansacStatus[i] != 0)
            {
                ransac_keypoints1.push_back(RAN_KP1[i]);
                ransac_keypoints2.push_back(RAN_KP2[i]);
                matches[i].queryIdx = index;
                matches[i].trainIdx = index;
                ransac_matches.push_back(matches[i]);
                index++;
            }
        }
        cv::Mat after_ransac_sift_match;
        cv::drawMatches(image1, ransac_keypoints1, image2, ransac_keypoints2,
                        ransac_matches, after_ransac_sift_match, cv::Scalar::all(-1), cv::Scalar::all(-1),
                        std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        cv::imshow("after_ransac_orb_match.png",after_ransac_sift_match);
    }
}

int main(int argc, char *argv[])
{
    cv::Mat image1 = cv::imread(RESOURCE_DIR"/16/box_in_scene.png", cv::IMREAD_GRAYSCALE);
    cv::Mat image2 = cv::imread(RESOURCE_DIR"/16/box.png", cv::IMREAD_GRAYSCALE);
    std::vector<cv::KeyPoint> keypoint1,keypoint2;
    cv::Mat descriptor1, descriptor2;
    extracte_freak(image1,keypoint1,descriptor1);
    extracte_freak(image2,keypoint2,descriptor2);
    match_two_image(image1,image2,keypoint1,keypoint2,descriptor1,descriptor2);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}