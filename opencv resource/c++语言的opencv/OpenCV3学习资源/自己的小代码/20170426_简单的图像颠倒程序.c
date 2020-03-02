#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat g_dstImage;
	Mat g_mapx,g_mapy;

	//读入图片
	Mat g_srcImage = imread("1.jpg");
	if (!g_srcImage.data)
	{
		printf("读取图片失败");
		return -1;
	}
	imshow("【原始图】", g_srcImage);

	//创建mapx和mapy
	g_dstImage.create(g_srcImage.size(), g_srcImage.type());
	g_mapx.create(g_srcImage.size(), CV_32FC1);
	g_mapy.create(g_srcImage.size(), CV_32FC1);

	for (int j = 0; j<g_srcImage.rows; j++)
	{
		for (int i = 0;i<g_srcImage.cols; i++)
		{
			g_mapx.at<float>(j, i) = static_cast<float>(i);
			g_mapy.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
		}
	}

	//利用新的mpx跟mapy进行remap
	remap(g_srcImage, g_dstImage, g_mapx, g_mapy,
		INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//显示效果图
	imshow("效果图", g_dstImage);
	waitKey(20170301);
	return 0;
}