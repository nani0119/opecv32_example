#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

int g_method = 0;

cv::Mat g_Histimg1;
cv::Mat g_Histimg2;
cv::Mat g_Histimg3;

void myTrackBarCB(int pos, void* param)
{
    double same = 0;
    double diff = 0;
    int method = 0;
    switch (pos)
    {
    case 0:
        std::cout << "method:HISTCMP_CORREL" << std::endl;
        method = cv::HISTCMP_CORREL;
        break;
    case 1:
        std::cout << "method:HISTCMP_CHISQR" << std::endl;
        method = cv::HISTCMP_CHISQR;
        break;
    case 2:
        std::cout << "method:HISTCMP_INTERSECT" << std::endl;
        method = cv::HISTCMP_INTERSECT;
        break;
    case 3:
        std::cout << "method:HISTCMP_BHATTACHARYYA" << std::endl;
        method = cv::HISTCMP_BHATTACHARYYA;
        break;
    default:
        std::cout << "unknow method" << std::endl;
        return;
    }
    same = cv::compareHist(g_Histimg1, g_Histimg2, method);
    diff = cv::compareHist(g_Histimg1, g_Histimg3, method);

    std::cout << "same:" << same << std::endl;
    std::cout << "diff:" << diff << std::endl;
}

void compareHist_example()
{
    cv::Mat img1 = cv::imread(RESOURCE_DIR"/13/desert.jpg");
    if(img1.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::Mat img2 = img1.clone();
    cv::Mat img3 = cv::Mat(img1.size(), img1.type(), cv::Scalar(0,0,0));

    cv::cvtColor(img1, img1, cv::COLOR_BGR2HSV);
    cv::cvtColor(img2, img2, cv::COLOR_BGR2HSV);
    cv::cvtColor(img3, img3, cv::COLOR_BGR2HSV);

    cv::namedWindow("img1", CV_WINDOW_AUTOSIZE);
    cv::imshow("img1", img1);
    cv::imshow("img2", img2);
    cv::imshow("img3", img3);

    int ch[2] = {0, 1};
    int histSize[] = {30, 32};
    float h_ranges[] = {0, 180}; // hue is [0, 180]
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    cv::calcHist(&img1, 1, ch, cv::noArray(), g_Histimg1, 2, histSize, ranges, true, false);
    cv::calcHist(&img2, 1, ch, cv::noArray(), g_Histimg2, 2, histSize, ranges, true, false);
    cv::calcHist(&img3, 1, ch, cv::noArray(), g_Histimg3, 2, histSize, ranges, true, false);

    cv::createTrackbar("method", "img1", &g_method, 4, myTrackBarCB, nullptr);
    myTrackBarCB(0, nullptr);

    while(1)
    {
        int key = cv::waitKey(100);
        if(key == 'q')
            break;
    }

    cv::destroyAllWindows();


}

int main(int argc, char const *argv[])
{
    compareHist_example();
    return 0;
}
