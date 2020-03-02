#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main(int argc, char* argv[])
{
	VideoCapture inputVideo(1);	

	int c;
	Mat result;

	while(1)
	{
		inputVideo >> result;
		imshow("input",result);
		c = waitKey(10);
		if (c == 27) break;
	}
	imshow("photo", result);
	imwrite("photo.bmp", result);
	waitKey(20170301);
	return 0;
}
