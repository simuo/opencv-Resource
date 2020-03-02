#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

void colorReduce(Mat &inputImage,Mat &outputImage,int div);

int main()
{
	Mat srcImage=imread("1.jpg");
	imshow("原始图像",srcImage);
	
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());
	
	colorReduce(srcImage,dstImage,32);
	 imshow("效果图",dstImage);
	 waitKey(20170301);
}

//使用指针访问像素
/* void colorReduce(Mat &inputImage,Mat &outputImage,int div)
{
	outputImage=inputImage.clone();
	int rowNumber=outputImage.rows;
	int colNumber=outputImage.cols*outputImage.channels();//列数*通道数=每一行的元素个数
	
	for(int i=0;i<rowNumber;i++)
	{
		uchar*data=outputImage.ptr<uchar>(i);
		for(int j=0;j<colNumber;j++)
		{
			data[j]=data[j]/div*div+div/2;
		}
	}
} */

//使用迭代器访问像素
/* void colorReduce(Mat &inputImage,Mat &outputImage,int div)
{
	outputImage=inputImage.clone();
	
	Mat_<Vec3b>::iterator begin=outputImage.begin<Vec3b>();
	Mat_<Vec3b>::iterator end=outputImage.end<Vec3b>();
	
	for(;begin!=end;++begin)
	{
		(*begin)[0]=(*begin)[0]/div*div+div/2;
		(*begin)[1]=(*begin)[1]/div*div+div/2;
		(*begin)[1]=(*begin)[2]/div*div+div/2;
	}
} */

//使用动态地址计算来访问
void colorReduce(Mat &inputImage,Mat &outputImage,int div)
{
	outputImage=inputImage.clone();
	int rowNumber=outputImage.rows;
	int colNumber=outputImage.cols;
	
	for(int i=0;i<rowNumber;i++)
	{
		for(int j=0;j<colNumber;j++)
		{
			outputImage.at<Vec3b>(i,j)[0]=outputImage.at<Vec3b>(i,j)[0]/div*div+div/2;
			outputImage.at<Vec3b>(i,j)[1]=outputImage.at<Vec3b>(i,j)[1]/div*div+div/2;
			outputImage.at<Vec3b>(i,j)[2]=outputImage.at<Vec3b>(i,j)[2]/div*div+div/2;
		}
	}
	
}