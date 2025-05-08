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
    set_first_name(first);
    set_last_name(last);
    set_full_name();
    set_dob(dob);
}

std::string Person::dob_str() const {
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << dob_[0] 
        << '-' 
        << std::setw(2) << std::setfill('0') << dob_[1]
        << '-'
        << std::setw(2) << std::setfill('0') << dob_[2];
    return ss.str();
}

std::string Person::format_name_(const std::string& str) {
    std::string name{str};
    std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return std::regex_replace(name, std::regex(" "), "_");
}

void Person::set_first_name(const std::string& str) {
    firstName_ = format_name_(str);
}

void Person::set_last_name(const std::string& str) {
    lastName_ = format_name_(str);
}

void Person::set_full_name() {
    fullName_ = firstName_ + " " + lastName_;
}

void Person::set_dob(const DateArray& date) {
    if (is_valid_date(date))
        dob_ = date;
    else
        throw BirthdayError("Invalid date.");
}

void Person::update_age(const DateArray& date) {
    if (!is_valid_date(date))
        throw BirthdayError("Invalid date.");

    uint16_t yearDiff = date[0] - dob_[0];
    uint16_t oneOrZero = 0;

    std::array<uint16_t,2> dateMD{date[1], date[2]};
    std::array<uint16_t,2> dobMD{dob_[1], dob_[2]};
    if ( dateMD < dobMD )
        oneOrZero = 1;

    age_ = yearDiff - oneOrZero;
}

std::ostream& operator<<(std::ostream& os, const Person& p) {
    os << "Person(" << p.first_name() 
        << "," << p.last_name() 
        << "," << p.dob_str() << ")";
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
