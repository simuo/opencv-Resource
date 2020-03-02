#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//定义全局变量
Mat g_srcImage, g_dstImage1,g_dstImage2,g_dstImage3;
int g_nBoxFiltetValue=3;		//方框滤波值
int g_nMeanBlurValue=3;			//均值滤波
int g_nGaussianBlurValue=3;     //高斯滤波值

//声明回调函数
static void on_BoxFilter(int,void*);    //方框滤波回调函数
static void on_MeanBlur(int,void*);		//均值滤波回调函数
static void on_GaussianBlur(int,void*); //高斯滤波回调函数

int main(int argc, char** argv)
{
	//载入原图
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("读取图片失败"); return -1; }

	//复制原图到3个Mat类
	g_dstImage1=g_srcImage.clone();
	g_dstImage2=g_srcImage.clone();
	g_dstImage3=g_srcImage.clone();
	
	//显示原图
	namedWindow("【原图】",1);
	imshow("【原图】",g_srcImage);
	
	//创建方框滤波窗口
	namedWindow("【方框滤波】",1);
	createTrackbar("方框滤波强度： ","【方框滤波】",&g_nBoxFiltetValue,40,on_BoxFilter);
	on_BoxFilter(g_nBoxFiltetValue,0);
	imshow("【方框滤波】",g_dstImage1);
	
	//创建均值滤波窗口
	namedWindow("【均值滤波】",1);
	createTrackbar("均值滤波强度： ","【均值滤波】",&g_nMeanBlurValue,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue,0);
	imshow("【均值滤波】",g_dstImage2);
	
	//创建高斯滤波窗口
	namedWindow("【高斯滤波】",1);
	createTrackbar("高斯滤波强度： ","【高斯滤波】",&g_nGaussianBlurValue,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue,0);
	imshow("【高斯滤波】",g_dstImage3);

	waitKey(20170301);
	return 0;
}

static void on_BoxFilter(int,void*)
{
	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFiltetValue+1,g_nBoxFiltetValue+1));
	imshow("【方框滤波】",g_dstImage1);
}

static void on_MeanBlur(int,void*)
{
	blur(g_srcImage,g_dstImage2,Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1));
	imshow("【均值滤波】",g_dstImage2);
}

static void on_GaussianBlur(int,void*)
{
	GaussianBlur(g_srcImage,g_dstImage3,Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),0,0);
	imshow("【高斯滤波】",g_dstImage3);
}