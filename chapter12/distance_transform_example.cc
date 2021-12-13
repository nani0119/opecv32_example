#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void distance_transform_example()
{
    float maxValue = 0;
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/star.jpg", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    img = ~img;
    cv::imshow("img", img);

    cv::Mat imgBlur;
    cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 5);

    cv::imshow("imgblur", imgBlur);

    cv::threshold(imgBlur,imgBlur,20,200,CV_THRESH_BINARY);

    cv::Mat imgDistance;
    cv::distanceTransform(imgBlur, imgDistance, cv::DIST_L1, 3);
#if 0
    for(int i = 0; i < imgDistance.rows; ++i)
    {
        for(int j = 0; j < imgDistance.cols; ++j)
        {
            if(imgDistance.at<float>(i, j) > maxValue)
            {
                maxValue = imgDistance.at<float>(i, j);
            }
        }
    }

    for(int i = 0; i < imgDistance.rows; ++i)
    {
        for(int j = 0; j < imgDistance.cols; ++j)
        {
            if(imgDistance.at<float>(i, j) > maxValue/1.9)
            {
                imgDistance.at<float>(i, j) = 255;
            }
        }
    }
#else
    cv::normalize(imgDistance, imgDistance, 0, 1, cv::NORM_MINMAX);
#endif
    cv::imshow("distanceImg", imgDistance);


    cv::waitKey(0);
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    distance_transform_example();
    return 0;
}
