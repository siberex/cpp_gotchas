set(PROJECT basics)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.20)
project(${PROJECT} CXX)

add_executable(${PROJECT}_strings
        strings.cpp
)

add_executable(${PROJECT}_variadic_template
        variadic_template.cpp
)