#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#define RESOURCE_DIR "../resource/"

void abs_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m1 (1, 1, CV_8SC3, cv::Scalar(-1, 2, -3));
    cv::Mat m2 (1, 1, CV_8SC3, cv::Scalar(1, -2, 3));
    std::cout << "m1 : "<< m1 << std::endl;
    std::cout << "m2 : "<< m2 << std::endl;

    std::cout << "abs(m1): "<<cv::abs(m1) << std::endl;
    std::cout << "abs(m2 - m1): "<<cv::abs(m2 - m1) << std::endl;

}

void add_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m1 (1, 1, CV_8SC3, cv::Scalar(-1, 2, -3));
    cv::Mat m2 (1, 1, CV_8SC3, cv::Scalar(1, -2, 3));
    cv::Mat m3 (1, 1, CV_8SC3, cv::Scalar(0, 0, 0));
    cv::add(m1, m2, m3);
    std::cout << "m1 + m2 = " << m3 << std::endl;
}

// 按权重混合
void addWeighted_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    float alpha = 0.4F;
    float beta = (1.0F - alpha);
    float gamma = 100.0F;

    cv::Mat display;
    cv::Mat flower = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    cv::Mat lotus = cv::imread(RESOURCE_DIR"/5/lotus.bmp");

    int w = std::min(flower.cols, lotus.cols);
    int h = std::min(flower.rows, lotus.rows);
    cv::Mat flowerRoi(flower, cv::Rect(0, 0, w, h));
    cv::Mat lotusRoi(lotus, cv::Rect(0,0, w, h));

    cv::addWeighted(flowerRoi, alpha, lotusRoi, beta, gamma, lotusRoi);

    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example", lotus);
    cv::waitKey(0);
    cv::destroyWindow("Example");

}

// 计算协方差
void calcCovarMatrix_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m1;
    m1.create(3, 3, CV_8UC1);
    rng.fill(m1, cv::RNG::UNIFORM, cv::Scalar(1,1,1), cv::Scalar(255, 255, 255));
    std::cout << m1 << std::endl;
    cv::Mat covar;
    cv::Mat mean;

    cv::calcCovarMatrix(m1, covar, mean, cv::COVAR_ROWS|cv::COVAR_NORMAL);
    std::cout << "covar:" << covar << std::endl;
    std::cout << "mean:" << mean << std::endl;
}


// 笛卡尔坐标转换为极坐标
void cartToPlar_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat x;
    cv::Mat y;
    x.create(1, 10, CV_32F);
    y.create(1, 10, CV_32F);
    rng.fill(x, cv::RNG::UNIFORM, 1, 255);
    rng.fill(y, cv::RNG::UNIFORM, 1, 255);

    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;

    cv::Mat magnitude;
    cv::Mat angle;

    cv::cartToPolar(x, y, magnitude, angle);

    std::cout << "magnitude:" << magnitude << std::endl;
    std::cout << "angle:" << angle << std::endl;

    cv::polarToCart(magnitude, angle, x, y);

    std::cout << "x:" << x << std::endl;
    std::cout << "y:" << y << std::endl;
}

// 检测范围
void checkRange_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Point p;
    cv::RNG rng;
    cv::Mat m(3, 3, CV_8U);
    rng.fill(m, cv::RNG::UNIFORM, 1, 100);

    m.at<unsigned char>(1, 1) = 200;

    std:: cout << "m: " << m << std::endl;
    cv::checkRange(m, true, &p, 1, 100);

    std::cout << "out of range point:" << p << std::endl;
}

void commpleteSymm_example()
{
   std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m(4, 4, CV_8U);
    rng.fill(m, cv::RNG::UNIFORM, 1, 100);
    std::cout << "m:" << m << std::endl;
    cv::completeSymm(m, true);
    std::cout << "symm:" << m << std::endl;
}

//dsti = saturateuchar( | α*srci + β | )
void convertScaleAbs_example()
{
   std::cout << std::endl << __func__ << ":" <<std::endl;
   cv::RNG rng;
   cv::Mat m(4, 4, CV_32F);
   rng.fill(m, cv::RNG::UNIFORM, 1, 300);
   cv::Mat ret;
   std::cout << "m:" << m << std::endl;

   cv::convertScaleAbs(m, ret, 1.5, 0);
   std::cout << "ret:" << ret << std::endl;
}

