#ifndef FIRSTWORKER_H
#define FIRSTWORKER_H

#include <iostream>
#include <thread>

#include <mutex>
#include <queue>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class FirstWorker
{
private:
    int secondFrameCounter = 0;
    int fiftFrameCounter = 0;
    int rotate = -1;
    std::string name = "";
    std::deque<cv::Mat> queue;
    int (*imshow)(cv::Mat, std::string);
    void (*print)(std::string message, std::string name);

public:
    FirstWorker(std::string name, int (*imshow)(cv::Mat, std::string), void (*print)(std::string, std::string));
    void push(cv::Mat *imagePtr);
    void operator()();
};

#endif // FIRSTWORKER_H
