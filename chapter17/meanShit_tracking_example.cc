#include <opencv2/opencv.hpp>

#define RESOURCE_DIR "../resource/"
//#define  DIST 0.5
#define  NUM 20

//全局变量
bool pause = false;
bool is_tracking = false;
cv::Rect drawing_box;
cv::Mat current;
double *hist1, *hist2;
double *m_wei;																	//权值矩阵
double C = 0.0;																   //归一化系数

void init_target(double *hist1, double *m_wei,  cv::Mat& current)
{
	cv::Mat pic_hist(300, 200, CV_8UC3); //生成直方图图像
	int t_h, t_w, t_x, t_y;
	double h, dist;
	int i, j;
	int q_r, q_g, q_b, q_temp;

	t_h = drawing_box.height;
	t_w = drawing_box.width;
	t_x = drawing_box.x;
	t_y = drawing_box.y;

	h = pow(((double)t_w)/2,2) + pow(((double)t_h)/2,2);			//带宽

	//初始化权值矩阵和目标直方图
	for (i = 0;i < t_w*t_h;i++)
	{
		m_wei[i] = 0.0;
	}

	for (i=0;i<4096;i++)
	{
		hist1[i] = 0.0;
	}

	for (i = 0;i < t_h; i++)
	{
		for (j = 0;j < t_w; j++)
		{
			dist = pow(i - (double)t_h/2,2) + pow(j - (double)t_w/2,2);
			m_wei[i * t_w + j] = 1 - dist / h;
			//printf("%f\n",m_wei[i * t_w + j]);
			C += m_wei[i * t_w + j] ;
		}
	}

	//计算目标权值直方
	for (i = t_y;i < t_y + t_h; i++)
	{
		for (j = t_x;j < t_x + t_w; j++)
		{
			//rgb颜色空间量化为16*16*16 bins
			q_r = ((u_char)current.data[i * current.step + j * 3 + 2]) / 16;
			q_g = ((u_char)current.data[i * current.step + j * 3 + 1]) / 16;
			q_b = ((u_char)current.data[i * current.step + j * 3 + 0]) / 16;
			q_temp = q_r * 256 + q_g * 16 + q_b;
			hist1[q_temp] =  hist1[q_temp] +  m_wei[(i - t_y) * t_w + (j - t_x)] ;
		}
	}

	//归一化直方图
	for (i=0;i<4096;i++)
	{
		hist1[i] = hist1[i] / C;
		//printf("%f\n",hist1[i]);
	}

	//生成目标直方图
	double temp_max=0.0;

	for (i = 0;i < 4096;i++)			//求直方图最大值，为了归一化
	{
		//printf("%f\n",val_hist[i]);
		if (temp_max < hist1[i])
		{
			temp_max = hist1[i];
		}
	}
	//画直方图
	CvPoint p1,p2;
	double bin_width=(double)pic_hist.cols/4096;
	double bin_unith=(double)pic_hist.rows/temp_max;

	for (i = 0;i < 4096; i++)
	{
		p1.x = i * bin_width;
		p1.y = pic_hist.rows;
		p2.x = (i + 1)*bin_width;
		p2.y = pic_hist.rows - hist1[i] * bin_unith;
		//printf("%d,%d,%d,%d\n",p1.x,p1.y,p2.x,p2.y);
		cv::rectangle(pic_hist,p1,p2,cvScalar(0,255,0),-1,8,0);
	}
	cv::imwrite("hist1.jpg",pic_hist);
}

