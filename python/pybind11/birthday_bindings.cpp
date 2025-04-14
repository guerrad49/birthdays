#include <pybind11/pybind11.h>

namespace pybirthdays {

namespace py = pybind11;

void init_person_bind(py::module_ &m);
void init_enums_bind(py::module_ &m);
void init_book_bind(py::module_ &m);

PYBIND11_MODULE(pyBirthdays, m) {
    init_person_bind(m);
    init_enums_bind(m);
    init_book_bind(m);
}

}  // End namespace pybirthdays.
