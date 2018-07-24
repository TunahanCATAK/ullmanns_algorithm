cmake_minimum_required(VERSION 3.10)
project(ullmanns_algorithm)

set(CMAKE_CXX_STANDARD 11)

add_executable(ullmanns_algorithm headers/Graph.hpp headers/Vertice.hpp main.cpp sources/Graph.cpp sources/Vertice.cpp)