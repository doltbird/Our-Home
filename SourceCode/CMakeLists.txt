cmake_minimum_required(VERSION 3.24)
project(main)

set(CMAKE_CXX_STANDARD 17)

add_executable(main.cpp FullTime.h FullTime.cpp Manager.cpp DormArea.cpp Building.cpp Date.h Date.cpp)
