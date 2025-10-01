set(PROJECT snippets)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.20)
project(${PROJECT} CXX)

add_executable(${PROJECT}
        main.cpp
        log.h
        random.h
)
