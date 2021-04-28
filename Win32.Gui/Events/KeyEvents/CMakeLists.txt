cmake_minimum_required(VERSION 3.0)
project(KeyEvents)

add_definitions(-DUNICODE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} WIN32 KeyEvents.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Win32.Gui/Events")
