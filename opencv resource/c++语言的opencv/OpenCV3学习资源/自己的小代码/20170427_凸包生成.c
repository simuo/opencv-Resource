#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

int main()
{
	//打印提示信息
	system("color 04");
	printf("按【ESC】结束程序\n按任意键切换图片\n");
	//初始化图像矩阵以及随机变量
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	//相关变量的定义
	char key;//键值
	vector<Point>points;//使用类模板生成点的向量
	int count;
	vector<int>hull;//定义int向量类型的凸包

	//生成一系列随机坐标的点
	while (1)
	{
		image = Scalar::all(0);
		points.clear();
		count = (unsigned)rng % 100 + 3;//点的数量为3~102的随机数
		

							/*生成点向量组的各个点的坐标*/
		for (int i = 0; i<count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols/10, image.cols * 9/10);
			point.y = rng.uniform(image.rows/10, image.rows * 9/10);

			points.push_back(point);//将生成的坐标点推入点向量组
		}

		
		convexHull(Mat(points), hull, true);//生成凸包

		//绘制出随机颜色的点
		for (int i = 0; i<count; i++)
		{
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255),
				rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		}

		int hullcount = (int)hull.size();//凸包的边数
		Point point0 = points[hull[hullcount - 1]];

		//绘制凸包的边
		for (int i = 0; i<hullcount; i++)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255),
				2, LINE_AA);
			point0 = point;
		}

		imshow("凸包示例图", image);
		key = (char)waitKey();
		if (key == 27)break;
	}
	return 0;
}