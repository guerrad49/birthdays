#include <gtest/gtest.h>

#include "person.hh"


namespace tests {

using namespace birthdays;

class PersonTest : public testing::Test {
protected:
    Person p_;
    Person g_;

    PersonTest() : 
        g_{"George MiChael", "bluTh", DateArray{1990,3,3}} {}
};

/// Test formatting of names.
TEST_F(PersonTest, NameFormatting) {
    EXPECT_EQ(g_.firstName(), "george_michael");
    EXPECT_EQ(g_.fullName(), "george_michael bluth");
}

/// Test date-of-birth.
TEST_F(PersonTest, DobTest) {
    DateArray d1{0,0,0};
    EXPECT_THROW(p_.setDoB(d1), std::domain_error);

    DateArray d2{2025,1,32};
    EXPECT_THROW(p_.setDoB(d2), std::domain_error);

    DateArray d3{2025,2,29};
    EXPECT_THROW(p_.setDoB(d3), std::domain_error);

    DateArray d4{2025,13,1};
    EXPECT_THROW(p_.setDoB(d4), std::domain_error);

    DateArray d5{2024,2,29};  // Leap year.
    EXPECT_NO_THROW(p_.setDoB(d5));
}

/// Test age.
TEST_F(PersonTest, AgeTest) {
    // Warning: Changing date changes test results.
    DateArray mockDate{2024,12,31};

    EXPECT_EQ(p_.age(), 255);  // Default.
    p_.setDoB(DateArray{2024,1,1});
    p_.calcAge(mockDate);
    EXPECT_EQ(p_.age(), 0);

    g_.calcAge(mockDate);
    EXPECT_EQ(g_.age(), 34);
}

/// Test comparisons.
TEST_F(PersonTest, ComparisonTest) {
    Person gmb{"georGe michaeL", "Bluth", DateArray{1990,3,3}};
    EXPECT_TRUE(g_ == gmb);

    gmb.setDoB(DateArray{1990,3,2});
    EXPECT_TRUE(g_ > gmb);
    gmb.setDoB(DateArray{1990,3,4});
    EXPECT_TRUE(g_ < gmb);
}

}  // End namespace tests.
