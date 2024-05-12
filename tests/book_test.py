import unittest

from birthdays import BirthdayBook, Person


class BookTests(unittest.TestCase):
    def setUp(self):
        self.bb = BirthdayBook()
        self.bb.load_from_file('tests/sample_data')
    
    def test_append_invalid_type(self):
        self.assertRaises(TypeError, self.bb.append, 3)

    def test_append_repeat(self):
        p = Person('john', 'doe', '2000-01-01')
        self.bb.append(p)
        origLen = len(self.bb)
        self.bb.append(p)
        self.assertEqual(origLen, len(self.bb))

    def test_remove(self):
        self.bb.remove('danny', 'carey')
        self.assertRaises(
            ValueError, 
            self.bb.remove, 'danny', 'carey'
            )
        
    def test_sort(self):
        self.assertRaises(
            ValueError, 
            self.bb.sort, how='stuff'
        )

    def test_sort_last(self):
        self.bb.sort('last')
        self.assertTrue(self.bb[0].last.startswith('a'))

    def test_sort_last_reverse(self):
        self.bb.sort('last', reverse=True)
        self.assertTrue(self.bb[0].last.startswith('z'))
    
    def test_sort_age(self):
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