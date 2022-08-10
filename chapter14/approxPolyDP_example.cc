
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#define RESOURCE_DIR "../resource/"

std::ostream& operator <<(std::ostream& output, cv::Moments moment)
{
    output << "m00:" << moment.m00 << std::endl;
    output << "m10:" << moment.m10 << " m01:" << moment.m01<<  std::endl;
    output << "m20:" << moment.m20 << " m11:" << moment.m11<< " m02:" << moment.m02 << std::endl;
    output << "m30:" << moment.m30 << " m21:" << moment.m21<< " m12:" << moment.m12  <<" m03:"<< moment.m03 << std::endl;  // moments
    output << "mu20:" << moment.mu20 << " mu11:" << moment.mu11<< " mu02:"<< moment.mu02 << std::endl;
    output << "mu30:" << moment.mu30 << " mu21:" << moment.mu21<< " m12:"<< moment.mu12  <<" mu03:"<< moment.mu03 << std::endl; // central moments
    output << "nu20:" << moment.nu20 << " nu11:" <<moment.nu11<< " nu02:" <<moment.nu02 << std::endl;
    output << "nu30:" << moment.nu30 << " nu21:" <<moment.nu21<< " nu12:" <<moment.nu12  <<" nu03:" <<moment.nu03 << std::endl; // Hu invariant moments
    return output;
}


void approxPolyDP_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/14/bricks.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat imgBlur;
    cv::GaussianBlur(img, imgBlur, cv::Size(5,5), 0);

    cv::Mat imgGray;
    cv::cvtColor(imgBlur, imgGray, cv::COLOR_BGR2GRAY);

    cv::Mat imgEdage;
    cv::Canny(imgGray, imgEdage, 100, 200);
    cv::imshow("Edage", imgEdage);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imgEdage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point());

    cv::Mat outImg(img.size(), CV_8UC3, cv::Scalar(0,0,0));

    for(int i = 0; i < contours.size(); i++)
    {
#if 1
        // 1
        std::vector<cv::Point> approxCurve;
        cv::approxPolyDP(contours[i], approxCurve, 0.01, true);
        for(int j = 1; j < approxCurve.size(); ++j)
        {
            cv::line(outImg, cv::Point(approxCurve[j-1]), cv::Point(approxCurve[j]), cv::Scalar(255,255,255));

        }
#endif

#if 1
        // 2
        cv::Rect rect = cv::boundingRect(contours[i]);
        cv::rectangle(outImg, rect, cv::Scalar(255, 0, 0));
#endif

#if 1
        // 3
        cv::Mat rotatedRectPoints;
        cv::RotatedRect rotatedRect = cv::minAreaRect(contours[i]);
        cv::boxPoints(rotatedRect, rotatedRectPoints);
        cv::Point2d point1;
        cv::Point2d point2;
        for(int i = 1; i < rotatedRectPoints.rows; i++)
        {
            point1 = cv::Point(rotatedRectPoints.at<float>(i-1, 0), rotatedRectPoints.at<float>(i-1, 1));
            point2 = cv::Point(rotatedRectPoints.at<float>(i, 0), rotatedRectPoints.at<float>(i, 1));
            cv::line(outImg, point1, point2, cv::Scalar(0, 255, 0));
        }
        point1 = cv::Point(rotatedRectPoints.at<float>(3, 0), rotatedRectPoints.at<float>(3, 1));
        point2 = cv::Point(rotatedRectPoints.at<float>(0, 0), rotatedRectPoints.at<float>(0, 1));
        cv::line(outImg, point1, point2, cv::Scalar(0, 255, 0));
#endif

#if 1
        // 4
        cv::Point2f center;
        float r;
        cv::minEnclosingCircle(contours[i], center, r);
        cv::circle(outImg, center, r, cv::Scalar(0,0,255));
        cv::circle(outImg, center, 1, cv::Scalar(0,0,255));
#endif

#if 1
        // 5
        cv::RotatedRect ellipseRect = cv::fitEllipse(contours[i]);
        cv::ellipse(outImg, ellipseRect, cv::Scalar(255, 255, 0));
#endif

#if 0
        //6
        //直线拟合
 	    //拟合结果为一个四元素的容器 比如Vec4f - (vx, vy, x0, y0)
	    //其中(vx, vy) 是直线的方向向量
	    //(x0, y0) 是直线上的一个点
        cv::Vec4f fitLine;
        cv::fitLine(contours[i], fitLine, cv::DIST_FAIR, 0, 0.01, 0.01);
        double k = fitLine[1]/fitLine[0];
        // 求直线上的两个点
        cv::Point p1(0, k*(0 - fitLine[2])+fitLine[3]);
        cv::Point p2(outImg.cols -1, k*(outImg.cols - 1 - fitLine[2]) + fitLine[3]);
        cv::line(outImg, p1, p2, cv::Scalar(0, 255,255));

#endif

#if 1
        // 7
        std::vector<cv::Point> hullPoints;
        cv::convexHull(contours[i], hullPoints);
        for(int i = 0; i < hullPoints.size(); i++)
        {
            cv::line(outImg, hullPoints[i%hullPoints.size()], hullPoints[(i+1)% hullPoints.size()], cv::Scalar(255, 0, 255));
        }
#endif

#if 1
        // 8
        std::cout << "contour index " << i << " length:"<<cv::arcLength(contours[i], true) << std::endl;
#endif

#if 1
        // 9
        cv::Point pointTest(contours[0][0].x+10, contours[0][0].y+10);
        cv::circle(outImg, pointTest, 1, cv::Scalar(255,255,255));
        double distance = cv::pointPolygonTest(contours[i], pointTest, true);
        std::cout << "point " << pointTest<< " far from contour index " << i << " is "<< distance << std::endl;;
#endif

#if 1 // 10
    std::cout << "contour index " << i << " area: "<< cv::contourArea(contours[i], false) << std::endl;
#endif

#if 1 // 11
        std::cout  <<"contour index " << i << " is ContourConvex? :"<<cv::isContourConvex(contours[i]) << std::endl;
#endif

#if 1 // 12
        cv::Moments moments = cv::moments(contours[i], false);
        std::cout  <<"contour index " << i << " moments :" << std::endl <<  moments << std::endl;
#endif
        cv::imshow("approxcurve", outImg);
        cv::waitKey(10);
        std::cout << "====================================================" << std::endl;

    }

    cv::waitKey(0);
    cv::destroyAllWindows();

}

