cmake_minimum_required(VERSION 3.10)
#********************************************
project(iDefender)
#********************************************
include(cmake/common.cmake)
include(cmake/qt.cmake)
include(cmake/hook.cmake)
#********************************************
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(USE_BASE_UI ON)
#********************************************
add_subdirectory(src)
