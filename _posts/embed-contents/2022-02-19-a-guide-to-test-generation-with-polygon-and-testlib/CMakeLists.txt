cmake_minimum_required(VERSION 3.22)
project(cf-1442a-clone)
include_directories(
    /home/darkkcyan/cp/contest-preparation  # path to testlib.h here
)

add_executable(validator validator.cpp)
