import unittest

from pyBirthdays import Book, Person, BirthdayError


class BookTest(unittest.TestCase):
    def setUp(self):
        self.eb = Book()
        self.bb = Book([
            Person("michael", "bluth", [1967,12,14]),
            Person("lindsay", "bluth funke", [1964,1,31]),
            Person("gob", "bluth", [1965,5,4]),
            Person("george michael", "bluth", [1990,3,3]),
            Person("maeby", "funke", [1990,9,22]),
            Person("buster", "bluth", [1973,9,30]),
            Person("tobias", "funke", [1964,4,4]),
            Person("george", "bluth sr", [1947,8,5]),
            Person("lucille", "bluth", [1948,1,30])
        ])

    def test_default_values(self):
        self.assertEqual(len(self.eb), 0)
        self.assertEqual(len(self.eb.ids), 0)

    def test_types(self):
        self.assertIsInstance(self.bb, Book)
        for p in self.bb:
            self.assertIsInstance(p, Person)

    def test_append(self):
        startSize = len(self.bb)
        p = Person("steve", "holt", [1990,1,10])
        self.bb.append(p)
        self.assertEqual(len(self.bb), startSize+1)
        self.assertEqual(len(self.bb.ids), startSize+1)

    def test_remove(self):
        startSize = len(self.bb)
        p = Person("gob", "bluth", [1965,5,4])
        self.bb.remove(p)
        self.assertEqual(len(self.bb), startSize-1)
        self.assertFalse(p in self.bb)

    def test_set_ages_as_of(self):
        defaultAges = [p.age for p in self.bb]
        self.assertTrue( all(a == 255 for a in defaultAges) )

        self.bb.set_ages_as_of([2025,1,9])
        updatedAges = [p.age for p in self.bb]
        self.assertFalse( all(a == 255 for a in updatedAges) )

    def test_enums(self):
        self.assertEqual(
            Book.SORT_CALENDAR,
            Book.SORT_METHOD(1)
        )
        self.assertEqual(
            Book.SORT_LASTNAME,
            Book.SORT_METHOD(2)
        )
        self.assertEqual(
            Book.FILTER_MONTH,
            Book.FILTER_METHOD(1)
        )
        self.assertEqual(
            Book.FILTER_FIRSTNAME,
            Book.FILTER_METHOD(3)
        )

    def test_sort(self):
        self.bb.sort(Book.SORT_CALENDAR)
        order = [8,1,3,6,2,7,4,5,0]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(Book.SORT_LASTNAME)
        order = [5,3,2,8,0,1,7,4,6]
        self.assertEqual(self.bb.ids, order)

        self.bb.set_ages_as_of([2024,12,31])
        self.bb.sort(Book.SORT_AGE)
        order = [3,4,5,0,2,1,6,8,7]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(Book.SORT_AGE, True)
        reversed = order[::-1]
        self.assertEqual(self.bb.ids, reversed)

    def test_filter(self):
        self.assertRaises(
            BirthdayError, 
            self.bb.filter, 
            method = Book.FILTER_MONTH, 
            value = 0
            )

        self.bb.filter(Book.FILTER_MONTH, 9)
        filtered = [4,5]
        self.assertEqual(self.bb.ids, filtered)

        # Reset to avoid additional filtering.
        self.bb.reset_ids()
        
        self.assertRaises(
            BirthdayError, 
            self.bb.filter, 
            Book.FILTER_LASTNAME, 
            '?'
        )
        
        self.bb.filter(Book.FILTER_LASTNAME, 'b')
        filtered = [0,1,2,3,5,7,8]
        self.assertEqual(self.bb.ids, filtered)

        # Test additional filtering.
        self.bb.filter(Book.FILTER_FIRSTNAME, 'g')
        filtered = [2,3,7]
        self.assertEqual(self.bb.ids, filtered)


if __name__ == "__main__":
    unittest.main()
