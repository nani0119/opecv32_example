#include <iostream>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void dft_example()
{
    cv::Mat m = (cv::Mat_<float>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat dst;
    cv::dft(m, dst);
    cv::Mat idst;
    cv::idft(dst, idst, cv::DFT_SCALE);

    std::cout << "m:" << m << std::endl;
    std::cout << "dst:" << dst << std::endl;
    std::cout << "idst:" << idst << std::endl;
}

void dft_img_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/lena.bmp", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    int r = cv::getOptimalDFTSize(img.rows);
    int c = cv::getOptimalDFTSize(img.cols);
    cv::Mat imgDst;
    cv::copyMakeBorder(img, imgDst, r - img.rows, 0, c - img.cols, 0, cv::BORDER_CONSTANT, cv::Scalar());

    img.convertTo(imgDst, CV_32F);
    cv::normalize(imgDst, imgDst, 0, 1, cv::NORM_MINMAX);
    cv::Mat imgDstTemp = imgDst.clone();
    cv::imshow("img", imgDstTemp);

    cv::Mat plant[] = {imgDst, cv::Mat(imgDst.size(), imgDst.type(), cv::Scalar::all(0))};
    cv::Mat ComplexDst;
    cv::merge(plant, 2, ComplexDst);

    cv::Mat dftDst;
    cv::dft(ComplexDst, dftDst, cv::DFT_COMPLEX_OUTPUT);

    cv::split(dftDst, plant);

    cv::Mat dftMagnitude;
    cv::magnitude(plant[0], plant[1], dftMagnitude);

    dftMagnitude += cv::Scalar::all(1);
    cv::log(dftMagnitude, dftMagnitude);
    cv::normalize(dftMagnitude, dftMagnitude, 0, 1, cv::NORM_MINMAX);


    cv::Mat dftResultImg(dftMagnitude.size(), dftMagnitude.type());

    cv::Mat roiDftMagnitudeTL(dftMagnitude, cv::Rect(0, 0, dftMagnitude.cols/2, dftMagnitude.rows/2));
    cv::Mat roiDftResultBR(dftResultImg, cv::Rect(dftResultImg.rows/2, dftResultImg.cols/2, dftResultImg.cols/2, dftResultImg.rows/2));
    roiDftMagnitudeTL.copyTo(roiDftResultBR);

    cv::Mat roiDftMagnitudeTR(dftMagnitude, cv::Rect(dftMagnitude.cols/2, 0, dftMagnitude.cols/2, dftMagnitude.rows/2));
    cv::Mat roiDftResultBL(dftResultImg, cv::Rect(0, dftResultImg.rows/2, dftResultImg.cols/2, dftResultImg.rows/2));
    roiDftMagnitudeTR.copyTo(roiDftResultBL);

    cv::Mat roiDftMagnitudeBL(dftMagnitude, cv::Rect(0, dftMagnitude.rows/2, dftMagnitude.cols/2, dftMagnitude.rows/2));
    cv::Mat roiDftResultTR(dftResultImg, cv::Rect(dftResultImg.rows/2, 0, dftResultImg.cols/2, dftResultImg.rows/2));
    roiDftMagnitudeBL.copyTo(roiDftResultTR);

    cv::Mat roiDftMagnitudeBR(dftMagnitude, cv::Rect(dftMagnitude.cols/2, dftMagnitude.rows/2, dftMagnitude.cols/2, dftMagnitude.rows/2));
    cv::Mat roiDftResultTL(dftResultImg, cv::Rect(0, 0, dftResultImg.cols/2, dftResultImg.rows/2));
    roiDftMagnitudeBR.copyTo(roiDftResultTL);

    cv::imshow("dft", dftResultImg);


    cv::Mat idftImg;
    cv::idft(dftDst, idftImg, cv::DFT_REAL_OUTPUT|cv::DFT_INVERSE);
    cv::normalize(idftImg, idftImg, 0, 1, cv::NORM_MINMAX);
    cv::imshow("idft", idftImg);

#if 1
    std::cout << "img  size :" << imgDstTemp.size()  << " type: "<< imgDstTemp.type()<< std::endl;
    std::cout << "idft size :" << idftImg.size()  << " type: "<< idftImg.type()<< std::endl;
    for(int i = 0; i < img.rows; ++i)
    {
        for(int j = 0; j < img.cols; ++j)
        {
            if(imgDstTemp.at<float>(i, j) - idftImg.at<float>(i, j) > 0.000001)
            {
                std::cout << "pos :" << i<< "," << j << " value:" << imgDstTemp.at<float>(i, j) << "  " << idftImg.at<float>(i, j)<< std::endl;
            }
        }
    }
#else
    std::cout << cv::sum(imgDstTemp - idftImg) << std::endl;
#endif
    cv::waitKey(0);
    cv::destroyAllWindows();

}

// 两个函数的卷积的傅里叶变换等于各自的傅里叶变换的乘积
// 两个函数傅里叶乘积的逆变换等于空域的卷积
void mulSpectrums_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/12/lena.bmp", cv::IMREAD_GRAYSCALE);
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat kernel = cv::getGaussianKernel(5, 40);
    kernel = kernel*kernel.t();
    kernel.convertTo(kernel, CV_32F);
    std::cout << "kernel:" << kernel << std::endl;

    int r = cv::getOptimalDFTSize(img.rows);
    int c = cv::getOptimalDFTSize(img.cols);
    cv::Mat imgDst;
    cv::copyMakeBorder(img, imgDst, r - img.rows, 0, c - img.cols, 0, cv::BORDER_CONSTANT, cv::Scalar());
    cv::imshow("img", imgDst);

    cv::Mat filter2DImg;
    cv::filter2D(imgDst, filter2DImg, CV_32F, kernel);
    cv::normalize(filter2DImg, filter2DImg, 0.0, 1.0, cv::NORM_MINMAX);
    cv::imshow("filter2DImg", filter2DImg);

    //========================================================
    cv::Mat convolveImg;
    imgDst.convertTo(convolveImg, CV_32F);

    cv::Mat tempKernel(convolveImg.size(), convolveImg.type(), cv::Scalar::all(0));
    cv::Mat roiKernel(tempKernel, cv::Rect(0, 0, kernel.cols, kernel.rows));
    kernel.copyTo(roiKernel);

    cv::dft(convolveImg, convolveImg, 0, convolveImg.rows);
    cv::dft(tempKernel, tempKernel, 0, kernel.rows);

    cv::mulSpectrums(convolveImg, tempKernel, convolveImg, cv::DFT_COMPLEX_OUTPUT);

    cv::idft(convolveImg, convolveImg, cv::DFT_SCALE, convolveImg.rows);

    cv::normalize(convolveImg, convolveImg, 0, 1, cv::NORM_MINMAX);
    cv::imshow("result", convolveImg);


    cv::waitKey(0);
    cv::destroyAllWindows();
}


int main(int argc, char const *argv[])
{
    //dft_example();
    dft_img_example();
    //mulSpectrums_example();
    return 0;
}


