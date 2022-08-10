#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

void myMouseCallback(int event, int x, int y, int flags, void *param)
{
    cv::Mat& img = *(cv::Mat*)param;

    std::cout << "event: ";
    switch (event)
    {
        case cv::EVENT_MOUSEMOVE:
            std::cout << "mouse move";
            break;
        case cv::EVENT_MOUSEWHEEL:
            std::cout << "mouse wheel";
            break;
        case cv::EVENT_LBUTTONDOWN:
            std::cout << "mouse left button down";
            break;
        case cv::EVENT_RBUTTONDOWN:
            std::cout << "mouse right button down";
            break;
        case cv::EVENT_MBUTTONDOWN:
            std::cout << "mouse middle button down";
            break;
        case cv::EVENT_LBUTTONUP:
            std::cout << "mouse left button up";
            break;
        case cv::EVENT_RBUTTONUP:
            std::cout << "mouse right button up";
            break;
        case cv::EVENT_MBUTTONUP:
            std::cout << "mouse middle button up";
            break;
        case cv::EVENT_LBUTTONDBLCLK:
            std::cout << "mouse left button double click";
            break;
        case cv::EVENT_RBUTTONDBLCLK:
            std::cout << "mouse right button double click";
            break;
        case cv::EVENT_MBUTTONDBLCLK:
            std::cout << "mouse middle button double click";
            break;
        default:
            std::cout << "unknown";
            break;
    }
    std::cout << std::endl;

    std::cout << "pos: [" << x << "," << y << "]" << std::endl;

    std::cout << "flags:";
    if(flags&cv::EVENT_FLAG_LBUTTON)
    {
        std::cout << "LBUTTON ";
    }

    if(flags&cv::EVENT_FLAG_RBUTTON)
    {
        std::cout << "RBUTTON ";
    }

    if(flags&cv::EVENT_FLAG_MBUTTON)
    {
        std::cout << "MBUTTON ";
    }

    if(flags&cv::EVENT_FLAG_CTRLKEY)
    {
        std::cout << "CTRLKEY ";
    }

    if(flags&cv::EVENT_FLAG_SHIFTKEY)
    {
        std::cout << "SHIFTKEY ";
    }

    if(flags&cv::EVENT_FLAG_ALTKEY)
    {
        std::cout << "ALTKEY";
    }
    std::cout << std::endl;

    if(x > 0 && y > 0)
    {
        img.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
        cv::imshow("example", img);
    }
}

void myTrackbar0Callback(int pos, void* param)
{
    std::cout << "trackbar0 pos: " << pos << std::endl;
    cv::setTrackbarPos("Trackbar1", "example", pos);
}

void myTrackbar1Callback(int pos, void* param)
{
    std::cout << "trackbar1 pos: " << pos << std::endl;
    cv::Mat& img = *(cv::Mat*)(param);

    for(cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>(); it != img.end<cv::Vec3b>(); ++it)
    {
        *it = cv::Vec3b(pos, pos, pos);
    }

    cv::imshow("example", img);
}

void native_window_example()
{
    std::cout << std::endl << __func__ << std::endl;
    int trackBar0Pos = 10;
    int trackBar1Pos = 0;
    cv::Mat img(512, 512, CV_8UC3);

    img = cv::Scalar::all(0);

    cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
    // 设置鼠标callback
    cv::setMouseCallback("example", myMouseCallback, (void*)&img);
    // 设置Trackbar
    cv::setTrackbarMin("Trackbar0", "example", 1);
    cv::setTrackbarMax("Trackbar0", "example", 250);
    cv::createTrackbar("Trackbar0", "example", &trackBar0Pos, 250, myTrackbar0Callback);
    cv::createTrackbar("Trackbar1", "example", &trackBar1Pos, 255, myTrackbar1Callback, (void*)&img);


    cv::imshow("example", img);

    while(1)
    {
        char key =(char)cv::waitKey(0);
        if(key == 'q')
        {
            break;
        }
    }
    cv::destroyAllWindows();


}

int main(int argc, char const *argv[])
{
    native_window_example();
    return 0;
}

