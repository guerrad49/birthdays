#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "person.h"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_person_bind(py::module_ &m) {
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

        // Binds operator== to __eq__.
        .def(py::self == py::self)

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
            "Calculate Person's age.", 
            py::arg("today")
        )
        
        .def(py::pickle(
            [](const Person& p) { // __getstate__
                return py::make_tuple(
                    p.firstName(),
                    p.lastName(),
                    p.dob()
                );
            },
            [](const py::tuple& t) { // __setstate__
                if (t.size() != 3)
                    throw std::runtime_error("Invalid state!");
                std::string fn = t[0].cast<std::string>();
                std::string ln = t[1].cast<std::string>();
                std::vector<uint16_t> dob = t[2].cast<std::vector<uint16_t>>();
                return Person{fn, ln, dob};
            }
        ))
        ;
    }

} // End namespace pybirthdays.
