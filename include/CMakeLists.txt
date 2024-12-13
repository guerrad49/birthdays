add_library(${LIB} INTERFACE
    person.h
    book.h
    )

target_include_directories(${LIB} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
