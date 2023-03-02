cmake_minimum_required(VERSION 3.24)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)
link_libraries(OpenMP::OpenMP_CXX)

add_executable(Lab2 main.cpp saveToFile.cpp quickSort.cpp)
