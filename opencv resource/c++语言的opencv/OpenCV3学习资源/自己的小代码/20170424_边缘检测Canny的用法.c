#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
	Mat src=imread("1.jpg");
	Mat src1=src.clone();
	
	imshow("【原始图】",src);
	
	//canny的简单用法
	cvtColor(src,src,COLOR_BGR2GRAY);
	Canny(src,src,150,100,3);
	imshow("【效果图1】",src);
	
	//Canny的高级用法
	Mat dst,edge,gray;
	dst.create(src1.size(),src1.type());
	dst=Scalar::all(255);
	
	//将src1转换为灰度图gray
	cvtColor(src1,gray,COLOR_BGR2GRAY);
	
	//对灰度图进行降噪得到edge
	blur(gray,edge,Size(3,3));
	
	//运行Canny算子
	Canny(edge,edge,3,9,3);
	
	//将src1通过edge过滤后贴到dst上，
	//dst上就获得了src1的彩色边缘
	src1.copyTo(dst,edge);
	
	imshow("【效果图2】",dst);
	
	waitKey(20170301);
	return 0;
}
	