void MeanShift_Tracking(cv::Mat& current)
{
	int num = 0, i = 0, j = 0;
	int t_w = 0, t_h = 0, t_x = 0, t_y = 0;
	double *w = 0, *hist2 = 0;
	double sum_w = 0, x1 = 0, x2 = 0,y1 = 2.0, y2 = 2.0;
	int q_r, q_g, q_b;
	int *q_temp;
	cv::Mat pic_hist;

	t_w = drawing_box.width;
	t_h = drawing_box.height;

	pic_hist = cv::Mat(cv::Size(300,200),CV_8UC3);     //生成直方图图像
	hist2 = (double *)malloc(sizeof(double)*4096);
	w = (double *)malloc(sizeof(double)*4096);
	q_temp = (int *)malloc(sizeof(int)*t_w*t_h);

	while ((pow(y2,2) + pow(y1,2) > 0.5)&& (num < NUM))
	{
		num++;
		t_x = drawing_box.x;
		t_y = drawing_box.y;
		memset(q_temp,0,sizeof(int)*t_w*t_h);
		for (i = 0;i<4096;i++)
		{
			w[i] = 0.0;
			hist2[i] = 0.0;
		}

		for (i = t_y;i < t_h + t_y;i++)
		{
			for (j = t_x;j < t_w + t_x;j++)
			{
				//rgb颜色空间量化为16*16*16 bins
				q_r = ((u_char)current.data[i * current.step + j * 3 + 2]) / 16;
				q_g = ((u_char)current.data[i * current.step + j * 3 + 1]) / 16;
				q_b = ((u_char)current.data[i * current.step + j * 3 + 0]) / 16;
				q_temp[(i - t_y) *t_w + j - t_x] = q_r * 256 + q_g * 16 + q_b;
				hist2[q_temp[(i - t_y) *t_w + j - t_x]] =  hist2[q_temp[(i - t_y) *t_w + j - t_x]] +  m_wei[(i - t_y) * t_w + j - t_x] ;
			}
		}

		//归一化直方图
		for (i=0;i<4096;i++)
		{
			hist2[i] = hist2[i] / C;
			//printf("%f\n",hist2[i]);
		}
		//生成目标直方图
		double temp_max=0.0;

		for (i=0;i<4096;i++)			//求直方图最大值，为了归一化
		{
			if (temp_max < hist2[i])
			{
				temp_max = hist2[i];
			}
		}
		//画直方图
		CvPoint p1,p2;
		double bin_width=(double)pic_hist.cols/(4368);
		double bin_unith=(double)pic_hist.rows/temp_max;

		for (i = 0;i < 4096; i++)
		{
			p1.x = i * bin_width;
			p1.y = pic_hist.rows;
			p2.x = (i + 1)*bin_width;
			p2.y = pic_hist.rows - hist2[i] * bin_unith;
			cv::rectangle(pic_hist,p1,p2,cvScalar(0,255,0),-1,8,0);
		}
		cv::imwrite("hist2.jpg",pic_hist);

		for (i = 0;i < 4096;i++)
		{
			if (hist2[i] != 0)
			{
				w[i] = sqrt(hist1[i]/hist2[i]);
			}else
			{
				w[i] = 0;
			}
		}

		sum_w = 0.0;
		x1 = 0.0;
		x2 = 0.0;

		for (i = 0;i < t_h; i++)
		{
			for (j = 0;j < t_w; j++)
			{
				//printf("%d\n",q_temp[i * t_w + j]);
				sum_w = sum_w + w[q_temp[i * t_w + j]];
				x1 = x1 + w[q_temp[i * t_w + j]] * (i - t_h/2);
				x2 = x2 + w[q_temp[i * t_w + j]] * (j - t_w/2);
			}
		}
		y1 = x1 / sum_w;
		y2 = x2 / sum_w;

		//中心点位置更新
		drawing_box.x += y2;
		drawing_box.y += y1;

		//printf("%d,%d\n",drawing_box.x,drawing_box.y);
	}
	free(hist2);
	free(w);
	free(q_temp);
	//显示跟踪结果
	cv::rectangle(current,cvPoint(drawing_box.x,drawing_box.y),cvPoint(drawing_box.x+drawing_box.width,drawing_box.y+drawing_box.height),CV_RGB(255,0,0),2);
	cv::imshow("Meanshift",current);
	//cvSaveImage("result.jpg",current);
}

void onMouse( int event, int x, int y, int flags, void *param )
{
	if (pause)
	{
		switch(event)
		{
		case CV_EVENT_LBUTTONDOWN:
			//the left up point of the rect
			drawing_box.x=x;
			drawing_box.y=y;
			break;
		case CV_EVENT_LBUTTONUP:
			//finish drawing the rect (use color green for finish)
			drawing_box.width=x-drawing_box.x;
			drawing_box.height=y-drawing_box.y;
			cv::rectangle(current,cvPoint(drawing_box.x,drawing_box.y),cvPoint(drawing_box.x+drawing_box.width,drawing_box.y+drawing_box.height),CV_RGB(255,0,0),2);
			cv::imshow("Meanshift",current);

			//目标初始化
			hist1 = (double *)malloc(sizeof(double)*16*16*16);
			m_wei =  (double *)malloc(sizeof(double)*drawing_box.height*drawing_box.width);
			init_target(hist1, m_wei, current);
			is_tracking = true;
			break;
		}
		return;
	}
}



int main(int argc, char* argv[])
{
	cvNamedWindow("Meanshift",1);
	cv::VideoCapture capture(RESOURCE_DIR"/17/test.mkv");
	capture.read(current);
	char res[20];
	int nframe = 0;

	while (1)
	{
	/*	sprintf(res,"result%d.jpg",nframe);
		cvSaveImage(res,current);
		nframe++;*/
		if(is_tracking)
		{
			MeanShift_Tracking(current);
		}

		int c=cv::waitKey(30);
		//暂停
		if(c == 'p')
		{
			pause = true;
			cv::setMouseCallback("Meanshift", onMouse, 0);
		}
		while(pause){
			if(cvWaitKey(0) == 'p')
				pause = false;
		}
		cv::imshow("Meanshift",current);
		capture.read(current); //抓取一帧
	}


	capture.release();
	cv::destroyAllWindows();
	return 0;
}
