#include "opencv2/opencv.hpp"
#include "Card.h"
#include <iostream>
#include <io.h>

using namespace cv;
using namespace std;

int main() {
	// ���� ���� �迭 ����
	Mat ShapeArray[4];
	Mat NumberArray[13]; 
	// ���� ��� ����
	const char * SImagePATH = "TestImage/ShapeImage/";
	const char * NImagePATH = "TestImage/NumberImage/"; 
	//test
	// InputSample�Լ��� �̿��Ͽ� �ش� ����� ��� ������ �о�� �迭�� ����
	CARD::InputSample(ShapeArray, SImagePATH, 4);
	CARD::InputSample(NumberArray, NImagePATH, 13);
	// �迭�� ����� ������ �񱳸� �� �ϱ� ���� ��輱�� ���� �ڸ��� 
	CARD::CutSample(ShapeArray, 4);
	CARD::CutSample(NumberArray, 13);
	// �ҽ� �̹����� grayscale�� �ҷ��� �� �ҽ� ������ RGBŸ������ ��ȯ�ؼ� ��� ���� ����
	Mat srcImage = imread("TestImage/SampleImage/Diamond10.bmp", 0);
	if (srcImage.empty())
		return -1;
	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	//MatchImage�Լ��� �̿��� �ҽ� �̹����� ���ð� ���� ��
	//���� ����� ������ ã�� �� ������ �´� case���� ����
	int CaseShape, CaseNumber;
	CARD::MatchImage(srcImage, dstImage, ShapeArray, CaseShape, 4);
	CARD::MatchImage(srcImage, dstImage, NumberArray, CaseNumber, 13);
	// ��� ���� �Էµ� Text default �� ����
	String ShapeValue = "Nothing Found";
	String NumberValue = "Nothing Found";
	//����� case���� ���� Text Value ����
	CARD::CaseShape(CaseShape, ShapeValue);
	CARD::CaseNumber(CaseNumber, NumberValue);
	// ��� ���� �Էµ� Text Location ���� 
	Point ShapeLocation(200, 50);
	Point NumberLocation(200, 80);
	// Text �ռ�
	putText(dstImage, ShapeValue, ShapeLocation, 3, 1, Scalar::all(0), 2);
	putText(dstImage, NumberValue, NumberLocation, 3, 1, Scalar::all(0), 2);
	// ���� ���
	imshow(ShapeValue+NumberValue, dstImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}