cmake_minimum_required(VERSION 3.2)

project(PictureBox VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Logo.bmp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/Resources/Logo.bmp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Logo.bmp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/Resources/Logo.bmp COPYONLY)

add_executable(PictureBox WIN32 PictureBox.cpp)
