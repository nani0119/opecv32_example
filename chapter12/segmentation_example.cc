#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

cv::Mat g_img;
cv::Mat g_img_dumy;
cv::Mat g_mask;
int g_loDiff = 20;
int g_upDiff = 10;
cv::Point g_seed(0, 0);

void myMouseCallback(int event, int x, int y, int flags, void *param)
{
    if(cv::EVENT_LBUTTONDOWN != event)
    {
        return;
    }

    if(param == nullptr)
    {
        std::cout << __func__<<":param is null" << std::endl;
        return;
    }

    cv::Mat& img = *((cv::Mat*)(param));
    cv::imshow("floodfill", img);
    cv::waitKey(1);
    g_mask = cv::Mat(img.rows+2, img.cols+2, CV_8UC1, cv::Scalar(0));
    cv::Mat imgDumy = img.clone();
    g_seed.x = x;
    g_seed.y = y;
    cv::Rect rect1;
    cv::Rect rect2;
    cv::floodFill(imgDumy, g_seed, cv::Scalar(255,255,0), &rect1, cv::Scalar(g_loDiff, g_loDiff, g_loDiff), cv::Scalar(g_upDiff, g_upDiff, g_upDiff), 4);
    cv::floodFill(img, g_mask,g_seed, cv::Scalar(255,255,0), &rect2, cv::Scalar(g_loDiff, g_loDiff, g_loDiff), cv::Scalar(g_upDiff, g_upDiff, g_upDiff), 4|cv::FLOODFILL_MASK_ONLY);

    cv::imshow("floodfill", imgDumy);

    cv::Mat singleChannelMask(g_mask, cv::Range(1, g_mask.rows-1), cv::Range(1, g_mask.cols - 1));
    std::cout << singleChannelMask.size() << std::endl;
    cv::Mat mask;
    cv::Mat maskChannels[] = {singleChannelMask, singleChannelMask, singleChannelMask};
    cv::merge(maskChannels, 3, mask);
    cv::Mat maskImg;
    std::cout << g_img.size() << " " << mask.size() << std::endl;
    g_img.copyTo(maskImg, mask);
    cv::imshow("mask", maskImg);
    cv::waitKey(1);
}

void trackbarDiffCallback(int pos, void* param)
{

    if(param == nullptr)
    {
        std::cout << __func__<<":param is null" << std::endl;
        return;
    }
    std::cout << __func__ << std::endl;
    cv::Mat& img = *((cv::Mat*)(param));
    cv::imshow("floodfill", img);
    cv::waitKey(1);
    g_mask = cv::Mat(img.rows+2, img.cols+2, CV_8UC1, cv::Scalar(0));
    cv::Mat imgDumy = img.clone();
    cv::Rect rect1;
    cv::Rect rect2;
    cv::floodFill(imgDumy, g_seed, cv::Scalar(255,255,0), &rect1, cv::Scalar(g_loDiff, g_loDiff, g_loDiff), cv::Scalar(g_upDiff, g_upDiff, g_upDiff), 4);
    cv::floodFill(img, g_mask,g_seed, cv::Scalar(255,255,0), &rect2, cv::Scalar(g_loDiff, g_loDiff, g_loDiff), cv::Scalar(g_upDiff, g_upDiff, g_upDiff), 4|cv::FLOODFILL_MASK_ONLY);

    cv::imshow("floodfill", imgDumy);
    cv::Mat maskImg;
    cv::Mat singleChannelMask(g_mask, cv::Range(1, g_mask.rows-1), cv::Range(1, g_mask.cols - 1));
    cv::Mat mask;
    cv::Mat maskChannels[] = {singleChannelMask, singleChannelMask, singleChannelMask};
    cv::merge(maskChannels, 3, mask);
    g_img.copyTo(maskImg, mask);
    cv::imshow("mask", maskImg);
    cv::waitKey(1);
}


void myTrackbarLoDiffCallback(int pos, void* param)
{
    std::cout << __func__<<":"<< pos <<  std::endl;
    g_loDiff = pos;
    trackbarDiffCallback(pos, param);
}

