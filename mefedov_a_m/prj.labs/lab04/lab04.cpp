#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


int main() {

        cv::VideoCapture video("C:/Imagine/mefedov_a_m/data/videoMoney.mp4");

        if (!video.isOpened())
            std::cout << "Error openning video" << std::endl;
        else {
            int fps = video.get(5);
        }

        /*if (!video.isOpened())
        {
            return -1;
        }

        cv::Mat frame;
        for (int i = 0; i < video.get(cv::CAP_PROP_FRAME_COUNT) / 5; i++) {
            if (i == 2 || 3 || 4) {
                std::cout << "find" << "\n";
            }
        }
        */


        return 0;
}