cmake_minimum_required(VERSION 3.15)
project(coursework)

set(CMAKE_CXX_STANDARD 14)

add_executable(coursework main.cpp Addition.cpp Addition.h Parsing.h Parsing.cpp Base.h Base.cpp ErrorCheck.cpp ErrorCheck.h)