#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

#define WINDOW_NAME "滑块实现亮度调节"

const int g_nMaxAlphaValue = 100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_dstImage;

//回调函数on_Trackbar(),即滑条滑动后，调整图片的亮度
void on_Trackbar(int, void*)
{
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;

	g_dstImage = Mat::zeros(g_srcImage1.size(), g_srcImage1.type());
	//根据alpha值对图像进行亮度调节
	for (int i = 0; i<g_srcImage1.rows; ++i)
		for (int j = 0; j<g_srcImage1.cols; ++j)
			for (int k = 0; k<3; ++k)
				g_dstImage.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(g_srcImage1.at<Vec3b>(i, j)[k] * g_dAlphaValue*2);

	//显示效果图
	imshow(WINDOW_NAME, g_dstImage);
}

int main(int argc, char** argv)
{
	g_srcImage1 = imread("1.jpg");

	if (!g_srcImage1.data) { printf("读取图片失败"); return -1; }


	//设置滑条初值
	g_nAlphaValueSlider = 50;

	//创建窗体
	namedWindow(WINDOW_NAME, 1);

	//在创建的窗体中创建一个滑条
	char TrackbarName[50];
	sprintf(TrackbarName, "亮度值%d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	//调用回调函数，进行两图的线性混合
	on_Trackbar(g_nAlphaValueSlider, 0);
	waitKey(20170301);
	return 0;
}