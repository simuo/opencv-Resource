#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	//读入图像
	Mat srcImage = imread("1.jpg",0);
	if (!srcImage.data) { printf("读取图片失败"); return -1; }
	imshow("原图", srcImage);

	//定义变量
	MatND dstHist;//定义直方图类型的变量
	int dims = 1;//维度为1维
	float hranges[] = { 0,255 };//数据的取值范围为0~255
	const float *ranges[] = { hranges };
	int width = 1024;//定义直方图的宽度
	int height = 512;//定义直方图的长度
	int size = 256;//分成256个等级
	int channels = 0;//统计对象为图像的通道0
	int scale = width / size;
	Mat dstImage(height, width, CV_8U, Scalar(0));

	//计算图像直方图
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims,
		&size, ranges);

	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

	//绘制直方图
	int hpt = saturate_cast<int>(0.9*height);
	for (int i = 0; i<size; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>((double)binValue / maxValue*hpt);
		rectangle(dstImage, Point(i*scale, height - 1),
			Point((i + 1)*scale - 1, height - realValue), Scalar(255),FILLED);
	}
	imshow("一维直方图", dstImage);
	waitKey(20170301);
	return 0;
}