void countNonZero_example()
{
   std::cout << std::endl << __func__ << ":" <<std::endl;
   cv::RNG rng;
   cv::Mat m(4, 4, CV_32F);
   rng.fill(m, cv::RNG::UNIFORM, 0, 300);
   std::cout << "m:" << m << std::endl;
   std::cout << "count of non zero:" << cv::countNonZero(m) << std::endl;
}

void dct_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("dctimg", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("inv-dctimg", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("diff-dctimg", cv::WINDOW_AUTOSIZE);

    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::imshow("img", gray);
    cv::Mat src;
    gray.convertTo(src, CV_32FC1, 1.0F/255.0F);


    cv::Mat dctImg;
    cv::dct(src, dctImg);

    cv::Mat invDctImag;
    cv::dct(dctImg, invDctImag, cv::DCT_INVERSE);

    cv::Mat diff = src - invDctImag;
    cv::Mat diffScale;
    cv::convertScaleAbs(diff, diffScale, 100);


    cv::imshow("dctimg", dctImg);
    cv::imshow("inv-dctimg", invDctImag);
    cv::imshow("diff-dctimg", diffScale);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void dft_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("dftimg", cv::WINDOW_AUTOSIZE);

    cv::Mat img = cv::imread(RESOURCE_DIR"/5/campus.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::Mat grayImg;
    cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

    cv::Mat paddedImg;                 //以0填充输入图像矩阵
    int m = cv::getOptimalDFTSize(grayImg.rows);
    int n = cv::getOptimalDFTSize(grayImg.cols);

    //填充输入图像grayImage，输入矩阵为padded，上方和左方不做填充处理
    //cv::copyMakeBorder(grayImg, paddedImg, 0, m - grayImg.rows, 0, n - grayImg.rows, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::copyMakeBorder(grayImg, paddedImg, 0, 0, 0, 0, cv::BORDER_CONSTANT, cv::Scalar::all(0));

    cv::Mat planes[] = {cv::Mat_<float>(paddedImg), cv::Mat::zeros(paddedImg.size(), CV_32F)};
    cv::Mat complexImg;
    cv::merge(planes, 2, complexImg);

    cv::dft(complexImg, complexImg);


    for(int i = 0; i < complexImg.cols; i++)
    {
        complexImg.at<cv::Vec2f>(0, i) = 0;
        complexImg.at<cv::Vec2f>(complexImg.rows, i) = 0;
    }


    cv::split(complexImg, planes);
    magnitude(planes[0], planes[1], planes[0]); // 即planes[0]为实部,planes[1]为虚部 planes[0] = magnitude

    cv::Mat magImg = planes[0];

    magImg += cv::Scalar::all(1);
    cv::log(magImg, magImg);

    //如果有奇数行或列，则对频谱进行裁剪
    magImg = magImg(cv::Rect(0, 0, magImg.cols&-2, magImg.rows&-2));

    // 归一化
    cv::normalize(magImg, magImg, 0, 1, CV_MINMAX);

    //重新排列傅里叶图像中的象限，使得原点位于图像中心
    int cx = magImg.cols / 2;
    int cy = magImg.rows / 2;

    cv::Mat q0(magImg, cv::Rect(0, 0, cx, cy));       //左上角图像划定ROI区域
    cv::Mat q1(magImg, cv::Rect(cx, 0, cx, cy));      //右上角图像
    cv::Mat q2(magImg, cv::Rect(0, cy, cx, cy));      //左下角图像
    cv::Mat q3(magImg, cv::Rect(cx, cy, cx, cy));     //右下角图像

#if 1
    //变换左上角和右下角象限
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
#endif

    cv::imshow("img", grayImg);
    cv::imshow("dftimg", magImg);

    // 反傅里叶变换
    cv::Mat invDftImg;
    //cv::dft(complexImg, invDftImg, cv::DFT_INVERSE|cv::DFT_REAL_OUTPUT);
    cv::idft(complexImg, invDftImg, cv::DFT_REAL_OUTPUT);
    cv::normalize(invDftImg, invDftImg, 0, 1, CV_MINMAX);

    cv::namedWindow("inv-img", CV_WINDOW_AUTOSIZE);
    cv::imshow("inv-img", invDftImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

// 计算行列式
void determinant_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m(10, 10, CV_32F);
    rng.fill(m, cv::RNG::NORMAL, 1, 255);
    std::cout << "m:" << m << std::endl;
    std::cout << "determinant of m :" << cv::determinant(m) << std::endl;
}

void divide_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m1(3, 3, CV_32F);
    cv::Mat m2(3, 3, CV_32F);
    rng.fill(m1, cv::RNG::NORMAL, 0, 255);
    rng.fill(m2, cv::RNG::NORMAL, 0, 255);

    //std::cout << "m1:" << m1 << std::endl;
    //std::cout << "m2:" << m2 << std::endl;
    cv::Mat ret;
    cv::divide(m1, m1, ret, 1.0);
    std::cout << "ret :" << ret << std::endl;
}

// 计算特征值和特征向量
void eigen_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m1(5, 5, CV_32F);
    rng.fill(m1, cv::RNG::NORMAL, 0, 255);

    // 对称矩阵
    cv::completeSymm(m1);

    cv::Mat eigenValues;
    cv::Mat eigenVectors;
    cv::eigen(m1, eigenValues, eigenVectors);
    std::cout << "eigenValues: " << eigenValues << std::endl;
    std::cout << "eigenVectors: " << eigenVectors << std::endl;
}

void exp_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m(3, 3, CV_32F);
    rng.fill(m, cv::RNG::NORMAL, 0, 255);

    cv::Mat ret;
    cv::exp(m, ret);

    std::cout << "m:" << m << std::endl;
    std::cout << "ret:　" << ret << std::endl;
}