void myTrackbarUpDiffCallback(int pos, void* param)
{
    std::cout << __func__<<":"<< pos <<  std::endl;
    g_upDiff = pos;
    trackbarDiffCallback(pos, param);
}


void floodfill_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/bricks.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    g_img = img.clone();
    g_img_dumy = img.clone();

    g_mask = cv::Mat(img.rows+2, img.cols+2, CV_8UC1, cv::Scalar(0));
    std::cout << g_mask.size() << std::endl;
    cv::namedWindow("floodfill");

    cv::setMouseCallback("floodfill", myMouseCallback, (void*)&img);
    cv::createTrackbar("loDiff", "floodfill", &g_loDiff, 255, myTrackbarLoDiffCallback, (void*)&img);
    cv::createTrackbar("upDiff", "floodfill", &g_upDiff, 255, myTrackbarLoDiffCallback, (void*)&img);

    cv::imshow("floodfill", img);

    while(1)
    {
        int key = cv::waitKey(1000);
        if(key >= 0 && key != 255)
        {
            break;
        }

    }
    cv::destroyAllWindows();
}
//==============================================================

cv::Vec3b randomColor(int val)
{
    val = val%255;
    cv::RNG rng;
    return cv::Vec3b(rng.uniform(0, val), rng.uniform(0, val), rng.uniform(0, val));
}

void watershed_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/bricks.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat imgBlur;
    cv::GaussianBlur(img, imgBlur, cv::Size(5,5), 0);

    cv::Mat imgGray;
    cv::cvtColor(imgBlur, imgGray, cv::COLOR_BGR2GRAY);

    cv::Mat imgEdage;
    cv::Canny(imgGray, imgEdage, 100, 200);
    cv::imshow("Edage", imgEdage);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(imgEdage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point());
    cv::Mat hierarchyContours = cv::Mat::zeros(imgEdage.size(), CV_8UC1);
    cv::Mat pointContours = cv::Mat::zeros(imgEdage.size(), CV_8UC1);

#if 1
    for(int i = 0; i < contours.size(); ++i)
    {
        for(int j = 0; j < contours[i].size(); ++j)
        {
            pointContours.at<unsigned char>(contours[i][j]) = (100 + i*10)%255;
        }
        cv::drawContours(hierarchyContours, contours, i, cv::Scalar((100+i*10)%255), 1, cv::LINE_4, hierarchy);
    }
#endif
    //cv::drawContours(hierarchyContours, contours, i, cv::Scalar(255), 1, cv::LINE_AA, hierarchy);
    cv::imshow("pointContours", pointContours);
    cv::imshow("hierarchyContours", hierarchyContours);

    cv::Mat markers = pointContours.clone();
    markers.convertTo(markers, CV_32SC1);
    cv::watershed(img, markers);

    cv::Mat afterWatershed;
    cv::convertScaleAbs(markers, afterWatershed);
    cv::imshow("watershedMarkers", afterWatershed);

    // 对每一个区域填色
    cv::Mat fillColorImg = cv::Mat(img.size(), CV_8UC3);
    for(int i = 0; i < markers.rows; i++)
    {
        for(int j = 0; j < markers.cols; j++)
        {
            int val = markers.at<int>(i, j);
            if( val == -1)
            {
                fillColorImg.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255,255);
            }
            else
            {
                fillColorImg.at<cv::Vec3b>(i, j) = randomColor(val);
            }
        }
    }

    cv::imshow("fillcolor", fillColorImg);

    //与原始图像融合
    cv::Mat wshed;
    cv::addWeighted(img, 0.5, fillColorImg, 0.5, 0, wshed);
    cv::imshow("add weighed img", wshed);

    cv::waitKey(0);
    cv::destroyAllWindows();
}
//====================================================================

