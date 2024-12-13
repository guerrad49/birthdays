cmake_minimum_required(VERSION 3.30)
set(LIB "Birthdays")
project(
    ${LIB}
    VERSION 1.0
    LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(include)
# add_subdirectory(tests)
add_subdirectory(python)

# add_executable(main main.cpp)

# target_link_libraries(main PUBLIC Birthdays)

# target_include_directories(main PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     )

# set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
