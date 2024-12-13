# set(PYBIND11_FINDPYTHON ON)
set(Python3_EXECUTABLE
    /Library/Frameworks/Python.framework/Versions/3.10/bin/python3
    )
find_package(Python
    3.10
    COMPONENTS
    Interpreter Development
    REQUIRED
    )
find_package(pybind11 CONFIG REQUIRED)

link_libraries(${LIB})

pybind11_add_module(Person MODULE person_bindings.cpp)

target_include_directories(Person PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# target_link_libraries(Person PUBLIC pybind11::module)