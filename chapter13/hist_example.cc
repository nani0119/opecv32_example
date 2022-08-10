#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void hist_example()
{
    std::vector<cv::Mat> src(5);
    cv::Mat tmp = cv::imread(RESOURCE_DIR"/13/HandIndoorColor.jpg");
    if(tmp.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    // Parse the first image into two image halves divided halfway on y
    cv::Size size = tmp.size();
    int width = size.width;
    int height = size.height;
    int halfheight = height>>1;

    std::cout << "Getting size [[" << tmp.cols << "] [" << tmp.rows << "]]" << std::endl;
    std::cout <<"Got size (w,h): (" <<size.width <<"," <<size.height <<")" <<std::endl;
    src[0] = cv::Mat(cv::Size(width, halfheight), CV_8UC3);
    src[1] = cv::Mat(cv::Size(width, halfheight), CV_8UC3);

    // Divide the first image into top and bottom halves into src[0] and src[1]
    cv::Mat_<cv::Vec3b>::iterator tmpit = tmp.begin<cv::Vec3b>();

    // top half
    for(cv::Mat_<cv::Vec3b>::iterator s0it = src[0].begin<cv::Vec3b>();s0it != src[0].end<cv::Vec3b>(); ++s0it, ++tmpit)
    {
        *s0it = *tmpit;
    }

    // bottom half

    for(cv::Mat_<cv::Vec3b>::iterator s1it = src[1].begin<cv::Vec3b>(); s1it != src[1].end<cv::Vec3b>(); ++s1it, ++tmpit)
    {
        *s1it = *tmpit;
    }

    // Load the other three images
    src[2] = cv::imread(RESOURCE_DIR"/13/HandOutdoorColor.jpg");
    if(src[2].empty())
    {
        std::cout << "src2 img is empty" << std::endl;
        return;
    }

    src[3] = cv::imread(RESOURCE_DIR"/13/HandOutdoorSunColor.jpg");
    if(src[3].empty())
    {
        std::cout << "src3 img is empty" << std::endl;
        return;
    }

    src[4] = cv::imread(RESOURCE_DIR"/13/desert.jpg");
    if(src[4].empty())
    {
        std::cout << "src3 img is empty" << std::endl;
        return;
    }

#if 0
    for(int i = 0; i < src.size(); i++)
    {
        std::stringstream ss;
        ss << i;
        std::string win = "img" + ss.str();
        cv::imshow(win.c_str(), src[i]);
    }
#endif

    // Compute the HSV image, and decompose it into separate planes.
    std::vector<cv::Mat> hsv(5), hist(5), hist_img(5);
    int h_bins = 8;
    int s_bins = 8;
    int hist_size[] = {h_bins, s_bins};
    int ch[] = {0, 1};
    float h_ranges[] = {0, 180};
    float s_ranges[] = {0, 255};
    const float* ranges[] = {h_ranges, s_ranges};
    int scale = 10;
    for(int i = 0; i < 5; i++)
    {
        cv::cvtColor(src[i], hsv[i], cv::COLOR_BGR2HSV);
        cv::calcHist(&hsv[i], 1, ch, cv::noArray(), hist[i], 2, hist_size, ranges, true, false);
        cv::normalize(hist[i], hist[i], 0, 255, cv::NORM_MINMAX);
        hist_img[i] = cv::Mat::zeros(hist_size[0]*scale, hist_size[1]*scale, CV_8UC3);

        // Draw our histogram For the 5 images
        for(int h = 0; h < hist_size[0]; ++h)
        {
            for(int s = 0; s < hist_size[1]; ++s)
            {
                float hval = hist[i].at<float>(h,s);
                cv::rectangle(
                        hist_img[i],
                        cv::Rect(h*scale, s*scale, scale, scale),
                        cv::Scalar::all(hval),
                        1
                );
            }
        }
    }
#if 1
        // Display
        cv::namedWindow( "Source0", cv::WINDOW_AUTOSIZE );cv::imshow( "Source0", src[0] );
        cv::namedWindow( "HS Histogram0", cv::WINDOW_AUTOSIZE );cv::imshow( "HS-Histogram0", hist_img[0] );
        cv::namedWindow( "Source1", cv::WINDOW_AUTOSIZE );cv::imshow( "Source1", src[1] );
        cv::namedWindow( "HS Histogram1", cv::WINDOW_AUTOSIZE ); cv::imshow( "HS-Histogram1", hist_img[1] );
        cv::namedWindow( "Source2", cv::WINDOW_AUTOSIZE ); cv::imshow( "Source2", src[2] );
        cv::namedWindow( "HS Histogram2", cv::WINDOW_AUTOSIZE ); cv::imshow( "HS-Histogram2", hist_img[2] );
        cv::namedWindow( "Source3", cv::WINDOW_AUTOSIZE ); cv::imshow( "Source3", src[3] );
        cv::namedWindow( "HS Histogram3", cv::WINDOW_AUTOSIZE ); cv::imshow( "HS-Histogram3", hist_img[3] );
        cv::namedWindow( "Source4", cv::WINDOW_AUTOSIZE ); cv::imshow( "Source4", src[4] );
        cv::namedWindow( "HS Histogram4", cv::WINDOW_AUTOSIZE ); cv::imshow( "HS-Histogram4", hist_img[4] );

#endif

    // Compare the histogram src0 vs 1, vs 2, vs 3, vs 4
    std::cout << "Comparison:\n"
                << "Corr Chi Intersect Bhat\n"
                << std::endl;

    for(int i=1; i<5; ++i)
    { // For each histogram
        std::cout << "Hist[0] vs Hist[" << i << "]: " << std::endl;;
        for(int j=0; j<4; ++j)
        { // For each comparison type
            std::cout << "method[" << j << "]: " << \
            cv::compareHist(hist[0],hist[i],j) \
            << " ";
        }
        std::cout << std::endl;
    }

    //Do EMD and report

    std::vector<cv::Mat> sig(5);
    std::cout << "\nEMD: " << std::endl;

    // Oi Vey, parse histograms to earth movers signatures

    for(int i = 0; i < 5; i++)
    {
        std::vector<cv::Vec3f> sigv;
        // (re)normalize histogram to make the bin weights sum to 1.
        cv::normalize(hist[i], hist[i], 1, 0, cv::NORM_L1);
        for(int h = 0; h < h_bins; h++)
        {
            for(int s = 0; s < s_bins; s++)
            {
                float bin_val = hist[i].at<float>(h, s);
                if(bin_val != 0)
                {
                    sigv.push_back(cv::Vec3f(bin_val, (float)h, (float)s));
                }
            }
        }
        // make Nx3 32fC1 matrix, where N is the number of nonzero histogram bins
        sig[i] = cv::Mat(sigv).clone().reshape(1);
        if(i > 0)
        {
            std::cout << "Hist[0] vs Hist[" << i << "]: " <<
                cv::EMD(sig[0], sig[i], cv::DIST_L2)
             << std::endl;
        }
    }




    cv::waitKey(0);
    cv::destroyAllWindows();

}

int main(int argc, char const *argv[])
{
    hist_example();
    return 0;
}
