#include <opencv2/opencv.hpp>
#include <cmath>

int main() {

	cv::Mat srcGreyImg = cv::imread("C:/Imagine/mefedov_a_m/data/cross_0256x0256.png", cv::IMREAD_GRAYSCALE);
	cv::Mat srcRgbImg = cv::imread("C:/Imagine/mefedov_a_m/data/cross_0256x0256.png");

	cv::imwrite("lab03_rgb.png", srcRgbImg);
	cv::imwrite("lab03_gre.png", srcGreyImg);

	cv::Mat LookUpTable(1, 256, CV_8UC1);

	uchar* m = LookUpTable.ptr();

	for (int x = 0; x < 256; ++x) {
		m[x] = 128 * (cos(x * 0.3) + 5);
	}

	cv::Mat img;
	cv::LUT(srcRgbImg, LookUpTable, img);
	cv::imwrite("lab03_rgb_res.png", img);

	cv::LUT(srcGreyImg, LookUpTable, img);
	cv::imwrite("lab03_gre_res.png", img);

	cv::Mat srcFunction(512, 512, CV_8UC1);

	for (int i = 1; i < 256; i++) {
		cv::line(srcFunction,
			cv::Point(i - 1 << 1, 511 - (((int)m[i - 1]) << 1)),
			cv::Point(i << 1, 511 - (((int)m[i]) << 1)),
			0, 1, 0);
	}

	cv::imwrite("lab03_viz_func.png", srcFunction);
}