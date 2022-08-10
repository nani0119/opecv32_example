#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"
void onTraceBarCallback(int pos, void* param);

int g_logPolarScale = 0;
int g_imageRoateAngle = 0;
int g_imageMove = 0;
void onTraceBarImgRoateAngle(int pos, void* param)
{
    if(param == nullptr)
    {
        std::cout << __func__<<":param is null" << std::endl;
        return;
    }
    g_imageRoateAngle = pos;
    cv::Mat& img = *((cv::Mat*)param);

    cv::Point2f center(img.cols*0.5f, img.rows*0.5f);
    cv::Mat roate_mat = cv::getRotationMatrix2D(center, pos, 1.0);
    cv::Mat dst;
    cv::warpAffine(img, dst, roate_mat, img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
    cv::imshow("img", dst);


    onTraceBarCallback(g_logPolarScale, (void*)&dst);
}

void onTraceBarImgMove(int pos, void* param)
{
    if(param == nullptr)
    {
        std::cout << __func__<<":param is null" << std::endl;
        return;
    }
    g_imageMove = pos;
    cv::Mat& img = *((cv::Mat*)param);

    cv::Point2f srcTri[] = {
        cv::Point2f(0,0), // src Top left
        cv::Point2f(img.cols-1, 0), // src Top right
        cv::Point2f(0, img.rows-1) // src Bottom left
    };

    cv::Point2f dstTri[] ={
        cv::Point2f(0+g_imageMove, 0+g_imageMove), // dst Top left
        cv::Point2f((img.cols-1)+g_imageMove, 0+g_imageMove), // dst Top right
        cv::Point2f(0+g_imageMove, (img.rows-1)+g_imageMove) // dst Bottom left
    };

    cv::Mat wrap_mat = cv::getAffineTransform(srcTri, dstTri);

    cv::Mat dst;
    cv::warpAffine(img, dst, wrap_mat, img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    cv::imshow("img", dst);

    onTraceBarCallback(g_logPolarScale, (void*)&dst);
}

void onTraceBarCallback(int pos, void* param)
{
    if(param == nullptr)
    {
        std::cout << __func__<<":param is null" << std::endl;
        return;
    }
    g_logPolarScale = pos;
    cv::Mat& img = *((cv::Mat*)param);

    cv::Point2f center(img.cols*0.5f, img.rows*0.5f);
    cv::Mat dst;
    cv::logPolar(img, dst, center, g_logPolarScale, cv::INTER_LINEAR|cv::WARP_FILL_OUTLIERS);

    cv::Mat invDst;
    cv::logPolar(dst, invDst, center, g_logPolarScale, cv::INTER_LINEAR|cv::WARP_INVERSE_MAP);

    cv::imshow("logPolar", dst);
    cv::imshow("inv-logPolar", invDst);
    //cv::circle(img, center, 3, cv::Scalar(255,255,255), 1);


}

void logPolar_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    int logPolarPos = 40;
    int imgMove = 0;
    int imgRoateAngle = 0;
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("inv-logPolar", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("logPolar", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("scale:", "logPolar", &logPolarPos, 100, onTraceBarCallback, (void*)&img);
    cv::createTrackbar("move:", "img", &imgMove, 200, onTraceBarImgMove, (void*)&img);
    cv::createTrackbar("angle:", "img", &imgRoateAngle, 360, onTraceBarImgRoateAngle, (void*)&img);
    onTraceBarCallback(logPolarPos, (void*)&img);
    cv::imshow("img", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}


void remap_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat dst;
    cv::Mat mapX(img.size(), CV_32F);
    cv::Mat mapY(img.size(), CV_32F);


    for(int r = 0; r < img.rows; ++r)
    {
        for(int c = 0; c < img.cols; ++c)
        {
            mapX.at<float>(r, c) = c;
            mapY.at<float>(r, c) = r;
        }
    }

#if 1
    for(int r = 0; r < img.rows/2; ++r)
    {
        for(int c = 0; c < img.cols/2; ++c)
        {
            mapX.at<float>(img.rows/4 + r, img.cols/4 + c) = img.cols*3/4 -1 - c;
            mapY.at<float>(img.rows/4 + r, img.cols/4 + c) = img.rows*3/4 -1 - r;
        }
    }
#endif

    // dst(x, y) = src(mapX(x, y), mapY(x, y))
    cv::remap(img, dst, mapX, mapY, cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    cv::imshow("img", img);
    cv::imshow("dst", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    //logPolar_example();
    remap_example();

    return 0;
}
