cmake_minimum_required(VERSION 3.0)
project(ApplicationIdle)

add_definitions(-DUNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(ApplicationIdle WIN32 ApplicationIdle.cpp)
