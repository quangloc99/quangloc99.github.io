cmake_minimum_required(VERSION 3.22)
project(cf-1442a-clone)
include_directories(
    /home/darkkcyan/cp/contest-preparation  # path to testlib.h here
)

add_executable(solution solution.cpp)
add_executable(validator validator.cpp)
add_executable(gen-totally-random gen-totally-random.cpp)
add_executable(gen-v1 gen-v1.cpp)
add_executable(gen-v2 gen-v2.cpp)
add_executable(gen-v3 gen-v3.cpp)
add_executable(gen-v4 gen-v4.cpp)

# The following is used to comple all code fragments in my blogs
add_executable(all-fragments all-fragments.cpp) 
