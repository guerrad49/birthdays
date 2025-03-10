#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cctype>
#include <iomanip>
#include <sstream>


namespace birthdays {

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
     * @param dob The date-of-birth ISO vector <year,month,day>.
     */
    Person(
        const std::string& first, 
        const std::string& last, 
        const std::vector<uint16_t>& dob = std::vector<uint16_t> {0,0,0}
        );
    
    /// Destructor.
    ~Person() = default;

    std::string firstName() const { return firstName_; }
    std::string  lastName() const { return lastName_; }
    std::string  fullName() const { return fullName_; }
    std::vector<uint16_t> dob() { return dob_; }
    uint16_t age() { return age_; }
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
    void setDoB(const std::vector<uint16_t>& v);
    void setAge(const uint8_t& age) { age_ = age; }

    /**
     * @brief Calculate and set age using today's date.
     * @param tdy Today's date vector.
     */
    void calcAge(const std::vector<uint16_t>& tdy);

protected:
    /// Person string representation.
    friend std::ostream& operator<<(std::ostream& os, const Person& p);

    /// Determine equality between two Person objects.
    friend bool operator==(const Person& lhs, const Person& rhs);
    /// Compare using dob vector comparison.
    friend bool operator<(const Person& lhs, const Person& rhs);
    friend bool operator>(const Person& lhs, const Person& rhs);
    friend bool operator<=(const Person& lhs, const Person& rhs);
    friend bool operator<=(const Person& lhs, const Person& rhs);

private:
    std::string firstName_;
    std::string lastName_;
    std::string fullName_;
    std::vector<uint16_t> dob_{0,0,0};  // Default is min.
    uint8_t age_{255};  // Default is max.
};

}  // End namespace birthdays.

#endif  // PERSON_H