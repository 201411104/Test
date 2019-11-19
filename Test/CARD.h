#include "opencv2/opencv.hpp"
#include <vector>

using namespace cv;
using namespace std;

class CARD
{
public:

	static void InputSample(Mat Array[], const char * PATH, int size);

	static void CutSample(Mat Array[], int size);

	static void MatchImage(Mat srcImage, Mat dstImage, Mat Array[], int& Case, int size);

	static void CaseShape(int CaseNumber, String& ShqpeValue);

	static void CaseNumber(int CaseNumber, String& NumberValue);

	static vector<Mat> InputImage(const char* PATH);//�����Ҵ�

	static vector<Mat> OutputImage(vector<Mat> Input);//�����Ҵ�

	static void MyTemplate(Mat InputImage, Mat& OutputImage, vector<Mat> Input, int& Case);//�����Ҵ�
};