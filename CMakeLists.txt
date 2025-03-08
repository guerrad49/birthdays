cmake_minimum_required(VERSION 3.30)

#===== Begin User Options =====#

option(BUILD_TESTING "Build C++ tests." OFF)
option(BUILD_EXAMPLES "Build C++ examples." OFF)
option(BUILD_PYBIND "Build Python bindings." OFF)

#===== End User Options =====#

project(
    practice
    VERSION 0.1.0
    LANGUAGES CXX
)

# Enable C++17 or higher.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create library.
set(LIB Birthdays)
add_subdirectory(src)

# Build tests with GTest.
if (BUILD_TESTING)
    add_subdirectory(tests/cpp)
endif()

# Build C++ examples.
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Build interface with Pybind.
if (BUILD_PYBIND)
    add_subdirectory(python)
endif()

# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
