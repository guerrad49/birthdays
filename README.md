# Birthdays

---

## Summary
Birthdays is a C++ library for managing a database of birthdays on MacOS. It provides:
* a Person object to manage an individual's information
* a Book object which is a collection of Person objects

The user can add/remove entries to/from the Book as well filter and sort using build-in options.


## Documentation
Comprehensive documentation for this project is available through the API reference [page](https://birthdays-a06c45.gitlab.io/index.html).


## Build
To build the library, [CMake](https://cmake.org/) is required at minimum. The build can be configured with the following options which all default to `OFF`.
* `BUILD_EXAMPLES=ON|OFF` which compiles C++ examples.
* `BUILD_TESTS=ON|OFF` which compiles C++ unit tests. Requires [GoogleTest](https://google.github.io/googletest/quickstart-cmake.html).
* `BUILD_PYBIND=ON|OFF` which builds the Python front-end. Requires [pybind11](https://pybind11.readthedocs.io/en/stable/installing.html).
* `BUILD_DOCS=ON|OFF` which builds the Doxygen documentation. Requires [Doxygen](https://www.doxygen.nl/).

Birthdays can be built following the steps below:
```
    $ git clone https://github.com/guerrad49/birthdays.git
    $ cd birthdays
    $ mkdir build
    $ cmake ..
    $ make
```

## Installation
Below is an example of how to install the Birthdays library at a specified location. From the source directory:
```
    $ mkdir install
    $ cd build
    $ cmake .. -DCMAKE_INSTALL_PREFIX=../install
    $ make
    $ make install
```

The installed files will be located under the `install` directory created. Alternatively, the user can omit the `DCMAKE_INSTALL_PREFIX` option and use the default location.


## Python
In order to build the Python front-end, the user must first have installed
1. the Birthdays library (with `BUILD_PYBIND=ON`);
2. the python packages `build`, `wheel` and `scikit_build_core`.

Then, simply follow the steps below.
```
    $ python3 -m build --wheel
    $ ...several lines of output...
    $ python3 -m pip install dist/<package_name>.whl
    $ python3
    >>> import pyBirthdays
    >>> help(pyBirthdays)
```

The front-end has its own set of [unittests](https://docs.python.org/3/library/unittest.html) and examples nested under the `python` directory.
