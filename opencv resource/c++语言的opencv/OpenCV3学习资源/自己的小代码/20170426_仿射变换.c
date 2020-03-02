#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

//定义窗口
#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【经过Warp后的图像】"
#define WINDOW_NAME3 "【经过Warp和Rotate后的图像】"


//主函数
int main()
{

	//读入图像
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	srcImage = imread("1.jpg", 1);
	if (!srcImage.data) {
		printf("读取图像失败\n"); return false;
	}
		dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols,
			srcImage.type());

		//三点法求得变换矩阵
		Point2f srcTriangle[3];
		Point2f dstTriangle[3];

		srcTriangle[0] = Point2f(0, 0);
		srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
		srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

		dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0),
			static_cast<float>(srcImage.rows*0.33));
		dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65),
			static_cast<float>(srcImage.rows*0.35));
		dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15),
			static_cast<float>(srcImage.rows*0.6));

		warpMat = getAffineTransform(srcTriangle, dstTriangle);//计算变换矩阵
		warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());

		//对图像进行放缩后旋转
		//先求得变换矩阵
		Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows/ 2);
		double angle = -30.0;
		double scale = 0.8;

		Mat roMat = getRotationMatrix2D(center, angle, scale);
		warpAffine(dstImage_warp, dstImage_warp_rotate,
			roMat, dstImage_warp.size());

		imshow(WINDOW_NAME1, srcImage);
		imshow(WINDOW_NAME2, dstImage_warp);
		imshow(WINDOW_NAME3, dstImage_warp_rotate);

		waitKey(20170301);
		return 0;

}
