#include <gtest/gtest.h>
#include "person.h"

class PersonTest : public testing:Test {
    PersonTest() {
        
    }
}


TEST(HelloTest, Basic) {
    EXPECT_EQ(7*6, 42);
}
