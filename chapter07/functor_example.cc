#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void PCA_example()
{
    std::cout << std::endl << __func__ << std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/7/face.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

    grayImg.convertTo(grayImg, CV_32F, 1.0/255);

    cv::namedWindow("gray-img", cv::WINDOW_AUTOSIZE);
    cv::imshow("gray-img", grayImg);


    cv::PCA pca {};
    pca(grayImg, cv::Mat(), cv::PCA::DATA_AS_COL, 50);

    cv::Mat vec = pca.project(grayImg);

    cv::namedWindow("project-img", cv::WINDOW_AUTOSIZE);
    cv::imshow("project-img", vec);


    cv::Mat src = pca.backProject(vec);

    cv::namedWindow("backproject-img", cv::WINDOW_AUTOSIZE);
    cv::imshow("backproject-img", src);

    cv::waitKey(0);
    cv::destroyAllWindows();

}


void SVD_example()
{
    std::cout << std::endl << __func__ << std::endl;
    cv::Mat A = (cv::Mat_<float>(3,3)<< 1, 2, 3, 4, 5, 6, 7, 8, 9);

    cv::SVD svd {};

    cv::Mat W, U, Vt;
    svd.compute(A, W, U, Vt, cv::SVD::FULL_UV);

    std::cout << "A" << A << std::endl;
    std::cout << "W" << W << std::endl;
    std::cout << "U" << U << std::endl;
    std::cout << "Vt" << Vt << std::endl;
}

void RNG_example()
{
    std::cout << std::endl << __func__ << std::endl;

    cv::RNG rng = cv::theRNG();
    std::cout << "(int)rng: "    << (int)rng << std::endl;
    std::cout << "float(rng): "  << float(rng) << std::endl;
    std::cout << "rng():"  << rng() << std::endl;
    std::cout << "rng(usinged int n):"  << rng(1000) << std::endl;

    std::cout << "rng.uniform(float a, float b):" << rng.uniform(0.0F, 0.5F) << std::endl;
    std::cout << "rng.uniform(int a, int b):" << rng.uniform(0, 2) << std::endl;
    std::cout << "rng.gaussian(double sigma):" << rng.gaussian(1) << std::endl;
}


int main(int argc, char const *argv[])
{
#if 0
    PCA_example();
    RNG_example();
#endif
    SVD_example();
    return 0;
}
