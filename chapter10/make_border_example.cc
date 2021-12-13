#include <opencv2/opencv.hpp>
#define IMG_WIDTH   400
#define IMG_HEIGHT  400
void myTrackbarCallback(int pos, void* param)
{
	if(param == nullptr)
	{
		std::cout << "param is nullptr"<< std::endl;
		return;
	}

	cv::Mat& img = *((cv::Mat*)param);
	cv::Mat dst;
	int boardtype = 0;
	if(pos == 0)
	{
		boardtype = cv::BORDER_CONSTANT;
		std::cout << "BorderType: BORDER_CONSTANT" << std::endl;
	}
	else if(pos == 1)
	{
    	boardtype = cv::BORDER_REPLICATE;
		std::cout << "BorderType: BORDER_REPLICATE" << std::endl;
    }
    else if(pos == 2)
	{
		boardtype = cv::BORDER_REFLECT;
		std::cout << "BorderType: BORDER_REFLECT" << std::endl;
	}
	else if(pos == 3)
	{
		boardtype = cv::BORDER_WRAP;
		std::cout << "BorderType: BORDER_WRAP" << std::endl;
	}
	else if(pos == 4)
	{
		boardtype = cv::BORDER_REFLECT_101;
		std::cout << "BorderType: BORDER_REFLECT_101" << std::endl;
	}

	cv::copyMakeBorder(img, dst, IMG_HEIGHT/2, IMG_HEIGHT/2, IMG_WIDTH/2, IMG_WIDTH/2, boardtype);
	cv::imshow("border", dst);
}

void fill_color(cv::Mat& img, cv::Scalar color)
{
    for(cv::MatIterator_<cv::Vec3b> it = img.begin<cv::Vec3b>(); it != img.end<cv::Vec3b()>(); ++it)
    {
        *it =  cv::Vec3b(color.val[0], color.val[1], color.val[2]);
    }
}


void copyMakeBorder_example()
{
    cv::Mat img(IMG_WIDTH, IMG_HEIGHT, CV_8UC3, cv::Scalar(0 , 0, 0));
    for(int r = 0; r < 2; r++)
    {
        for(int c = 0; c < 2; c++)
        {
            cv::Mat partImg = cv::Mat(img, cv::Rect(r*(IMG_WIDTH/2), c*(IMG_HEIGHT/2), IMG_WIDTH/2, IMG_HEIGHT/2));

            if(r == 0)
            {
                if(c == 0)
                	fill_color(partImg, cv::Scalar(255, 0, 0));
				else
				    fill_color(partImg, cv::Scalar(0, 255, 0));
            }
			else
			{
				if(c == 0)
					fill_color(partImg, cv::Scalar(0, 0, 255));
				else
					fill_color(partImg, cv::Scalar(255, 255, 255));
			}
        }
    }
	int boarderType = 0;;
    cv::namedWindow("border", cv::WINDOW_AUTOSIZE);
    //cv::imshow("border", img);
	cv::createTrackbar("borderType:", "border", &boarderType, 4, myTrackbarCallback, (void*)(&img));
	myTrackbarCallback(0, &img);
    while(cv::waitKey(30) !='q')
	{

	}
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    copyMakeBorder_example();
    return 0;
}
