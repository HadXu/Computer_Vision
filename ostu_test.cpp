#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


int Myostu(const Mat image)
{
	if (image.channels() != 1) {
		cout << "�Ҷ�ͼ��" << endl;
		return 0;
	}

	double Histogram[256] = { 0 };
	uchar *data = image.data;
	double totalNum = image.rows * image.cols;

	// ��ֲ�ֱ��ͼ
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			Histogram[data[i*image.step + j]]++;
		}
	}
	// ��һ��
	for (int i = 0; i < 256; i++)
		Histogram[i] /= totalNum;

	//  ȫ��ƽ���Ҷȷ���
	double mg=0.0;

	for (int i = 0; i < 256; i++)
		mg += i * Histogram[i];

	int threshold = 0;
	double maxVariance = 0;

	// ���������� �ۻ��� �ۻ���ֵ
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
	Mat img = imread("te.png");  //����Լ�ͼ���·�� 
	imshow("ԭͼ��", img);


	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	int T = Myostu(gray);
	cout << T << endl;
	Mat det;
	threshold(gray, det, T, 255, CV_THRESH_BINARY);

	imshow("det", det);


	//imshow("��ֵͼ��", gray);



	Mat otsu;
	threshold(gray, otsu, 0, 255, CV_THRESH_OTSU);

	imshow("dst", otsu);

	waitKey(0);
	return 0;
}







