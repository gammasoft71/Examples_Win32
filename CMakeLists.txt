cmake_minimum_required(VERSION 3.20)

project(Win32)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Win32.System)
add_subdirectory(Win32.Gui)
add_subdirectory(Win32.UnitTests)
