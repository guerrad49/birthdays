#include <gtest/gtest.h>

#include "person.h"

namespace testing {

using namespace Birthdays;

class PersonTest : public testing::Test {
protected:
    Person p_;
    Person g_;

    using Date = std::vector<uint16_t>;

    PersonTest() : 
        g_{"George MiChael", "bluTh", Date{1988,6,7}} {}
};

// Test constructors.
TEST_F(PersonTest, ConstructorsTest) {
    Date zero{0,0,0};

    EXPECT_TRUE(p_.firstName().empty());
    EXPECT_EQ(p_.dob(), zero);

    Person lb{"lindsay", "bluth"};
    EXPECT_EQ(lb.fullName(), "lindsay bluth");
    EXPECT_EQ(lb.dob(), zero);
}
    
// Test formatting of names.
TEST_F(PersonTest, NameFormatting) {
    EXPECT_EQ(g_.firstName(), "george_michael");
    EXPECT_EQ(g_.fullName(), "george_michael bluth");
}

// Test age.
TEST_F(PersonTest, AgeTest) {
    // Warning: Changing "today" changes test results.
    Date today{2024,12,31};

    EXPECT_EQ(p_.age(), 255);
    p_.setDoB(Date{2024,1,1});
    p_.setAge(today);
    EXPECT_EQ(p_.age(), 0);

    g_.setAge(today);
    EXPECT_EQ(g_.age(), 36);
}

// Test comparisons.
TEST_F(PersonTest, ComparisonTest) {
    Person gmb{"georGe michaeL", "Bluth", Date{1988,6,7}};
    EXPECT_TRUE(g_ == gmb);

    gmb.setDoB(Date{1988,6,6});
    EXPECT_TRUE(g_ > gmb);
    gmb.setDoB(Date{1988,6,8});
    EXPECT_TRUE(g_ < gmb);
}

}  // End namespace testing.