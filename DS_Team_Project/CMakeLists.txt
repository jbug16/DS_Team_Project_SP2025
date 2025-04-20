cmake_minimum_required(VERSION 3.15)
project(DS_Team_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS_Team_Project
    minheap.cpp
    airport.cpp
    flight.cpp
    graph.cpp
    main.cpp)
