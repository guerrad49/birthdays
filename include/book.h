#ifndef BOOK_H
#define BOOK_H

#include "person.h"

namespace Birthdays {

class Book {    
public:
    std::vector<size_t> indices;

    enum SORTING_METHOD
    {
        SORT_CALENDAR = 1,
        SORT_LASTNAME = 2,
        SORT_AGE = 3
    };

    enum FILTER_METHOD
    {
        FILTER_MONTH = 1,
        FILTER_LASTNAME = 2,
        FILTER_FIRSTNAME = 3
    };

    /// Default constructor.
    Book() = default;

    /**
     * \brief Appends Person to book_ list.
     * \details Performs a dedupe check first.
     * \param p The Person to append.
     */
    void append(const Person& p);

    /**
     * \brief Removes Person given names.
     * \details Remove is performed when both names match.
     * \param first The first name.
     * \param last The last name.
     */
    void remove(const std::string& first, const std::string& last);

    void calc_ages(const std::vector<uint16_t>& tdy);

    /// Prints book_ elements using indices as order.
    void display();

    /// Create an index for every element of book_.
    void reset_indices();

    auto begin() { return book_.begin(); }
    auto end() { return book_.end(); }
    // auto cbegin() const { return book_.cbegin(); }
    // auto cend() const { return book_.cend(); }

    /**
     * \brief Sort book_ indices.
     * \details Sorting options are given in SORTING_METHOD enum.
     * \param method The method for sorting.
     */
    void sort(int method = SORT_CALENDAR);

    /**
     * \brief Filter book_ indices.
     * \details Filter options are given in FILTER_METHOD enum.
     * \param method The method for filtering.
     * \param value The value to filter by.
     */
    void filter(int method, char value);

private:
    std::vector<Person> book_;
};

}  // End namespace Birthdays.

#endif  // BOOK_H