// 翻转
void flip_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/campus.jpg");
    cv::namedWindow("origin", CV_WINDOW_AUTOSIZE);
    cv::imshow("origin", img);

    // x-aix flip
    cv::Mat xFlipImg;
    cv::flip(img, xFlipImg, 0);
    cv::namedWindow("x-aix", CV_WINDOW_AUTOSIZE);
    cv::imshow("x-aix", xFlipImg);

    // y-aix flip
    cv::Mat yFlipImg;
    cv::flip(img, yFlipImg, 1);
    cv::namedWindow("y-aix", CV_WINDOW_AUTOSIZE);
    cv::imshow("y-aix", yFlipImg);

    // xy-aix flip
    cv::Mat xyFlipImg;
    cv::flip(img, xyFlipImg, -1);
    cv::namedWindow("xy-aix", CV_WINDOW_AUTOSIZE);
    cv::imshow("xy-aix", xyFlipImg);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

// D = α * op(src1)* op(src2) + β * op(src3)  广义矩阵乘法
void gemm_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;

    cv::Mat m1(3, 3, CV_32F);
    rng.fill(m1, cv::RNG::NORMAL, 0, 255);

    cv::Mat m2(3, 3, CV_32F);
    rng.fill(m2, cv::RNG::NORMAL, 0, 255);

    cv::Mat m3(3, 3, CV_32F);
    rng.fill(m3, cv::RNG::NORMAL, 0, 255);

    cv::Mat ret;

    cv::gemm(m1, m2, 1.0, m3, 2.0, ret, cv::GEMM_1_T|cv::GEMM_3_T);

    std::cout << "ret:" << ret << std::endl;
}

void inRange_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;

    cv::Mat m1(3, 3, CV_8UC3);
    rng.fill(m1, cv::RNG::NORMAL, 0, 255);

    std::cout << "m1:"<< std::endl << m1 << std::endl;

    cv::Mat lowwer(3, 3, CV_8UC3);
    rng.fill(lowwer, cv::RNG::NORMAL, cv::Scalar(0,0,0), cv::Scalar(1,1,1));

    cv::Mat upper(3, 3, CV_8UC3);
    rng.fill(upper, cv::RNG::NORMAL, cv::Scalar(256, 256, 256), cv::Scalar(300, 300, 300));

    cv::Mat ret;

    cv::inRange(m1, lowwer, upper, ret);
    std::cout << "ret: " << std::endl << ret << std::endl;
}

