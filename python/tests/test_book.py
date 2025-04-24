import unittest

import pyBirthdays
from pyBirthdays import Person, Book


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
        # TODO: Test display empty book output.

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

    def test_update_ages(self):
        defaultAges = [p.age for p in self.bb]
        self.assertTrue( all(a == 255 for a in defaultAges) )

        self.bb.update_ages([2025,1,9])
        updatedAges = [p.age for p in self.bb]
        self.assertFalse( all(a == 255 for a in updatedAges) )

    def test_enums(self):
        self.assertEqual(
            pyBirthdays.SORT_CALENDAR,
            pyBirthdays.SORT_METHOD(1)
        )
        self.assertEqual(
            pyBirthdays.SORT_LASTNAME,
            pyBirthdays.SORT_METHOD(2)
        )
        self.assertEqual(
            pyBirthdays.FILTER_MONTH,
            pyBirthdays.FILTER_METHOD(1)
        )
        self.assertEqual(
            pyBirthdays.FILTER_FIRSTNAME,
            pyBirthdays.FILTER_METHOD(3)
        )

    def test_sort(self):
        self.bb.sort(pyBirthdays.SORT_CALENDAR)
        order = [8,1,3,6,2,7,4,5,0]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(pyBirthdays.SORT_LASTNAME)
        order = [5,3,2,8,0,1,7,4,6]
        self.assertEqual(self.bb.ids, order)

        self.bb.update_ages([2024,12,31])
        self.bb.sort(pyBirthdays.SORT_AGE)
        order = [3,4,5,0,2,1,6,8,7]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(pyBirthdays.SORT_AGE, True)
        reversed = order[::-1]
        self.assertEqual(self.bb.ids, reversed)

    def test_filter(self):
        self.bb.filter(pyBirthdays.FILTER_MONTH, 9)
        filtered = [4,5]
        self.assertEqual(self.bb.ids, filtered)

        # Reset to avoid additional filtering.
        self.bb.reset_ids()
        self.bb.filter(pyBirthdays.FILTER_LASTNAME, 'b')
        filtered = [0,1,2,3,5,7,8]
        self.assertEqual(self.bb.ids, filtered)

        # Test additional filtering.
        self.bb.filter(pyBirthdays.FILTER_FIRSTNAME, 'g')
        filtered = [2,3,7]
        self.assertEqual(self.bb.ids, filtered)


if __name__ == "__main__":
    unittest.main()
