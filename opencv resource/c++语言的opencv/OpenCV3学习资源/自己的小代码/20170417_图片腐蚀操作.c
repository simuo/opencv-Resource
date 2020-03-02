#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImg=imread("dog.jpg");
	imshow("原图",srcImg);
	Mat element = getStructuringElement(MORPH_RECT,Size(15,15));
	Mat dsImg;
	erode(srcImg,dsImg,element);//腐蚀算法
	imshow("腐蚀后",dsImg);
	waitKey(20170301);
	return 0;
}