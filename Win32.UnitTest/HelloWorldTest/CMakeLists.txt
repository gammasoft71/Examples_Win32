cmake_minimum_required(VERSION 3.20)

project(HelloWorldTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DUNICODE)

add_library(HelloWorldTest SHARED HelloWorldTest.cpp)
