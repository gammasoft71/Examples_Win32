cmake_minimum_required(VERSION 3.2)

project(TabControl VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(${PROJECT_NAME} WIN32 TabControl.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Win32.Gui/Containers")
