#include <iostream>
#include <limits>
#include <opencv2/opencv.hpp>
#define RESOURCE_DIR "../resource/"

cv::Mat src_temp,inpaintMask;
cv::Point prePoint;  //上一个鼠标点
void on_mouse(int event, int x, int y, int flag, void* param)
{
    if(param == nullptr)
    {
        std::cout << "param is empty" << std::endl;
        return;
    }
    cv::Mat& img = *((cv::Mat*)param);
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        prePoint = cv::Point(x, y);
    }
    else if (event == cv::EVENT_MOUSEMOVE && (flag & cv::EVENT_FLAG_LBUTTON))//左键按下且鼠标移动
	{
		cv::Point pt(x, y);
		cv::line(inpaintMask, prePoint, pt, cv::Scalar::all(255), 3, 8, 0);//构造掩模，就是标记哪些地方需要修复
		cv::line(src_temp, prePoint, pt, cv::Scalar::all(255), 3, 8, 0);
		prePoint = pt;
		cv::imshow("origin", src_temp);
	}

    if (event == cv::EVENT_RBUTTONDOWN)
    {
        //按下右键，重置图片和掩模，重新开始画白线并修复图像白色区域
        src_temp = img.clone();
        imshow("origin", src_temp);
        inpaintMask = cv::Mat::zeros(img.size(), CV_8UC1);
    }
}

void inpaint_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert_d.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    src_temp = img.clone();
	imshow("origin", img);
    inpaintMask = cv::Mat::zeros(img.size(), CV_8UC1);
    cv::setMouseCallback("origin", on_mouse, (void*)&img);
    while(1)
    {
        int key = cv::waitKey(0);
        cv::Mat inpaintedImage;
        if(key == 'a')
        {
            std::cout << "algo:INPAINT_TELEA" << std::endl;
            cv::inpaint(src_temp, inpaintMask, inpaintedImage, 5, cv::INPAINT_TELEA);
        }
        else if(key == 'b')
        {
            std::cout << "algo:INPAINT_NS" << std::endl;
            cv::inpaint(src_temp, inpaintMask, inpaintedImage, 5, cv::INPAINT_NS);
        }
        else if(key == 'q')
        {
            std::cout << "exit" << std::endl;
            break;
        }
        imshow("inpaintImage", inpaintedImage);
    }
    cv::destroyAllWindows();
}

cv::Mat addSaltNoise(const cv::Mat& srcImage, int n)
{
    cv::Mat dstImage = srcImage.clone();

    for(int k = 0; k < n; k++)
    {
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        	if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//盐噪声
		}
		else
		{
			dstImage.at<cv::Vec3b>(i, j)[0] = 255;
			dstImage.at<cv::Vec3b>(i, j)[1] = 255;
			dstImage.at<cv::Vec3b>(i, j)[2] = 255;
		}
    }

    for (int k = 0; k < n; k++)
	{
		//随机取值行列
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//图像通道判定
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//椒噪声
		}
		else
		{
			dstImage.at<cv::Vec3b>(i, j)[0] = 0;
			dstImage.at<cv::Vec3b>(i, j)[1] = 0;
			dstImage.at<cv::Vec3b>(i, j)[2] = 0;
		}
	}
    return dstImage;
}

cv::Mat addGaussianNoise(const cv::Mat srcImage, double mean, double stddev)
{
    cv::Mat mu;
    cv::Mat sigma;
    cv::Mat noise = cv::Mat::zeros(srcImage.size(), srcImage.type());
    cv::Mat dstImage;

    if(dstImage.channels() == 1)
    {
        mu = (cv::Mat_<double>(1,1)<< mean);
        sigma = (cv::Mat_<double>(1,1)<< stddev);
    }
    else
    {
        mu = (cv::Mat_<double>(1,3)<< mean, mean,mean);
        sigma = (cv::Mat_<double>(1,3)<< stddev, stddev, stddev);


    }
    cv::randn(noise, mu, sigma);
    cv::add(srcImage, noise, dstImage);
    return dstImage;
}

void fastNlMeansDenoising_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Mat GNoiseImg = addGaussianNoise(img, 0, 20);
    cv::Mat SNoiseImg = addSaltNoise(img, 20);

    cv::Mat DeSNoiseImg;
    //cv::medianBlur(SNoiseImg, DeSNoiseImg, 5);
    cv::fastNlMeansDenoisingColored(SNoiseImg, DeSNoiseImg, 10, 10, 7, 21);

    cv::Mat DeGNoiseImg;
    //cv::medianBlur(GNoiseImg, DeGNoiseImg, 5);
    cv::fastNlMeansDenoisingColored(GNoiseImg, DeGNoiseImg, 10, 10, 7, 21);

    cv::imshow("img", img);
    cv::imshow("imgGNoiseImg", GNoiseImg);
    cv::imshow("SNoiseImg", SNoiseImg);
    cv::imshow("DeSNoiseImg", DeSNoiseImg);
    cv::imshow("DeGNoiseImg", DeGNoiseImg);
    cv::waitKey(0);

    cv::destroyAllWindows();
}

void noiseMean_example()
{
    int count = 5;
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }
    cv::Vec3i origin = img.at<cv::Vec3b>(img.rows/2, img.cols/2);
    cv::Vec3i sum = img.at<cv::Vec3b>(img.rows/2, img.cols/2);

    for(int i = 0; i < count; ++i)
    {
        cv::Mat noiseImg = addGaussianNoise(img, 0, 25);
        //cv::Mat noiseImg = addSaltNoise(img, 200);
        sum += noiseImg.at<cv::Vec3b>(noiseImg.rows/2, noiseImg.cols/2);
        sum = sum / 2;
        //std::cout << "sum:" << sum << std::endl;
    }

    std::cout << "origin:" << origin << std::endl;
    std::cout << "mean" <<  sum << std::endl;
}



int main(int argc, char const *argv[])
{
    //inpaint_example();
    //fastNlMeansDenoising_example();
    noiseMean_example();
    return 0;
}
