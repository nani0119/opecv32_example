#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void affine_transformation_example()
{
    cv::Mat img = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(img.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Point2f srcTri[] = {
        cv::Point2f(0,0), // src Top left
        cv::Point2f(img.cols-1, 0), // src Top right
        cv::Point2f(0, img.rows-1) // src Bottom left
    };

    cv::Point2f dstTri[] ={
        cv::Point2f(img.cols*0.f, img.rows*0.33f), // dst Top left
        cv::Point2f(img.cols*0.85f, img.rows*0.25f), // dst Top right
        cv::Point2f(img.cols*0.15f, img.rows*0.7f) // dst Bottom left
    };

    cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
    std::cout << "affine warp mat:" << warp_mat << std::endl;

    cv::Mat dst;
    cv::warpAffine(img, dst, warp_mat, img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    cv::Mat dst2;
    cv::warpAffine(dst, dst2, warp_mat, img.size(), cv::WARP_INVERSE_MAP|cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());


    cv::Mat iM;
    cv::invertAffineTransform(warp_mat, iM);
    std::cout << "invert affine transform mtx:" << iM << std::endl;
    cv::Mat dst3;
    cv::warpAffine(dst, dst3, iM, img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

    for(int i = 0; i < 3; i++)
    {
        cv::circle(dst,dstTri[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
    }


    cv::imshow("origin", img);
    cv::imshow("affline", dst);
    cv::imshow("inv-affline1", dst2);
    cv::imshow("inv-affline2", dst3);

    cv::waitKey(0);

    for(int frame = 0; ;++frame)
    {
        //compute rotation matrix
        cv::Point2f center(img.cols*0.5f, img.rows*0.5f);
        double angle = frame*3 % 360;
        double scale = (cos((angle - 60)* CV_PI/180) + 1.05)*0.8;
        cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, scale);
        cv::warpAffine(img, dst, rot_mat, img.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
        cv::imshow("Rotated Image", dst);
        int key = cv::waitKey(33);
        if(key >= 0 && key != 255)
        {
            break;
        }
    }
    cv::destroyAllWindows();
}

void transform_example()
{
    cv::Mat src = (cv::Mat_<cv::Vec2b>(2,1)<< cv::Vec2b(1, 1), cv::Vec2b(2, 2));
    cv::Mat dst;
    cv::Mat mtx = (cv::Mat_<char>(1, 2) << 1, 1);
    std::cout << "src:" << src << std::endl;
    std::cout << "mtx:" << mtx << std::endl;

    cv::transform(src, dst, mtx);
    std::cout << "dst:" << dst << std::endl;
}

void perspective_transformation_example()
{
    cv::Mat src = cv::imread(RESOURCE_DIR"/11/desert.jpg");
    if(src.empty())
    {
        std::cout << "img is empty" << std::endl;
        return;
    }

    cv::Point2f srcQuad[] = {
        cv::Point2f(0, 0), // src Top left
        cv::Point2f(src.cols - 1, 0), // src Top right
        cv::Point2f(src.cols - 1, src.rows - 1), // src Bottom right
        cv::Point2f(0, src.rows - 1)  // src Bottom left
    };

    cv::Point2f dstQuad[] = {
        cv::Point2f(src.cols * 0.05f, src.rows * 0.33f),
        cv::Point2f(src.cols * 0.9f, src.rows * 0.25f),
        cv::Point2f(src.cols * 0.8f, src.rows * 0.9f),
        cv::Point2f(src.cols * 0.2f, src.rows * 0.7f)
    };
    // COMPUTE PERSPECTIVE MATRIX
    cv::Mat warp_mat = cv::getPerspectiveTransform(srcQuad, dstQuad);

    cv::Mat dst;
    cv::warpPerspective(src, dst, warp_mat, src.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255,255,255));

    for(int i = 0; i < 4; i++)
    {
        cv::circle(dst, dstQuad[i], 5, cv::Scalar(255, 0, 255), -1, cv::LINE_AA);
    }

    cv::imshow("origin", src);
    cv::imshow("Perspective Transform ", dst);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    //affine_transformation_example();
    transform_example();
    perspective_transformation_example();
    return 0;
}
