#Require cmake version 3.12
cmake_minimum_required(VERSION 3.12)

#Make sure we are using C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

#For Windows make sure that DLL is in the same folder as EXE
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Create projects
project(Engine VERSION 1.0)
project(Decay VERSION 1.0)

add_subdirectory(Engine)
add_subdirectory(Decay)