// 求逆矩阵
void invert_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;

    cv::Mat m1(3, 3, CV_32FC1);
    rng.fill(m1, cv::RNG::NORMAL, 0, 255);

    cv::Mat ret;
    double success = cv::invert(m1, ret);

    std::cout << "success:" << success << std::endl;
    std::cout << "ret:" << ret << std::endl;
}


void log_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/campus.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat src;
    img.convertTo(src, CV_32F, 1.0F/255.0F, 0);
    cv::namedWindow("src", CV_WINDOW_AUTOSIZE);
    cv::imshow("src", src);

    cv::Mat ret;
    src += cv::Scalar::all(1);
    cv::log(src, ret);
    cv::namedWindow("log", CV_WINDOW_AUTOSIZE);
    cv::imshow("log", ret);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

// lookup table transform
void LUT_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat index(512, 512, CV_8UC3);
    rng.fill(index, cv::RNG::UNIFORM, 0, 255);

    cv::Mat table(1, 256, CV_8UC1);
    for(int i = 0; i < table.cols; i++)
    {
        table.at<u_char>(0, i) = i;
    }

    cv::Mat img;
    cv::LUT(index, table, img);
    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

//dsti =sqrt(xi2 + yi2)
void magnitude_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m1(1, 1, CV_32FC3, cv::Scalar(1.0,1.0,1.0));
    cv::Mat ret;
    cv::magnitude(m1, m1, ret);

    std::cout << "ret:" << ret << std::endl;
}

void max_min_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m1(1, 3, CV_8UC3);
    cv::Mat m2(1, 3, CV_8UC3);
    rng.fill(m1, cv::RNG::UNIFORM, 1, 255);
    rng.fill(m2, cv::RNG::UNIFORM, 1, 255);

    std::cout << "m1:" << m1 << std::endl;
    std::cout << "m2:" << m2 <<std::endl;

    std::cout << "max1:" << cv::max(m1, m2) << std::endl;
    std::cout << "min1:" << cv::min(m1, m2) << std::endl;
    std::cout << "max2:" << cv::max(m1, 200) << std::endl;
    std::cout << "min2:" << cv::max(m1, 200) << std::endl;
    cv::max(m1, m1, m2);
    std::cout << "max3:" << m2 << std::endl;
    cv::min(m1, m1, m2);
    std::cout << "min3:" << m2 << std::endl;
}


void mean_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat m1(3, 3, CV_8UC3);
    cv::Mat m2(1, 3, CV_8U);
    rng.fill(m1, cv::RNG::UNIFORM, 1, 255);
    rng.fill(m2, cv::RNG::UNIFORM, 1, 255);

    std::cout << "m1:" << m1 << std::endl;
    std::cout << "mean of m1 :" << cv::mean(m1) << std::endl;

    std::cout << "m2:" << m2 << std::endl;
    std::cout << "mean of m2 :" << cv::mean(m2, (m2 < 150))<< std::endl;
}

void meanStdDev_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/campus.jpg");

    cv::Mat mean;
    cv::Mat meanStdDev;

    cv::meanStdDev(img, mean, meanStdDev);

    std::cout << "mean:" << mean << std::endl;
    std::cout << "meanStdDev:" << meanStdDev << std::endl;

}

