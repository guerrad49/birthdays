/// @file person.hh

#pragma once

#include <iostream>
#include <string>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cctype>
#include <iomanip>
#include <sstream>


namespace birthdays {

/**
 * @brief Represents a date as an array of three integers.
 * @details The format is [Year, Month, Day].
 */
using DateArray = std::array<uint16_t,3>;

/// @brief Class to manage a person's data.
class Person {
public:
    /**
     * @enum Relationship.
     * @brief The relationship of a Person to the user.
     */
    enum class RELATIONSHIP {
        FAMILY = 1, 
        FRIEND = 2, 
        OTHER = 3
    };

    friend class Book;

    Person() = default;  // Default constructor.

    /**
     * @brief Creates Person from given data.
     * @param firstName The first name.
     * @param lastName The last name.
     * @param dob The date-of-birth in ISO format.
     * @param rel 
     */
    Person(
        const std::string& firstName, 
        const std::string& lastName, 
        const DateArray& dob, 
        RELATIONSHIP rel = RELATIONSHIP::OTHER
        );
    
    ~Person() = default;  // Default destructor.

    /// Gets the first name string.
    std::string first_name() const { return firstName_; }
    /// Gets the last name string.
    std::string  last_name() const { return lastName_; }
    /// Gets the formatted full name string.
    std::string  full_name() const { return fullName_; }
    /// Gets the date-of-birth array.
    DateArray dob() const { return dob_; }
    /// Gets the date-of-birth as ISO-formatted string.
    std::string dob_str() const;
    /// Gets the age value.
    uint16_t age() const { return age_; }
    /// Gets the relationship value.
    RELATIONSHIP relationship() const { return rel_; }

    /// Sets the first name.
    void set_first_name(const std::string& str);
    /// Sets the last name.
    void set_last_name(const std::string& str);
    /// Sets the full name.
    void set_full_name();
    /// Sets the date-of-birth array.
    void set_dob(const DateArray& date);
    /// Sets the age value.
    void set_age(const uint8_t& age) { age_ = age; }
    /// Sets the relationship value.
    void set_relationship(RELATIONSHIP rel) { rel_ = rel; }

    /// Sets the age as of given date.
    void set_age_as_of(const DateArray& date);

protected:
    /// Person string representation.
    friend std::ostream& operator<<(std::ostream& os, const Person& p);

    friend bool operator==(const Person& lhs, const Person& rhs);
    friend bool operator!=(const Person& lhs, const Person& rhs);
    friend bool operator<(const Person& lhs, const Person& rhs);
    friend bool operator>(const Person& lhs, const Person& rhs);
    friend bool operator<=(const Person& lhs, const Person& rhs);
    friend bool operator>=(const Person& lhs, const Person& rhs);

private:
    /// The person's first name.
    std::string firstName_;
    /// The person's last name.
    std::string lastName_;
    /// The person's full name.
    std::string fullName_;
    /// The person's date-of-birth array.
    DateArray dob_;
    /// The person's age.
    uint8_t age_{255};
    /// The person's relationship to the user.
    RELATIONSHIP rel_{RELATIONSHIP::OTHER};

    /**
     * @brief Format names to lowercase and underscores.
     * @param str The name string to format.
     * @return The formatted name.
     */
    std::string to_lowercase_(const std::string& str);
};

}  // End namespace birthdays.
