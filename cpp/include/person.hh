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

/// @brief Typedef for a date array.
using DateArray = std::array<uint16_t,3>;

/// @brief Class to manage a Person's data.
class Person {
public:
    /**
     * @enum Relationship.
     * @brief The relationship of a Person to the user.
     */
    enum class RELATIONSHIP {
        FRIEND = 1, 
        FAMILY = 2, 
        OTHER = 3
    };

    friend class Book;

    Person() = default;  // Default constructor.

    /**
     * @brief Constructor.
     * @details Creates Person with given data.
     * @param first The first name.
     * @param last The last name.
     * @param dob The date-of-birth array i.e. <year,month,day>.
     */
    Person(
        const std::string& first, 
        const std::string& last, 
        const DateArray& dob, 
        RELATIONSHIP rel = RELATIONSHIP::OTHER
        );
    
    ~Person() = default;  // Default destructor.

    std::string first_name() const { return firstName_; }
    std::string  last_name() const { return lastName_; }
    std::string  full_name() const { return fullName_; }
    DateArray dob() const { return dob_; }
    uint16_t age() const { return age_; }
    /// @brief Get date-of-birth as ISO-formatted string.
    std::string dob_str() const;
    RELATIONSHIP relationship() const { return rel_; }

    
    void set_first_name(const std::string& str);
    void set_last_name(const std::string& str);
    void set_full_name();
    void set_dob(const DateArray& date);
    void set_age(const uint8_t& age) { age_ = age; }
    void set_relationship(RELATIONSHIP rel) { rel_ = rel; }

    /// @brief Update age as of given date.
    void set_age_as_of(const DateArray& date);

protected:
    /// @brief Person string representation.
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
    /// The person's date-of-birth.
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
