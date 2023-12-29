cmake_minimum_required(VERSION 3.20)

project(ColoredTabPages)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

add_executable(ColoredTabPages WIN32 ColoredTabPages.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Win32.Gui/Others")
