#include <iostream>
#include <vector>

#include "person.hh"
#include "book.hh"

int main() {
    using namespace birthdays;

    Book bb{
        Person{"ozwald", "cobblepot", DateArray{1976,5,31}},
        Person{"sophia",   "falcone", DateArray{1985,8,16}},
        Person{"victor",   "aguilar", DateArray{1997,10,26}},
        Person{   "eve",     "karlo", DateArray{1973,10,22}},
        Person{"johnny",      "viti", DateArray{1969,5,22}},
        Person{ "benny", "cobblepot", DateArray{2015,2,8}}
    };

    std::cout << "Book after initialization." << std::endl;
    bb.display();

    std::cout << std::endl;
    std::cout << "Update ages using 2024-12-31." << std::endl;
    bb.update_ages(DateArray{2024,12,31});
    bb.display();

    std::cout << std::endl;
    std::cout << "Using default sort (calendar)." << std::endl;
    bb.sort();
    bb.display();

    return 0;
}