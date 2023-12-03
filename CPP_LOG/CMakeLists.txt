cmake_minimum_required(VERSION 3.26)
project(Code)

set(CMAKE_CXX_STANDARD 23)

#include_directories(Code/CPP_LOG/Logger)
add_executable(main main.cpp
        Logger/Logger.cpp)
