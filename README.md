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
