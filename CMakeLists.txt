# CMake Version
cmake_minimum_required(VERSION 3.0.0)

# Project
project(CMakeTemplate VERSION 0.1.0)

include(CTest)
enable_testing()

# Executable files
add_executable(Main main.cpp)

# Project name and version
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
