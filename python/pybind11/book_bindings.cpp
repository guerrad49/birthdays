#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "book.h"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

void init_book_bind(py::module_ &m) {
    py::class_<Book>(m, "Book")
        .def(py::init<>())

        .def(py::init([](py::list values) {
            Book b;
            for (auto v: values)
                b.append(v.cast<const Person&>());
            return new Book{b};
            })
        )

        .def("__getitem__",
            [](const Book& b, int index) {
                return b[index];
            }
        )
        .def("__len__",
            [](const Book&b) {
                return b.size();
            }
        )

        .def_readwrite(
            "ids", 
            &Book::ids,
            "The id list corresponding to Book members."
        )

        .def(
            "append", 
            &Book::append, 
            "Appends a member to Book."
        )
        
        .def(
            "remove", 
            &Book::remove, 
            "Removes a member from Book."
        )
        
        .def(
            "update_ages", 
            &Book::update_ages, 
            "Updates ages of all members in Book."
        )

        .def(
            "display", 
            &Book::display,
            "Formatted print of Book using ids."
        )
        
        .def(
            "reset_ids", 
            &Book::reset_ids, 
            "Reset Book ids to initial state i.e. [0,1,2..]."
        )

        .def(
            "sort", 
            &Book::sort,
            py::arg("method") = 1, 
            py::arg("reverse") = false, 
            "Sort Book ids by method."
        )

        .def(
            "filter", 
            &Book::filter, 
            "Filter Book ids by method."
        );

    // TODO: Handle enums.
    }

}  // End namespace pybirthdays.