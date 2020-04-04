cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(SGE LANGUAGES CXX)

# C++ properties
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define Release build type by default
if(NOT DEFINED CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif() 

message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(src)
add_subdirectory(tests)
