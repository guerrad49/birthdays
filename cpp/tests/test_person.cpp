#include <gtest/gtest.h>

#include "person.hh"


namespace tests {

using namespace birthdays;

class PersonTest : public testing::Test {
protected:
    Person p_;
    Person g_;

    using Date = std::vector<uint16_t>;

    PersonTest() : 
        g_{"George MiChael", "bluTh", Date{1990,3,3}} {}
};

/// Test constructors.
TEST_F(PersonTest, ConstructorsTest) {
    Date zero{0,0,0};

    EXPECT_TRUE(p_.firstName().empty());
    EXPECT_EQ(p_.dob(), zero);

    Person lb{"lindsay", "bluth"};
    EXPECT_EQ(lb.fullName(), "lindsay bluth");
    EXPECT_EQ(lb.dob(), zero);
}
    
/// Test formatting of names.
TEST_F(PersonTest, NameFormatting) {
    EXPECT_EQ(g_.firstName(), "george_michael");
    EXPECT_EQ(g_.fullName(), "george_michael bluth");
}

/// Test age.
TEST_F(PersonTest, AgeTest) {
    // Warning: Changing date changes test results.
    Date mockDate{2024,12,31};

    EXPECT_EQ(p_.age(), 255);  // Default.
    p_.setDoB(Date{2024,1,1});
    p_.calcAge(mockDate);
    EXPECT_EQ(p_.age(), 0);

    g_.calcAge(mockDate);
    EXPECT_EQ(g_.age(), 34);
}

/// Test comparisons.
TEST_F(PersonTest, ComparisonTest) {
    Person gmb{"georGe michaeL", "Bluth", Date{1990,3,3}};
    EXPECT_TRUE(g_ == gmb);

    gmb.setDoB(Date{1990,3,2});
    EXPECT_TRUE(g_ > gmb);
    gmb.setDoB(Date{1990,3,4});
    EXPECT_TRUE(g_ < gmb);
}

}  // End namespace tests.
