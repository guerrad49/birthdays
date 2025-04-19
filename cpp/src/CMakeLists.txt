add_library(${LIB}
    person.cpp
    book.cpp
)

target_include_directories(${LIB} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/cpp/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

set_target_properties(${LIB}
    PROPERTIES
    LINKER_LANGUAGE CXX
)

# Installation.
install(TARGETS ${LIB} 
    EXPORT ${LIB}Targets
    DESTINATION lib
)

install(FILES 
    ${CMAKE_SOURCE_DIR}/cpp/include/book.hh 
    ${CMAKE_SOURCE_DIR}/cpp/include/person.hh 
    DESTINATION include)
