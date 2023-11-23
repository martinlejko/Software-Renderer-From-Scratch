cmake_minimum_required(VERSION 3.24)
project(src)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        src
        main.cpp
        tgaimage.h
        tgaimage.cpp
        graphics.h
        graphics.cpp
        datatypes.h
        model.h model.cpp)
