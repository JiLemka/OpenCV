#include <opencv2/opencv.hpp>
#include <iostream>
#include <ctime>

int main() {

  cv::Mat img(180, 768, CV_8UC1);
  // draw dummy image
  img = 0;
  cv::Rect2d rc = {0, 0, 768, 60 };

  for (int i = 0; i < 180; i++)
	  for (int j = 0; j < 768; j++)
		  img.at<uchar>(i, j) = j / 3;

  cv::rectangle(img, rc, { 100 }, 1);
  rc.y += rc.height;

  unsigned int start_time = clock();
  cv::Mat tmp( img );
  tmp.convertTo(tmp, CV_32FC1, 1.0/255.0);
  cv::pow(tmp, 2.2, tmp);
  tmp.convertTo(tmp, CV_8UC1, 255.0);

  unsigned int end_time = clock();
  unsigned int search_time = end_time - start_time;
  std::cout << "G1 = " << search_time << " ms" << "\n";

  tmp(rc).copyTo(img(rc));

  cv::rectangle(img, rc, { 250 }, 1);
  rc.y += rc.height;

  unsigned int start = clock();

  for (int i = rc.y; i < 180; i++)
	  for (int j = 0; j < 768; j++)
		  img.at<uchar>(i, j) = pow(img.at<uchar>(i, j) / 255.0, 2.2) * 255.0;
  unsigned int end = clock();
  unsigned int search = end - start;
  std::cout << "G2 = " << search << " ms" << "\n";

  cv::rectangle(img, rc, { 150 }, 1);
  // save result
  cv::imwrite("lab01.png", img);
 
}
