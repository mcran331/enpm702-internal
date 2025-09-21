cmake_minimum_required(VERSION 3.28)
project(assignments)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Common settings
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra)

# add assignment subdirectories as needed
add_subdirectory(assignment1)
