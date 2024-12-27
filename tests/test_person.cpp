#include <gtest/gtest.h>

#include "person.h"

using namespace Birthdays;

class PersonTest : public testing::Test {
protected:
    // PersonTest() {
    //     // g_.setFirstName("George MiChael");
    //     // g_.setLastName("bluTh");
    // }

    Person p_;
    Person* g_;
    virtual void SetUp() override {
        g_ = new Person("George MiChael", "bluTh");
    }

    // Person g_{"George MiChael", "bluTh"};
};

// Test default constructor.
TEST_F(PersonTest, DefaultConstructor) {
    EXPECT_TRUE(p_.firstName().empty());
    std::vector<uint16_t> zero{0,0,0};
    EXPECT_EQ(p_.dob(), zero);
}

// // Test formatting of names.
// TEST_F(PersonTest, NameFormatting) {
//     Person g{"George MiChael", "bluTh", std::vector<uint16_t>{1988,6,7}};
//     EXPECT_EQ(g.fullName(), "george_michael bluth");
// }

// // Test age.
// TEST_F(PersonTest, AgeTest) {
//     Person g{"George MiChael", "bluTh", std::vector<uint16_t>{1988,6,7}};
//     std::vector<uint16_t> today{2024,12,27};
//     g.setAge(today);
//     EXPECT_EQ(g.age(), 36);
//     EXPECT_EQ(p_.age(), 255);

//     Person baby("jane", "doe", std::vector<uint16_t>{2024,1,1});
//     baby.setAge(today);
//     EXPECT_EQ(baby.age(), 0);
// }
