#include <pybind11/pybind11.h>

namespace pybirthdays {

namespace py = pybind11;

void init_bind_person(py::module_ &m);
void init_bind_enums(py::module_ &m);
void init_bind_book(py::module_ &m);
void init_bind_error(py::module_ &m);

PYBIND11_MODULE(pyBirthdays, m) {
    init_bind_person(m);
    init_bind_enums(m);
    init_bind_book(m);
    init_bind_error(m);
}

}  // End namespace pybirthdays.
