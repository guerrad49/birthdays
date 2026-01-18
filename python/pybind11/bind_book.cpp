#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "book.hh"


namespace pybirthdays {

namespace py = pybind11;
using namespace birthdays;

// Helper function to wrap the class methods.
void define_book_methods(py::class_<Book>& cls) {
    cls.def("__getitem__",
        [](const Book& b, int index) {
            return b[index];
        }, 
        py::arg("index")
    );

    cls.def("__len__",
        [](const Book&b) {
            return b.size();
        }
    );

    cls.def_readwrite(
        "ids", 
        &Book::ids,
        "The id list corresponding to Book members."
    );

    cls.def(
        "append", 
        &Book::append, 
        "Appends a member to Book.", 
        py::arg("p")
    );
    
    cls.def(
        "remove", 
        &Book::remove, 
        "Removes a member from Book.", 
        py::arg("p")
    );
    
    cls.def(
        "set_ages_as_of", 
        &Book::set_ages_as_of, 
        "Updates ages of all members as of given date.", 
        py::arg("date")
    );

    cls.def(
        "display", 
        &Book::display,
        "Prints formatted Book ordered by ids."
    );
    
    cls.def(
        "reset_ids", 
        &Book::reset_ids, 
        "Reset Book ids to initial state i.e. [0,1,2..]."
    );

    cls.def(
        "sort", 
        &Book::sort, 
        py::arg("method") = Book::SORT_METHOD::CALENDAR, 
        py::arg("reverse") = false, 
        "Sort Book ids by method."
    );

    cls.def(
        "filter", 
        [](Book& b, Book::FILTER_METHOD method, py::object obj) {
            if (py::isinstance<py::int_>(obj)) {
                int val = obj.cast<int>();
                b.filter(method, val);
            }
            else if (py::isinstance<py::str>(obj)) {
                std::string val = obj.cast<std::string>();
                b.filter(method, val[0]);
            }
        }, 
        py::arg("method"), 
        py::arg("value"), 
        "Filter Book ids by method."
    );
}

void init_bind_book(py::module_ &m) {
    /// Register the class.
    py::class_<Book> book(m, "Book");

    /// Register SORT_METHOD inside 'Book' scope.
    py::enum_<Book::SORT_METHOD>(book, "SORT_METHOD")
        .value("SORT_CALENDAR", Book::SORT_METHOD::CALENDAR)
        .value("SORT_LASTNAME", Book::SORT_METHOD::LASTNAME)
        .value("SORT_AGE", Book::SORT_METHOD::AGE)
        .export_values()
        ;

    /// Register FILTER_METHOD inside 'Book' scope.
    py::enum_<Book::FILTER_METHOD>(book, "FILTER_METHOD")
        .value("FILTER_MONTH", Book::FILTER_METHOD::MONTH)
        .value("FILTER_LASTNAME", Book::FILTER_METHOD::LASTNAME)
        .value("FILTER_FIRSTNAME", Book::FILTER_METHOD::FIRSTNAME)
        .export_values()
        ;
    
    /// Wrap the constructors.
    book.def(py::init<>());

    book.def(py::init([](py::list values) {
        Book b;
        for (auto v: values)
            b.append(v.cast<const Person&>());
        return new Book{b};
        }), 
        py::arg("people")
    );

    /// Call the helper function for wrapping methods.
    define_book_methods(book);
}
        

}  // End namespace pybirthdays.
