cmake_minimum_required(VERSION 3.30)
project(
    practice
    VERSION 1.0
    LANGUAGES CXX
    )

# Enable C++17 or higher.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create library.
add_subdirectory(src)

# Add testing.
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

# Add examples.
option(BUILD_EXAMPLES "Build the examples." OFF)
if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


# # Link the library to executable.
# target_link_libraries(${PROJECT_NAME} PUBLIC Birthdays)

# # Specify library header locations.
# target_include_directories(${PROJECT_NAME} PUBLIC
#     "${PROJECT_BINARY_DIR}"
#     "${PROJECT_SOURCE_DIR}/lib"
#     )

# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
