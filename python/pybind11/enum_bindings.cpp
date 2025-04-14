#include <pybind11/pybind11.h>

#include "book.h"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_enums_bind(py::module_ &m) {    
    py::enum_<SORT_METHOD>(m, "SORT_METHOD")
        .value("SORT_CALENDAR", SORT_METHOD::CALENDAR)
        .value("SORT_LASTNAME", SORT_METHOD::LASTNAME)
        .value("SORT_AGE", SORT_METHOD::AGE)
        .export_values()
        ;

    py::enum_<FILTER_METHOD>(m, "FILTER_METHOD")
        .value("FILTER_MONTH", FILTER_METHOD::MONTH)
        .value("FILTER_LASTNAME", FILTER_METHOD::LASTNAME)
        .value("FILTER_FIRSTNAME", FILTER_METHOD::FIRSTNAME)
        .export_values()
        ;
}

}  // End namespace pybirthdays.
