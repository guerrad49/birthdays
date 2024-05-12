import unittest
from datetime import date

from birthdays import Person, BirthdayBook, FutureDateError


TODAY = date.today()


class PersonTests(unittest.TestCase):
    def setUp(self):
        self.marc = Person('Marc', 'Del Castro', '1990-04-30')

    def test_person_fullname(self):
        self.assertEqual(self.marc.fullname(), 'marc del_castro')
    
    def test_person_age(self):
        self.assertEqual(self.marc.age, 34)

    def test_person_age_zero(self):
        baby = Person('cute', 'baby', TODAY.isoformat())
        self.assertEqual(baby.age, 0)

    def test_person_dob_future(self):
        self.assertRaises(
            FutureDateError, 
            Person, 
            'arnold', 'terminator', '3000-01-01'
        )

    def test_person_from_tuple(self):
        tup = ('Jane', 'Doe', '2007-05-10')
        p = Person(*tup)
        self.assertEqual(
            repr(p), 
            "Person('jane', 'doe', '2007-05-10')"
            )

class BookTests(unittest.TestCase):
    def setUp(self):
        self.bb = BirthdayBook()
        self.bb.load_from_file('test')
    
    def test_book_remove(self):
        self.bb.remove('danny', 'carey')
        self.assertRaises(
            ValueError, 
            self.bb.remove, 'danny', 'carey'
            )
        
    def test_book_sort(self):
        self.assertRaises(
            ValueError, 
            self.bb.sort, how='stuff'
        )

    def test_book_sort_last(self):
        self.bb.sort('last')
        self.assertTrue(self.bb[0].last.startswith('a'))

    def test_book_sort_last_reverse(self):
        self.bb.sort('last', reverse=True)
        self.assertTrue(self.bb[0].last.startswith('z'))
    
    def test_book_sort_age(self):
        self.bb.sort('age')
        ages = [p.age for p in self.bb]
        self.assertEqual(ages, [63, 50, 50, 34, 23])

    def test_filter_month(self):
        danny = Person('danny', 'carey', '1961-05-10')
        filtered = self.bb.filter('month', 5)
        self.assertEqual(len(filtered), 1)
        self.assertIn(danny, filtered)


if __name__ == '__main__':
    unittest.main()