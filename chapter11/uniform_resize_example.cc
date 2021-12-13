#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#define RESOURCE_DIR "../resource/"

void resize_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat upsizeImg;
    cv::resize(img, upsizeImg, cv::Size(0,0), 1.5, 1.5, cv::INTER_CUBIC);

    cv::Mat downsizeImg;
    cv::resize(img, downsizeImg, cv::Size(0,0), 0.5, 0.5, cv::INTER_LINEAR);

    cv::imshow("origin", img);
    cv::imshow("upsize", upsizeImg);
    cv::imshow("downsize", downsizeImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

void image_pyramids_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::imshow("origin", img);

    cv::Mat pyrDownDst;
    cv::pyrDown(img, pyrDownDst, cv::Size(), cv::BORDER_DEFAULT);
    cv::imshow("pyrDown", pyrDownDst);

    cv::Mat pyrUpDst;
    cv::pyrUp(pyrDownDst, pyrUpDst, cv::Size(), cv::BORDER_DEFAULT);
    cv::imshow("pyrUp", pyrUpDst);

    std::vector<cv::Mat> dst;
    cv::buildPyramid(img, dst, 5);
    for(auto it = dst.begin(); it != dst.end(); ++it)
    {
        cv::imshow("Pyramid", *it);
        cv::waitKey(2000);
    }

    cv::waitKey(0);
    cv::destroyAllWindows();

}



int main(int argc, char const *argv[])
{
    //resize_example();
    image_pyramids_example();
    return 0;
}
