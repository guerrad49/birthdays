#ifndef PERSON_HH
#define PERSON_HH

#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cctype>
#include <regex>
#include <sstream>
#include <iomanip>

namespace Birthdays {

class Person {
public:
    friend class Book;

    /// Default Constructor.
    Person() = default;

    /**
     * \brief Constructor.
     * \details Creates Person with given data.
     * \param first The first name.
     * \param last The last name.
     * \param dob The date-of-birth ISO vector <year,month,day>.
     */
    Person(
        const std::string& first, 
        const std::string& last, 
        const std::vector<uint16_t>& dob = std::vector<uint16_t> {0,0,0}
        );

    /// Destructor.
    ~Person() = default;

    std::string firstName() { return firstName_; }
    std::string lastName() { return lastName_; }
    std::string fullName() { return fullName_; }
    std::vector<uint16_t> dob() { return dob_; }
    uint8_t age() { return age_; }
    /// Get date-of-birth as ISO-formatted string.
    std::string dobStr();

    /**
     * \brief Format names to lowercase and underscores.
     * \param str The name string to format.
     * \return The formatted name.
     */
    std::string formatName(const std::string& str);
    void setFirstName(const std::string& str);
    void setLastName(const std::string& str);
    void setFullName();
    void setDoB(const std::vector<uint16_t>& v);

    /**
     * \brief Compute and set age using today's date.
     * \param tdy Today's date vector.
     */
    void setAge(const std::vector<uint16_t>& tdy);

protected:
    /**
     * \brief Determine equality between two class objects.
     * \param lhs The Person on left-hand side.
     * \param rhs The Person on right-hand side.
     * \return True/False
     */
    friend bool operator==(const Person &lhs, const Person &rhs);

private:
    std::string firstName_;
    std::string lastName_;
    std::string fullName_;
    std::vector<uint16_t> dob_{0,0,0};  // Default is min.
    uint8_t age_{255};  // Default is max.
};

// Definitions.

Person::Person(
    const std::string& first, 
    const std::string& last, 
    const std::vector<uint16_t>& dob
    ) {
    this->setFirstName(first);
    this->setLastName(last);
    this->setFullName();
    this->setDoB(dob);
}

std::string Person::dobStr() {
    std::stringstream ss;
    ss << dob_[0] << '-' 
        << std::setw(2) << std::setfill('0') << dob_[1]
        << '-'
        << std::setw(2) << std::setfill('0') << dob_[2];
    return ss.str();
}

std::string Person::formatName(const std::string& str) {
    std::string name{str};
    std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return std::regex_replace(name, std::regex(" "), "_");
}

void Person::setFirstName(const std::string& str) {
    firstName_ = formatName(str);
}

void Person::setLastName(const std::string& str) {
    lastName_ = formatName(str);
}

void Person::setFullName() {
    fullName_ = firstName_ + " " + lastName_;
}

void Person::setDoB(const std::vector<uint16_t>& v) {
    dob_ = v;
}

void Person::setAge(const std::vector<uint16_t>& tdy) {    
    uint16_t yearDiff = tdy[0] - dob_[0];
    uint8_t oneOrZero = 0;
    if ( (tdy[1] < dob_[1]) && (tdy[2] < dob_[2]) )
        oneOrZero = 1;
    age_ = yearDiff - oneOrZero;
}

bool operator==(const Person& lhs, const Person& rhs) {
    return (lhs.firstName_ == rhs.firstName_) && 
        (lhs.lastName_ == rhs.lastName_) &&
        (lhs.dob_ == rhs.dob_);
}

}  // End namespace Birthdays.

#endif  // PERSON_HH