void split_merge_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat channels[3] = {cv::Mat(), cv::Mat(), cv::Mat()};
    cv::split(img, channels);

    cv::namedWindow("B", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("G", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("R", CV_WINDOW_AUTOSIZE);
    cv::imshow("B", channels[0]);
    cv::imshow("G", channels[1]);
    cv::imshow("R", channels[2]);

    cv::Mat dst;
    cv::merge(channels, 3, dst);

    cv::namedWindow("merge", CV_WINDOW_AUTOSIZE);
    cv::imshow("merge", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();

}

void minMaxIdx_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat channels[3] = {cv::Mat(), cv::Mat(), cv::Mat()};
    cv::split(img, channels);

    double minValue;
    double maxValue;
    int minLoc;
    int maxLoc;

    cv::minMaxIdx(channels[0], &minValue, &maxValue, &minLoc, &maxLoc);
    std::cout << "minValue: " << minValue << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "minLoc: " << minLoc << std::endl;
    std::cout << "maxLoc: " << maxLoc << std::endl;
}

void minMaxLoc_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat channels[3] = {cv::Mat(), cv::Mat(), cv::Mat()};
    cv::split(img, channels);

    double minValue;
    double maxValue;
    cv::Point minLoc;
    cv::Point maxLoc;

    cv::minMaxLoc(channels[0], &minValue, &maxValue, &minLoc, &maxLoc);
    std::cout << "minValue: " << minValue << std::endl;
    std::cout << "maxValue: " << maxValue << std::endl;
    std::cout << "minLoc: " << minLoc << std::endl;
    std::cout << "maxLoc: " << maxLoc << std::endl;
}


void mixChannels_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    const cv::Mat srcv[1] = {img};
    size_t nsrc = 1;
    cv::Mat dstv[2] = {cv::Mat(img.size(), img.type()), cv::Mat(img.rows, img.cols, CV_8UC1)};
    size_t ndst = 2;
    const int fromTo[] = {0, 2, 1, 1, 2, 0, 0, 3};
    size_t nPairs = 4;

    std::cout << "size:" << img.size() << std::endl;
    std::cout << "type:" << img.type() << std::endl;

    cv::mixChannels(srcv, nsrc, dstv, ndst, fromTo, nPairs);

    cv::namedWindow("inv", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("R", CV_WINDOW_AUTOSIZE);
    cv::imshow("inv", dstv[0]);
    cv::imshow("R", dstv[1]);

    cv::waitKey(0);
    cv::destroyAllWindows();
}


// dsti = saturate(scale*src1i*src2i)
void multiply_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat src1(1,2, CV_8SC1, cv::Scalar(30));
    std::cout << "src1:" << src1 << std::endl;
    cv::Mat src2(1,2, CV_8SC3, cv::Scalar(10, 20 ,30));
    std::cout << "src2:" << src2 << std::endl;

    cv::Mat ret;
    cv::multiply(src1, src1, ret);
    std::cout << "src1 X src1:" << ret << std::endl;

    cv::multiply(src2, src2, ret);
    std::cout << "src2 X src2:" << ret << std::endl;

}


void mulTransposed_example()
{
    std::cout << std::endl
              << __func__ << ":" << std::endl;
    cv::Mat m(3, 3, CV_8UC1);
    cv::RNG rng;
    rng.fill(m, cv::RNG::UNIFORM, 1, 255);

    std::cout << "m:" << m << std::endl;
    cv::Mat ret;
    cv::mulTransposed(m, ret, true);
    std::cout <<"aTa:" << ret << std::endl;
    cv::mulTransposed(m, ret, false);
    std::cout <<"aTa:" << ret << std::endl;
}

// 计算范数
void norm_example()
{
    std::cout << std::endl
              << __func__ << ":" << std::endl;

    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");

    std::cout << "norm of L1:" << cv::norm(img, cv::NORM_L1) << std::endl;
    std::cout << "norm of L2:" << cv::norm(img, cv::NORM_L2) << std::endl;
    std::cout << "norm of inf:" << cv::norm(img, cv::NORM_INF) << std::endl;

    std::cout << "norm of L1:" << cv::norm(img, img, cv::NORM_L1) << std::endl;
    std::cout << "norm of L2:" << cv::norm(img, img, cv::NORM_L2) << std::endl;
    std::cout << "norm of inf:" << cv::norm(img, img, cv::NORM_INF) << std::endl;
}


