cmake_minimum_required(VERSION 3.20)

project(HelloWorldUnitTest VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DUNICODE)

add_library(HelloWorldUnitTest SHARED HelloWorldTest.cpp)
set_target_properties(HelloWorldUnitTest PROPERTIES FOLDER Win32.UnitTests/HelloWorldsUnitTests)
