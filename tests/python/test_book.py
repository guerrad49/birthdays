import unittest

from Person import Person
from Book import Book


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
        p = Person("steve", "holt")
        self.bb.append(p)
        self.assertEqual(len(self.bb), startSize+1)
        self.assertEqual(len(self.bb.ids), startSize+1)

    def test_remove(self):
        startSize = len(self.bb)
        p = Person("gob", "bluth", [1965,5,4])
        self.bb.remove(p)
        self.assertEqual(len(self.bb), startSize-1)

    def test_update_ages(self):
        defaultAges = [p.age for p in self.bb]
        self.assertTrue( all(a == 255 for a in defaultAges) )

        self.bb.update_ages([2025,1,9])
        updatedAges = [p.age for p in self.bb]
        self.assertFalse( all(a == 255 for a in updatedAges) )


if __name__ == "__main__":
    unittest.main()