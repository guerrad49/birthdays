#include <iostream>
#include <vector>

#include "person.h"

int main() {
    using namespace Birthdays;

    Person p{"david", "guerra"};
    std::cout << p.fullName() << std::endl;
    
    Person q{"marisela", "melendez"};
    std::cout << q.fullName() << std::endl;

    return 0;
}