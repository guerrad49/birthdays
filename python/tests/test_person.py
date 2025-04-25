import pickle
import tempfile
import unittest
from itertools import product

from pyBirthdays import Person, BirthdayError


class PersonTest(unittest.TestCase):
    def setUp(self):
        self.p = Person()
        self.gmb = Person("George MiChael", "bluTh", [1990,3,3])

    def test_default_values(self):
        self.assertEqual(self.p.firstName, "")
        self.assertEqual(self.p.lastName, "")
        self.assertEqual(self.p.dob, [0,0,0])

    def test_types(self):
        self.assertIsInstance(self.gmb.firstName, str)
        self.assertIsInstance(self.gmb.dob, list)
        self.assertIsInstance(self.gmb, Person)

    def test_fullname(self):
        self.assertEqual(
            self.gmb.fullName, "george_michael bluth"
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
        self.p.dob = [1978,6,7]

        ages = list()
        for m in range(1,13):
            # Assume all months have 30 days.
            for today in product([2024],[m],range(1,31)):
                self.p.calcAge(list(today))
                ages.append(self.p.age)

        change = 5*30 + 6  # 6 months and 6 days
        for a in ages[:change]:
            self.assertEqual(a, 45)
        for a in ages[change:]:
            self.assertEqual(a, 46)

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


if __name__ == "__main__":
    unittest.main()
