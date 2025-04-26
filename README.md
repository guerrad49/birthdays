<h1 align="center">
<img src="logo/birthdays.png" width="500" height="200">
</h1>


## Library
Birthdays is a C++ library for managing a database of birthdays. It provides:
* a Person object to manage individual information
* a Book object which is a list-like container of Person objects


## Details
A Person is created by passing *First Name*, *Last Name*, and *Date-of-Birth* (yyy-mm-dd). Each Person can be added/removed to/from a Book. The Book can perform sorting and filtering for the user. Displaying the Book for the user computes each Person's age to provide up-to-date information. Ages are **not** stored in database.


## Pre-Requisites
At minimum, `CMake` is required to build the library. Optionally:
* `googletest` to build C++ unit tests
* `pybind11` to build Python interface


## Build
The user has the following CMake options which all default to `OFF`:
* `BUILD_EXAMPLES=ON|OFF` which compiles C++ examples
* `BUILD_TESTS=ON|OFF` which compiles C++ unit tests
* `BUILD_PYBIND=ON|OFF` which compiles Python interface

Birthdays can be built following the steps below:
```
    git clone https://github.com/guerrad49/lib_example.git
    cd lib_example
    mkdir build
    cmake ..
    make
```


## Python
The Python interface adds "state" functionality which can be used in conjuction with the `pickle` module. The user can use the pre-installed shared-object in the `install` directory by adding `/path/to/install` to their `PYTHONPATH`. The user can then run unittests and examples provided under the `python` directory. The `python/examples` provideds a tool using Birthdays efficiently. Run `/path/to/example/bday_tool.py -h` to see usage instructions.
