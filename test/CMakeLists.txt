cmake_minimum_required(VERSION 3.20)

include(CTest)
find_package(catch2 REQUIRED)
enable_testing()

add_subdirectory(src)