void moments_example()
{
    cv::Mat img1 = cv::imread(RESOURCE_DIR"/14/moments1.jpg", cv::IMREAD_GRAYSCALE);
    if(img1.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat imgEdage1;
    cv::Canny(img1, imgEdage1, 100, 200);
    cv::imshow("Edage1", imgEdage1);

    std::vector<std::vector<cv::Point>> contours1;
    std::vector<cv::Vec4i> hierarchy1;
    cv::findContours(imgEdage1, contours1, hierarchy1, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point());
    std::cout << "contours1:" << contours1.size() << std::endl;
    // Central moments are invariant under translation
    // Normalized central moments are also invariant under scaling
    // Hu invariant moments are invariant under rotation

    cv::Moments moments1 = cv::moments(contours1[0], false);

    //std::cout << "contours moments:" << std::endl << moments << std::endl;
    std::cout << "==================================" << std::endl;
    double huMoments1[7];
    cv::HuMoments(moments1, huMoments1);

    std::cout << "first:" << std::endl;
    for(int i = 0; i < 7; i++)
    {
        std::cout << "h" << i << ":" << huMoments1[i] << std::endl;
    }



    cv::Mat img2 = cv::imread(RESOURCE_DIR"/14/moments2.jpg", cv::IMREAD_GRAYSCALE);
    if(img2.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

#if 1
    int width = img2.cols* 0.9;
    int height = img2.rows*0.9;
    cv::resize(img2, img2, cv::Size(width, height));
#endif

    cv::Mat imgEdage2;
    cv::Canny(img2, imgEdage2, 100, 200);
    cv::imshow("Edage2", imgEdage2);

    std::vector<std::vector<cv::Point>> contours2;
    std::vector<cv::Vec4i> hierarchy2;
    cv::findContours(imgEdage2, contours2, hierarchy2, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point());
    std::cout << "contours2:" << contours2.size() << std::endl;
    cv::Moments moments2 = cv::moments(contours2[0], false);
    double huMoments2[7];
    cv::HuMoments(moments2, huMoments2);
    std::cout << "secode:" << std::endl;
    for(int i = 0; i < 7; i++)
    {
        std::cout << "h" << i << ":" << huMoments2[i] << std::endl;
    }


    std::cout << "match shape:" <<cv::matchShapes(contours1[0], contours2[0], cv::CONTOURS_MATCH_I1, 0) << std::endl;

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    //approxPolyDP_example();
    moments_example();
    return 0;
}
