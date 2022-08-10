#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void videoIO_example()
{
    std::cout << std::endl << __func__ << std::endl;
    int key;
    cv::VideoCapture capture(RESOURCE_DIR"/2/test.avi");
    if(!capture.isOpened())
    {
        std::cout << "open video file fail"<< std::endl;
        return;
    }
    double w = capture.get(cv::CAP_PROP_FRAME_WIDTH);
    double h = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
    double fps = capture.get(cv::CAP_PROP_FPS);
    unsigned int f = (unsigned int)capture.get(cv::CAP_PROP_FOURCC);
    char fourcc[] = {
                        (char) f, // First character is lowest bits
                        (char)(f >> 8), // Next character is bits 8-15
                        (char)(f >> 16), // Next character is bits 16-23
                        (char)(f >> 24), // Last character is bits 24-31
                        '\0' // and don't forget to terminate
                    };
    int frameCount = (int)capture.get(cv::CAP_PROP_FRAME_COUNT);
    double format = capture.get(cv::CAP_PROP_FORMAT);
    double mode = capture.get(cv::CAP_PROP_MODE);

    std::cout << "video info:" << std::endl;
    std::cout << "width:" << w << std::endl;
    std::cout << "height:" << h << std::endl;
    std::cout << "fps:" << fps << std::endl;
    std::cout << "fourcc:" << fourcc << std::endl;
    std::cout << "frameCount:" << frameCount << std::endl;
    std::cout << "format:" << format << std::endl;
    std::cout << "mode:" << mode << std::endl;


    cv::VideoWriter writer("invertTest.avi", cv::VideoWriter::fourcc('M','P','E','G'), fps, cv::Size(w, h));
    if(!writer.isOpened())
    {
        std::cout << "writer open fail" << std::endl;
        return;
    }

    cv::Mat img;
    for(int i = frameCount -1; i >= 0; --i)
    {

        if(!capture.set(cv::CAP_PROP_POS_FRAMES, i))
        {
            std::cout << "set frame pos fail" << std::endl;
        }
        capture.read(img);
        if(img.empty())
        {
            std::cout << "img empty" << std::endl;
            break;
        }
        writer << img;
    }

    capture.release();
    writer.release();




    cv::namedWindow("video", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture reader("invertTest.avi");
    if(!reader.isOpened())
    {
        std::cout << "read video file fail"<< std::endl;
        return;
    }

    int cnt = reader.get(cv::CAP_PROP_FRAME_COUNT);
    for(int i = 0; i < cnt; i++)
    {

        if(!reader.grab())
        {
            std::cout << "grab fail" << std::endl;
        }
        if(reader.retrieve(img))
        {
            cv::imshow("video", img);
        }
        else
        {
            std::cout << "retrive img fail" << std::endl;
        }
        std::this_thread::sleep_for((std::chrono::milliseconds(1))*((1000/fps) -1));
        cv::waitKey(1); // 没有waitKey 图片不显示, cv::startWindowThread() 也可以用来更新图片
        //std::cout << i << std::endl;
        //cv::waitKey(1000/fps);
    }
    reader.release();
    //cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    videoIO_example();
    return 0;
}
