#Require cmake version 3.12
cmake_minimum_required(VERSION 3.12)

#Make sure we are using C++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Create projects
project(Engine VERSION 1.0)
#project(Decay VERSION 1.0)

add_subdirectory(Engine)
add_subdirectory(Decay)