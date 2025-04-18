#include <regex>
#include <stdexcept>

#include "person.hh"
#include "utils.hh"


namespace birthdays {

// Member functions.

Person::Person(
    const std::string& first, 
    const std::string& last, 
    const DateArray& dob
) {
    this->setFirstName(first);
    this->setLastName(last);
    this->setFullName();
    this->setDoB(dob);
}

std::string Person::dobStr() const {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << dob_[0] 
        << '-' 
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

void Person::setDoB(const DateArray& v) {
    if (is_valid_date(v))
        dob_ = v;
    else
        throw std::domain_error("ERROR: Invalid date.");
}

void Person::calcAge(const DateArray& tdy) {
    uint16_t yearDiff = tdy[0] - dob_[0];
    uint16_t oneOrZero = 0;

    std::array<uint16_t,2> subTdy{tdy[1], tdy[2]};
    std::array<uint16_t,2> subDob{dob_[1], dob_[2]};
    if ( subTdy < subDob )
        oneOrZero = 1;

    age_ = yearDiff - oneOrZero;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person(" << p.firstName() 
        << "," << p.lastName() 
        << "," << p.dobStr() << ")";
    return os;
}

// Non-member functions.

bool operator==(const Person& lhs, const Person& rhs) {
    return (lhs.firstName_ == rhs.firstName_) && 
        (lhs.lastName_ == rhs.lastName_) &&
        (lhs.dob_ == rhs.dob_);
}

bool operator<(const Person &lhs, const Person &rhs) {
    return lhs.dob_ < rhs.dob_;
}

bool operator>(const Person &lhs, const Person &rhs) {
    return rhs < lhs;
}

bool operator<=(const Person &lhs, const Person &rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Person &lhs, const Person &rhs) {
    return !(lhs < rhs);
}

}  // End namespace birthdays.
