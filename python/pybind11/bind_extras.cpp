#include <pybind11/pybind11.h>

#include "book.hh"
#include "person.hh"
#include "utils.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_bind_enums(py::module_ &m) {    
    /// Export the enum RELATIONSHIP.
    py::enum_<Person::RELATIONSHIP>(m, "RELATIONSHIP")
        .value("FRIEND", Person::RELATIONSHIP::FRIEND)
        .value("FAMILY", Person::RELATIONSHIP::FAMILY)
        .value("OTHER", Person::RELATIONSHIP::OTHER)
        .export_values()
        ;

    /// Export the enum SORT_METHOD.
    py::enum_<Book::SORT_METHOD>(m, "SORT_METHOD")
        .value("SORT_CALENDAR", Book::SORT_METHOD::CALENDAR)
        .value("SORT_LASTNAME", Book::SORT_METHOD::LASTNAME)
        .value("SORT_AGE", Book::SORT_METHOD::AGE)
        .export_values()
        ;

    /// Export the enum FILTER_METHOD.
    py::enum_<Book::FILTER_METHOD>(m, "FILTER_METHOD")
        .value("FILTER_MONTH", Book::FILTER_METHOD::MONTH)
        .value("FILTER_LASTNAME", Book::FILTER_METHOD::LASTNAME)
        .value("FILTER_FIRSTNAME", Book::FILTER_METHOD::FIRSTNAME)
        .export_values()
        ;
}

void init_bind_error(py::module_ &m) {
    py::register_exception<BirthdayError>(m, "BirthdayError");
}

}  // End namespace pybirthdays.
