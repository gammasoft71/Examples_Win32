cmake_minimum_required(VERSION 3.2)

project(GroupBox VERSION 1.0.0)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(GroupBox WIN32 GroupBox.cpp)