void normalize_example()
{
    std::cout << std::endl
              << __func__ << ":" << std::endl;
    cv::RNG rng;
    cv::Mat m(1, 5, CV_8UC2);
    rng.fill(m, cv::RNG::UNIFORM, 1, 255);
    std::cout << "m:" << m << std::endl;
    cv::Mat ret;

    cv::normalize(m, ret, 128, 0, cv::NORM_INF);
    std::cout << "result of NORM_INF:" << ret << std::endl;

    cv::normalize(m, ret, 128, 0, cv::NORM_L1);
    std::cout << "result of NORM_L1:" << ret << std::endl;

    cv::normalize(m, ret, 128, 0, cv::NORM_L2);
    std::cout << "result of NORM_L2:" << ret << std::endl;

    cv::normalize(m, ret, -128, 128, cv::NORM_MINMAX, CV_8SC1);
    std::cout << "result of NORM_MINMAX:" << ret << std::endl;
}

void perspectiveTransform_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    int img_height = img.rows;
    int img_width = img.cols;

    std::vector<cv::Point2f> corners(4);
	corners[0] = cv::Point2f(0,0);
	corners[1] = cv::Point2f(img_width-1,0);
	corners[2] = cv::Point2f(0,img_height-1);
	corners[3] = cv::Point2f(img_width-1,img_height-1);

    std::vector<cv::Point2f> corners_trans(4);
	corners_trans[0] = cv::Point2f(20,120);
	corners_trans[1] = cv::Point2f(200,50);
	corners_trans[2] = cv::Point2f(0,img_height-1);
	corners_trans[3] = cv::Point2f(img_width-50,img_height-1);

    cv::Mat transform = cv::getPerspectiveTransform(corners,corners_trans);
    std::cout<< "transform:" << transform <<std::endl;

    std::vector<cv::Point2f> ponits, points_trans;
	for(int i=0; i<img_height; i++)
    {
		for(int j=0; j<img_width; j++)
        {
			ponits.push_back(cv::Point2f(j,i));
		}
	}

    cv::perspectiveTransform( ponits, points_trans, transform);
    cv::Mat img_trans = cv::Mat::zeros(img_height,img_width,CV_8UC3);
    int count = 0;

    for(int i=0; i<img_height; i++)
    {
		uchar* p = img.ptr<uchar>(i);
		for(int j=0;j<img_width;j++){
			int y = points_trans[count].y;
			int x = points_trans[count].x;
			uchar* t = img_trans.ptr<uchar>(y);
			t[x*3]  = p[j*3];
			t[x*3+1]  = p[j*3+1];
			t[x*3+2]  = p[j*3+2];
			count++;
		}
	}

    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("prj", CV_WINDOW_AUTOSIZE);
    cv::imshow("img", img);
    cv::imshow("prj", img_trans);

    cv::waitKey(0);
    cv::destroyAllWindows();

}

//  计算相位 dsti = atan2(yi, xi)
void phase_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat x(1, 10, CV_32FC1);
    cv::Mat y(1, 10, CV_32FC1);

    rng.fill(x, cv::RNG::UNIFORM, 1, 255);
    rng.fill(y, cv::RNG::UNIFORM, 1, 255);

    cv::Mat ret;
    cv::phase(x, y, ret);

    std::cout << "ret: " << ret << std::endl;
}

void pow_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::RNG rng;
    cv::Mat src(1, 10, CV_32FC1);
    rng.fill(src, cv::RNG::UNIFORM, 1, 255);


    cv::Mat ret;
    cv::pow(src, 2, ret);

    std::cout << "ret: " << ret << std::endl;
}

void randu_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(3, 3, CV_8SC2);

    cv::randu(m, cv::Scalar(1, -10), cv::Scalar(10, -1));

    std::cout << "randu: " << m << std::endl;
}

void randn_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(3, 3, CV_8SC2);
    cv::randn(m, cv::Scalar(1, -10), cv::Scalar(10, 1));

    std::cout << "randn: " << m << std::endl;
}

void randShuffle_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(1, 10, CV_8SC1);

    cv::randu(m, 1, 10);
    std::cout << "m:" << m << std::endl;

    cv::randShuffle(m);
    std::cout << "result of randShuffle:" << m << std::endl;

}

