#include "opencv2/opencv.hpp"
#include "CARD.h"
#include <iostream>
#include <io.h>

using namespace cv;
using namespace std;

void CARD::InputSample(Mat Array[], const char * PATH, int size){
	string temp = format("%s*.bmp", PATH);
	const char * ctemp = temp.c_str();
	struct _finddata_t c_file;
	intptr_t hFile = _findfirst(ctemp, &c_file);

	if (hFile == -1) return;

	for (int i = 0 ; i < size ; i++) {
		string NewPATH = format("%s%s", PATH, &c_file.name);
		Array[i] = imread(NewPATH, IMREAD_GRAYSCALE);
		//cout << "Array["<<i<<"] = "<<NewPATH << endl;
		if (_findnext(hFile, &c_file) == -1)break;
	}
	_findclose(hFile);
	//system("pause");
	return;
}
//입력 경로에 있는 bmp파일을 입력한 size만큼 순차적으로 읽어 입력 Array에 imread 함수 이용하여 저장

void CARD::CutSample(Mat Array[], int size){
	Mat temp, temp2;
	
	for (int i = 0; i < size; i++) {
		Canny(Array[i], temp, 50, 100);
		threshold(temp, temp2, 128, 255, THRESH_BINARY);
		int rows = temp2.rows;
		int cols = temp2.cols;

		Point Max(0, 0);
		Point Min(cols, rows);

		for (int y = 0; y < rows; y++) {
			for (int x = 0; x < cols; x++) {
				if (temp2.at<uchar>(y, x) == 255 && x < Min.x)Min.x = x;
				else if (temp2.at<uchar>(y, x) == 255 && x > Max.x)Max.x = x;

				if (temp2.at<uchar>(y, x) == 255 && y < Min.y)Min.y = y;
				else if (temp2.at<uchar>(y, x) == 255 && y > Max.y)Max.y = y;
			}
		}
		Rect rect(Min.x, Min.y, (Max.x - Min.x), (Max.y - Min.y));
		Array[i] = Array[i](rect);
	}
	/*imshow("Canny", temp);
	waitKey(0);
	imshow("threshold", temp2);
	waitKey(0);
	imshow("rect", Array[size-1]);
	waitKey(0);*/
	return;
}
//입력 Array 내의 값을 Canny edge 검출 후 이진화한다
//그 이미지가 들어갈 수 있는 최소크기 사각형으로 이미지를 자른다.

void CARD::MatchImage(Mat srcImage, Mat dstImage, Mat Array[], int & Case, int size){
	double maxVal, Val = 0;
	Point maxLoc, Loc;
	Mat result;
	for (int i = 0; i < size; i++) {
		if (!Array[i].data)break;

		matchTemplate(srcImage, Array[i], result, TM_CCORR_NORMED);
		minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
		if (maxVal > Val) {
			Val = maxVal;
			Loc = maxLoc;
			Case = i;
		}
	}
	rectangle(dstImage, Loc,
		Point(Loc.x + Array[Case].cols, Loc.y + Array[Case].rows), Scalar(0, 0, 255), 2);
	//cout << Case << endl;
}
//matchtemplate함수를 이용해 입력 이미지를 배열 내의 샘플 이미지와 비교해 가장 비슷한 이미지를 찾고
//그 이미지의 크기에 맞는 빨간색 사각형 합성, 배열 주소값을 case 변수에 저장

void CARD::CaseShape(int CaseNumber, String& ShqpeValue) {
	switch (CaseNumber) {
	case(0):
		ShqpeValue = "Clover"; break;
	case(1):
		ShqpeValue = "Diamond"; break;
	case(2):
		ShqpeValue = "Heart"; break;
	case(3):
		ShqpeValue = "Spade"; break;
	default:
		break;
	}
}
// 저장된 case변수 별로 합성할 텍스트 value를 수정

void CARD::CaseNumber(int CaseNumber, String& NumberValue) {
	switch (CaseNumber) {
	case(0):
		NumberValue = "Ace"; break;
	case(1):
		NumberValue = "Two"; break;
	case(2):
		NumberValue = "Three"; break;
	case(3):
		NumberValue = "Four"; break;
	case(4):
		NumberValue = "Five"; break;
	case(5):
		NumberValue = "Six"; break;
	case(6):
		NumberValue = "Seven"; break;
	case(7):
		NumberValue = "Eight"; break;
	case(8):
		NumberValue = "Nine"; break;
	case(9):
		NumberValue = "Ten"; break;
	case(10):
		NumberValue = "Jack"; break;
	case(11):
		NumberValue = "Queen"; break;
	case(12):
		NumberValue = "King"; break;
	default:
		break;
	}
}
// 저장된 case변수 별로 합성할 텍스트 value를 수정

vector<Mat> CARD::InputImage(const char * PATH) {

	vector<Mat> v;
	string temp = format("%s*.bmp",PATH);
	const char * ctemp = temp.c_str();
	struct _finddata_t c_file;
	intptr_t hFile = _findfirst(ctemp, &c_file);

	if (hFile == -1) return v; 

	for (int i = 0 ;; i++) {
		string ShapePATH = format("%s%s", PATH, &c_file.name);
		v.push_back(imread(ShapePATH, 0));
		if (_findnext(hFile, &c_file) == -1)break;
	}
	_findclose(hFile);
	return v;
}
//동적 할당
vector<Mat> CARD::OutputImage(vector<Mat> Input) {
	vector<Mat> v;
	Mat trans, trans2;
	for (int i = 0 ; i < Input.size() ; i++){
		Canny(Input[i], trans2, 50, 100);
		threshold(trans2, trans, 128, 255, THRESH_BINARY);

		int height = trans.rows;
		int width = trans.cols;
		Point Max(0, 0);
		Point Min(trans.cols, trans.rows);

		for (int y = 0; y < trans.rows; y++) {
			for (int x = 0; x < trans.cols; x++) {
				if (trans.at<uchar>(y, x) == 255 && x < Min.x) Min.x = x;
				else if (trans.at<uchar>(y, x) == 255 && x > Max.x) Max.x = x;

				if (trans.at<uchar>(y, x) == 255 && y < Min.y) Min.y = y;
				else if (trans.at<uchar>(y, x) == 255 && y > Max.y) Max.y = y;
			}//경계값 사각형 검출
		}
		Rect rect(Min.x, Min.y, (Max.x - Min.x), (Max.y - Min.y));
		v.push_back(Input[i](rect));
	}
	return v;
}
//동적 할당
void CARD::MyTemplate(Mat InputImage, Mat& OutputImage, vector<Mat> Input, int& Case) {
	double maxVal, Val = 0;
	Point maxLoc, Loc;
	Mat result;
	for (int i = 0 ; i < Input.size() ; i++) {
		if (!Input[i].data) break;
		matchTemplate(InputImage, Input[i], result, TM_CCORR_NORMED);
		minMaxLoc(result, NULL, &maxVal, NULL, &maxLoc);
		if (maxVal > Val) {
			Val = maxVal;
			Loc = maxLoc;
			Case = i;
		}
	}
	rectangle(OutputImage, Loc,
		Point(Loc.x + Input[Case].cols, Loc.y + Input[Case].rows), Scalar(0, 0, 255), 2);
}
//비교 후 사각형 그리기