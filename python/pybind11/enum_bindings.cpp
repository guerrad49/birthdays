#include <pybind11/pybind11.h>

#include "book.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_enums_bind(py::module_ &m) {    
    py::enum_<Book::SORT_METHOD>(m, "SORT_METHOD")
        .value("SORT_CALENDAR", Book::SORT_METHOD::CALENDAR)
        .value("SORT_LASTNAME", Book::SORT_METHOD::LASTNAME)
        .value("SORT_AGE", Book::SORT_METHOD::AGE)
        .export_values()
        ;

    py::enum_<Book::FILTER_METHOD>(m, "FILTER_METHOD")
        .value("FILTER_MONTH", Book::FILTER_METHOD::MONTH)
        .value("FILTER_LASTNAME", Book::FILTER_METHOD::LASTNAME)
        .value("FILTER_FIRSTNAME", Book::FILTER_METHOD::FIRSTNAME)
        .export_values()
        ;
}

}  // End namespace pybirthdays.
