#include <ope#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define r 1000
int main()
{
	Mat src = imread("楼房.jpg");
	Mat mid, dst;

	imshow("【原始图】", src);

	//canny处理
	Canny(src, mid, 50, 700, 3);
	cvtColor(src, dst, COLOR_BGR2GRAY);

	//imshow("【效果图1】", dst);

	//霍夫变换
	vector<Vec2f> lines;
	HoughLines(mid, lines, 1, CV_PI / 180, 100, 0, 0);

	for (int i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point p1, p2;

		//坐标变换
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;

		//把一个点变成两个点
		p1.x = cvRound(x0 + r*(-b));
		p1.y = cvRound(y0 + r*(a));
		p2.x = cvRound(x0 - r*(-b));
		p2.y = cvRound(y0 - r*(a));

		//根据两个点划线
		line(src, p1, p2, Scalar(55, 100, 195), 1, LINE_AA);
	}


	imshow("【效果图2】", src);

	waitKey(20170301);
	return 0;
}


	