#ifndef SECONDWORKER_H
#define SECONDWORKER_H

#include <iostream>
#include <thread>

#include <mutex>
#include <queue>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class SecondWorker
{
private:
    cv::Mat incomingFrame;
    int id;
    bool inProcesses = false;
    std::string name = "";
    int (*imshow)(cv::Mat image, std::string);
    void (*print)(std::string message, std::string name);

public:
    SecondWorker(std::string name, int (*imshow)(cv::Mat, std::string), void (*print)(std::string, std::string));
    void push(cv::Mat *imagePtr);
    void LogitechFrameProcessingMagic(cv::Mat *image);
    void process();
    void operator()(float desiredProcessTime);
};

#endif // SECONDWORKER_H
