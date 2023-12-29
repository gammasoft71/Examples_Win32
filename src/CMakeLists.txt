cmake_minimum_required(VERSION 3.20)

project(src)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Win32.System)
add_subdirectory(Win32.Gui)
add_subdirectory(Win32.UnitTests)
