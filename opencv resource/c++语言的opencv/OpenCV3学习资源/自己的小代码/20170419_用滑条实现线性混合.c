#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

#define WINDOW_NAME "【线性混合示例】"

const int g_nMaxAlphaValue=100;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

//声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

//回调函数on_Trackbar(),即滑条滑动后，调整线性混合的程度
void on_Trackbar(int,void*)
{
	//求出当前alpha值相对于最大值的比例
	g_dAlphaValue=(double)g_nAlphaValueSlider/g_nMaxAlphaValue;
	g_dBetaValue=1-g_dAlphaValue;
	
	//进行线性混合
	addWeighted(g_srcImage1,g_dAlphaValue,g_srcImage2,g_dBetaValue,0,g_dstImage,-1);
	
	//显示效果图
	imshow(WINDOW_NAME,g_dstImage);
}

int main(int argc,char** argv)
{
	g_srcImage1=imread("1.jpg");
	g_srcImage2=imread("2.jpg");
	
	if(!g_srcImage1.data){printf("读第一幅图片错误");return -1;}
	if(!g_srcImage2.data){printf("读第二幅图片错误");return -1;}
	
	//设置滑条初值
	g_nAlphaValueSlider=50;
	
	//创建窗体
	namedWindow(WINDOW_NAME,1);
	
	//在创建的窗体中创建一个滑条
	char TrackbarName[50];
	sprintf(TrackbarName,"透明值%d",g_nMaxAlphaValue);
	
	createTrackbar(TrackbarName,WINDOW_NAME,&g_nAlphaValueSlider,g_nMaxAlphaValue,on_Trackbar);
	
	//调用回调函数，进行两图的线性混合
	on_Trackbar(g_nAlphaValueSlider,0);
	 waitKey(20170301);
	 return 0;
}
	