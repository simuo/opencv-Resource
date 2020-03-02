#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "图像"


//全局变量
Mat srcImage1, inpaintMask;
Point previousPoint(-1, -1);

//声明鼠标响应函数
static void On_Mouse(int event, int x, int y, int flags, void*);

//主函数
int main()
{
	//读入图像
	Mat srcImage = imread("dog.jpg",-1);
	if (!srcImage.data) { printf("读取图片失败"); return -1; }
	imshow(WINDOW_NAME1, srcImage);

	//初始化掩膜
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	//设置鼠标回调函数
	setMouseCallback(WINDOW_NAME1, On_Mouse, 0);

	//轮询按键
	while (1)
	{
		char c = (char)waitKey();

		//按“ESC”退出
		if (c == 27)
			break;

		//按“2”恢复原始图像
		if(c == '2')
		{
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}

		//按“1”或空格，进行图像修补
		if (c == '1' || c == ' ')
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage,
				3, INPAINT_TELEA);
			imshow(WINDOW_NAME1, inpaintedImage);
		}
	}

	return 0;
}

static void On_Mouse(int event, int x, int y, int flags, void*)
{
	//鼠标左键谈起事件
	if (event == EVENT_LBUTTONUP || !(flags&EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);

	//鼠标左键被按下事件
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);

	//鼠标拖动事件
	else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x<0)
			previousPoint = pt;
		//绘制白色线条
		line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage1);
	}

}