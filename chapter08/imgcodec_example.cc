#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"

void imgCodec_example()
{
    std::cout << std::endl << __func__ << std::endl;

    cv::Mat src = cv::imread(RESOURCE_DIR"/8/lotus.bmp");

    std::vector<uchar> dataEncod;
    cv::imencode(".bmp", src, dataEncod);

    // 存储到本地
    std::string strEncode(dataEncod.begin(), dataEncod.end());
    std::ofstream ofs("imgencode_cplus.txt");
    ofs << strEncode;
    ofs.flush();
    ofs.close();

    // 从本地读出数据
    std::ifstream ifs("imgencode_cplus.txt");
    std::stringstream sstr;
    while(ifs >> sstr.rdbuf());
    ifs.close();
    std::string strTmp = sstr.str();
    std::vector<uchar> data(strTmp.begin(), strTmp.end());


    cv::Mat dataDecode =  cv::imdecode(data, cv::IMREAD_COLOR);

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::imshow("img", dataDecode);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main(int argc, char const *argv[])
{
    imgCodec_example();
    return 0;
}
