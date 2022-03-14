#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


int main() {
        
    std::string video = "../../../data/videoMoney.mp4";
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
        std::cout << videocap1.get(cv::CAP_PROP_FRAME_COUNT) << " ";
    }

    cv::imshow("frame1", frame[0]);
    cv::imshow("frame2", frame[1]);
    cv::imshow("frame3", frame[2]);
   
    cv::waitKey(0);

     return 0;
}