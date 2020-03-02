#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"

Mat g_srcImage, g_dstImage;
Mat g_mapx, g_mapy;

int update_map(int key);
static void showHelpText();

int main()
{
	//控制台显示设置
	system("color 2F");
	showHelpText();

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

	//创建窗口并显示
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	//按键轮询，根据案件，然更新重映射方法，来显示不同的效果图
	while (1)
	{
		int key = waitKey(0);
		if ((key & 255) == 27)
		{
			cout << "程序退出........\n";
			break;
		}

		//更新mapx跟mapy
		update_map(key);

		//利用新的mpx跟mapy进行remap
		remap(g_srcImage, g_dstImage, g_mapx, g_mapy,
			INTER_LINEAR, BORDER_CONSTANT, Scalar(255, 0, 0));

		//显示效果图
		imshow(WINDOW_NAME, g_dstImage);
	}

	return 0;
}

int update_map(int key)
{
	for (int j = 0; j<g_srcImage.rows; j++)
	{
		for (int i = 0; i<g_srcImage.cols; i++)
		{
			switch (key)
			{
				//按下1，实现缩小
			case '1':
				if (i>g_srcImage.cols*0.25&&i<g_srcImage.cols*0.75
					&&j>g_srcImage.rows*0.25&&j<g_srcImage.rows*0.75)
				{
					g_mapx.at<float>(j, i) = static_cast<float>(
						2 * (i - g_srcImage.cols*0.25) + 0.5);
					g_mapy.at<float>(j, i) = static_cast<float>(
						2 * (j - g_srcImage.rows*0.25) + 0.5);
				}
				else
				{
					g_mapx.at<float>(j, i) = 0;
					g_mapy.at<float>(j, i) = 0;
				}
				break;

				//按下2，实现上下颠倒
			case'2':
				g_mapx.at<float>(j, i) = static_cast<float>(i);
				g_mapy.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;

				//按下3，实现左右颠倒
			case'3':
				g_mapx.at<float>(j, i) = static_cast<float>(g_srcImage.rows - i);
				g_mapy.at<float>(j, i) = static_cast<float>(j);
				break;

				//按下3，实现左右颠倒
			case'4':
				g_mapx.at<float>(j, i) = static_cast<float>(g_srcImage.rows - i);
				g_mapy.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			}
		}
	}
	return 1;
}

static void showHelpText()
{
	printf("\n\n\n\t欢迎使用重映射示例程序！\n\n");
	printf("\n\n按键操作提示：\n\n"
		"\t\t键盘按键【ESC】-退出程序\n"
		"\t\t键盘按键【1】-缩放\n"
		"\t\t键盘按键【2】-上下颠倒\n"
		"\t\t键盘按键【3】-左右颠倒\n"
		"\t\t键盘按键【4】-上下左右颠倒\n");
}
