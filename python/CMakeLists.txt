set(Python3_EXECUTABLE
    /Library/Frameworks/Python.framework/Versions/3.10/bin/python3
    )
find_package(Python3
    3.10
    COMPONENTS
    Interpreter Development
    REQUIRED
    )
find_package(pybind11 CONFIG REQUIRED)

link_libraries(${PROJECT_NAME})

pybind11_add_module(person SHARED person_bindings.cpp)

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
