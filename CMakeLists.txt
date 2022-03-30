cmake_minimum_required(VERSION 3.21)
project(circulararray_sin_nombre)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(circulararray_sin_nombre
        circulararray.h
        main.cpp
        queue.h
        stack.h
        tester.h)
