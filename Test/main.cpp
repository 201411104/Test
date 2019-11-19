#include "opencv2/opencv.hpp"
#include "Card.h"
#include <iostream>
#include <io.h>

using namespace cv;
using namespace std;

int main() {
	// 샘플 저장 배열 선언
	Mat ShapeArray[4];
	Mat NumberArray[13]; 
	// 샘플 경로 설정
	const char * SImagePATH = "TestImage/ShapeImage/";
	const char * NImagePATH = "TestImage/NumberImage/"; 
	//test
	// InputSample함수를 이용하여 해당 경로의 모든 파일을 읽어와 배열에 저장
	CARD::InputSample(ShapeArray, SImagePATH, 4);
	CARD::InputSample(NumberArray, NImagePATH, 13);
	// 배열에 저장된 값들을 비교를 잘 하기 위해 경계선에 맞춰 자르기 
	CARD::CutSample(ShapeArray, 4);
	CARD::CutSample(NumberArray, 13);
	// 소스 이미지를 grayscale로 불러온 후 소스 영상을 RGB타입으로 변환해서 출력 영상에 저장
	Mat srcImage = imread("TestImage/SampleImage/Diamond10.bmp", 0);
	if (srcImage.empty())
		return -1;
	Mat dstImage;
	cvtColor(srcImage, dstImage, COLOR_GRAY2BGR);
	//MatchImage함수를 이용해 소스 이미지를 샘플과 비교한 후
	//가장 비슷한 영상을 찾아 그 영상의 맞는 case값을 저장
	int CaseShape, CaseNumber;
	CARD::MatchImage(srcImage, dstImage, ShapeArray, CaseShape, 4);
	CARD::MatchImage(srcImage, dstImage, NumberArray, CaseNumber, 13);
	// 출력 영상에 입력될 Text default 값 설정
	String ShapeValue = "Nothing Found";
	String NumberValue = "Nothing Found";
	//저장된 case값에 따라 Text Value 변경
	CARD::CaseShape(CaseShape, ShapeValue);
	CARD::CaseNumber(CaseNumber, NumberValue);
	// 출력 영상에 입력될 Text Location 지정 
	Point ShapeLocation(200, 50);
	Point NumberLocation(200, 80);
	// Text 합성
	putText(dstImage, ShapeValue, ShapeLocation, 3, 1, Scalar::all(0), 2);
	putText(dstImage, NumberValue, NumberLocation, 3, 1, Scalar::all(0), 2);
	// 영상 출력
	imshow(ShapeValue+NumberValue, dstImage);
	waitKey(0);
	destroyAllWindows();
	return 0;
}