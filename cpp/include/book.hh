#ifndef BOOK_HH
#define BOOK_HH

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

    void update_ages(const DateArray& tdy);

    /// Prints book_ elements using ids as order.
    void display();

    /// Create an id for every Person in book_.
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

#endif  // BOOK_HH