void reduce_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(3, 3, CV_8UC2);

    for(cv::MatIterator_<cv::Vec2b> it = m.begin<cv::Vec2b>(); it != m.end<cv::Vec2b>(); ++it)
    {
        *it = cv::Vec2b(it.pos().y, it.pos().x);
    }

    std::cout << "m:" << m << std::endl;

    cv::Mat ret;
    cv::reduce(m, ret, 0, cv::REDUCE_SUM, CV_32FC2);
    std::cout << "sum:" << ret <<std::endl;

    cv::reduce(m, ret, 0, cv::REDUCE_AVG, CV_32FC2);
    std::cout << "avg:" << ret <<std::endl;

    cv::reduce(m, ret, 0, cv::REDUCE_MAX);
    std::cout << "max:" << ret <<std::endl;

    cv::reduce(m, ret, 0, cv::REDUCE_MIN);
    std::cout << "min:" << ret <<std::endl;
}

void repeat_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(2, 2, CV_8UC1);

    for(cv::MatIterator_<char> it = m.begin<char>(); it != m.end<char>(); ++it)
    {
        *it = it.pos().y+it.pos().x;
    }

    std::cout << "m:" << m << std::endl;
    std::cout << "ret:" << cv::repeat(m, 2, 3) << std::endl;
}

// dsti = scale * src1i + src2i

void scaleAdd_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat src1(2, 2, CV_8UC1);
    cv::randu(src1, 1, 10);
    std::cout << "src1:" << src1 << std::endl;

    cv::Mat src2(2, 2, CV_8UC1);
    cv::randu(src2, 1, 10);
    std::cout << "src2:" << src2 << std::endl;

    cv::Mat ret;
    cv::scaleAdd(src1, 0.1, src2, ret);

    std::cout << "ret:" << ret << std::endl;
}

void setIdentity_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat src(5, 6, CV_8UC1);
    cv::randu(src, 1, 100);

    std::cout << "src:" << src << std::endl;

    cv::setIdentity(src, 10);

    std::cout << "ret:" << src << std::endl;
}

void solve_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat A = (cv::Mat_<float>(2, 2) << 1, 1, 1, -11);
    cv::Mat C = (cv::Mat_<float>(2, 1) << 1, 5);

    cv::Mat B;

    cv::solve(A, C, B);

    std::cout << "B:" << B << std::endl;

}

void solveCubic_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat coeffs = (cv::Mat_<float>(1, 4) << 1, 1, 1, 1);

    cv::Mat roots;
    cv::solveCubic(coeffs, roots);

    std::cout << "roots:" << roots << std::endl;
}

void solvePoly_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat coeffs = (cv::Mat_<float>(1, 4) << 1, 1, 1, 1);

    cv::Mat roots;
    cv::solvePoly(coeffs, roots);

    std::cout << "roots:" << roots << std::endl;
}

void sort_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat m(3, 3, CV_8U);
    cv::randu(m, 1, 10);
    std::cout << "m:" << m << std::endl;

    cv::Mat dst;
    cv::sort(m, dst, cv::SORT_ASCENDING);
    std::cout << "dst:" << dst << std::endl;

    cv::sort(m, dst, cv::SORT_ASCENDING|cv::SORT_EVERY_ROW);
    std::cout << "dst:" << dst << std::endl;

    cv::sort(m, dst, cv::SORT_ASCENDING|cv::SORT_EVERY_COLUMN);
    std::cout << "dst:" << dst << std::endl;

}

void sortIdx_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m = (cv::Mat_<float>(3, 3) << 0.0, 0.1, 0.2, 1.0, 1.1, 1.2, 2.0 , 2.1, 2.2);

    std::cout << "m" << m << std::endl;

    cv::Mat dst;

    // 排序后元素应该在的位置
    cv::sortIdx(m, dst, cv::SORT_DESCENDING|cv::SORT_EVERY_ROW);
    std::cout << "dst:" << dst << std::endl;

    cv::sortIdx(m, dst, cv::SORT_ASCENDING|cv::SORT_EVERY_COLUMN);
    std::cout << "dst:" << dst << std::endl;
}

void sqrt_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m = (cv::Mat_<float>(1, 4) << 1, 2, 3, 4);

    cv::Mat dst;
    cv::sqrt(m, dst);

    std::cout << "root:" << dst <<std::endl;
}

