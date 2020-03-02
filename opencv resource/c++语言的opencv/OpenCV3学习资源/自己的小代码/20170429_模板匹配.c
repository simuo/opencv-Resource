#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始图像"
#define WINDOW_NAME2 "效果图像"

//全局变量的定义
Mat g_srcImage;
Mat g_templateImage;//模板
Mat g_resultImage;//匹配结果
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;//滑条最大值为5，对应六种方法

						  //声明回调函数
void on_Matching(int, void*);

int main()
{
	//读入图像
	g_srcImage = imread("dog.jpg");
	g_templateImage = imread("爪子.jpg");

	//创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);

	//创建滑条
	createTrackbar("匹配方法：", WINDOW_NAME1,
		&g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);

	on_Matching(0, 0);
	waitKey(20170301);
	return 0;

}

void on_Matching(int, void*)
{
	//将原图拷贝一份
	Mat srcImage;
	g_srcImage.copyTo(srcImage);

	//初始化结果输出矩阵g_resultImage
	int resultImage_cols = g_srcImage.cols -
		g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows -
		g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols,
		resultImage_rows, CV_32FC1);

	//进行匹配和标准化
	matchTemplate(g_srcImage, g_templateImage,
		g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1,
		NORM_MINMAX , -1, Mat());

	//通过minMax定位最匹配的位置
	double minValue, maxValue;
	Point minLocation, maxLocation, matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue,
		&minLocation, &maxLocation, Mat());

	//对于SQDIFF和SQDIFF_NORMED方法，数值越小越匹配，
	//其余方法数值越大越匹配
	if (g_nMatchMethod == TM_SQDIFF ||
		g_nMatchMethod == TM_SQDIFF_NORMED)
		matchLocation = minLocation;
	else
		matchLocation = maxLocation;

	//根据matchLocation绘制一个矩形，表示匹配结果
	rectangle(srcImage, matchLocation,
		Point(matchLocation.x + g_templateImage.cols,
			matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	rectangle(g_resultImage, matchLocation,
		Point(matchLocation.x + g_templateImage.cols,
			matchLocation.y + g_templateImage.rows),
		Scalar(0, 0, 255), 2, 8, 0);

	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}
