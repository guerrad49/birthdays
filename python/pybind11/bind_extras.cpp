#include <pybind11/pybind11.h>

#include "book.hh"
#include "person.hh"
#include "utils.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_bind_error(py::module_ &m) {
    py::register_exception<BirthdayError>(m, "BirthdayError");
}

}  // End namespace pybirthdays.
