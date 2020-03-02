#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始图像"


//全局变量的定义
Mat g_srcImage;
Mat g_hsvImage;//HSV格式图像
Mat g_hueImage;//色调通道
int g_bins = 30;//直方图组距


//声明回调函数
void on_BinChage(int, void*);

//主函数
int main(int argc, char** argv)
{
	//读入图像
	g_srcImage = imread("楼房.jpg");
	if (!g_srcImage.data) { printf("读取图片失败"); return -1; }

	//转换为HSV通道格式
	cvtColor(g_srcImage, g_hsvImage, COLOR_BGR2HSV);
	
	//分离Hue色调通道
	g_hueImage.create(g_hsvImage.size(),g_hsvImage.depth());
	int ch[]={0,0};
	mixChannels(&g_hsvImage,1,&g_hueImage,1,ch,1);

	//创建窗口和滑条
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	createTrackbar("色调组距：", WINDOW_NAME1, &g_bins,
		180, on_BinChage);
		
	on_BinChage(0,0);
	imshow(WINDOW_NAME1, g_srcImage);


	waitKey(20170301);
	return 0;
}

//回调函数
void on_BinChage(int, void*)
{
	MatND hist;
	int histSize=MAX(g_bins,2);
	float hue_range[]={0,180};
	const float*ranges={hue_range};
	
	//计算直方图并归一化
	calcHist(&g_hueImage,1,0,Mat(),hist,1,&histSize,
	&ranges,true,false);
	normalize(hist,hist,0,255,NORM_MINMAX,-1,Mat());

	//计算反向投影
	MatND backproj;
	calcBackProject(&g_hueImage,1,0,hist,backproj,
	&ranges,1,true);
	
	//显示反向投影
	imshow("反向投影",backproj);
	
	//绘制直方图
	int w=400,h=400;
	int bin_w=cvRound((double)w/histSize);//计算直方图分了多少组
	Mat histImg=Mat::zeros(w,h,CV_8UC3);
	
	for(int i=0;i<g_bins;i++)
	{
		rectangle(histImg,Point(i*bin_w,h),
		Point((i+1)*bin_w,h-cvRound(hist.at<float>(i)*h/255.0)),
		Scalar(100,123,255),-1);
	}
	
	//显示效果图
	imshow("直方图",histImg);
}