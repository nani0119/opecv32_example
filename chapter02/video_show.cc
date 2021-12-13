#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char const *argv[])
{
    int key;
    cv::namedWindow("example", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]));

    cv::Mat frame;
    while(1)
    {
        cap >> frame;
        if(frame.empty())
        {
            std::cout << "exit: frame is empty" << std::endl;
            break;
        }
        cv::imshow("example", frame);
        if((key = cv::waitKey(33)) >= 0 && key != 255)
        {
            std::cout << "exit:press key: "<< key << std::endl;
            break;
        }
    }
    cv::destroyWindow("example");
    return 0;
}
