#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void connectedComponents_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/14/circle.png", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::threshold(img, img, 128, 255, cv::THRESH_BINARY);
    cv::bitwise_not(img,img);
    cv::imshow("img", img);

    cv::Mat labels;
    cv::Mat stats;
    cv::Mat centroids;
    int nccomps = cv::connectedComponentsWithStats(img, labels, stats, centroids);
    std::cout << "Total Connected Components Detected: " << nccomps << std::endl;



    cv::Mat img_color = cv::Mat::zeros(img.size(), CV_8UC3);




    std::vector<cv::Vec3b> colors(nccomps +1);

    for (int i = 0; i < nccomps; i++)
    {
        colors[i] = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
        if (stats.at<int>(i - 1, cv::CC_STAT_AREA) < 100)
        {
            colors[i] = cv::Vec3b(0, 0, 0); // small regions are painted with black too.
        }
    }
    colors[0] = cv::Vec3b(0,0,0); // background pixels remain black.


    for (int y = 0; y < img_color.rows; y++)
    {
        for (int x = 0; x < img_color.cols; x++)
        {
            int label = labels.at<int>(y, x);
            CV_Assert(0 <= label && label <= nccomps);
            img_color.at<cv::Vec3b>(y, x) = colors[label];
        }
    }


    for(int i = 0; i < nccomps; i++)
    {
        cv::rectangle(img_color,
                        cv::Rect(stats.at<int>(i, 0), stats.at<int>(i, 1), stats.at<int>(i, 2), stats.at<int>(i, 3)),
                        cv::Scalar(0, 0, 255)
                    );
    }


    for(int i = 0; i < nccomps; i++)
    {
        cv::circle(img_color, cv::Point(centroids.at<double>(i, 0), centroids.at<double>(i, 1)), 1, cv::Scalar(255, 255, 255));
    }
    cv::imshow("Labeled map", img_color);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    connectedComponents_example();
    return 0;
}
