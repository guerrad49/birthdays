#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "person.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_bind_person(py::module_ &m) {
    py::class_<Person>(m, "Person")
        .def(py::init<>())
        
        .def(py::init<
            const std::string &, 
            const std::string &, 
            const DateArray &
            >(),
            py::arg("first"), 
            py::arg("last"), 
            py::arg("dob")
        )
        
        .def("__repr__",
            [](const Person& self) {
                std::ostringstream oss;
                oss << self;
                return oss.str();
            }
        )

        // Binds operator== to __eq__.
        .def(
            py::self == py::self, 
            py::arg("other")
        )

        .def_property(
            "firstName", 
            &Person::first_name, 
            &Person::set_first_name,
            "The Person's (formatted) first name."
        )

        .def_property(
            "lastName", 
            &Person::last_name, 
            &Person::set_last_name, 
            "The Person's (formatted) last name."
        )
        
        .def_property(
            "fullName", 
            &Person::full_name, 
            &Person::set_full_name, 
            "The Person's full name. Joins first and last names."
        )
        
        .def_property(
            "dob", 
            &Person::dob, 
            &Person::set_dob, 
            "The Person's date-of-birth list i.e. [year,month,day]."
        )

        .def_property(
            "age", 
            &Person::age, 
            &Person::set_age, 
            "The Person's age."
        )

        .def(
            "set_age_as_of", 
            &Person::set_age_as_of, 
            "Update age as of given date.", 
            py::arg("date")
        )
        
        .def(py::pickle(
            [](const Person& self) { // __getstate__
                /* Tuple that fully encodes the object state. */
                return py::make_tuple(
                    self.first_name(),
                    self.last_name(),
                    self.dob()
                );
            },
            [](const py::tuple& t) { // __setstate__
                if (t.size() != 3)
                    throw std::runtime_error("Invalid state!");
                std::string fn = t[0].cast<std::string>();
                std::string ln = t[1].cast<std::string>();
                DateArray dob = t[2].cast<DateArray>();
                /* Return a newly created C++ instance. */
                return new Person{fn, ln, dob};
            }
        ))
        ;
    }

} // End namespace pybirthdays.
