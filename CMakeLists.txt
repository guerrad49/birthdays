cmake_minimum_required(VERSION 3.30)
project(
    practice
    VERSION 1.0
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)

# Create the target.
add_executable(${PROJECT_NAME} check.cpp)

# Link the library to executable.
target_link_libraries(${PROJECT_NAME} PUBLIC Birthdays)

# Specify library header locations.
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/lib"
    )

# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)

option(RUN_GTESTS "Build testing scripts." OFF)

if (RUN_GTESTS)
    add_subdirectory(tests/cpp)
endif()