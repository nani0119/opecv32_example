#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>

#define RESOURCE_DIR "../resource/"

using namespace std;

void calcOpticalFlowPyrLK_example()
{
    cv::Mat originImg;
    cv::Mat oldImg;
    cv::VideoCapture cap;
    cv::RNG rng;

    if(!cap.open(RESOURCE_DIR"/16/motion.mkv"))
    {
        cerr<< "open video file fail" << endl;
        return;
    }


    cap>>oldImg;
    originImg = oldImg.clone();

    cv::cvtColor(oldImg, oldImg, cv::COLOR_BGR2GRAY);

    vector<cv::Point2f> oldCorners;
    int maxCorners = 1;
    double qualityLevel = 0.3;
    double  minDistance = 10;
    int blockSize = 3;
    cv::goodFeaturesToTrack(oldImg, oldCorners, maxCorners, qualityLevel, minDistance, cv::noArray(), blockSize);

    cv::Size winSize(4, 4);
    cv::cornerSubPix(oldImg, oldCorners, winSize, cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 40, 0.01));

    cv::Mat newImg;
    vector<vector<cv::Point2f>> tracker(maxCorners);
    vector<uchar> features_found(maxCorners, 1);
    while(1)
    {
        cap >> newImg;
        if(!newImg.data)
        {
            break;
        }

        //cv::waitKey(30);
        for(int i = 0; i < maxCorners; i++)
        {
            if(features_found[i] != 0)
            {
                tracker[i].push_back(oldCorners[i]);
            }
        }


        cv::cvtColor(newImg, newImg, cv::COLOR_BGR2GRAY);
        vector<cv::Point2f> newCorners;

        cv::calcOpticalFlowPyrLK(oldImg, newImg, oldCorners, newCorners, features_found,cv::noArray(), cv::Size( 4*2+1, 4*2+1 ), 10);


        oldCorners = newCorners;
        oldImg = newImg;
    }

    cap.set(cv::CAP_PROP_POS_MSEC, 0);
    cv::Mat img;
    int countFrame = 0;
    while(1)
    {
        cap >> img;
        if(!img.data)
        {
            break;
        }
        for(int i = 0; i < maxCorners; i++)
        {
            for(int j = 1; j < countFrame; j++)
            {
                cv::circle(img, tracker[i][j], 1, cv::Scalar(rng(255), rng(255),rng(255)));
                cv::line(img, tracker[i][j-1], tracker[i][j],cv::Scalar(rng(255), rng(255),rng(255)),1);
            }
        }
        cv::imshow("img", img);
        cv::waitKey(30);
        countFrame++;
    }
#if 0
    for(auto it = corners.begin(); it != corners.end(); ++it)
    {
        cv::circle(originImg, *it, 3, cv::Scalar(0, 255, 0));
    }

    cap.release();

    cv::imshow("img", originImg);
    cv::waitKey(0);
#endif
    cv::waitKey(0);
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    calcOpticalFlowPyrLK_example();
    return 0;
}
