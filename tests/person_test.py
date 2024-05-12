import unittest
from datetime import date

from birthdays import Person, FutureDateError


class PersonTests(unittest.TestCase):
    def setUp(self):
        self.marc = Person('Marc', 'Del Castro', '1990-04-30')
    
    def test_instance_via_unpacking(self):
        tup = ('Jane', 'Doe', '2007-05-10')
        p = Person(*tup)
        self.assertEqual(
            repr(p), 
            "Person('jane', 'doe', '2007-05-10')"
            )

    def test_fullname(self):
        self.assertEqual(self.marc.fullname(), 'marc del_castro')
    
    def test_age(self):
        self.assertEqual(self.marc.age, 34)

    def test_age_zero(self):
        today = date.today().isoformat()
        baby  = Person('cute', 'baby', today)
        self.assertEqual(baby.age, 0)

    def test_dob_future(self):
        self.assertRaises(
            FutureDateError, 
            Person, 
            'arnold', 'terminator', '3000-01-01'
        )


if __name__ == '__main__':
    unittest.main()