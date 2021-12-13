#include <opencv2/opencv.hpp>
#include <opencv2/dpm.hpp>
#include <iostream>
#include <stdio.h>
#define RESOURCE_DIR "../resource/"

using namespace std;


void drawBoxes(cv::Mat &frame,
        vector<cv::dpm::DPMDetector::ObjectDetection> ds,
        cv::Scalar color,
        string text)
{
    for (unsigned int i = 0; i < ds.size(); i++)
    {
        rectangle(frame, ds[i].rect, color, 2);
    }

    // draw text on image
    cv::Scalar textColor(0,0,250);
    putText(frame, text, cv::Point(10,50), cv::FONT_HERSHEY_PLAIN, 2, textColor, 2);
}

void DPMDetector_example()
{
    cv::VideoCapture capture(RESOURCE_DIR"/22/vtest.avi");
    if(!capture.isOpened())
    {
        cerr << "open video file fail"<< std::endl;
        return;
    }

    cv::Ptr<cv::dpm::DPMDetector> detector = cv::dpm::DPMDetector::create(std::vector<std::string>(1, RESOURCE_DIR"/22/inriaperson.xml"));

    if(detector->isEmpty())
    {
        cerr << "load classifier fail" << endl;
        return;
    }
    cout << "class count:" << detector->getClassCount() << endl;
    std::vector<std::string> classNames = detector->getClassNames();
    cout << "class name:";
    for(auto it = classNames.begin(); it != classNames.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    cv::Mat img;
    cv::Mat gray;
    cv::Mat frame;
    std::vector<cv::Rect> objects;
    capture>>img;
    while(!img.empty())
    {
        img.copyTo(frame);
        //cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
        //cv::equalizeHist(gray, gray);
        std::vector<cv::dpm::DPMDetector::ObjectDetection> ds;
        detector->detect(img, ds);
        double t = (double) cv::getTickCount();
        if(cv::waitKey(30) ==  'q')
        {
            break;
        }
        t = ((double) cv::getTickCount() - t)/cv::getTickFrequency();//elapsed time
        char text[40] = {0};
        sprintf(text,"%0.1f fps", 1.0/t);
        drawBoxes(frame, ds, cv::Scalar(0, 0, 255), text);
        cv::imshow("video", frame);
        capture>>img;
    }

    capture.release();
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    DPMDetector_example();
    return 0;
}
