#include <opencv2/opencv.hpp>


#define RESOURCE_DIR "../resource/"
#define SHIFT_METHOD meanShift
//#define SHIFT_METHOD CamShift
using namespace std;
//================================================================
bool pause = false;
bool is_tracking = false;
cv::Rect drawing_box;



int h_bins = 180;
int s_bins = 256;
int v_bins = 256;
float h_ranges[] = {0, 180};
float s_ranges[] = {0, 255};
float v_ranges[] = {0, 255};

cv::Mat roi_hist;
// int h_low_threshold = 26;
// int s_low_threshold = 43;
// int v_low_threshold = 46;
// int h_up_threshold = 34;
// int s_up_threshold = 255;
// int v_up_threshold = 255;
// channel h:0 s:1  v:2
int dims = 1;
int channel[] = {0};
int hist_size[] = {h_bins};
const float* ranges[] = {h_ranges};
//================================================================

void MeanShift_Tracking(cv::Mat& current)
{
    cv::Mat current_hsv;
    cv::Mat backproject;
    cv::cvtColor(current, current_hsv, cv::COLOR_BGR2HSV);
    cv::calcBackProject(&current_hsv, 1, channel, roi_hist, backproject, ranges);

    cv::imshow("backprojection", backproject);

    cv::TermCriteria term_crit = cv::TermCriteria(cv::TermCriteria::EPS|cv::TermCriteria::COUNT, 10, 1);
    cv::SHIFT_METHOD(backproject, drawing_box, term_crit);
}


cv::Point2d startPoint(0, 0);
cv::Point2d endPoint(0, 0);
void onMouse( int event, int x, int y, int flags, void *param )
{
    if(param == nullptr)
    {
        cout << "param is null";
        return;
    }
    cv::Mat& current = *((cv::Mat*)(param));
    cv::Point2d movingPoint(0, 0);
    if(event == cv::EVENT_MOUSEMOVE && flags&cv::EVENT_FLAG_LBUTTON)
    {
        cout << "mouse moving:" << x <<" " << y << endl;
        movingPoint.x = x;
        movingPoint.y = y;
        cv::Mat currentTmp = current.clone();
        cv::rectangle(currentTmp, startPoint, movingPoint, cv::Scalar(0, 0, 255));
        cv::imshow("MeanShift", currentTmp);
        cv::waitKey(1);
    }
    else if(event == cv::EVENT_LBUTTONDOWN)
    {
        cout << "mouse left button down:" << x <<" " << y << endl;
        startPoint.x = x;
        startPoint.y = y;
        cv::imshow("MeanShift", current);
        cv::waitKey(1);
    }
    else if(event == cv::EVENT_LBUTTONUP)
    {
        cout << "mouse left button up:" << x <<" " << y << endl;
        endPoint.x = x;
        endPoint.y = y;
        drawing_box.height = cv::abs(endPoint.y - startPoint.y);
        drawing_box.width = cv::abs(endPoint.x - startPoint.x);
        if(endPoint.x > startPoint.x && endPoint.y > startPoint.y)
        {
            drawing_box.x = startPoint.x;
            drawing_box.y = startPoint.y;
        }
        else
        {
            drawing_box.x=endPoint.x;
            drawing_box.y=endPoint.y;
        }
        cout << drawing_box<<endl;
        cv::Mat currentTmp = current.clone();
        cv::rectangle(currentTmp, drawing_box, cv::Scalar(0, 0, 255));
        cv::imshow("MeanShift", currentTmp);
        int key = cv::waitKey(0);
        if(key == 'p')
        {
            pause = false;
            is_tracking = true;


            cv::Mat ROI = current(drawing_box);
            cv::imshow("ROI", ROI);
            cv::Mat hsv_roi;
            cv::cvtColor(ROI, hsv_roi,cv::COLOR_BGR2HSV);
            //inRange函数设置亮度阈值 去除低亮度的像素点的影响 将低于和高于阈值的值设为0
            cv::Mat mask(hsv_roi.size(), CV_8UC1, cv::Scalar(255));
            //cv::inRange(hsv_roi, cv::Scalar(h_low_threshold, s_low_threshold, v_low_threshold), cv::Scalar(h_up_threshold, s_up_threshold, v_up_threshold), mask);
            cv::calcHist(&hsv_roi, 1, channel, mask, roi_hist, dims, hist_size, ranges);

            //归一化，像素值区间[0,255]
            cv::normalize(roi_hist,roi_hist,0,255,cv::NORM_MINMAX);
        }
    }

	return;
}

int main(int argc, char const *argv[])
{
    cv::Mat img;
    cv::VideoCapture capture(RESOURCE_DIR"/17/test.mkv");
    if(!capture.isOpened())
    {
        std::cout << "open video file fail"<< std::endl;
        return 1;
    }
    capture.read(img);
    cv::namedWindow("MeanShift", cv::WINDOW_AUTOSIZE);
    // 设置鼠标callback
    //

    while(!img.empty())
    {
        if(is_tracking == false)
        {
            cv::imshow("MeanShift", img);
            char key =(char)cv::waitKey(30);
            if(key == 'p')
            {
                cv::setMouseCallback("MeanShift", onMouse, (void*)&img);
                pause = true;
            }
            else if(key == 'q')
            {
                break;
            }
            while(pause)
            {
                if(cv::waitKey(30) == 'q')
                {
                    break;
                }
            }
        }
        else
        {
            MeanShift_Tracking(img);
            cv::rectangle(img, drawing_box, cv::Scalar(0, 0, 255));
            cv::imshow("MeanShift", img);
            cv::waitKey(30);
        }
        capture.read(img);
        //cv::waitKey(30);
    }
    capture.release();
    cv::destroyAllWindows();
    return 0;
}
