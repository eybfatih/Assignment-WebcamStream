cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -pthread")

project(WebcamStream)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED) # this will generate the flag for CMAKE_THREAD_LIBS_INIT


include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(WebcamStream main.cpp firstworker.cpp secondworker.cpp)
target_link_libraries(WebcamStream ${OpenCV_LIBS})
target_link_libraries(WebcamStream ${CMAKE_THREAD_LIBS_INIT})

