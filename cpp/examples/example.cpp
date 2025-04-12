#include <iostream>
#include <vector>

#include "person.h"
#include "book.h"

int main() {
    using namespace birthdays;
    using Date = std::vector<uint16_t>;

    Book bb{
        Person{"ozwald", "cobblepot", Date{1976,5,31}},
        Person{"sophia",   "falcone", Date{1985,8,16}},
        Person{"victor",   "aguilar", Date{1997,10,26}},
        Person{   "eve",     "karlo", Date{1973,10,22}},
        Person{"johnny",      "viti", Date{1969,5,22}},
        Person{ "benny", "cobblepot", Date{2015,2,8}}
    };

    std::cout << "Book after initialization." << std::endl;
    bb.display();

    std::cout << std::endl;
    std::cout << "Update ages using 2024-12-31." << std::endl;
    bb.update_ages(Date{2024,12,31});
    bb.display();

    std::cout << std::endl;
    std::cout << "Using default sort (calendar)." << std::endl;
    bb.sort();
    bb.display();

    return 0;
}