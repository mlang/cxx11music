cmake_minimum_required(VERSION 2.8)
project(cxx11music CXX)
find_package(Boost REQUIRED)
add_definitions(-std=c++11)
add_executable(${CMAKE_PROJECT_NAME}test test.cpp)