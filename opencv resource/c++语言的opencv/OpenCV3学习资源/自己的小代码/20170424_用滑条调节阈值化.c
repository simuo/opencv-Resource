#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int g_nThresholdValue=100;//阈值
int g_nThresholdType=3;//亮度值
Mat g_srcImage,g_grayImage, g_dstImage;

#define WINDOW_NAME "【效果图】"

//回调函数on_Threshold(int，void*)声明
void on_Threshold(int,void*);


int main(int argc, char** argv)
{
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("读取图片失败"); return -1; }

	//转换为灰度图
	cvtColor(g_srcImage,g_grayImage,COLOR_RGB2GRAY);

	//创建窗体
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

	//创建滑条
	createTrackbar("模式：", WINDOW_NAME, 
	&g_nThresholdType, 4, on_Threshold);
	
	createTrackbar("阈值：", WINDOW_NAME, 
	&g_nThresholdValue, 255, on_Threshold);

	//调用回调函数
	on_Threshold(0, 0);

	waitKey(20170301);
	return 0;
}

void on_Threshold(int, void*)
{
	threshold(g_grayImage,g_dstImage,g_nThresholdValue,
	255,g_nThresholdType);
	
	imshow("【原始图】", g_srcImage);
	imshow(WINDOW_NAME, g_dstImage);
}