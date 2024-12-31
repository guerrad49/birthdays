#ifndef BOOK_H
#define BOOK_H

#include <initializer_list>

#include "person.h"

namespace Birthdays {

class Book {    
public:
    std::vector<size_t> ids;

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

    /// @brief Initializer list constructor.
    Book(std::initializer_list<Person> list);

    /**
     * @brief Appends Person to book_ list.
     * @details Performs a dedupe check first.
     * @param p The Person to append.
     */
    void append(const Person& p);

    /**
     * @brief Removes Person given names.
     * @details Remove is performed when full names match.
     * @param p The Person to remove.
     */
    void remove(const Person& p);

    void update_ages(const std::vector<uint16_t>& tdy);

    /// Prints book_ elements using ids as order.
    void display();

    /// Create an id for every Person in book_.
    void reset_ids();

    auto begin() { return book_.begin(); }
    auto end() { return book_.end(); }

    /**
     * @brief Sort book_ ids.
     * @details Sorting options are given in SORTING_METHOD enum.
     * @param method The method for sorting.
     */
    void sort(int method = SORT_CALENDAR);

    /**
     * @brief Filter book_ ids.
     * @details Filter options are given in FILTER_METHOD enum.
     * @param method The method for filtering.
     * @param value The value to filter by.
     */
    void filter(int method, char value);

private:
    std::vector<Person> book_;
};

}  // End namespace Birthdays.

#endif  // BOOK_H