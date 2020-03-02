cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

add_executable(src
        affiliation_exposure.cpp
        decomposed_exposure.cpp
        network_exposure.cpp)
