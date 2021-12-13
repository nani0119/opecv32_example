#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

#define RESOURCE_DIR "../resource/"

using namespace std;

// GLoabl storage

// Float, 3-ch images

cv::Mat IavgF;
cv::Mat IdiffF;
cv::Mat IprevF;
cv::Mat IhiF;
cv::Mat IlowF;
cv::Mat tmp;
cv::Mat tmp2;


// Float, 1-channel images
//
vector<cv::Mat> Igray(3);
vector<cv::Mat> Ilow(3);
vector<cv::Mat> Ihi(3);


// Float 1-ch image

cv::Mat Imaskt;

// Counts number of images learned for averaging later
float Icount;

// I is just a sample image for allocation purposes (passed in for sizing)

void allocateImages(const cv::Mat& I)
{
    cv::Size sz = I.size();
    IavgF = cv::Mat::zeros(sz, CV_32FC3);
    IdiffF = cv::Mat::zeros(sz, CV_32FC3);
    IprevF = cv::Mat::zeros(sz, CV_32FC3);
    IhiF = cv::Mat::zeros(sz, CV_32FC3);
    IlowF = cv::Mat::zeros(sz, CV_32FC3);
    Icount = 0.00001; // Protect against divide by zero
    tmp = cv::Mat::zeros(sz, CV_32FC3);
    tmp2 = cv::Mat::zeros(sz, CV_32FC3);
    Imaskt = cv::Mat(sz, CV_32FC1);
}

// Learn the background statistics for one more frame
// I is a color sample of the background, 3-channel, 8u

void accumulateBackground( cv::Mat& I )
{
    static int first = 1; // nb. Not thread safe
    I.convertTo( tmp, CV_32F ); // convert to float
    if (!first)
    {
        IavgF += tmp;
        cv::absdiff(tmp, IprevF, tmp2);
        IdiffF += tmp2;
        Icount += 1.0;
    }
    first = 0;
    IprevF = tmp;
}

void setHighThreshold( float scale )
{
    IhiF = IavgF + (IdiffF * scale);
    cv::split( IhiF, Ihi);
}

void setLowThreshold( float scale )
{
    IlowF = IavgF - (IdiffF * scale);
    cv::split( IlowF, Ilow );
}

void createModelsfromStats()
{
    IavgF *= (1.0/Icount);
    IdiffF *= (1.0/Icount);
    // Make sure diff is always something
    //
    IdiffF += cv::Scalar( 1.0, 1.0, 1.0 );

    setHighThreshold( 7.0 );
    setLowThreshold( 6.0 );
}



// Create a binary: 0,255 mask where 255 means foreground pixel
// I Input image, 3-channel, 8u
// Imask Mask image to be created, 1-channel 8u
//

void backgroundDiff(cv::Mat& I, cv::Mat& Imask)
{
    I.convertTo( tmp, CV_32F); // To float
    cv::split( tmp, Igray );

    // Channel 1
    //
    cv::inRange( Igray[0], Ilow[0], Ihi[0], Imask );

    // Channel 2
    //
    cv::inRange( Igray[1], Ilow[1], Ihi[1], Imaskt );
    Imask = cv::min( Imask, Imaskt );

    // Channel 3
    //
    cv::inRange( Igray[2], Ilow[2], Ihi[2], Imaskt );
    Imask = cv::min( Imask, Imaskt );

    // Finally, invert the results
    //
    Imask = 255-Imask;
}

int main(int argc, char const *argv[])
{
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE );
    cv::Mat image;
    cv::VideoCapture cap;
    if(!cap.open(RESOURCE_DIR"/15/background.mkv"))
    {
        cerr << "Couldn't open video file" << endl;
        return -1;
    }

    cap>>image;
    allocateImages(image);

    cap.set(cv::CAP_PROP_POS_MSEC, 0);
    // FIRST PROCESSING LOOP (TRAINING):
    while(1)
    {
        cap >> image;
        if( !image.data )
        {
            break;
        }

        accumulateBackground(image);
        cv::imshow("video", image );
        if(cv::waitKey(7) == 0x20)
        {
            break;
        }

    }

    // We have all of our data, so create the models
    createModelsfromStats();

    // SECOND PROCESSING LOOP (TESTING):
    cv::Mat mask;
    cap.set(cv::CAP_PROP_POS_MSEC, 0);
    while(1)
    {
        cap>>image;
        if( !image.data )
        {
           break;
        }
        backgroundDiff( image, mask );
        // A simple visualization is to write to the red channel
        //
        cv::split( image, Igray );
        Igray[2] = cv::max( mask, Igray[2] );
        cv::merge( Igray, image );
        cv::imshow("result", image );
        if( cv::waitKey(7) == 0x20 )
        {
            break;
        }
    }

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}
