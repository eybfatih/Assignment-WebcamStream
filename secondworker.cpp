#include "secondworker.h"


/*
 * Simple constructor
 * name: worker name
 * imshow: function pointer to avoid race condition, shows image on the screen
 * print: function pointer to avoid race condition, shows text on the screen
 */
SecondWorker::SecondWorker(std::string name, int (*imshow)(cv::Mat, std::string), void (*print)(std::string message, std::string name)) {
    this->name = name;
    this->imshow = imshow;
    this->print = print;
    srand (time(NULL));
}

/*
 * Pushing new image
 */
void SecondWorker::push(cv::Mat *imagePtr) {
    incomingFrame = *imagePtr;
}

/*
 * simulation of computational heavy algorithm
 */
void SecondWorker::LogitechFrameProcessingMagic(cv::Mat *image) {

    int sleepTimeInMs = rand() % 1000 + 500;

    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTimeInMs));
}

/*
 * Simple thread function using functors
 */
void SecondWorker::process() {

    // check if queue empty or not, it may necessary at the begining
    if (incomingFrame.empty()) {
        this->print("empty", this->name);
        inProcesses = false;
        return;
    }

    // get the newest frame for processing
    cv::Mat image = incomingFrame.clone();

    // simulation of magic function
    LogitechFrameProcessingMagic(&image);

    // calculate the mean value of left half side of the image
    cv::Size size = image.size();
    cv::Rect const box(0, 0, int(size.width/2), size.height);
    cv:: Mat roi = image(box);
    cv::cvtColor(roi, roi, cv::COLOR_BGR2GRAY);
    cv::Scalar m = cv::mean(roi);

    // insensitivity range assumed as a 255 @todo: change it later
    int insensitivityRange = 255;

    // Display a mirrored image if the mean pixel intensity of the left half of the frame is above half of the insensitivity range
    if (m[0] > insensitivityRange / 2)
        cv::flip(image, image, 1);

    // show image on the screen
    imshow(image, this->name);
}


/*
 * Simple thread function using functors
 */
void SecondWorker::operator()(float desiredProcessTime) {
    while (true) {

        auto prevClock = std::chrono::high_resolution_clock::now();

        // processes for w2
        process();

        auto nextClock = std::chrono::high_resolution_clock::now();

        // calculate the elapsed time taking for processing
        double processingTime = (nextClock - prevClock).count() / 1e9;
        // calculate the time it takes to sleep in seconds
        double sleepSecs = desiredProcessTime - processingTime;

        // make sure the loop time is under 1 second to sleep
        // following codes ensure that process incoming frames as close to every 1 second as possible
        if (sleepSecs > 0.0)
            std::this_thread::sleep_for(std::chrono::nanoseconds((int64_t)(sleepSecs * 1e9)));

        std::string s = std::to_string(sleepSecs);
        this->print("process time: " + std::to_string(processingTime) + " sleep time " + std::to_string(sleepSecs), this->name);

    }
}
