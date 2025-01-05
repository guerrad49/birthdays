#include <gtest/gtest.h>

#include "book.h"

namespace testing {

using namespace Birthdays;

class BookTest : public testing::Test {
protected:
    Book e_;  // Empty book.
    Book bb_;

    using Date = std::vector<uint16_t>;

    BookTest() : bb_{
        Person{"michael", "bluth", Date{1967,12,14}},
        Person{"lindsay", "bluth funke", Date{1964,1,31}},
        Person{"gob", "bluth", Date{1965,5,4}},
        Person{"george michael", "bluth", Date{1990,3,3}},
        Person{"maeby", "funke", Date{1990,9,22}},
        Person{"buster", "bluth", Date{1973,9,30}},
        Person{"tobias", "funke", Date{1964,4,4}},
        Person{"george", "bluth sr", Date{1947,8,5}},
        Person{"lucille", "bluth", Date{1948,1,30}}
    } {}
};

// Test constructors.
TEST_F(BookTest, ConstructorsTest) {
    EXPECT_EQ(e_.size(), 0);
    EXPECT_EQ(bb_.size(), 9);
}

// Test appending to book.
TEST_F(BookTest, AppendTest) {
    e_.append(Person{"steve", "holt"});
    EXPECT_EQ(e_.size(), 1);
    // Try to append repeat entry.
    bb_.append(Person{"maeby", "funke", Date{1990,9,22}});
    EXPECT_EQ(bb_.size(), 9);
}

// Test removing from book.
TEST_F(BookTest, RemoveTest) {
    bb_.remove(Person{"buster", "bluth", Date{1973,9,30}});
    EXPECT_EQ(bb_.size(), 8);
    // Try to remove entry not in book.
    bb_.remove(Person{"steve", "holt"});
    EXPECT_EQ(bb_.size(), 8);
    e_.remove(Person{"steve", "holt"});
    EXPECT_EQ(e_.size(), 0);
}

// Test sorting methods.
TEST_F(BookTest, SortingTest) {
    bb_.sort(bb_.SORT_CALENDAR);
    std::vector<size_t> order{8,1,3,6,2,7,4,5,0};
    EXPECT_EQ(bb_.ids, order);

    bb_.update_ages(Date{2024,12,31});
    bb_.sort(bb_.SORT_AGE);
    order = std::vector<size_t>{3,4,5,0,2,1,6,8,7};
    EXPECT_EQ(bb_.ids, order);

    bb_.sort(bb_.SORT_AGE, true);
    order = std::vector<size_t>{7,8,6,1,2,0,5,4,3};
    EXPECT_EQ(bb_.ids, order);
}

// Test filtering methods.
TEST_F(BookTest, FilteringTest) {
    bb_.filter(bb_.FILTER_MONTH, 9);
    std::vector<size_t> filtered{4,5};
    EXPECT_EQ(bb_.ids, filtered);

    bb_.reset_ids();
    bb_.filter(bb_.FILTER_LASTNAME, 'f');
    filtered = std::vector<size_t>{4,6};
    EXPECT_EQ(bb_.ids, filtered);

    bb_.reset_ids();
    bb_.filter(bb_.FILTER_FIRSTNAME, 'g');
    filtered = std::vector<size_t>{2,3,7};
    EXPECT_EQ(bb_.ids, filtered);
}

}  // End namespace testing.