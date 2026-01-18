#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include "person.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

// Helper function to wrap the class methods.
void define_person_methods(py::class_<Person>& cls) {
    cls.def("__repr__",
        [](const Person& self) {
            std::ostringstream oss;
            oss << self;
            return oss.str();
        }
    );

    // Binds operator== to __eq__.
    cls.def(
        py::self == py::self, 
        py::arg("other")
    );

    cls.def_property(
        "firstName", 
        &Person::first_name, 
        &Person::set_first_name,
        "The Person's (formatted) first name."
    );

    cls.def_property(
        "lastName", 
        &Person::last_name, 
        &Person::set_last_name, 
        "The Person's (formatted) last name."
    );
    
    cls.def_property(
        "fullName", 
        &Person::full_name, 
        &Person::set_full_name, 
        "The Person's full name. Joins first and last names."
    );
    
    cls.def_property(
        "dob", 
        &Person::dob, 
        &Person::set_dob, 
        "The Person's date-of-birth list i.e. [year,month,day]."
    );

    cls.def_property(
        "age", 
        &Person::age, 
        &Person::set_age, 
        "The Person's age."
    );

    cls.def_property(
        "relationship", 
        &Person::relationship, 
        &Person::set_relationship, 
        "The Person's relationship to user."
    );

    cls.def(
        "dobIso",
        &Person::dob_str,
        "Get date-of-birth in ISO format."
    );

    cls.def(
        "set_age_as_of", 
        &Person::set_age_as_of, 
        "Update age as of given date.", 
        py::arg("date")
    );
    
    cls.def(py::pickle(
        [](const Person& self) { // __getstate__
            /* Tuple that fully encodes the object state. */
            return py::make_tuple(
                self.first_name(), 
                self.last_name(), 
                self.dob(), 
                self.relationship()
            );
        },
        [](const py::tuple& t) { // __setstate__
            if (t.size() != 4)
                throw std::runtime_error("Invalid state!");
            std::string fn = t[0].cast<std::string>();
            std::string ln = t[1].cast<std::string>();
            DateArray dob = t[2].cast<DateArray>();
            Person::RELATIONSHIP rel = t[3].cast<Person::RELATIONSHIP>();
            /* Return a newly created C++ instance. */
            return new Person{fn, ln, dob, rel};
        }
    ));
}

void init_bind_person(py::module_ &m) {
    /// Register the class.
    py::class_<Person> person(m, "Person");

    /// Register RELATIONSHIP inside 'Person' scope.
    py::enum_<Person::RELATIONSHIP>(person, "RELATIONSHIP")
    .value("FAMILY", Person::RELATIONSHIP::FAMILY)
    .value("FRIEND", Person::RELATIONSHIP::FRIEND)
    .value("OTHER", Person::RELATIONSHIP::OTHER)
    .export_values()
    ;

    /// Wrap the constructors.
    person.def(py::init<>());
    
    person.def(py::init<
        const std::string &, 
        const std::string &, 
        const DateArray &, 
        Person::RELATIONSHIP
        >(),
        py::arg("first"), 
        py::arg("last"), 
        py::arg("dob"), 
        py::arg("relationship") = Person::RELATIONSHIP::OTHER
    );
    
    /// Call the helper function for wrapping methods.
    define_person_methods(person);
}

} // End namespace pybirthdays.
