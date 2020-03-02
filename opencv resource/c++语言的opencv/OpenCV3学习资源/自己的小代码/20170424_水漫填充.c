#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	Mat src = imread("dog.jpg");

	imshow("原图", src);
	Scalar s(3, 3, 3);
	Rect ccomp;
	floodFill(src, Point(30, 30), Scalar(255, 55, 55), &ccomp,
		s,s);
	imshow("填充后", src);

	waitKey(20170301);
	return 0;
}