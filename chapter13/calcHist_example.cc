#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void calcHist_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/13/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::imshow("img", img);
    cv::Mat histImg (img.size(), CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Mat images[] = { img};
    int nimgages = 1;
    int channels[1] = {0};
    int dims = 1;
    const int histSize[] = {255};
    float range[] = {0, 255};
    const float* ranges[] = {range};

    int hist_w = histImg.cols;
    int hist_h = histImg.rows;
    int bin_width = cvRound(double(hist_w)/histSize[0]);

    std::cout << img.channels() << std::endl;
    for(int c = 0; c < img.channels(); c++)
    {
        cv::Mat hist;
        channels[0] = c;
        cv::calcHist(images, nimgages, channels, cv::noArray(), hist, dims, histSize, ranges, true, false);
        //std::cout << hist.size() << std::endl;
        //std::cout << hist.channels() << std::endl;
        //std::cout << hist.dims<< std::endl;
        cv::normalize(hist, hist, 0, histImg.rows, cv::NORM_MINMAX);

        cv::Scalar color;
        if(c == 0)
        {
            color = cv::Scalar(255, 0, 0);
        }else if(c == 1)
        {
            color = cv::Scalar(0, 255, 0);
        }
        else
        {
            color = cv::Scalar(0, 0, 255);
        }

        for(int i = 1; i < histSize[0]; i++)
        {
            cv::line(histImg, cv::Point2d(bin_width*(i - 1), hist_h - cvRound(hist.at<float>(i-1))),
                                cv::Point2d(bin_width*(i), hist_h - cvRound(hist.at<float>(i))),
                                color, 1, 8 ,0);
        }

    }

    cv::imshow("hist", histImg);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void calcHist_HUV_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/13/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::imshow("img", img);

    cv::Mat hsvImg;
    cv::cvtColor(img, hsvImg, cv::COLOR_RGB2HSV);
    cv::imshow("hsvimg", hsvImg);

    float h_ranges[] = {0, 180}; // hue is [0, 180]
    float s_ranges[] = {0, 256};
    const float* ranges[] = {h_ranges, s_ranges};
    int histSize[] = {30, 32};
    int ch[] = {0, 1};

    cv::Mat hist;
    // Compute the histogram
    //
    cv::calcHist(&hsvImg, 1, ch, cv::noArray(), hist, 2, histSize, ranges, true);
    cv::normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

    int scale = 10;
    cv::Mat histImg(histSize[0]*scale, histSize[1]*scale, CV_8UC3);

    // Draw our histogram.
    //
    for (int h = 0; h < histSize[0]; h++)
    {
        for (int s = 0; s < histSize[1]; s++)
        {
            float hval = hist.at<float>(h, s);
            cv::rectangle(
                histImg,
                cv::Rect(h * scale, s * scale, scale, scale),
                cv::Scalar::all(hval),
                -1);
        }
    }

    cv::imshow("H-S histogram", histImg);
    cv::waitKey(0);

    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    //calcHist_example();
    calcHist_HUV_example();
    return 0;
}
