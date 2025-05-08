#pragma once

#include <vector>
#include <initializer_list>

#include "person.hh"


namespace birthdays {

/// @brief A vector-like container of Person objects.
class Book {
public:
    enum class SORT_METHOD {
        CALENDAR = 1,
        LASTNAME = 2,
        AGE = 3
    };

    enum class FILTER_METHOD {
        MONTH = 1,
        LASTNAME = 2,
        FIRSTNAME = 3
    };

    std::vector<size_t> ids;

    Book() = default;  // Default constructor.

    /// @brief Initializer list constructor.
    Book(std::initializer_list<Person> list);

    ~Book() = default;  // Default desctructor.

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

    /// @brief Update Person ages as of given date.
    void set_ages_as_of(const DateArray& date);

    /// @brief Prints book_ elements using ids as order.
    void display();

    /// @brief Create an id for every Person in book_.
    void reset_ids();

    size_t size() const { return book_.size(); }
    Person operator[](int index) const;

    auto begin() { return book_.begin(); }
    auto   end() { return book_.end(); }
    auto cbegin() const { return book_.cbegin(); }
    auto   cend() const { return book_.cend(); }

    /**
     * @brief Sort book_ ids.
     * @details Sorting options are given in SORT_METHOD enum.
     * @param method The method for sorting.
     * @param reverse The truth value for sorting in reverse.
     */
    void sort(
        SORT_METHOD method = SORT_METHOD::CALENDAR, 
        bool reverse = false
    );

    /**
     * @brief Filter book_ ids.
     * @details Filter options are given in FILTER_METHOD enum.
     * @param method The method for filtering.
     * @param value The value to filter by.
     */
    void filter(FILTER_METHOD method, char value);

private:
    std::vector<Person> book_;
};

}  // End namespace birthdays.
