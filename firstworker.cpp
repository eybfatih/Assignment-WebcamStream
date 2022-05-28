#include "firstworker.h"


/*
 * Simple constructor
 * name: worker name
 * imshow: function pointer to avoid race condition, shows image on the screen
 * print: function pointer to avoid race condition, shows text on the screen
 */
FirstWorker::FirstWorker(std::string name, int (*imshow)(cv::Mat, std::string), void (*print)(std::string message, std::string name)) {
    this->name = name;
    this->imshow = imshow;
    this->print = print;
}

/*
 *  W1 shall queue up to 10 frames.
 *  If the queue is full, the newest frames overwrite the oldest frame.
 */
void FirstWorker::push(cv::Mat *imagePtr) {
    cv::Mat image = imagePtr->clone();

    if (queue.size() < 10)
        queue.push_back(image);
    else {
        queue.pop_front();
        queue.push_front(image);
    }
}

/*
 * Simple thread function using functors
 */
void FirstWorker::operator()() {
    while (true) {
        // check if queue empty or not, it may necessary at the begining
        if (queue.empty()) {
            // avoid unnecessary waste of power thanks to sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        // get the oldest element of the queue
        cv::Mat image = queue.front();
        queue.pop_front();

        // process every 2nd frame, drop the other one
        secondFrameCounter += 1;
        if (secondFrameCounter % 2 == 0) {
            // avoid unnecessary waste of power thanks to sleep
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);

        // change rotation status after every 5 frames pushed
        fiftFrameCounter += 1;
        if (fiftFrameCounter % 5 == 0) {
            rotate += 1;
            if (rotate > 2)
                rotate = -1;
        }

        // apply rotation, Rotate the image clockwise 90 deg. after every 5 frames pushed
        if (rotate >= 0)
            cv::rotate(image, image, rotate);

        // show image on the screen
        this->imshow(image, this->name);
    }
}
