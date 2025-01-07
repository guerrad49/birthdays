set(Python3_EXECUTABLE
    /Library/Frameworks/Python.framework/Versions/3.10/bin/python3
)
set(pybind11_DIR 
    /Library/Frameworks/Python.framework/Versions/3.10/lib/python3.10/site-packages/pybind11/share/cmake/pybind11
)

find_package(Python3
    3.10
    COMPONENTS
    Interpreter Development
    REQUIRED
)

find_package(pybind11 CONFIG REQUIRED)

link_libraries(${LIB})

pybind11_add_module(Person MODULE person_bindings.cpp)
pybind11_add_module(Book MODULE book_bindings.cpp)

# target_link_libraries(person
#     PUBLIC
#     ${PYTHON_LIBRARIES}
#     pybind11::module
#     )

# set_target_properties(${PROJECT_NAME}
#     PROPERTIES
#     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
#     PREFIX ""
#     SUFFIX ".$(python3 -c 'import sys; print(sys.implementation.suffix)')"
#     )
