cmake_minimum_required(VERSION 3.28)
project(MPI_Evaluate)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(MPI_Evaluate main.cpp)

target_link_libraries(MPI_Evaluate PRIVATE MPI::MPI_CXX)