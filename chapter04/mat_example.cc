#include <iostream>
#include <opencv2/opencv.hpp>

// 使用at方法访问数组
void info()
{
    using namespace std;
    cv::Mat m;
    m.create(3, 3, CV_32SC3);
    cv::RNG rng;
    rng.fill(m, cv::RNG::UNIFORM, 0, 255);
    cout << "m =:" << endl << m << endl<<endl;
    cout << "type:" << m.type() << endl;
    cout << "depth:" << m.depth() << endl;
    cout << "channel:" << m.channels() << endl;
    cout << "total:" << m.total() << endl;
    cout << "size:" << m.size() << endl;
    cout << "elemSize:" << m.elemSize() << endl;    //Mat中单个像素点所占的字节数(与通道数有关)
    cout << "elemSize1:" << m.elemSize1() << endl;  //计算depth所占的字节数(与通道数无关)

}

void access()
{
    using namespace std;
    cv::Mat m = cv::Mat::eye(3, 3, CV_8UC3);
    cout << "m = " << m << endl << endl;

    // 使用at方法访问指定元素
    for(int row = 0; row < m.rows; row++)
    {
        for(int col = 0; col < m.cols; col++)
        {
            for(int channel = 0; channel < m.channels(); channel++)
            {
                if(m.at<cv::Vec3b>(row, col)[channel] != channel + 1)
                {
                    m.at<cv::Vec3b>(row, col)[channel] = channel + 1;
                }
            }
        }
    }

    cout << "m = " << m << endl << endl;

    // 使用迭代器

    for(cv::MatConstIterator it = m.begin<cv::Vec3b>(); it != m.end<cv::Vec3b>(); ++it)
    {
        for(int i = 0; i < it.elemSize; i++)
        {
            cout << "element ("<<it.pos().x << ","<< it.pos().y << "), channel " << i + 1 << " is " << static_cast<int>((*it)[i]) << endl;
        }
    }


    cout << endl << endl;
    // 使用ptr方法
    cv::RNG rng;
    rng.fill(m, cv::RNG::NORMAL, 1, 255);

    for(int row = 0; row < m.rows; row++)
    {
        cv::Vec3b* p = m.ptr<cv::Vec3b>(row);
        for(int col = 0; col < m.cols; col++)
        {
            //cout << p[col] << " ";
            cout << "[";
            for(int channel = 0; channel < m.channels(); channel++)
            {
                cout << static_cast<int>((*p)[channel]) << " ";
            }
            cout << "]";
        }

        cout << endl;
    }
    cout << endl;
}

void accessByAccess()
{
    using namespace std;
    cv::Mat m(5, 5, CV_16UC3, cv::Scalar(0,0,0));
#if 0
    for(cv::MatIterator_<cv::Vec3s> it = m.begin<cv::Vec3s>(); it != m.end<cv::Vec3s>(); ++it)
    {
        for(int channel = 0; channel < m.channels(); ++channel)
        {
            (*it)[channel] =  (it.pos().y + 1)*100 + (it.pos().x + 1)*10 + channel;
        }
    }
#else
    for(int row = 0; row < m.rows; row++)
    {
        for(int col = 0; col < m.cols; col++)
        {
            short base = (row + 1)*100 + (col + 1)*10;
            //m.at<cv::Vec3s>(row, col) = cv::Vec3s(base+1 , base+2, base+3);
            for(int channel = 0; channel < m.channels(); channel++)
            {
                m.at<cv::Vec3s>(row, col)[channel] = base + (channel + 1);
            }
        }
    }
#endif
    cout << "m = " << endl << m << endl << endl;

    cout << "m.row(3) =" << m.row(3) << endl;
    cout << "m.col(3) =" << m.col(3) << endl;
    cout << "m(Rect(3, 3, 1, 1)) =" << m(cv::Rect(3, 3, 1,1)) << endl;
    cout << "m(Range(3, 4), Range(3, 4)) =" << m(cv::Range(3,4), cv::Range(3,4)) << endl;
    cout << "m.diag() = " << m.diag() << endl;

}

void N_AryAccess()
{
    using namespace std;
    cv::RNG rng;
    const int n_mat_size = 3;
    const int mat_sz[] = {n_mat_size, n_mat_size};

//mat是否连续导致nplants不同
#if 0
    // 连续的mat
    cv::Mat m0 {2, mat_sz, CV_8UC1};
    cv::Mat m1 {2, mat_sz, CV_8UC1};
    rng.fill(m0, cv::RNG::UNIFORM, 0, 255);
    rng.fill(m1, cv::RNG::UNIFORM, 0, 255);
#else
    //　构造不连续mat
    cv::Mat m(8, 8, CV_8UC1);
    rng.fill(m, cv::RNG::UNIFORM, 0, 255);
    cv::Mat m0 = m(cv::Rect(0, 0, 3, 3));
    // cout << "m0 is continues:" << m0.isContinuous() << endl;
    //cv::Mat m1 = m(cv::Rect(1, 1, 3, 3));
    cv::Mat m1 {2, mat_sz, CV_8UC1};
    // cout << "m1 is continues:" << m1.isContinuous() << endl;
#endif
    const cv::Mat* arrays[] = {&m0, &m1, 0};
    cv::Mat my_planes[2];
    cv::NAryMatIterator it(arrays, my_planes);

    cout << "it.narrays = " <<it.narrays << endl;
    // nplanes 超平面个数，（超平面最多连续元素的平面）
    cout << "it.nplanes = " <<it.nplanes << endl;
    cout << "it.sizes = " <<it.size << endl;

    for(int p = 0; p < it.nplanes; ++p , ++it)
    {
        for(int i = 0; i < it.narrays; i++)
        {
            cout << i << "-th array with planes " << p << " = " << it.planes[i] << endl<<endl;
        }
    }

}


int main(int argc, char const *argv[])
{
    //info();
    //access();
    accessByAccess();
    //N_AryAccess();
    return 0;
}
