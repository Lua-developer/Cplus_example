// CPP Opencv 히스토그램 평활화
#include<opencv2/opencv.hpp>
#include<vector>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int ac, char** av) {
  // Mat 객체를 이용하여 이미지 텐서로 변환
	Mat img = imread("Hello.png");
  // Ycbcr 컨버팅, 결과 이미지 디폴트 생성자 호출
	Mat Ycbcr_img, result_img;
  // Ycbcr 컨버팅
	cvtColor(img, Ycbcr_img, COLOR_BGR2YCrCb);
	// 채널을 저장할 vector 생성
  vector<Mat> channels;
	split(Ycbcr_img, channels);
	// Ycbcr 이미지의 Y영역 밝기값을 평활화
	equalizeHist(channels[0], channels[0]);
  // 채널 합치기
	merge(channels, Ycbcr_img);
  // BGR채널로 변환
	cvtColor(Ycbcr_img, result_img, COLOR_YCrCb2BGR);
	imshow("test", result_img);
	waitKey(0);
}
