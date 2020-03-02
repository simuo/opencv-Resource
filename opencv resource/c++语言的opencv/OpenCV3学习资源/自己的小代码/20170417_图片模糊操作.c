#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImg=imread("dog.jpg");
	imshow("原图",srcImg);
	
	Mat dsImg;
	
	blur(srcImg,dsImg,Size(7,7));//均值滤波
	imshow("腐蚀后",dsImg);
	
	waitKey(20170301);
	return 0;
}