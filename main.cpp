#include <iostream>
#include <thread>

#include <mutex>
#include <opencv2/highgui.hpp>

#include "firstworker.h"
#include "secondworker.h"


// lock the threads to avoid race condition for the mutual outputs
std::mutex printMutex;
void sharedPrint(std::string message, std::string name) {

    printMutex.lock();
    std::cout << name << ": " <<message << std::endl;
    printMutex.unlock();
}


// lock the threads to avoid race condition for the mutual outputs
std::mutex imshowMutex;
int sharedImshow(cv::Mat image, std::string name) {

    imshowMutex.lock();

    cv::imshow(name, image);
    int key = cv::waitKey(10);

    imshowMutex.unlock();

    return key;
}


int main(int argc, char** argv) {

    int videoSource = 0;

    // set the video source using command line
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        if (i  == 1) {
            std::cout << "Video Source: " << argv[i] << std::endl;
            videoSource = atoi(argv[i]);
        }
    }

    sharedPrint("Press 'ESC' to Exit", "Main");

    cv::Mat frame;
    cv::VideoCapture cap = cv::VideoCapture(videoSource);

    // create worker1 and set paramteres as windowName, imshow function pointer, print pointer pointer
    FirstWorker *w1 = new FirstWorker("W1", sharedImshow, sharedPrint);
    // run thread for worker1
    std::thread w1Thread(std::ref(*w1));

    // create worker2 and set paramteres as windowName, imshow function pointer, print pointer pointer
    SecondWorker *w2 = new SecondWorker("W2", sharedImshow, sharedPrint);
    // run thread for worker2
    std::thread w2Thread(std::ref(*w2), 1.0);

    while(true) {
        cap.read(frame);

        // set the frames to workers
        w1->push(&frame);
        w2->push(&frame);

        int key = sharedImshow(frame, "image");

        // press ESC to exit
        if (key == 27)
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

//    w1Thread.join();
//    w2Thread.join();

    return 0;
}
