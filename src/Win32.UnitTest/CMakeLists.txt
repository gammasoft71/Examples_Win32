cmake_minimum_required(VERSION 3.20)

project(Win32.UnitTest.Examples)

file(GLOB SUBDIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach (SUBDIR ${SUBDIRS})
  if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR} AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}/CMakeLists.txt")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIR}")
    set_target_properties(${SUBDIR} PROPERTIES FOLDER Win32.UnitTest)
  endif ()
endforeach ()
