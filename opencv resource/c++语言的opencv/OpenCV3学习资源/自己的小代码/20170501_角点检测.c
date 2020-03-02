#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME "【Shi-Tomasi角点检测】"

//全局变量的定义
Mat g_srcImage;
Mat g_grayImage;
int g_maxCornerNumber=33;//滑条当前值
int g_maxTrackbarNumber=500;//滑条最大值


//声明回调函数
void on_GoodFeaturesToTrack(int, void*);

int main()
{
	//读入图像
	g_srcImage = imread("dog.jpg");
	cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
	
	//创建窗口
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	
	//创建滑条
	createTrackbar("最大角点数：", WINDOW_NAME, 
	&g_maxCornerNumber,g_maxTrackbarNumber, 
	on_GoodFeaturesToTrack);

	on_GoodFeaturesToTrack(0,0);
	waitKey(20170301);
	return 0;
	
}

void on_GoodFeaturesToTrack(int, void*)
{
	if(g_maxCornerNumber<=1){g_maxCornerNumber=1;}
	
	
	
	imshow(WINDOW_NAME,copy);
	
}
