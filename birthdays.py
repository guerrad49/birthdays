import pickle
from datetime import date


class Person:
    def __init__(self, firstName: str, lastName: str, dob: str) -> None:
        self.firstName = firstName
        self.lastName  = lastName
        self.dob = date.fromisoformat(dob)
        self.age = self.get_age()


    def get_age(self) -> int:
        today = date.today()
        oneOrZero = ((today.month, today.day) < (self.dob.month, self.dob.day))
        yearDiff  = today.year - self.dob.year
        return yearDiff - oneOrZero


    def get_full_name(self) -> str:
        return '{} {}'.format(self.firstName, self.lastName)


    def to_dict(self) -> dict:
        d = {
            'first_name': self.firstName,
            'last_name' : self.lastName,
            'date_of_birth': date.strftime(self.dob, '%Y-%m-%d'),
            'age': self.age
        }
        return d


class BirthdayBook:
    def __init__(self, filename: str) -> None:
        self.filename = filename
        self.book = self.get_book_entries()

    def get_book_entries(self) -> list:
        """Create list of Person objects from local file"""
        with open(self.filename, 'rb') as f:
            data = pickle.load(f)
        
        return [
            Person(p['first_name'], p['last_name'], p['date_of_birth']) 
            for p in data
            ]
    

    def add_entry(self, *args) -> None:
        args = [x.lower() for x in args]
        p    = Person(*args)
        self.book.append(p)
        self.update_database()


    def remove_entry(self, *args) -> None:
        args = [x.lower() for x in args]
        deleted_entry = False
        
        for i, p in enumerate(self.book):
            if (args[0] == p.first_name) and (args[1] == p.last_name):
                del self.book[i]
                deleted_entry = True
                break

        if deleted_entry:
            self.update_database()
        else:
            print('Entry not found. Database unchanged.')


    def update_database(self) -> list:
        data = [p.to_dict() for p in self.book]
        with open(self.filename, 'wb') as f:
            pickle.dump(data, f)


    def sort_book(self, how: str):
        if how == 'last':
            sortedBook = sorted(self.book, key=lambda p: p.lastName)
        elif how == 'age':
            sortedBook = sorted(
                self.book, 
                key=lambda p: (p.dob.year, p.dob.month, p.dob.day)
                )
        elif how == 'calendar':
            sortedBook = sorted(
                self.book, 
                key=lambda p: (p.dob.month, p.dob.day) 
                )

        return sortedBook


    def filter_book(self, how: str, key: int | str) -> list:
        """Narrow book to entries that pass user-specified filter"""

        if isinstance(key, str):
            key = key.lower()
        
        sortedBook = self.sort_book('calendar')

        if how == 'month':
            filteredBook = [
                p for p in sortedBook if p.dob.month == int(key)
                ]
        elif how == 'last':
            filteredBook = [
                p for p in sortedBook if p.lastName.startswith(key)
                ]
        elif how == 'first':
            filteredBook = [
                p for p in sortedBook if p.lastName.startswith(key)
                ]

        return filteredBook

    def display_book(self, book: list):
        """Print details of entries with formatting"""
        if len(book) == 0:
            print('Empty book.')
            return 0
    
        for person in book:
            fullname = person.get_full_name()
            isoDob   = date.strftime(person.dob, '%Y-%m-%d')
            line     = '{:>25}   {}   {:2}'.format(
                fullname, isoDob, person.age
                )
            print(line)
