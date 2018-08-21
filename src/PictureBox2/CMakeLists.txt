cmake_minimum_required(VERSION 3.2)

project(PictureBox2 VERSION 1.0.0)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(PictureBox2 WIN32 PictureBox2.rc PictureBox2.h PictureBox2.cpp)
