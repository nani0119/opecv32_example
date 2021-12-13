#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void matchTemplate_example()
{
    // Read in the template to be used for matching:
    cv::Mat templ = cv::imread(RESOURCE_DIR"/13/template.jpg");
    if(templ.empty())
    {
        std::cout << "template img is empty" << std::endl;
        return;
    }

    // Read in the source image to be searched:
    cv::Mat src = cv::imread(RESOURCE_DIR"/13/searched.jpg");
    if(src.empty())
    {
        std::cout << "searched img is empty" << std::endl;
        return;
    }

    // Do the matching of the template with the image
    cv::Mat result;
    // TM_SQDIFF --- perfect match will be 0 and bad matches will be large
    // TM_SQDIFF_NORMED --- a perfect match will return a 0.
    // TM_CCORR --- a perfect match will be large and bad matches will be small or 0
    // TM_CCORR_NORMED --- an extreme mismatch for cv::TM_CCORR_NORMED will return a score near 0
    // TM_CCOEFF --- a perfect match will be 1 and a perfect mismatch will be –1; a value of 0 simply means that there is no correlation
    // TM_CCOEFF_NORMED ---  a relative match  will return a positive score and a relative mismatch will return a negative score

    cv::matchTemplate(src, templ, result, cv::TM_SQDIFF);
    cv::normalize(result, result, 1, 0, cv::NORM_MINMAX);

    cv::imshow("result", result);

    double minVal;
    double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;

    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::noArray());

    std::cout << "method TM_SQDIFF: minVlal:" << minVal << " location: " << minLoc << std::endl;
    std::cout << "method TM_SQDIFF: maxVlal:" << maxVal << " location: " << maxLoc << std::endl;

    cv::rectangle(src, cv::Point(minLoc.x, minLoc.y),  cv::Point(minLoc.x + templ.cols, minLoc.y + templ.rows), cv::Scalar(0, 255, 0));
    cv::rectangle(src, cv::Point(maxLoc.x, maxLoc.y),  cv::Point(maxLoc.x + templ.cols, minLoc.y + templ.rows), cv::Scalar(0, 0, 255));

    cv::imshow("match", src);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    matchTemplate_example();
    return 0;
}
