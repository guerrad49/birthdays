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

using DateArray = std::array<uint16_t,3>;

/// @brief Class to manage a Person's data.
class Person {
public:
    friend class Book;

    /// Default Constructor.
    Person() = default;

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
        const DateArray& dob
        );
    
    /// Destructor.
    ~Person() = default;

    std::string firstName() const { return firstName_; }
    std::string  lastName() const { return lastName_; }
    std::string  fullName() const { return fullName_; }
    DateArray dob() const { return dob_; }
    uint16_t age() const { return age_; }
    /// Get date-of-birth as ISO-formatted string.
    std::string dobStr() const;

    /**
     * @brief Format names to lowercase and underscores.
     * @param str The name string to format.
     * @return The formatted name.
     */
    std::string formatName(const std::string& str);
    void setFirstName(const std::string& str);
    void setLastName(const std::string& str);
    void setFullName();
    void setDoB(const DateArray& v);
    void setAge(const uint8_t& age) { age_ = age; }

    /**
     * @brief Calculate and set age using today's date.
     * @param tdy Today's date array.
     */
    void calcAge(const DateArray& tdy);

protected:
    /// Person string representation.
    friend std::ostream& operator<<(std::ostream& os, const Person& p);

    /// Determine equality between two Person objects.
    friend bool operator==(const Person& lhs, const Person& rhs);
    /// Compare using dob array comparison.
    friend bool operator<(const Person& lhs, const Person& rhs);
    friend bool operator>(const Person& lhs, const Person& rhs);
    friend bool operator<=(const Person& lhs, const Person& rhs);
    friend bool operator<=(const Person& lhs, const Person& rhs);

private:
    std::string firstName_;
    std::string lastName_;
    std::string fullName_;
    DateArray dob_;
    uint8_t age_{255};  // Default is max.
};

}  // End namespace birthdays.
