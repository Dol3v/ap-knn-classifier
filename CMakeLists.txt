cmake_minimum_required(VERSION 3.22)
project(ap1_knn_classifier)

set(CMAKE_CXX_STANDARD 11)

add_executable(ap1_knn_classifier main.cpp metric.h csv.h csv.cpp)
