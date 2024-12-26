#include <iostream>
#include <sstream>
#include <stdexcept>

#include "book.h"

namespace Birthdays {

void Book::append(const Person& p)
{
    for (const Person& q: book_)
    {
        if ( p == q )
        {
            std::cout << "Book.append: Person `" <<
                p.fullName() << "` already in Book!" << std::endl;
            return;
        }
    }

    book_.push_back(p);
}

void Book::remove(const std::string& first, const std::string& last)
{
    bool entryFound = false;
    uint16_t index = 0;

    for (const Person& q: book_)
    {
        if ( (first == q.firstName()) && (last == q.lastName()) )
        {
            entryFound = true;
            break;
        }
        index++;
    }

    if (!entryFound)
    {
        std::cout << "Book.remove: Person `" <<
            first << " " << last << "` not found!" << std::endl;
        return;
    }

    book_.erase(book_.begin() + index);
}

void Book::calc_ages(const std::vector<uint16_t>& tdy)
{
    for (Person q: book_)
        q.setAge(tdy);
}

void Book::display()
{
    std::cout << "Book Contents:" << std::endl;

    if (book_.empty())
    {
        std::cout << "   Empty book." << std::endl;
        return;
    }

    for (const size_t &i: indices)
    {
        std::stringstream ss;
        ss << std::setw(23) << book_[i].fullName()
            << std::setw(13) << book_[i].dobStr()
            << "   " << book_[i].age();
    }
}

void Book::reset_indices()
{
    indices.clear();
    indices.reserve(book_.size());
    for (size_t i = 0; i < book_.size(); ++i)
        indices.push_back(i);
}

// void Book::sort(int method)
// {
//     auto compare = [this, method] (int i, int j) -> bool
//     {
//         const Person &p = book_[i];
//         const Person &q = book_[j];

//         switch(method)
//         {
//             case SORT_LASTNAME:
//                 return p.lastName_ > q.lastName_;
//                 break;
//             case SORT_AGE:
//                 return p.age_ > q.age_;
//                 break;
//             default:  // SORT_CALENDAR
//                 // if month is same, compare day
//                 if (p.dateOfBirth_[1] == q.dateOfBirth_[1])
//                     return p.dateOfBirth_[2] < q.dateOfBirth_[2];
//                 // else compare month only
//                 return p.dateOfBirth_[1] < q.dateOfBirth_[1];
//                 break;
//         }
//     };

//     std::sort(indices.begin(), indices.end(), compare);
// }

// void Book::filter(int method, char value)
// {
//     std::vector<size_t> filtered;

//     switch(method)
//     {
//         // filter Persons with birthday in month `value`
//         case FILTER_MONTH:
//             for (const size_t &i: indices)
//                 if (book_[i].dateOfBirth_[1] == value)
//                     filtered.push_back(i);
//             break;
//         // filter Persons who's last name starts with `value`
//         case FILTER_LASTNAME:
//             for (const size_t &i: indices)
//                 if (book_[i].lastName_[0] == value)
//                     filtered.push_back(i);
//             break;
//         // filter Persons who's first name starts with `value`
//         case FILTER_FIRSTNAME:
//             for (const size_t &i: indices)
//                 if (book_[i].firstName_[0] == value)
//                     filtered.push_back(i);
//             break;
//     }
    
//     indices.clear();
//     indices = filtered;
// }

}  // End namespace Birthdays.