cv::Mat g_bgdModel;
cv::Mat g_fgdModel;
cv::Point g_rectS;
cv::Point g_rectE;
cv::Mat g_grabCutMask;
int g_rectStartPointSeted = 0;
void myGrabCutMouseCallback(int event, int x, int y, int flags, void *param)
{
    if(param == nullptr)
    {
        std::cout << __func__ <<"param is null" << std::endl;
        return;
    }
    cv::Mat& img = *((cv::Mat*)(param));


    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        if(flags&cv::EVENT_FLAG_CTRLKEY)
        {
            std::cout << "left button press down" << std::endl;
            g_rectS = cv::Point(x, y);
            g_rectStartPointSeted = 1;
        }
        break;
    case cv::EVENT_MOUSEMOVE:
        if(flags&cv::EVENT_FLAG_CTRLKEY)
        {
            if(g_rectStartPointSeted)
            {
                std::cout << "left button move" << std::endl;
                g_rectE = cv::Point(x, y);
                cv::Mat imgTemp = img.clone();
                cv::rectangle(imgTemp, g_rectS, g_rectE, cv::Scalar(255, 0, 0), 1, 8, 0);
                cv::imshow("grabCut", imgTemp);
                cv::waitKey(10);
            }
        }
        break;
    case cv::EVENT_LBUTTONUP:
        if(flags&cv::EVENT_FLAG_CTRLKEY)
        {
            std::cout << "left button press up" << std::endl;
            g_rectE = cv::Point(x, y);
            cv::Mat imgTemp;
            //cv::rectangle(imgTemp, g_rectS, g_rectE, cv::Scalar(255, 0, 0), 1, 8, 0);
            cv::imshow("grabCut", img);
            cv::waitKey(10);
            g_grabCutMask = cv::Mat::zeros(img.size(), CV_8UC1);
            cv::grabCut(img, g_grabCutMask, cv::Rect(g_rectS, g_rectE), g_bgdModel, g_fgdModel, 11, cv::GC_INIT_WITH_RECT);
#if 1
            for(int i = 0; i < g_grabCutMask.rows; ++i)
            {
                for(int j = 0; j < g_grabCutMask.cols; ++j)
                {
                    if(g_grabCutMask.at<char>(i, j) == cv::GC_FGD || g_grabCutMask.at<char>(i, j) == cv::GC_PR_FGD)
                    {
                        //g_grabCutMask.at<char>(i, j) = 1;
                    }
                    else
                    {
                        g_grabCutMask.at<char>(i, j) = 0;
                    }
                }
            }
#endif
            img.copyTo(imgTemp, g_grabCutMask);
            //cv::normalize(g_grabCutMask, g_grabCutMask, 0, 1, cv::NORM_MINMAX);
            cv::imshow("grabCut", imgTemp);
            g_rectStartPointSeted = 0;
            cv::waitKey(10);
        }
        break;

    default:
        break;
    }
}

void grabCut_example()
{
    int key = 0;
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::namedWindow("grabCut", CV_WINDOW_AUTOSIZE);
    cv::setMouseCallback("grabCut", myGrabCutMouseCallback, (void*)(&img));
    cv::imshow("grabCut", img);
    while(1)
    {
        key = cv::waitKey(1000);
        if(key == 'q')
        {
            break;
        }
    }
    cv::destroyAllWindows();

}

//=========================================================
int g_spatialWindow = 20;
int g_colorWindow = 40;
int g_maxLevel = 2;
void showMeanShiftImg(cv::Mat& img);
void MSTrackbarCB(int pos, void* param)
{
    if(param == nullptr)
    {
        std::cout << "param is null" << std::endl;
        return;
    }
    cv::Mat& img = *((cv::Mat*)(param));
    cv::Mat dst;
    cv::pyrMeanShiftFiltering(img, dst, g_spatialWindow, g_colorWindow, g_maxLevel);
    cv::imshow("dst", dst);
}

void pyrMeanShiftFiltering_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);
    cv::createTrackbar("spatial window", "img", &g_spatialWindow, 255, MSTrackbarCB, (void*)(&img));
    cv::createTrackbar("color window", "img", &g_colorWindow, 255, MSTrackbarCB, (void*)(&img));
    cv::createTrackbar("max level", "img", &g_maxLevel, 10, MSTrackbarCB, (void*)(&img));

    MSTrackbarCB(0, (void*)(&img));

    int key = 0;
    while(1)
    {
        key = cv::waitKey(100);
        if(key == 'q')
        {
            break;
        }
    }
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    //floodfill_example();
    watershed_example();
    //grabCut_example();
    //pyrMeanShiftFiltering_example();
    return 0;
}
