cmake_minimum_required(VERSION 3.14)
project(boids-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(boids-sim src/main.cpp)
target_link_libraries(boids-sim PRIVATE raylib)