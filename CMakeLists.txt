# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)  # enable C++11 standard

project ("RPiComponents")

# Include sub-projects.
add_subdirectory ("src")