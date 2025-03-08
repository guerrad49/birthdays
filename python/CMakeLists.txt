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

set(PYLIB "py${LIB}")
add_library(${PYLIB} MODULE
    person_bindings.cpp
    book_bindings.cpp
    pybirthdays.cpp
)

target_link_libraries(
    ${PYLIB} ${LIB} pybind11::module
)

set_target_properties(
    ${PYLIB} PROPERTIES
    PREFIX ""
    SUFFIC ".so"
)
