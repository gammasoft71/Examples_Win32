cmake_minimum_required(VERSION 3.20)

project(StaticPicture)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
add_definitions(-DUNICODE)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Logo.bmp ${CMAKE_CURRENT_BINARY_DIR}/Debug/Resources/Logo.bmp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Logo.bmp ${CMAKE_CURRENT_BINARY_DIR}/Release/Resources/Logo.bmp COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Resources/Logo.bmp ${CMAKE_CURRENT_BINARY_DIR}/Resources/Logo.bmp COPYONLY)

add_executable(${PROJECT_NAME} WIN32 StaticPicture.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Win32.Gui/Controls")
