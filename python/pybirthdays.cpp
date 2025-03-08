#include <pybind11/pybind11.h>

namespace birthdays::python {

void bind_person_class(pybind11::module_ &m);
void bind_book_class(pybind11::module_ &m);

PYBIND11_MODULE(pyBirthdays, m) {
    bind_person_class(m);
    bind_book_class(m);
}

}  // End namespace birthdays::python.