#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <vector>

#include "person.h"

namespace py = pybind11;

namespace Birthdays {

PYBIND11_MODULE(Birthdays, m) {
    py::class_<Person>(m, "Person")
        .def(py::init<>())
        .def(py::init<const std::string &, const std::string &>())
        .def(py::init<
            const std::string &, 
            const std::string &, 
            const std::vector<uint16_t> &
            >())
        .def_property("firstName", &Person::firstName, &Person::setFirstName)
        .def_property("lastName", &Person::lastName, &Person::setLastName)
        .def_property("fullName", &Person::fullName, &Person::setFullName)
        .def("dob", &Person::dob)
        .def("age", &Person::age)
        .def("dobStr", &Person::dobStr)
        .def("__repr__",
            [](Person& p) {
                return "Person(" + p.firstName() + "," + p.lastName() + ")";
            }
        );
    }

} // End namespace Birthdays.