cmake_minimum_required(VERSION 3.17)
project(rhoamc)



add_executable(
        rhoam
        rhoam.cpp
        interpreter.cpp
        interpreter.h
)
target_compile_features(rhoam PUBLIC cxx_std_14)