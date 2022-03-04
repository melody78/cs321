cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

project(cs321-networking-lab)

add_executable(server server.cpp)
add_executable(client client.cpp)
