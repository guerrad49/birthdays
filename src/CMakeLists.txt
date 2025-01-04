add_library(${LIB}
    person.cpp
    book.cpp
)

target_include_directories(${LIB} PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/include"
)

set_target_properties(${LIB}
    PROPERTIES
    LINKER_LANGUAGE CXX
)
