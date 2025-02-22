#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#define RESOURCE_DIR "../resource/"
using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    // load images
    Mat src = imread(RESOURCE_DIR"/19/times-square.jpg");
    if (!src.data)
    {
        printf("could not load image...\n");
        return -1;
    }
    // show images
    namedWindow("input image", cv::WINDOW_AUTOSIZE);
    imshow("input image", src);
    Mat replaceImg = imread(RESOURCE_DIR"/19/kgirls.jpg");
    imshow("adv content", replaceImg);
    // 定义两个平面上四个角坐标
    vector<Point> src_corners(4);
    vector<Point> dst_corners(4);
    // 原图像平面四点坐标
    src_corners[0] = Point(0, 0);
    src_corners[1] = Point(replaceImg.cols, 0);
    src_corners[2] = Point(0, replaceImg.rows);
    src_corners[3] = Point(replaceImg.cols, replaceImg.rows);
    // 目标平面四个角坐标
    dst_corners[0] = Point(70, 131);
    dst_corners[1] = Point(168, 216);
    dst_corners[2] = Point(21, 199);
    dst_corners[3] = Point(148, 267);
    // 计算单应性矩阵与透视变换
    Mat h = findHomography(src_corners, dst_corners);
    Mat output_img;
    warpPerspective(replaceImg, output_img, h, src.size());
    // create mask
    Mat m1 = Mat::zeros(replaceImg.size(), CV_8UC1);
    m1 = Scalar(255);
    Mat mask_output;
    warpPerspective(m1, mask_output, h, src.size());
    imshow("Mask Result", mask_output);
    // use mask
    Mat result1;
    add(output_img, output_img, result1, mask_output);
    Mat result2;
    bitwise_not(mask_output, mask_output);
    add(src, result1, result2, mask_output);
    // put them together
    Mat result;
    add(result1, result2, result);
    imshow("Final Result", result);
    waitKey(0);
    return 0;
}