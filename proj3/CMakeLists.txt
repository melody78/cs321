cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)

# set the project name
project(Networking)

# add the executable
add_executable(server server.cpp)
add_executable(client client.cpp)
