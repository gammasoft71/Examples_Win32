cmake_minimum_required(VERSION 3.2)

project(HelloWorldMessage2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(${PROJECT_NAME} WIN32 HelloWorldMessage2.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Win32.Gui/HelloWorlds")
