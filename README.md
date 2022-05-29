# Assignments-WebcamStream
Luxoft coding task WebCam stream

Please provide the solution as a public git repository with clear instructions on how to build and run the project. Please use C++14 or newer, opencv 3.0.0 or newer. The task should take 8-10hrs to code.

    1. Open camera feed.
    2. Create two workers: w1 and w2. Each worker shall perform its work in a separate thread.
    3. Create two windows for updates from W1 and W2. It is critical that the frame processing rules (in bold) for both workers are implemented exactly as described.

    • Worker w1:

        1. Process every 2nd frame.
        2. W1 shall queue up to 10 frames. If the queue is full, the newest frames overwrite the oldest frame.
        3. Rotate the image clockwise 90 deg. after every 5 frames pushed (1st-5th frame: no rotation, 6th-10th: 90 deg., 11th-15th: 180 deg., 16th-20th: 270 deg., 21th-25th: no rotation etc.). Display the image in gray scale.

    • Worker w2:

        1. Process incoming frames as close to every 1 second (but never more often) as possible.
        2. W2 shall only process 1 frame at a time, if frame is pushed when processing is in progress, incoming frame shall be dropped.
        3. Perform a computational-heavy algorithm called `LogitechFrameProcessingMagic` on a frame (simulate this by sleeping a random time between 500-1500 [ms]). Display a mirrored image if the mean pixel intensity of the left half of the frame is above half of the insensitivity range, otherwise display the original image.

    What pixel color format would fit the aforementioned requirements best and why?



# Usage
Tested on linux and windows using both Visual Studio and Qt

### 1. You may clone the repository directly to your workflow
It may be necessary to change ***videoSource***. Integer value that represents your camera.

### 2. Windows Build
Clone the github repository

    mkdir build
    cd build
    cmake -DOpenCV_DIR="C:/Users/fme/Documents/opencv/build" ../

Change the path above as your opencv dir

Open ***WebcamStream.sln*** with ***Visual Studio***

    Build All

***.exe*** file will be created under the ***Debug*** folder.

Open Command Promt and type:

    ./WebcamStream.exe 0

You can change the value ***0*** for select your camera.

### 2. Linux Build
Clone the github repository

    mkdir build
    cd build
    cmake ../
    make

***WebcamStream*** file will be created under the ***build*** folder.

Open Terminal and type:

    ./WebcamStream 0

You can change the value ***0*** for select your camera.
