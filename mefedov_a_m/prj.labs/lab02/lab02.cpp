#include <opencv2/opencv.hpp>
#include <vector>

int main() {

	//Качество 25%


	cv::Mat sourceImg = cv::imread("C:/Imagine/mefedov_a_m/data/cross_0256x0256.png");
	cv::imwrite("cross_0256x0256_025.jpg", sourceImg, {cv::IMWRITE_JPEG_QUALITY, 25});

	cv::Mat img025 = cv::imread("C:/Imagine/mefedov_a_m/build.vs.2019/prj.labs/lab02/cross_0256x0256_025.jpg");

	//Мозаика исходного изображения
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	int histW = 512, histH = 256;

	cv::Mat bgr[3];
	cv::split(sourceImg, bgr);
	cv::Mat color[3];
	cv::Mat sourceImgChange(512, 512, CV_8UC3);
	cv::Mat g = cv::Mat::zeros(cv::Size(256, 256), CV_8UC1);

	cv::merge(std::vector<cv::Mat>({ bgr[0], g, g }), color[0]);
	cv::merge(std::vector<cv::Mat>({ g, bgr[1], g }), color[1]);
	cv::merge(std::vector<cv::Mat>({ g, g, bgr[2] }), color[2]);

	sourceImg.copyTo(sourceImgChange(cv::Rect(0, 0, 256, 256)));
	color[1].copyTo(sourceImgChange(cv::Rect(0, 256, 256, 256)));
	color[2].copyTo(sourceImgChange(cv::Rect(256, 0, 256, 256)));
	color[0].copyTo(sourceImgChange(cv::Rect(256, 256, 256, 256)));
	cv::imwrite("cross_0256x0256_png_channels.png", sourceImgChange);

	//Мозаика jpeg изображения с качество 25%

	cv::Mat bgr025[3];
	cv::split(img025, bgr025);
	cv::Mat color025[3];
	cv::Mat imgChange025(512, 512, CV_8UC3);

	cv::merge(std::vector<cv::Mat>({ bgr025[0], g, g }), color025[0]);
	cv::merge(std::vector<cv::Mat>({ g, bgr025[1], g }), color025[1]);
	cv::merge(std::vector<cv::Mat>({ g, g, bgr025[2] }), color025[2]);

	img025.copyTo(imgChange025(cv::Rect(0, 0, 256, 256)));
	color[1].copyTo(imgChange025(cv::Rect(0, 256, 256, 256)));
	color[2].copyTo(imgChange025(cv::Rect(256, 0, 256, 256)));
	color[0].copyTo(imgChange025(cv::Rect(256, 256, 256, 256)));
	cv::imwrite("cross_0256x0256_jpg_channels.jpg", imgChange025);

	//Гистограмма для png

	cv::Mat bHist, gHist, rHist;

	int binW = cvRound((double)histW / histSize);

	cv::calcHist(&bgr[0], 1, 0, cv::Mat(), bHist, 1, &histSize, &histRange, true, false);
	cv::calcHist(&bgr[1], 1, 0, cv::Mat(), gHist, 1, &histSize, &histRange, true, false);
	cv::calcHist(&bgr[2], 1, 0, cv::Mat(), rHist, 1, &histSize, &histRange, true, false);

	cv::Mat blueHistImg(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat greenHistImg(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat redHistImg(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat rgbHistImg(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));

	cv::normalize(bHist, bHist, 0, blueHistImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(gHist, gHist, 0, greenHistImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(rHist, rHist, 0, redHistImg.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < histSize; i++) {
		cv::line(blueHistImg, cv::Point(binW*(i-1), histH - cvRound(bHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(bHist.at<float>(i))),
		cv::Scalar(255, 0, 0), 2, 8, 0);
		
		cv::line(greenHistImg, cv::Point(binW * (i - 1), histH - cvRound(gHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(gHist.at<float>(i))),
		cv::Scalar(0, 255, 0), 2, 8, 0);

		cv::line(redHistImg, cv::Point(binW * (i - 1), histH - cvRound(rHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(rHist.at<float>(i))),
		cv::Scalar(0, 0, 255), 2, 8, 0);
		
		cv::line(rgbHistImg, cv::Point(binW * (i - 1), histH - cvRound(bHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(bHist.at<float>(i))),
		cv::Scalar(255, 0, 0), 2, 8, 0);

		cv::line(rgbHistImg, cv::Point(binW * (i - 1), histH - cvRound(gHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(gHist.at<float>(i))),
		cv::Scalar(0, 255, 0), 2, 8, 0);

		cv::line(rgbHistImg, cv::Point(binW * (i - 1), histH - cvRound(rHist.at<float>(i - 1))),
		cv::Point(binW * (i), histH - cvRound(rHist.at<float>(i))),
		cv::Scalar(0, 0, 255), 2, 8, 0);
		
	}

	cv::Mat srcImgHist(histH * 2, histW * 2, CV_8UC3, cv::Scalar(255, 0, 0));

	rgbHistImg.copyTo(srcImgHist(cv::Rect(0, 0, histW, histH)));
	blueHistImg.copyTo(srcImgHist(cv::Rect(histW, histH, histW, histH)));
	greenHistImg.copyTo(srcImgHist(cv::Rect(0, histH, histW, histH)));
	redHistImg.copyTo(srcImgHist(cv::Rect(histW, 0, histW, histH)));
	cv::imwrite("cross_0256x0256_hists.png", srcImgHist);

	//Гистограмма для jpeg

	cv::Mat blueHist025, greenHist025, redHist025;

	cv::calcHist(&bgr025[0], 1, 0, cv::Mat(), blueHist025, 1, &histSize, &histRange, true, false);
	cv::calcHist(&bgr025[1], 1, 0, cv::Mat(), greenHist025, 1, &histSize, &histRange, true, false);
	cv::calcHist(&bgr025[2], 1, 0, cv::Mat(), redHist025, 1, &histSize, &histRange, true, false);

	cv::Mat blueHistImg025(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat greenHistImg025(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat redHistImg025(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));
	cv::Mat rgbHistImg025(histH, histW, CV_8UC3, cv::Scalar(255, 255, 255));

	cv::normalize(blueHist025, blueHist025, 0, blueHistImg025.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(greenHist025, greenHist025, 0, greenHistImg025.rows, cv::NORM_MINMAX, -1, cv::Mat());
	cv::normalize(redHist025, redHist025, 0, redHistImg025.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < histSize; i++) {
		cv::line(blueHistImg025, cv::Point(binW * (i - 1), histH - cvRound(blueHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(blueHist025.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);

		cv::line(greenHistImg025, cv::Point(binW * (i - 1), histH - cvRound(greenHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(greenHist025.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);

		cv::line(redHistImg025, cv::Point(binW * (i - 1), histH - cvRound(redHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(redHist025.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);

		cv::line(rgbHistImg025, cv::Point(binW * (i - 1), histH - cvRound(blueHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(blueHist025.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);

		cv::line(rgbHistImg025, cv::Point(binW * (i - 1), histH - cvRound(greenHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(greenHist025.at<float>(i))),
			cv::Scalar(0, 255, 0), 2, 8, 0);

		cv::line(rgbHistImg025, cv::Point(binW * (i - 1), histH - cvRound(redHist025.at<float>(i - 1))),
			cv::Point(binW * (i), histH - cvRound(redHist025.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}

	cv::Mat srcImgHist025(histH * 2, histW * 2, CV_8UC3, cv::Scalar(255, 0, 0));

	rgbHistImg025.copyTo(srcImgHist025(cv::Rect(0, 0, histW, histH)));
	blueHistImg025.copyTo(srcImgHist025(cv::Rect(histW, histH, histW, histH)));
	greenHistImg025.copyTo(srcImgHist025(cv::Rect(0, histH, histW, histH)));
	redHistImg025.copyTo(srcImgHist025(cv::Rect(histW, 0, histW, histH)));
	cv::imwrite("cross_0256x0256_hists025.jpg", srcImgHist025);

}