cmake_minimum_required(VERSION 3.30)

#===== Begin User Options =====#

option(BUILD_GTESTS "Build C++ tests." OFF)
option(BUILD_EXAMPLES "Build C++ examples." OFF)
option(BUILD_PYBIND "Build Python bindings." OFF)

#===== End User Options =====#

project(
    birthdays
    VERSION 0.1.0
    LANGUAGES CXX
)

# Enable C++20 or higher.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GNUInstallDirs)

# Global library name.
set(LIB Birthdays)

# Library source directory.
add_subdirectory(cpp/src)

# Build C++ examples.
if (BUILD_EXAMPLES)
    add_subdirectory(cpp/examples)
endif()

# Build C++ tests.
if (BUILD_GTESTS)
    add_subdirectory(cpp/tests)
endif()

# Build interface with Pybind.
if (BUILD_PYBIND)
    add_subdirectory(python/pybind11)
endif()
