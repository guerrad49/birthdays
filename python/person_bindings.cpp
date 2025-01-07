#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "person.h"

namespace py = pybind11;
using namespace Birthdays;

namespace python {

PYBIND11_MODULE(Person, m) {
    py::class_<Person>(m, "Person")
        // Constructors.
        .def(py::init<>())
        .def(py::init<
            const std::string &, 
            const std::string &, 
            const std::vector<uint16_t> &
            >(),
            py::arg("first") = "",
            py::arg("last") = "",
            py::arg("dob") = std::vector<uint16_t>{0,0,0}
        )
        
        .def("__repr__",
            [](const Person& p) {
                std::ostringstream oss;
                oss << p;
                return oss.str();
            }
        )

        .def_property("firstName", &Person::firstName, &Person::setFirstName)
        .def_property("lastName", &Person::lastName, &Person::setLastName)
        .def_property("fullName", &Person::fullName, &Person::setFullName)
        .def_property("dob", &Person::dob, &Person::setDoB)
        .def_property("age", &Person::age, &Person::setAge)

        .def("calcAge", &Person::calcAge);
    }

} // End namespace python.