#ifndef UTILS_HH
#define UTILS_HH

#include <array>
#include <string>
#include <cstdint>
#include <exception>


namespace birthdays {

class BirthdayError : public std::exception {
public:
    BirthdayError(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

inline bool is_valid_date(const std::array<uint16_t,3>& date) {
    uint16_t  year = date[0];
    uint16_t month = date[1];
    uint16_t   day = date[2];

    if (month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[] = {
        0, 31, 28, 31, 30, 31, 30, 
        31, 31, 30, 31, 30, 31
    };
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
        daysInMonth[2] = 29;

    return day <= daysInMonth[month];
}

inline bool is_valid_month(char c) {
    if (c < 1 || c > 12)
        return false;
    return true;
}

inline bool is_valid_letter(char c) {
    unsigned char lowerCase = std::tolower(c);
    if (lowerCase < 'a' || lowerCase > 'z')
        return false;
    return true;
}

}  // End namespace birthdays.

#endif  // UTILS_HH
