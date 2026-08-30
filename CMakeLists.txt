cmake_minimum_required(VERSION 3.14)
project(VectorDB CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(vector_engine src/main.cpp)