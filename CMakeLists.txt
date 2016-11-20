cmake_minimum_required(VERSION 3.5)
project(DiscMeasurement)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(READ_FILES read_measurement.cc Timer.h FileReader.cc FileReader.h)
add_executable(read ${READ_FILES})