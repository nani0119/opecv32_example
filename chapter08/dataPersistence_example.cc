#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <opencv2/opencv.hpp>

void DataPersistence_write_example()
{
    std::cout << std::endl << __func__ << std::endl;
    cv::FileStorage fs("test.yml", cv::FileStorage::WRITE);

    // 方式１
    fs.write("frameCout", 5);

    time_t rawtime;
    time(&rawtime);
    // 方式２
    fs << "calibrationDate" << asctime(localtime(&rawtime));

    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0,1);
    cv::Mat distCOeffs = (cv::Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);

    fs << "cameraMatrix" << cameraMatrix << "distCOeffs" << distCOeffs;

    fs << "features" << "[";
    for(int i = 0; i < 3; i++)
    {
        int x = rand()%640;
        int y = rand()%480;
        uchar lbp = rand()%256;

        fs<<"{:";
        fs<< "x"<< x << "y" << y ;
        fs<< "lbp" << "[:";
        for(int j = 0; j < 8; j++)
        {
            fs << ((lbp >> j)&1);
        }
        fs << "]";
        fs<<"}";

    }

    fs << "]";
    fs.release();
}


void DataPersistence_read_example()
{
    std::cout << std::endl << __func__ << std::endl;
    cv::FileStorage fs("test.yml", cv::FileStorage::READ);

    // 读方式１
    int frameCount  = (int)fs["frameCout"];

    // 读方式２
    std::string date;
    fs["calibrationDate"] >> date;

    cv::Mat cameraMatrix, distCoeffs;
    fs["cameraMatrix"] >> cameraMatrix;
    fs["distCoeffs"] >> distCoeffs;

    std::cout << "frameCount: " << frameCount << std::endl
                << "calibration date: " << date << std::endl
                << "camera matrix: " << cameraMatrix << std::endl
                << "distortion coeffs: " << distCoeffs << std::endl;

    cv::FileNode features = fs["features"];
    int idx = 0;
    std::vector<uchar> lbpval;
    for(cv::FileNodeIterator it = features.begin(); it != features.end(); ++it, ++idx)
    {
        std::cout << "feature #" << idx << ": ";
        std::cout << "x=" << (int)(*it)["x"] << ", y=" << (int)(*it)["y"] << ", lbp: (";
        // ( Note: easily read numerical arrays using FileNode >> std::vector. )
        (*it)["lbp"] >> lbpval;
        for(int i = 0; i < (int)lbpval.size(); i++)
        {
            std::cout << " " << (int)lbpval[i];
        }
        std::cout << ")" << std::endl;
    }

    fs.release();
}

int main(int argc, char const *argv[])
{
    DataPersistence_write_example();
    DataPersistence_read_example();
    return 0;
}
