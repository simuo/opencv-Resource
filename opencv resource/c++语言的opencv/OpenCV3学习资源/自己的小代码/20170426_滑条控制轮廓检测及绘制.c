#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始图像"
#define WINDOW_NAME2 "轮廓图"

//全局变量的定义
Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 80;
int g_nThresh_max = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point>> g_vContours;
vector<Vec4i> g_vHierarchy;

//声明回调函数
void on_ThreshChange(int, void*);

//主函数
int main(int argc, char** argv)
{
	//读入图像
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("读取图片失败"); return -1; }

	//转换为灰度图并降噪
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	//创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	//创建滑条
	createTrackbar("canny阈值：", WINDOW_NAME1, &g_nThresh,
		g_nThresh_max, on_ThreshChange);

	//调用回调函数，进行两图的线性混合
	on_ThreshChange(0, 0);
	waitKey(20170301);
	return 0;
}

//回调函数
void on_ThreshChange(int, void*)
{
	//用canny算子检测边缘，进行二值化
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	//寻找轮廓
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy,
		RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	//绘制轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i<g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255),
			g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy,
			0, Point());
	}
	//显示效果图
	imshow(WINDOW_NAME2, drawing);
}