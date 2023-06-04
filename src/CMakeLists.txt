cmake_minimum_required(VERSION 3.22)
project(tp3)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(LIB_DIRECTORY lib)

set(SOURCES_LIST
        ${LIB_DIRECTORY}/knapsack.hpp
        ${LIB_DIRECTORY}/algorithms.hpp
        ${LIB_DIRECTORY}/algorithms.cpp)

add_executable(tp3 main.cpp ${SOURCES_LIST})

target_include_directories (tp3 PRIVATE ${SOURCES_LIST})