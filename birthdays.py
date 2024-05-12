"""
birthdays
---------

This module provides two main classes for the user to build, and manage,
a database of people and their birthdays:
    1. Person
    2. BirthdayBook
The BirthdayBook class is a type of list intended to hold objects of 
Person type.

See Also
--------
pickle module
"""


import pickle
from datetime import date
from typing import Optional


class FutureDateError(Exception):
    def __str__(self) -> str:
        msg = 'date-of-birth cannot be in the future'
        return msg


class Person(object):
    """An instance of this class represents a person with attributes."""
    
    def __init__(self, first: str, last: str, dob: str) -> None:
        """
        Parameters
        ----------
        first:
            The Person's first name
        last:
            The Person's last name (spaces converted to underscores)
        dob:
            The Person's date-of-birth (yyy-mm-dd)
        
        Examples
        --------
        >>> p = Person('maynard', 'keenan', '1964-04-17')

        See Also
        --------
        Person.set_dob
        Person.set_age
        """

        self.first = first.lower()
        self.last  = last.replace(' ', '_').lower()
        self.set_dob(dob)
        self.set_age()

    def __repr__(self) -> str:
        """Overwrite to be more informative."""

        return "Person('{}', '{}', '{}')".format(
            self.first, self.last, date.isoformat(self.dob)
        )

    def __eq__(self, other):
        """Overwrite to determine equality of different objects."""

        if isinstance(other, self.__class__):
            return self.__dict__ == other.__dict__
        else:
            return False
    
    def set_dob(self, dob: str) -> None:
        """
        Set the Person's date-of-birth as a datetime.date object.
        Method is called at object instantiation.

        Parameters
        ----------
        dob:
            The date-of-birth in iso format

        Exceptions
        ----------
        Raises error if dob is in the future
        """

        dateObj = date.fromisoformat(dob)
        if dateObj > date.today():
            raise FutureDateError
        self.dob = dateObj

    def set_age(self) -> None:
        """
        Compute and set a Person's age from Person.dob attribute.
        Method is called at object instantiation.
        """
        
        tday = date.today()
        oneOrZero = ((tday.month, tday.day) < (self.dob.month, self.dob.day))
        yearDiff  = tday.year - self.dob.year
        self.age  = yearDiff - oneOrZero

    def fullname(self) -> str:
        return '{} {}'.format(self.first, self.last)


class BirthdayBook(list):
    """
    An instance of this class is a type of list holding Person objects.

    Examples
    --------
    >>> bb = BirthdayBook()

    See Also
    --------
    class list
    """
    
    def load_from_file(self, file: str) -> None:
        """
        Create list of Person objects from pickle file.
        
        Parameters
        ----------
        file:
            The file[path] containing the data
        """
        
        with open(file, 'rb') as f:
            data = pickle.load(f)
        
        for p in data:
            self.append(p)

    def append(self, x: Person) -> None:
        """
        Overwrite to handle uniqueness by Person names.

        Parameters
        ----------
        x:
            The Person too append to BirthdayBook
        """

        if not isinstance(x, Person):
            msg = 'BirthdayBook.append: argument is not Person type'
            raise TypeError(msg)
        
        for p in self:
            if (x.first == p.first) and (x.last == p.last):
                msg = '{} is already in BirthdayBook'.format(x)
                print(msg)
                return None
            
        super().append(x)

    def remove(self, first: str, last: str) -> None:
        """
        Overwrite to remove item using Person's names.

        Parameters
        ----------
        first:
            The Person's first name
        last:
            The Person's last name
                
        Exceptions
        ----------
        Raises error if Person is not in BirthdayBook
        """
        
        first = first.lower()
        last  = last.replace(' ', '_').lower()
        
        entryFound = False
        for i, p in enumerate(self):
            if (first == p.first) and (last == p.last):
                del self[i]
                entryFound = True
                break

        if not entryFound:
            msg = 'BirthdayBook.remove: value not found'
            raise ValueError(msg)

    def update(self, file: str):
        """
        Update the local database.

        Parameters
        ----------
        file:
            The file[path] to write as pickle file
        """

        with open(file, 'wb') as f:
            pickle.dump(self, f)

    def sort(
            self, 
            how:     Optional[str]  = 'calendar', 
            reverse: Optional[bool] = False
            ) -> None:
        """
        Overwrite to allow custom in-place sorting options.

        Parameters
        ----------
        how:
            The method for sorting: <calendar>, <last> or <age>
        reverse:
            The option for sorting in reverse
        
        Examples
        --------
        >>> bb.sort()   # sorts by calendar
        >>> bb.sort(how='age', reverse=True)   # sorts by age
        
        Exceptions
        ----------
        Raises error if invalid option is passed
        """

        how = how.lower()

        if how == 'calendar':
            super().sort(
                key=lambda p: (p.dob.month, p.dob.day), 
                reverse=reverse
                )
        elif how == 'last':
            super().sort(key=lambda p: p.last, reverse=reverse)
        elif how == 'age':
            super().sort(
                key=lambda p: (p.dob.year, p.dob.month, p.dob.day), 
                reverse=reverse
                )            
        else:
            msg = 'BirthdayBook.sort: invalid parameter <how> value'
            raise ValueError(msg)


    def filter(self, how: str, value: int | str) -> list:
        """
        Filter book based on custom options.

        Parameters
        ----------
        how:
            The method for filtering: 
                <month>
                <last>  = short for last-name-starts-with
                <first> = short for first-name-starts-with
        value:
            The value to use when filtering
        
        Returns
        -------
        filteredBook:
            The narrowed book after filters have been applied
        
        Examples
        --------
        >>> # filter Persons with birthdays in May
        >>> filtA = bb.filter(how='month', value=5)
        >>> # filter Persons with last name letter 'b'
        >>> filtB = bb.filter(how='last', value='b')
        """
        
        self.sort('calendar')

        if how == 'month':
            filteredBook = [
                p for p in self if p.dob.month == int(value)
                ]
        elif how == 'last':
            filteredBook = [
                p for p in self if p.last.startswith(value.lower())
                ]
        elif how == 'first':
            filteredBook = [
                p for p in self if p.first.startswith(value.lower())
                ]
        else:
            msg = 'BirthdayBook.filter: invalid parameter <how> value'
            raise ValueError(msg)

        return filteredBook

    def display(self, book: Optional[list] = None) -> None:
        """
        Pretty print of book entries.

        Parameters
        ----------
        book:
            The book list to display
        """

        if book:
            bookToDisplay = book
        else:
            bookToDisplay = self
        
        if len(bookToDisplay) == 0:
            print('Empty book.')
            return None
    
        for person in bookToDisplay:
            fullname = person.fullname()
            isoDob   = date.isoformat(person.dob)
            line     = '{:>25}   {}   {:2}'.format(
                fullname, isoDob, person.age
                )
            print(line)
