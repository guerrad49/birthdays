#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "book.h"

namespace py = pybind11;
using namespace Birthdays;

namespace python {

PYBIND11_MODULE(Book, m) {
    py::class_<Book>(m, "Book")
        // Constructors.
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

        .def_readwrite("ids", &Book::ids)

        .def("append", &Book::append)
        .def("remove", &Book::remove)
        
        .def("update_ages", &Book::update_ages)
        .def("display", &Book::display)
        .def("reset_ids", &Book::reset_ids)

        .def("sort", &Book::sort,
            py::arg("method") = 1,
            py::arg("reverse") = false
        )
        .def("filter", &Book::filter);

    // TODO: Handle enums.
    }

}  // End python namespace.