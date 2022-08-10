#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>



void drawSomething()
{
    std::cout << std::endl <<__func__<<std::endl;
    cv::Mat img = cv::Mat::zeros(512, 512, CV_8UC3);
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    // draw circle

    cv::circle(img, cv::Point2f(100, 100), 100, cv::Scalar(255, 0 , 0), 1 , 8, 0);// shift: center>>0  radius>>0
    // draw circle center point
    cv::circle(img, cv::Point2f(100, 100), 0, cv::Scalar(255, 0 , 0), 1 , 8, 0);

    cv::circle(img, cv::Point2f(100, 100), 100, cv::Scalar(0, 255 , 0), 1 , 8, 1); // shift: center>>1  radius>>1
    // draw circle center point
    cv::circle(img, cv::Point2f(100, 100), 0, cv::Scalar(0, 255 , 0), 1 , 8, 1);

    cv::circle(img, cv::Point2f(100, 100), 100, cv::Scalar(0, 0 , 255), 1 , 8, 2);// shift: center>>2  radius>>2
    // draw circle center point
    cv::circle(img, cv::Point2f(100, 100), 0, cv::Scalar(0, 0 , 255), 1 , 8, 2);


    // draw rect
    cv::rectangle(img, cv::Point2f(0, 0), cv::Point2f(200, 200), cv::Scalar(0, 0, 255), 1, 8, 0);

    cv::Rect r(50,50, 100, 100);
    cv::rectangle(img, r, cv::Scalar(255, 255, 255), 1, 8, 0);

    // draw line
    cv::Point p1 (0,0);
    cv::Point p2 (250, 250);

    cv::Point p3 (250, 250);
    cv::Point p4 (300,300);

    cv::line(img, p1, p2, cv::Scalar(100,100,100), 1, 8);
    cv::line(img, p3, p4, cv::Scalar(200,200,200), 1, 8);

    // clipLine
    std::cout <<std::boolalpha << " clipline1:" <<  cv::clipLine(r, p1, p2) << std::endl;
    cv::Size s(50, 50);
    std::cout <<std::boolalpha << " clipline2:" <<  cv::clipLine(s, p1, p2) << std::endl;

    // draw ellipse
    cv::Point center(300, 300);
    cv::Size ellipseSize(200, 100);
    double angle = 90;
    double startAngle = 0;
    double endAngle = 360;
    cv::Scalar color(255, 255, 255);
    cv::ellipse(img, center, ellipseSize, angle, startAngle, endAngle, color, 1, 8, 0);


    cv::RotatedRect rotateRect (center, ellipseSize, 180);
    cv::ellipse(img, rotateRect, cv::Scalar(255, 200, 100), 1, 8);


    std::vector<cv::Point> pts;
    cv:: ellipse2Poly(cv::Point(350, 350), cv::Size(100, 50), 10, 0, 360, 1 , pts);
    for(std::vector<cv::Point>::iterator it = pts.begin(); it != pts.end(); ++it)
    {
        cv::circle(img, *it, 0, cv::Scalar(200, 200 , 200), 1 , 8,  0);
    }

    // fillConvexPoly

    cv::Point pointList[] = { cv::Point(80, 100) ,cv::Point(120, 140),cv::Point(200, 120)};
    cv::fillConvexPoly(img, pointList, 3, cv::Scalar(230, 100 , 250), 8, 0);

    // fillPoly
	cv::Point root_points[2][3];
	root_points[0][0] = cv::Point(215, 220);
	root_points[0][1] = cv::Point(460, 225);
	root_points[0][2] = cv::Point(466, 450);
	root_points[1][0] = cv::Point(235, 465);
	root_points[1][1] = cv::Point(260, 390);
	root_points[1][2] = cv::Point(96, 310);
    root_points[1][3] = cv::Point(466, 450);

    const cv::Point* ppt[2] = { root_points[0], root_points[1]};
    int npts[] = {3, 4};
    cv::Scalar c(230, 230 , 250);
    cv::fillPoly(img, ppt, npts, 2, c);

    // polyLines()
    cv::polylines(img, ppt, npts, 2, true, cv::Scalar(255,0,0), 8, 8, 0);


    // lineIterator

    cv::LineIterator iter = cv::LineIterator(img, cv::Point(0, 0), cv::Point(11,10), 8, true);
    for(int i = 0; i < iter.count; ++iter, i++)
    {
        std::cout << "pos:" << iter.pos() << "value:" << *((cv::Vec3b*)*iter) << std::endl;;
    }

    // font

    int base_line = 0;
    std::cout << "font size:" << cv::getTextSize("hello world",cv::FONT_HERSHEY_PLAIN, 1.0, 1, &base_line)<< std::endl;
    std::cout << "base line:" << base_line << std::endl;
    cv::putText(img, "hello world", cv::Point(0, 400), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(255,255,255));



    cv::imshow("img", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void drawCross()
{
    cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255,255,255));
    cv::namedWindow("cross", cv::WINDOW_AUTOSIZE);
    for(int y = 0; y < img.rows; y+=20)
    {
        for(int x = 0; x < img.cols; x+=20)
        {
            circle(img, cv::Point(x, y), 1, cv::Scalar(0, 0, 255), -1);
        }
    }
    cv::imshow("cross", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    //drawSomething();
    drawCross();
    return 0;
}
