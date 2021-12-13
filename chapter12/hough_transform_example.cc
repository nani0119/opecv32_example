#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"


void hough_lines_detect_example()
{
    cv::Mat src = cv::imread(RESOURCE_DIR"/12/line.png");
    if(src.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::imshow("src", src);

    cv::Mat img;
    cv::cvtColor(src, img, cv::COLOR_BGR2GRAY);

    cv::imshow("img", img);

    cv::Mat imgBlur;
    cv::GaussianBlur(img, imgBlur, cv::Size(3, 3), 5);

    cv::imshow("imgblur", imgBlur);

    cv::Mat imgEdage;
    cv::Canny(imgBlur, imgEdage, 100, 200, 3);

    cv::threshold(imgEdage, imgEdage, 255/2, 255, cv::THRESH_BINARY);

    cv::imshow("imgEdage", imgEdage);

    cv::Mat houghLines;
#if 0
    cv::HoughLinesP(imgEdage, houghLines,1, CV_PI/180, 10, 100, 10);
    for(int i = 0; i < houghLines.rows; i++)
    {
        cv::Mat r = houghLines.row(i);
        cv::line(src, cv::Point(r.at<int>(0, 0), r.at<int>(0, 1)), cv::Point(r.at<int>(0, 2), r.at<int>(0, 3)), cv::Scalar(255, 255, 0), 1, cv::LINE_AA);
    }
#else
    cv::HoughLines(imgEdage, houghLines, 1, CV_PI/180,  100);
    //std::cout << houghLines << std::endl;
    cv::RNG rngs = {12345};
    for(int i = 0; i < houghLines.rows; ++i)
    {
        float rho = houghLines.at<float>(i, 0);
        float theta = houghLines.at<float>(i, 1);
        double sin_theta = sin(theta);
        double cos_theta = cos(theta);
        double x = rho * cos_theta;
        double y = rho * sin_theta;
        cv::Point pt1, pt2;
        pt1.x = cvRound(x+1000*(-sin_theta));
        pt1.y = cvRound(y+1000*(cos_theta));
        pt2.x = cvRound(x-1000*(-sin_theta));
        pt2.y = cvRound(y-1000*(cos_theta));

        cv::Scalar colors = cv::Scalar(rngs.uniform(0, 255), rngs.uniform(0, 255), rngs.uniform(0, 255));
        cv::line(src, pt1, pt2, colors, 1);

    }


#endif
    cv::imshow("houghline", src);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


void hough_circle_detect_example()
{
  cv::Mat src = cv::imread(RESOURCE_DIR"/12/circle.png");
    if(src.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::imshow("src", src);


    cv::Mat imgBlur;
    cv::medianBlur(src, imgBlur,5);
    cv::imshow("imgblur", imgBlur);

    cv::Mat grayImg;
    cv::cvtColor(imgBlur, grayImg, cv::COLOR_BGR2GRAY);
    cv::imshow("gray", grayImg);

//    cv::Mat imgEdage;
//    cv::Canny(grayImg, imgEdage, 100, 200, 3);
//    cv::imshow("imgEdage", imgEdage);

    //cv::Mat imgEdage;
    //cv::threshold(imgBlur, imgEdage, 255/2, 255, cv::THRESH_BINARY);



     cv::Mat houghCircles;
    //InputArray image, // 输入图像 ,必须是8位的单通道灰度图像
	//OutputArray circles, // 输出结果&#xff0c;发现的圆信息
	//Int method, // 方法 - HOUGH_GRADIENT
	//Double dp, // dp  1;  accumulator resolution (ratio)
	//Double mindist, // 10 最短距离-可以分辨是两个圆的, 否则认为是同心圆- rows/8
	//Double param1, // canny edge detection low threshold
	//Double param2, // 中心点累加器阈值 – 候选圆心
	//Int minradius, // 最小半径
	//Int maxradius//最大半径
    cv::HoughCircles(grayImg, houghCircles, cv::HOUGH_GRADIENT, 1, 10, 100, 40, 5, 100);
    for(int i = 0; i < houghCircles.cols; i++)
    {
        cv::Vec3f cc = houghCircles.at<cv::Vec3f>(0, i);
        //std::cout << cc << std::endl;
        cv::circle(src, cv::Point(cc[0], cc[1]), cc[2], cv::Scalar(0,0,255), 2, cv::LINE_AA);
        cv::circle(src, cv::Point(cc[0], cc[1]), 2, cv::Scalar(255,0,0), 1, cv::LINE_AA);
    }
    cv::imshow("result", src);

    cv::waitKey(0);
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{

    //hough_lines_detect_example();
    hough_circle_detect_example();
    return 0;
}
