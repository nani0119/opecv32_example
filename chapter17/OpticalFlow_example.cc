#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "opencv2/optflow.hpp"
#include "opencv2/highgui.hpp"

#define RESOURCE_DIR "../resource/"

using namespace std;
using namespace cv;
using namespace cv::optflow;//calcOpticalFlowSF 's namespace
const size_t choice = 4;

// choice
// 1    2    3
// calcOpticalFlowFarneback   calcOpticalFlowSF   calcOpticalFlowPyrLK
void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color) {
    // cflowmap is the pre frame with the line of Optical Flow
    // flow is a V-by-2 array, store float point
    //      store the delta of x,y
    // step is every step pixel
    for (int y = 0; y < cflowmap.rows; y += step)
        for (int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at< Point2f>(y, x);
            line(cflowmap, Point(x, y), Point(cvRound(x + fxy.x), cvRound(y + fxy.y)),
                color);
            circle(cflowmap, Point(cvRound(x + fxy.x), cvRound(y + fxy.y)), 1, color, -1);
        }
}

void drawOptFlowMap(Mat& cflowmap, int step, const Scalar& color, vector<Point2f> &retPts) {
    // same as above, retPts is the next frame point
    auto it = retPts.begin();
    for (int y = 0; y < cflowmap.rows; y += step)
        for (int x = 0; x < cflowmap.cols; x += step)
        {
            line(cflowmap, Point(x, y), *it, color);
            circle(cflowmap, *it, 1, color, -1);
            it++;
        }
}

int main(int argc, char *argv[])
{
    Mat flow;//flow = aft - pre
    Mat pre = imread(RESOURCE_DIR"/17/1hf.bak.jpg", IMREAD_COLOR);
    Mat aft = imread(RESOURCE_DIR"/17/2hf.bak.jpg", IMREAD_COLOR);//           CV_LOAD_IMAGE_GRAYSCALE   gray ; IMREAD_COLOR   color
    if (pre.empty() || aft.empty()){
        printf("Unable to load the image");
        return 1;
    }


    Mat cflow = pre; Mat cflow2 = aft;// store the  3-channel mat of frame, cflow is for show color with line
    cvtColor(pre, pre, CV_BGR2GRAY);
    cvtColor(aft, aft, CV_BGR2GRAY);

    //below parameter of calcOpticalFlowPyrLK
    vector<Point2f> prePts;
    size_t step = 10;
    vector<Point2f> nextPts(pre.rows * pre.cols);
    vector<uchar> status;
    vector<float> err;
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    cv::Ptr<cv::DenseOpticalFlow> dualTVL1 = createOptFlow_DualTVL1();

    switch (choice)
    {
    case 1:// calcOpticalFlowFarneback
        calcOpticalFlowFarneback(pre, aft, flow, 0.5, 3, 15, 3, 5, 1.2, cv::OPTFLOW_FARNEBACK_GAUSSIAN); // info in the flow; note that input mat should in 1-channel
        drawOptFlowMap(flow, cflow, 10, CV_RGB(0, 255, 0));
        break;
    case 2:// calcOpticalFlowSF
        calcOpticalFlowSF(cflow, cflow2,
            flow,
            3, 2, 4, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10);// info in the flow; note that input mat should in 3-channel
        drawOptFlowMap(flow, cflow, 10, CV_RGB(0, 255, 0));
        break;
    case 3:// calcOpticalFlowPyrLK
        for (int y = 0; y < pre.rows; y += step)
            for (int x = 0; x < pre.cols; x += step)
            {
                prePts.push_back(Point(x, y));
            }

        // above get a point vector in step
        calcOpticalFlowPyrLK(pre, aft, prePts, nextPts, status, err, Size(31, 31), 3, termcrit, 0, 0.001);// info in the flow; note that input mat should in 1-channel
        drawOptFlowMap(cflow, step, CV_RGB(0, 255, 0), nextPts);
        break;
    case 4:
        dualTVL1->calc(pre, aft, flow);
        drawOptFlowMap(flow, cflow, 10, CV_RGB(0, 255, 0));
        break;
    default:
        break;
    }

    imshow("pre", pre);
    imshow("after", aft);
    //cflow is the pre with OpticalFlow line
    imshow("pre with OpticalFlow line", cflow);
    waitKey(0);
    return 0;
}