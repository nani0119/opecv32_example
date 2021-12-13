#include <opencv2/opencv.hpp>


// 根据状态向量确定点的位置。
// 这里状态向量是通过矩阵mat的形式表示，矩阵为2行1列，共两个元素分别表示角和角速度。
// 以整幅图片img的中心为原点，图片列数的1/3位半径，确定目标的位置。
#define phi2xy(mat) \
cv::Point(cvRound(img.cols / 2 + img.cols / 3 * cos(mat.at<float>(0))), cvRound(img.rows / 2 - img.cols / 3 * sin(mat.at<float>(0))))

void KalmanFilter_example()
{
    // 1. 初始化Kalman矩阵
    // 状态向量维度为2维，分别表示目标的角和角速度
    // 测量向量维度为1维，只测量角度
    // 控制向量维度为0维，即不会受到外部控制改变运动状态
    cv::KalmanFilter kalman(2, 1, 0);

    // 2. 设置初始Kalman滤镜计算关键属性
    //=======================预测过程参数====================//
    // 设置转移矩阵，用于预测k+1时刻的状态向量
    // 从物理模型上考虑，k时刻系统状态为(φ, ω)，则k+1时刻系统状态为(φ+ω*dt, w)，
    // 则转移矩阵为{1, dt, 0, 1}，这里为了方便设dt=1，实际上应该根据连续两个
    // 视频帧的时间差来设置该值
    float F[] = {1, 1, 0, 1};
    kalman.transitionMatrix = cv::Mat(2, 2, CV_32F, F).clone();
    // 设置流程的噪声协方差矩阵，用于预测k+1时刻的状态协方差矩阵
    // 假设状态向量维度为N，则其尺寸为NxN
    cv::setIdentity(kalman.processNoiseCov, cv::Scalar(1e-5));
    //=======================校准过程参数====================//
    // 设置测量矩阵，用于从k时刻测量结果反应出的校准前矩阵计算实际测量结果的矩阵
    cv::setIdentity(kalman.measurementMatrix, cv::Scalar(1));
    // 设置测量的噪声协方差矩阵，假设测量向量维度为N，则其尺寸为NxN
    cv::setIdentity(kalman.measurementNoiseCov, cv::Scalar(1e-1));

    // 3. 设置初始的状态向量，和初始的不确定度即状态向量的协方差矩阵
    cv::Mat x_k = cv::Mat::zeros(2, 1, CV_32F);
    randn(x_k, 0.0, 0.1);
    // 设置初始状态为随机值
    kalman.statePost = x_k.clone();
    // 设置初始状态向量的协方差矩阵
    // 这里设置为单位向量表示不同维度之间的分布是独立的，无相关
    cv::setIdentity(kalman.errorCovPost, cv::Scalar(1));

    // 4. 循环更新系统状态，并可视化目标位置
    // 准备绘图用的矩阵
    cv::Mat img(500, 500, CV_8UC3);
    // 初始化测量矩阵
    cv::Mat z_k = cv::Mat::zeros(1, 1, CV_32F);
    // 每次测量时的随机偏差矩阵，用于计算z_k
    cv::Mat z_k_r = cv::Mat::zeros(1, 1, CV_32F);
    for (;;)
    {
        // 记录上一次的校准值，用于绘图
        cv::Mat lastCorrectedState = kalman.statePost.clone();

        // 预测当前状态向量
        kalman.predict();

        // 真正的应用程序中应该使用传感的测量值，这里为了演示使用了模拟值
        // 在上一次的测量结果上，加上随机值作为当前的测量向量z_k
        // 这里随机分布的方差取测量误差的标准差
        cv::randn(z_k_r, 0.0,
                  sqrt(static_cast<double>(kalman.measurementNoiseCov.at<float>(0, 0))));
        z_k = kalman.measurementMatrix * lastCorrectedState + z_k_r;

        // 校准测量值
        kalman.correct(z_k);

        // 绘图
        img = cv::Scalar::all(0);
        // 用蓝色圆表示上一次的测量值
        cv::circle(img, phi2xy(lastCorrectedState), 6, cv::Scalar(255, 0, 0), 1, cv::LINE_AA);
        // 用绿色圆表示预测值
        cv::circle(img, phi2xy(kalman.statePre), 6, cv::Scalar(0, 255, 0), 1, cv::LINE_AA);
        // 用红色圆表示观察值
        cv::circle(img, phi2xy(z_k), 6, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        // 用白色圆表示校准后的值
        cv::circle(img, phi2xy(kalman.statePost), 6, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);
        cv::imshow("Kalman", img);

        // 挂起程序
        if ((cv::waitKey(1000) & 255) =='q')
        {
            break;
        }
    }
}

int main(int argc, char const *argv[])
{
    KalmanFilter_example();
    return 0;
}
