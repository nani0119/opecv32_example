#include <opencv2/opencv.hpp>
#include <iostream>
#define RESOURCE_DIR "../resource/"

using namespace std;


void drawBox(cv::Mat& img, vector<cv::Rect>& rects)
{
    enum { BLUE, AQUA, CYAN, GREEN };
    static cv::Scalar colors[] = {
                cv::Scalar( 0, 0, 255 ),
                cv::Scalar( 0, 128, 255 ),
                cv::Scalar( 0, 255, 255 ),
                cv::Scalar( 0, 255, 0 )
    };

    int i = 0;
    for(vector<cv::Rect>::iterator r = rects.begin(); r != rects.end(); ++r)
    {
        cv::rectangle(img, *r, colors[i%4]);
        ++i;
    }
}

void cascadeClassifier_example()
{
    cv::VideoCapture capture(RESOURCE_DIR"/22/vtest.avi");
    if(!capture.isOpened())
    {
        cerr << "open video file fail"<< std::endl;
        return;
    }

    cv::Ptr<cv::CascadeClassifier> cascade( new cv::CascadeClassifier(RESOURCE_DIR"/22/haarcascade_fullbody.xml"));

    if(cascade->empty())
    {
        cerr << "load classifier fail" << endl;
        return;
    }

    cv::Mat img;
    cv::Mat gray;
    std::vector<cv::Rect> objects;
    capture>>img;
    while(!img.empty())
    {
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(gray, gray);
        cascade->detectMultiScale(gray, objects, 1.1, 3, 0, cv::Size(), cv::Size());
        drawBox(img, objects);
        objects.clear();
        cv::imshow("video", img);
        if(cv::waitKey(30) ==  'q')
        {
            break;
        }
        capture>>img;
    }

    capture.release();
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    cascadeClassifier_example();
    return 0;
}
