
# This is just for IDE autocompletion, no need to build this with cmake
set(PROJECT cpp23)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.20)
project(${PROJECT} CXX)

add_executable(${PROJECT}_span
        ${CMAKE_CURRENT_LIST_DIR}/span.cpp
)
