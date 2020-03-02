#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat dstImage;
	Mat blueChannel, greenChannel, redChannel;
	vector<Mat>channels;

	split(srcImage, channels);
	blueChannel = channels.at(0);
	greenChannel = channels.at(1);
	redChannel = channels.at(2);

	imshow("Blue", channels.at(0));
	imshow("Green", greenChannel);
	imshow("Red", redChannel);

	merge(channels, dstImage);
	imshow("合并后的图片", dstImage);
	waitKey(20170301);
	return 0;
}
