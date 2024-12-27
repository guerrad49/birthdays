# Set the library variable.
set(LIB Birthdays)

add_library(${LIB} PUBLIC
    person.cpp
    )

target_include_directories(${LIB} PUBLIC
    # $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    # $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
    )

set_target_properties(${LIB}
    PROPERTIES
    LINKER_LANGUAGE CXX
)