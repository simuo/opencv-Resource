//注意：录制视频的尺寸大小由摄像头决定
#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	
	//配置视频
	Size s(640, 480);//定义视频的宽度和高度

	VideoWriter writer = VideoWriter("myvideo.avi",
		CV_FOURCC('M', 'J', 'P', 'G'), 25, s);//配置视频文件参数
	
	if (!writer.isOpened())//检查是否成功创建
	{
		cerr << "Can not create video file.\n" << endl;
		return -1;
	}

	//打开摄像头
	int c;
	VideoCapture inputVideo(1);
	Mat frame(s, CV_8UC3);

	//将摄像头读到的数据生成视频文件
	for (;;)
	{
		inputVideo >> frame;
		//将图像写入视频
		writer << frame;
		imshow("input", frame);
		c = waitKey(10);
		if (c == 27) break;

	}
	return 0;
}