void split_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");

    std::vector<cv::Mat> mv;
    std::vector<cv::Mat> dst(3);

    cv::split(img, mv);
    for(int channel = 0; channel < img.channels(); channel++)
    {
         cv::sort(mv[channel], dst[channel], cv::SORT_ASCENDING|cv::SORT_EVERY_COLUMN);
    }

    cv::Mat dst_img;
    cv::merge(dst, dst_img);

    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("sort-img", CV_WINDOW_AUTOSIZE);

    cv::imshow("img", img);
    cv::imshow("sort-img", dst_img);

    cv::waitKey(0);
    cv::destroyAllWindows();



}

// dsti = saturate(src1i − src2i)

void subtract_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;

    cv::Mat m1(3, 3, CV_8UC3);
    cv::randu(m1, cv::Scalar(1, 1, 1), cv::Scalar(10,10,10));

    cv::Mat m2(3, 3, CV_8UC3);
    cv::randu(m2, cv::Scalar(1, 1, 1), cv::Scalar(10,10,10));

    cv::Mat ret;
    cv::subtract(m1, m2, ret);

    std::cout << "ret:" << ret << std::endl;


}

void sum_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");

    std::cout << "sum:" << cv::sum(img) << std::endl;
}

void trace_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m(3, 3, CV_8SC2);

    cv::randu(m, 1, 10);
    std::cout << "m:" << m << std::endl;

    std::cout << "trace:" << cv::trace(m) << std::endl;
}

void transform_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat img = cv::imread(RESOURCE_DIR"/5/flower.jpg");
    //cv::Mat img(3, 3, CV_8UC3, cv::Scalar(100,100,100));
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    img.convertTo(img, CV_32FC3);
    cv::normalize(img, img, 0, 1, cv::NORM_MINMAX);

    cv::Mat mtx = (cv::Mat_<float>(1, 3) << 1.0 ,1.0 , 1.0);
    cv::Mat dst(img.size(), CV_32FC3);

    cv::transform(img, dst , mtx);

    cv::normalize(dst, dst, 0, 1, cv::NORM_MINMAX);


    cv::namedWindow("img", CV_WINDOW_AUTOSIZE);
    cv::namedWindow("add3c", CV_WINDOW_AUTOSIZE);

    cv::imshow("img", img);
    cv::imshow("add3c", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();


}

void transpose_example()
{
    std::cout << std::endl << __func__ << ":" <<std::endl;
    cv::Mat m = (cv::Mat_<int>(3, 3) << 10 ,11, 12, 20, 21, 22, 30, 31, 32);
    std::cout << "m:" << m << std::endl;

    cv::Mat dst;
    cv::transpose(m, dst);
    std::cout << "transpose:" << dst << std::endl;

}

int main(int argc, char const *argv[])
{
#if 0
    abs_example();
    add_example();
    addWeighted_example();
    calcCovarMatrix_example();
    calcCovarMatrix_example();
    checkRange_example();
    commpleteSymm_example();
    convertScaleAbs_example();
    countNonZero_example();
    dct_example();
    dft_example();
    determinant_example();
    divide_example();
    eigen_example();
    exp_example();
    flip_example();
    gemm_example();
    inRange_example();
    invert_example();
    log_example();
    LUT_example();
    magnitude_example();
    max_min_example();
    mean_example();
    meanStdDev_example();
    split_merge_example();
    minMaxIdx_example();
    minMaxLoc_example();
    mixChannels_example();
    multiply_example();
    mulTransposed_example();
    norm_example();
    normalize_example();
    perspectiveTransform_example();
    phase_example();
    pow_example();
    randu_example();
    randn_example();
    randShuffle_example();
    reduce_example();
    repeat_example();
    scaleAdd_example();
    setIdentity_example();
    solve_example();
    solveCubic_example();
    solvePoly_example();
    sort_example();
    sortIdx_example();
    sqrt_example();
    split_example();
    subtract_example();
    sum_example();
    trace_example();
    transform_example();
#endif
    mean_example();
//    transpose_example();
    return 0;
}
