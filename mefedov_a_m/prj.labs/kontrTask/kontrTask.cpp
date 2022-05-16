#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() 
{
    cv::Mat kernel;
    cv::Point anchor;
    double delta;
    int ddepth;
    int kernel_size;
    cv::Mat img(450, 300, CV_8UC1);

    for (int i = 0; i < 150; i++)
    {
        for (int j = 0; j < 150; j++)
        {
            img.at<uchar>(i, j) = 0;                 
            img.at<uchar>(i, j + 150) = 127;             
            img.at<uchar>(i + 150, j) = 255;           
            img.at<uchar>(i + 300, j) = 127;           
            img.at<uchar>(i + 150, j + 150) = 0;        
            img.at<uchar>(i + 300, j + 150) = 255;       
        }

    }
    cv::circle(img, cv::Point(75, 75), 49, 127, cv::FILLED);
    cv::circle(img, cv::Point(75 + 149, 75), 49, 255, cv::FILLED);
    cv::circle(img, cv::Point(75, 75 + 149), 49, 0, cv::FILLED);
    cv::circle(img, cv::Point(75 + 149, 75 + 149), 49, 255, cv::FILLED);
    cv::circle(img, cv::Point(75, 75 + 298), 49, 0, cv::FILLED);
    cv::circle(img, cv::Point(75 + 149, 75 + 298), 49, 127, cv::FILLED);


    cv::imwrite("kontrTask.png", img);
    //cv::imshow("kontrTask", img);

    //cv::waitKey(0);

    cv::Mat kernel1 = (cv::Mat_<int>(2, 2) << 1, 0, 0, -1);
    cv::Mat I1;
    cv::filter2D(img, I1, -1, kernel1, cv::Point(-1, -1), 0.0);

    //cv::imshow("kontrTask", img);
    cv::imwrite("kontrTaskNew.png", I1);

    cv::Mat kernel2 = (cv::Mat_<int>(2, 2) << 0, 1, -1, 0);
    cv::Mat I2;
    cv::filter2D(img, I2, -1, kernel2, cv::Point(-1, -1), 0.0);

    //cv::imshow("kontrTask", img);
    cv::imwrite("kontrTaskNew2.png", I2);
    //cv::waitKey(0);

    cv::Mat geometrySred(img);
    for (int i = 0; i < img.rows; i++)
        for (int j = 0; j < img.cols; j++)
            geometrySred.at<uchar>(i, j) = sqrt(I1.at<uchar>(i, j) * I2.at<uchar>(i, j));

    cv::imwrite("geomtrySred.png", geometrySred);

    return 0;
}