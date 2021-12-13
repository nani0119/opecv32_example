#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    cout << "opencv version:" << CV_VERSION << endl;
    cout << "BuildInformation:" << cv::getBuildInformation()  << endl;
    cout << "the number of threads used by OpenCV for parallel regions:" << cv::getNumThreads() << endl;
    cout << "the number of ticks:" << cv::getTickCount() << endl;
    cout << "the number of ticks per second:" << cv::getTickFrequency() << endl;
    cout << "the number of logical CPUs available for the process:" << cv::getNumberOfCPUs() << endl;
    return 0;
}
