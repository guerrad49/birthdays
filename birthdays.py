#!/usr/bin/env python3

import pdb
import pickle
import string
import argparse
from datetime import date


class BirthdayBook:
    def __init__(self, filename):
        self.filename = filename
        self.book = self.get_book_entries()

    def get_book_entries(self) -> list:
        '''Create list of Person objects from local file'''
        with open(self.filename, 'rb') as f:
            data = pickle.load(f)
        
        return [
            Person(p['first_name'], p['last_name'], p['date_of_birth']) 
            for p in data
            ]
        
    def add_entry(self, *args):
        args = [x.lower() for x in args]
        p    = Person(*args)
        self.book.append(p)
        self.update_database()

    def remove_entry(self, *args):
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

    def sort_book(self, sort_by: string):
        if sort_by == 'last':
            sorted_book = sorted(self.book, key=lambda p: p.last_name)
        elif sort_by == 'age':
            sorted_book = sorted(self.book, 
                                 key=lambda p: (p.dob.year, p.dob.month, p.dob.day)
                                 )
        elif sort_by == 'calendar':
            sorted_book = sorted(self.book, key=lambda p: (p.dob.month, p.dob.day) )

        return sorted_book

    def filter_book(self, filter_by: string, key: 'int or str') -> list:
        '''Narrow book to entries that pass user-specified filter'''
        if isinstance(key, str):
            key = key.lower()
        
        sorted_book = self.sort_book('calendar')

        if filter_by == 'month':
            filtered_book = [p for p in sorted_book if p.dob.month == int(key)]
        elif filter_by == 'last':
            filtered_book = [p for p in sorted_book if p.last_name.startswith(key)]
        elif filter_by == 'first':
            filtered_book = [p for p in sorted_book if p.first_name.startswith(key)]

        return filtered_book

    def display_book(self, book: list):
        '''Print details of entries with formatting'''
        if len(book) == 0:
            print('Empty book.')
            return 0
    
        for person in book:
            fullname   = person.get_full_name()
            dob_in_iso = date.strftime(person.dob, '%Y-%m-%d')
            line = '{:>25}   {}   {:2}'.format(fullname, dob_in_iso, person.age)
            print(line)


class Person:
    def __init__(self, first_name: string, last_name: string, dob: string):
        self.first_name = first_name
        self.last_name  = last_name
        self.dob = date.fromisoformat(dob)
        self.age = self.get_age()

    def get_age(self) -> int:
        today = date.today()
        one_or_zero = ((today.month, today.day) < (self.dob.month, self.dob.day))
        year_diff   = today.year - self.dob.year
        return year_diff - one_or_zero

    def get_full_name(self) -> string:
        return '{} {}'.format(self.first_name, self.last_name)
    
    def to_dict(self) -> dict:
        d = {
            'first_name': self.first_name,
            'last_name' : self.last_name,
            'date_of_birth': date.strftime(self.dob, '%Y-%m-%d'),
            'age': self.age
        }
        return d

#=======================================================================

def parse_args():
    p = argparse.ArgumentParser()

    p.add_argument('file', help='local pickle file holding database')
    p.add_argument('-s', '--sort', choices=['age','last','calendar'],
        help='sort birthdays in specified manner')

    changes = p.add_mutually_exclusive_group()
    changes.add_argument('-a', '--append', nargs=3,
        help='append person to database: <first> <last> <dob>')
    changes.add_argument('-r', '--remove', nargs=2,
        help='remove person from database: <first> <last>')

    filters = p.add_mutually_exclusive_group()
    filters.add_argument('-m', '--month', type=int,
        help='filter birthdays by given month number e.g. 2, 10')
    filters.add_argument('-f', '--first',
        help='filter entries who\'s first name begins with given letter')
    filters.add_argument('-l', '--last',
        help='filter entries who\'s last name begins with given letter')
    
    args = p.parse_args()

    if args.month and args.month not in range(1,13):
        p.error('error: --month must be integer between 1 and 12 inclusive.')
    if args.last and args.last not in string.ascii_letters:
        p.error('error: --last must be a letter in the alphabet.')
    if args.first and args.first not in string.ascii_letters:
        p.error('error: --first must be a letter in the alphabet.')
        
    return args

#=======================================================================


if __name__ == '__main__':

    args = parse_args()
    bb   = BirthdayBook(args.file)

    if args.sort:
        sorted_book = bb.sort_book(args.sort)
        bb.display_book(sorted_book)

    if args.append:
        bb.add_entry(*args.append)
    elif args.remove:
        response = input('Are you sure you want to remove someone? (y/n)\t')
        if response == 'y':
            bb.remove_entry(*args.remove)
            
    if args.month:
        filtered_book = bb.filter_book('month', args.month)
        bb.display_book(filtered_book)
    elif args.last:
        filtered_book = bb.filter_book('last', args.last)
        bb.display_book(filtered_book)
    elif args.first:
        filtered_book = bb.filter_book('first', args.first)
        bb.display_book(filtered_book)