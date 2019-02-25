// FaceRecognition.cpp : Defines the entry point for the console application.
//

#ifndef LIB_CS
#include "stdafx.h"
#include <tchar.h>
#include <time.h>
#include <thread>
#include "TGMTfile.h"
#include "TGMTdebugger.h"
#include "TGMTutil.h"
#include "TGMTConfig.h"
#include "TextLocator.h"
#include "TGMTdraw.h"
#include <fcntl.h>
#include <io.h>

#define APP_NAME "TextLocator - http://thigiacmaytinh.com"

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
	std::vector<cv::Rect> boundRect;
	cv::Mat img_gray, img_sobel, img_threshold, element;
	cv::cvtColor(img, img_gray, CV_BGR2GRAY);
	cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
	cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
	element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3));
	cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
	std::vector< std::vector< cv::Point> > contours;
	cv::findContours(img_threshold, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{	
		if (contours[i].size() > 100)
		{
			cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
			cv::Rect appRect(boundingRect(cv::Mat(contours_poly[i])));
			if (appRect.width > appRect.height)
				boundRect.push_back(appRect);
		}
	}
	return boundRect;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void _tmain(int argc, _TCHAR* argv[])
{
	SET_CONSOLE_TITLE(APP_NAME);
	SET_CONSOLE_FONT("Arial");

	SetConsoleOutputCP(CP_UTF8);

	PrintUnicode(L"Chương trình nhận dạng text từ ảnh chung folder, sử dụng thư viện Tesseract\n");


	GetTGMTConfig()->LoadSettingFromFile();


	std::cout << "\n";

	std::vector<std::string> files = TGMTfile::GetImageFilesInDir(TGMTfile::GetCurrentDir());

	if (files.size() == 0)
	{
		PrintError("Can not find any file");
		return;
	}
	
	for (int i = 0; i < files.size(); i++)
	{
		clock_t startTimeReadText = clock();
		std::string f = files[i];
		PrintMessageGreen(f.c_str());


		cv::Mat mat = cv::imread(f);
		std::vector<cv::Rect> boxes = detectLetters(mat);
		
		TGMTdraw::DrawRectangles(mat, boxes, 2);
		std::string fileName = TGMTfile::GetFileName(f);
		ShowImage(mat, fileName.c_str());

		clock_t elapsed = clock() - startTimeReadText;
		std::wcout << "\n-----------------------\n";

	}

	cv::waitKey();
	PrintUnicode(L"Đã đọc xong tất cả ảnh");

	getchar();
}
#endif