#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

void colorReduction(cv::Mat& videocap1, int div = 64) {
    int totalRows = videocap1.rows;
    int totalColumns = videocap1.cols * videocap1.channels();

    for (int i = 0; i < totalRows; i++) {
        uchar* data = videocap1.ptr<uchar>(i);
        for (int j = 0; j < totalColumns; j++) {
            data[j] = data[j] / div * div + div / 2;
        }
    }
}


void Binarisation(cv::Mat& img, uchar threshold) {
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
    cv::threshold(img, img, threshold, 255, cv::THRESH_BINARY);
}


int main() {
        
    std::string video = "../../../data/video.MOV";
    cv::VideoCapture videocap1 = cv::VideoCapture(video);

    if (!videocap1.isOpened())
        std::cout << "Error openning video" << std::endl;

    cv::Mat frame[3];
    uint16_t framesNumber = videocap1.get(cv::CAP_PROP_FRAME_COUNT);

    for (int i = 0; i < framesNumber; ++i) {
        if (i == (framesNumber / 5) * 2)
            videocap1 >> frame[0];
        if (i == (framesNumber / 5) * 3)
            videocap1 >> frame[1];
        if (i == (framesNumber / 5) * 4)
            videocap1 >> frame[2];

        videocap1.grab();
        std::cout << videocap1.get(cv::CAP_PROP_POS_FRAMES) << " ";
    }


    for (int i = 0; i < 3; i++)
        cv::imwrite("frameSource" + std::to_string(i + 1) + ".png", frame[i]);

    cv::Mat Mask;
    for (int i = 0; i < 3; ++i) {
        colorReduction(frame[i]);
        cv::imwrite("frameCR" + std::to_string(i + 1) + ".png", frame[i]);
        Binarisation(frame[i], 160);
        cv::imwrite("frameBinar" + std::to_string(i + 1) + ".png", frame[i]);
        cv::morphologyEx(frame[i], Mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(40, 40)));
        cv::imwrite("frameMORPH" + std::to_string(i + 1) + ".png", frame[i]);

        cv::Mat centroids, stats, res;
        int n = cv::connectedComponentsWithStats(Mask, res, stats, centroids);
        std::vector<cv::Vec3b> labels(n);
        int max = 0, imax = 0;
        for (int j = 1; j < n; j++) {
            if (max < stats.at<int>(j, cv::CC_STAT_AREA)) {
                max = stats.at<int>(j, cv::CC_STAT_AREA);
                imax = j;
            }
        }

        for (int j = 0; j < n; j++)
            labels[j] = cv::Vec3b(0, 0, 0);

        labels[imax] = cv::Vec3b(255, 255, 255);
        cv::Mat exit(Mask.rows, Mask.cols, CV_8UC3);
        for (int i = 0; i < exit.rows; i++) {
            for (int j = 0; j < exit.cols; j++) {
                int label = res.at<int>(i, j);
                cv::Vec3b& pixel = exit.at<cv::Vec3b>(i, j);
                pixel = labels[label];
            }
        }
        cv::imwrite("Component" + std::to_string(i+1) + ".png", exit);
    }
     return 0;
}