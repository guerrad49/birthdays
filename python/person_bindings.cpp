#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "person.h"


namespace birthdays::python {

namespace py = pybind11;
using namespace birthdays;

void bind_person_class(pybind11::module_ &m) {
    py::class_<Person>(m, "Person")
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

        .def_property(
            "firstName", 
            &Person::firstName, 
            &Person::setFirstName,
            "The Person's (formatted) first name."
        )

        .def_property(
            "lastName", 
            &Person::lastName, 
            &Person::setLastName, 
            "The Person's (formatted) last name."
        )
        
        .def_property(
            "fullName", 
            &Person::fullName, 
            &Person::setFullName, 
            "The Person's full name. Joins first and last names."
        )
        
        .def_property(
            "dob", 
            &Person::dob, 
            &Person::setDoB, 
            "The Person's date-of-birth list i.e. [year,month,day]."
        )

        .def_property(
            "age", 
            &Person::age, 
            &Person::setAge, 
            "The Person's age."
        )

        .def(
            "calcAge", 
            &Person::calcAge, 
            "Calculate Person's age."
        );
    }

} // End namespace birthdays::python.