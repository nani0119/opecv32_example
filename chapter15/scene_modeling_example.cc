#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void scene_modeling_example()
{
    cv::VideoCapture cap;
    if(!cap.open(RESOURCE_DIR"/15/tree.avi"))
    {
        std::cerr << "could not open video file" << std::endl;
        return;
    }
    cv::Point pt1(10,10), pt2(30,30);
    int max_buffer;
    cv::Mat rawImage;

    std::ofstream b, g, r;
    b.open("blines.csv");
    g.open("glines.csv");
    r.open("rlines.csv");

    while(1)
    {
        cap >> rawImage;
        if(!rawImage.data)
        {
            break;
        }

        cv::LineIterator it(rawImage, pt1, pt2, 8);
        for(int i = 0; i < it.count; i++, ++it)
        {
            b << (int)(*it)[0] << ", ";
            g << (int)(*it)[1] << ", ";
            r << (int)(*it)[2] << ", ";
            //(*it)[0] = 255;
            //(*it)[1] = 255;
            (*it)[2] = 255;    // Mark this sample in red
        }
        b << "\n"; g << "\n"; r << "\n";

        cv::imshow("img", rawImage);
        int c = cv::waitKey(10);
    }
    b << std::endl;
    g << std::endl;
    r << std::endl;
    b.close();
    g.close();
    r.close();
    std::cout << "\n"
    << "Data stored to files: blines.csv, glines.csv and rlines.csv\n\n"
    << std::endl;

}

int main(int argc, char const *argv[])
{
    scene_modeling_example();
    return 0;
}
