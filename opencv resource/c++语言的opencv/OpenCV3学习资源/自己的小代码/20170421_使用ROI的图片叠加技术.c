#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("dog.jpg");
	Mat logoImage = imread("logo.jpg");

	Mat imageROI = srcImage(Rect(439, 500, logoImage.cols, logoImage.rows));

	Mat mask = imread("logo.jpg", 0);
	logoImage.copyTo(imageROI, mask);

	imshow("加上logo后", srcImage);
	waitKey(20170301);
	return 0;
}