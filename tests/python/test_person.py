import unittest
from itertools import product

from Person import Person

class PersonTest(unittest.TestCase):
    def setUp(self):
        self.p = Person()
        self.gmb = Person("George MiChael", "bluTh", [1990,3,3])

    def test_default_values(self):
        self.assertEqual(self.p.firstName, "")
        self.assertEqual(self.p.lastName, "")
        self.assertEqual(self.p.dob, [0,0,0])

    def test_fullname(self):
        self.assertEqual(
            self.gmb.fullName, "george_michael bluth"
        )

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


if __name__ == "__main__":
    unittest.main()