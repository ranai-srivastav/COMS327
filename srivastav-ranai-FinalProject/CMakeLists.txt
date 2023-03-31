cmake_minimum_required(VERSION 3.20)
project(FaceSwap)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

#find_library(lib_name, dlib)
#include_directories( ~/dlib-19.24/dlib)

set(CMAKE_CXX_STANDARD 17)

add_executable(FaceSwap main.cpp)

target_link_libraries(FaceSwap ${OpenCV_LIBS} )
#target_link_libraries(FaceSwap lib_name)
