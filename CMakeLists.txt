cmake_minimum_required(VERSION 3.17)
project(rhoamc)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        rhoam
        rhoam.cpp
        interpreter.cpp
        interpreter.h
)