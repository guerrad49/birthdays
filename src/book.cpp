#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "book.h"

namespace Birthdays {

Book::Book(std::initializer_list<Person> list) : book_(list) {
    this->reset_ids();
}

void Book::append(const Person& p) {
    for (const Person& q: book_) {
        if (p == q) {
            std::cout << "INFO - Book.append: " << p
                << " already in Book!" << 
                std::endl;
            return;
        }
    }

    // Add next id.
    if (ids.empty())
        ids.push_back(0);
    else {
        auto max = std::max_element(ids.begin(), ids.end());
        ids.push_back(*max + 1);
    }

    book_.push_back(p);
}

void Book::remove(const Person& p) {
    bool entryFound = false;
    size_t index = 0;

    for (const Person& q: book_) {
        if ( p.fullName() == q.fullName() ) {
            entryFound = true;
            break;
        }
        index++;
    }

    if (!entryFound) {
        std::cout << "INFO - Book.remove: " << p
            << " not found!" << 
            std::endl;
        return;
    }

    ids.erase(ids.begin() + index);
    book_.erase(book_.begin() + index);
}

void Book::update_ages(const std::vector<uint16_t>& tdy) {
    for (Person& q: book_)
        q.setAge(tdy);
}

void Book::display() {
    std::cout << "Book Contents:" << std::endl;

    if (book_.empty()) {
        std::cout << "   Empty book." << std::endl;
        return;
    }

    for (const size_t& i: ids) {
        std::stringstream ss;
        ss << std::setw(23) << book_[i].fullName()
            << std::setw(13) << book_[i].dobStr()
            << "   " << book_[i].age();
        std::cout << ss.str() << std::endl;
    }
}

void Book::reset_ids() {
    ids.clear();
    ids.reserve(book_.size());
    for (size_t i = 0; i < book_.size(); ++i)
        ids.push_back(i);
}

Person Book::operator[](int index) const {
    if (index >= 0 && index < book_.size()) {
        return book_[index];
    } else {
        throw std::out_of_range("Index out of range");
    }
}

void Book::sort(int method, bool reverse) {
    auto compare = [this, method] (int i, int j) -> bool {
        const Person &p = book_[i];
        const Person &q = book_[j];

        switch(method) {
            case SORT_LASTNAME:
                return p.lastName_ < q.lastName_;
                break;
            case SORT_AGE:
                return p.age_ < q.age_;
                break;
            default:  // SORT_CALENDAR
                // If month is same, compare day.
                if (p.dob_[1] == q.dob_[1])
                    return p.dob_[2] < q.dob_[2];
                // Else compare month only.
                return p.dob_[1] < q.dob_[1];
                break;
        }
    };

    std::sort(ids.begin(), ids.end(), compare);
    
    if (reverse)
        std::reverse(ids.begin(), ids.end());
}

void Book::filter(int method, char value) {
    std::vector<size_t> filtered;

    switch(method) {
        // Filter birthdays on month `value`.
        case FILTER_MONTH:
            for (const size_t &i: ids)
                if (book_[i].dob_[1] == value)
                    filtered.push_back(i);
            break;
        // Filter last names starting with `value`.
        case FILTER_LASTNAME:
            for (const size_t &i: ids)
                if (book_[i].lastName_[0] == value)
                    filtered.push_back(i);
            break;
        // Filter first names starting with `value`.
        case FILTER_FIRSTNAME:
            for (const size_t &i: ids)
                if (book_[i].firstName_[0] == value)
                    filtered.push_back(i);
            break;
    }
    
    ids.clear();
    ids = filtered;
}

}  // End namespace Birthdays.