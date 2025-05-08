import unittest

import pyBirthdays as bdays


class BookTest(unittest.TestCase):
    def setUp(self):
        self.eb = bdays.Book()
        self.bb = bdays.Book([
            bdays.Person("michael", "bluth", [1967,12,14]),
            bdays.Person("lindsay", "bluth funke", [1964,1,31]),
            bdays.Person("gob", "bluth", [1965,5,4]),
            bdays.Person("george michael", "bluth", [1990,3,3]),
            bdays.Person("maeby", "funke", [1990,9,22]),
            bdays.Person("buster", "bluth", [1973,9,30]),
            bdays.Person("tobias", "funke", [1964,4,4]),
            bdays.Person("george", "bluth sr", [1947,8,5]),
            bdays.Person("lucille", "bluth", [1948,1,30])
        ])

    def test_default_values(self):
        self.assertEqual(len(self.eb), 0)
        self.assertEqual(len(self.eb.ids), 0)

    def test_types(self):
        self.assertIsInstance(self.bb, bdays.Book)
        for p in self.bb:
            self.assertIsInstance(p, bdays.Person)

    def test_append(self):
        startSize = len(self.bb)
        p = bdays.Person("steve", "holt", [1990,1,10])
        self.bb.append(p)
        self.assertEqual(len(self.bb), startSize+1)
        self.assertEqual(len(self.bb.ids), startSize+1)

    def test_remove(self):
        startSize = len(self.bb)
        p = bdays.Person("gob", "bluth", [1965,5,4])
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
            bdays.SORT_CALENDAR,
            bdays.SORT_METHOD(1)
        )
        self.assertEqual(
            bdays.SORT_LASTNAME,
            bdays.SORT_METHOD(2)
        )
        self.assertEqual(
            bdays.FILTER_MONTH,
            bdays.FILTER_METHOD(1)
        )
        self.assertEqual(
            bdays.FILTER_FIRSTNAME,
            bdays.FILTER_METHOD(3)
        )

    def test_sort(self):
        self.bb.sort(bdays.SORT_CALENDAR)
        order = [8,1,3,6,2,7,4,5,0]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(bdays.SORT_LASTNAME)
        order = [5,3,2,8,0,1,7,4,6]
        self.assertEqual(self.bb.ids, order)

        self.bb.set_ages_as_of([2024,12,31])
        self.bb.sort(bdays.SORT_AGE)
        order = [3,4,5,0,2,1,6,8,7]
        self.assertEqual(self.bb.ids, order)

        self.bb.sort(bdays.SORT_AGE, True)
        reversed = order[::-1]
        self.assertEqual(self.bb.ids, reversed)

    def test_filter(self):
        self.assertRaises(
            bdays.BirthdayError, 
            self.bb.filter, 
            method = bdays.FILTER_MONTH, 
            value = 0
            )

        self.bb.filter(bdays.FILTER_MONTH, 9)
        filtered = [4,5]
        self.assertEqual(self.bb.ids, filtered)

        # Reset to avoid additional filtering.
        self.bb.reset_ids()
        
        self.assertRaises(
            bdays.BirthdayError, 
            self.bb.filter, 
            bdays.FILTER_LASTNAME, 
            '?'
        )
        
        self.bb.filter(bdays.FILTER_LASTNAME, 'b')
        filtered = [0,1,2,3,5,7,8]
        self.assertEqual(self.bb.ids, filtered)

        # Test additional filtering.
        self.bb.filter(bdays.FILTER_FIRSTNAME, 'g')
        filtered = [2,3,7]
        self.assertEqual(self.bb.ids, filtered)


if __name__ == "__main__":
    unittest.main()
