#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int g_nContrastValue;//对比度值
int g_nBrightValue;//亮度值
Mat g_srcImage, g_dstImage;


//回调函数on_Trackbar(),即滑条滑动后，调整图片的亮度
static void on_ConstrastAndBright(int, void*)
{
	namedWindow("【原始图】", 1);
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//亮度和对比度调节
	for (int i = 0; i<g_srcImage.rows; i++)
		for (int j = 0; j<g_srcImage.cols; j++)
			for (int k = 0; k<3; k++)
				g_dstImage.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(g_srcImage.at<Vec3b>(i, j)[k] * g_nContrastValue *0.01+g_nBrightValue);

	//显示效果图
	imshow("【原始图】", g_srcImage);
	imshow("【效果图】", g_dstImage);
}

int main(int argc, char** argv)
{
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("读取图片失败"); return -1; }

	//设置对比度和亮度的初始值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	//创建窗体
	namedWindow("【效果图】", 1);

	//在创建的窗体中创建一个对比度条，一个亮度条
	createTrackbar("对比度：", "【效果图】", &g_nContrastValue, 300, on_ConstrastAndBright);
	createTrackbar("亮  度：", "【效果图】", &g_nBrightValue, 200, on_ConstrastAndBright);

	//调用回调函数，进行两图的线性混合
	on_ConstrastAndBright(g_nContrastValue, 0);
	on_ConstrastAndBright(g_nBrightValue, 0);

	waitKey(20170301);
	return 0;
}