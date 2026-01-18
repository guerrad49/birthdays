import pickle
import tempfile
import unittest
from itertools import product

from pyBirthdays import Person, BirthdayError


class PersonTest(unittest.TestCase):
    def setUp(self):
        self.p = Person()
        self.gmb = Person(
            "George MiChael", "bluTh", 
            [1990,3,3], Person.FAMILY
            )

    def test_default_values(self):
        self.assertEqual(self.p.firstName, "")
        self.assertEqual(self.p.lastName, "")
        self.assertEqual(self.p.dob, [0,0,0])
        self.assertEqual(
            self.p.relationship, 
            Person.OTHER
            )

    def test_types(self):
        self.assertIsInstance(self.gmb.firstName, str)
        self.assertIsInstance(self.gmb.dob, list)
        self.assertIsInstance(self.gmb, Person)

    def test_fullname(self):
        self.assertEqual(
            self.gmb.fullName, "george michael bluth"
        )

    def test_dob(self):
        with self.assertRaises(BirthdayError) as ctx:
            self.p.dob = [0,0,0]
        with self.assertRaises(BirthdayError) as ctx:
            self.p.dob = [2025,1,32]
        with self.assertRaises(BirthdayError) as ctx:
            self.p.dob = [2025,2,29]
        with self.assertRaises(BirthdayError) as ctx:
            self.p.dob = [2024,13,1]

    def test_age(self):
        self.p.dob = [1980,6,7]

        ages = list()
        for m in range(1,13):
            # All days in 2024. Notice discarding invalid dates.
            for today in product([2024],[m],range(1,32)):
                try:
                    self.p.set_age_as_of(list(today))
                except BirthdayError:
                    continue
                ages.append(self.p.age)

        daysBeforeBday = 31 + 29 + 31 + 30 + 31 + 6  # Leap year.
        for a in ages[:daysBeforeBday]:
            self.assertEqual(a, 43)
        for a in ages[daysBeforeBday:]:
            self.assertEqual(a, 44)

    def test_comparison(self):
        p1 = Person("george michael", "bluth", [1990,3,3])
        self.assertEqual(self.gmb, p1)
        p1.lastName = "funke"
        self.assertNotEqual(self.gmb, p1)

    # Test the pickling bindings for Person.
    def test_pickling(self):
        with tempfile.NamedTemporaryFile() as fp:
            pickle.dump(self.gmb, fp)
            fp.flush()  # Ensure data is written to file.
            fp.seek(0)
            loaded_obj = pickle.load(fp)
            self.assertEqual(self.gmb, loaded_obj)
            self.assertEqual(
                self.gmb.relationship, 
                loaded_obj.relationship
            )


if __name__ == "__main__":
    unittest.main()
