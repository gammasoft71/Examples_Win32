cmake_minimum_required(VERSION 3.2)

project(RadioButton VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(RadioButton WIN32 RadioButton.cpp)
