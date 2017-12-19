#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int Myostu(const Mat image)
{
	if (image.channels() != 1) {
		cout << "灰度图像" << endl;
		return 0;
	}

	double Histogram[256] = { 0 };
	uchar *data = image.data;
	double totalNum = image.rows * image.cols;

	// 求分布直方图
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Histogram[data[i*image.step + j]]++;
		}
	}
	// 归一化
	for (int i = 0; i < 256; i++)
		Histogram[i] /= totalNum;

	//  全局平均灰度分量
	double mg=0.0;

	for (int i = 0; i < 256; i++)
		mg += i * Histogram[i];

	int threshold = 0;
	double maxVariance = 0;

	// 各个分量的 累积和 累积均值
	double pk = 0, mk = 0;

	for (int i = 0; i < 256; i++) {
		pk += Histogram[i];
		mk += Histogram[i] * i;

		double t = mg * pk - mk;

		double variance = t * t / (pk * (1 - pk));
		if (variance > maxVariance) {
			maxVariance = variance;
			threshold = i;
		}
	}
	return threshold;
}

int main()
{
	Mat img = imread("te.png");  //存放自己图像的路径 
	imshow("原图像", img);


	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	int T = Myostu(gray);
	cout << T << endl;
	Mat det;
	threshold(gray, det, T, 255, CV_THRESH_BINARY);

	imshow("det", det);


	//imshow("二值图像", gray);



	Mat otsu;
	threshold(gray, otsu, 0, 255, CV_THRESH_OTSU);

	imshow("dst", otsu);

	waitKey(0);
	return 0;
}







