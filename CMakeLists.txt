cmake_minimum_required(VERSION 3.16)
project(lab_6)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab_6 main.cpp data-struct/triangle.cpp data-struct/triangle.h obj-reader/objFileReader.cpp obj-reader/objFileReader.h work-with-bmp/bitmapRender.cpp work-with-bmp/bitmapRender.h)