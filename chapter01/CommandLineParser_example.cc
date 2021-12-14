#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
// opencv_CommandLineParser_example --@image1=asadsdf.jpg --@image2=qweqweqwe.jpg  --@repeat=3 -N=1 --fps=30.0 --path=zxccvvv --ts
// opencv_CommandLineParser_example asadsdf.jpg qweqweqwe.jpg  3 -N=1 --fps=30.0 --path=zxccvvv --ts
int main(int argc, char const *argv[])
{
    const string keys = {
        "{help h usage ? | | print this message }"
        "{@image1 | | image1 for compare }"
        "{@image2 | | image2 for compare }"
        "{@repeat |1 | number }"
        "{path |. | path to file }"
        "{fps | -1.0 | fps for output video }"
        "{N count |100 | count of objects }"
        "{ts timestamp | | use time stamp }"
    };
    cv::CommandLineParser parser(argc, argv, keys);
    parser.about("opencv CommandLineParser example");

    if(parser.has("help"))
    {
        parser.printMessage();
        return 0;
    }


#if 1
    int N = parser.get<int>("N");
    cout << "N:" << N << endl;

    double fps = parser.get<double>("fps");
    cout << "fps:" << fps << endl;

    string path = parser.get<string>("path");
    cout << "path:" << path << endl;

    bool use_time_stamp = parser.has("timestamp");
    cout << "use_time_stamp:"  << use_time_stamp << endl;

    string img1 = parser.get<string>(0);
    cout << "@image1:" << img1 << endl;

    string img2 = parser.get<string>(1);
    cout << "@image2:" << img2 << endl;

    int repeat = parser.get<int>(2);
    cout << "@repeat:" << repeat << endl;
#endif
    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }
    cout << "finish" << endl;

    return 0;
}
