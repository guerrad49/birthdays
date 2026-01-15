#include <gtest/gtest.h>

#include "person.hh"
#include "utils.hh"


namespace tests {

using namespace birthdays;

class PersonTest : public testing::Test {
protected:
    Person p_;
    Person g_;

    PersonTest() : 
        g_{
            "George MiChael", "bluTh", 
            DateArray{1990,3,3}, 
            Person::Relationship::FAMILY
        } {}
};

/// @brief Test formatting of names.
TEST_F(PersonTest, NameFormatting) {
    EXPECT_EQ(g_.first_name(), "george michael");
    EXPECT_EQ(g_.full_name(), "george michael bluth");
}

/// @brief Test relationship to user.
TEST_F(PersonTest, RelationshipTest) {
    EXPECT_EQ(p_.relationship(), Person::Relationship::OTHER);
    EXPECT_EQ(g_.relationship(), Person::Relationship::FAMILY);
}

/// @brief Test date-of-birth.
TEST_F(PersonTest, DobTest) {
    DateArray d1{0,0,0};
    EXPECT_THROW(p_.set_dob(d1), BirthdayError);

    DateArray d2{2025,1,32};
    EXPECT_THROW(p_.set_dob(d2), BirthdayError);

    DateArray d3{2025,2,29};
    EXPECT_THROW(p_.set_dob(d3), BirthdayError);

    DateArray d4{2025,13,1};
    EXPECT_THROW(p_.set_dob(d4), BirthdayError);

    DateArray d5{2024,2,29};  // Leap year.
    EXPECT_NO_THROW(p_.set_dob(d5));
}

/// @brief Test age.
/// @warning Changing *mockDate* changes test results.
TEST_F(PersonTest, AgeTest) {
    DateArray mockDate{2024,12,31};

    EXPECT_EQ(p_.age(), 255);  // Default.
    p_.set_dob(DateArray{2024,1,1});
    p_.set_age_as_of(mockDate);
    EXPECT_EQ(p_.age(), 0);

    g_.set_age_as_of(mockDate);
    EXPECT_EQ(g_.age(), 34);
}

/// @brief Test comparisons.
TEST_F(PersonTest, ComparisonTest) {
    Person gmb{"georGe michaeL", "Bluth", DateArray{1990,3,3}};
    EXPECT_TRUE(g_ == gmb);

    gmb.set_dob(DateArray{1990,3,2});
    EXPECT_TRUE(g_ > gmb);
    gmb.set_dob(DateArray{1990,3,4});
    EXPECT_TRUE(g_ < gmb);
}

}  // End namespace tests.
