#!/usr/bin/env python3

import pdb
import pickle
import string
import argparse
from datetime import date, datetime


class BirthdayBook:
    def __init__(self, file):
        self.file     = file        
        self.entries  = self.get_entries()

    def get_entries(self):
        '''Create a list consisting of Person objects from file'''
        with open(self.file, 'rb') as f:
            raw = pickle.load(f)
        
        return [Person(p['first'], p['last'], p['dob']) for p in raw]
        
    def add_entry(self, *args):
        '''Add a new person to database and update file'''
        args = [x.lower() for x in args]
        p    = Person(*args)
        self.entries.append(p)
        self.update()

    def remove_entry(self, *args):
        '''Remove a person from database and update file'''
        args     = [x.title() for x in args]
        fname    = ' '.join(args)
        init_len = len(self.entries)
        
        for i, p in enumerate(self.entries):
            if fname == p.get_full_name():
                del self.entries[i]
                break

        if init_len > len(self.entries):
            self.update()
            pass
        else:
            print('Entry not found. Database unchanged.')

    def update(self):
        '''Update local file containing database'''
        list_of_dicts = [p.to_dict() for p in self.entries]
        with open(self.file, 'wb') as f:
            pickle.dump(list_of_dicts, f)

    def sort_book(self, opt):
        '''Sorting options. Return list of Person objects'''
        if opt == 'last':
            ordered = sorted(self.entries, key=lambda p: p.last)
        elif opt == 'age':
            ordered = sorted(self.entries, key=lambda p: (p.dob.year, p.dob.month, p.dob.day) )
        elif opt == 'calendar':
            ordered = sorted(self.entries, key=lambda p: (p.dob.month, p.dob.day) )

        return ordered

    def filter_book(self, opt, key):
        '''Filter birthdays and return list of Person objects'''
        sorted_list = self.sort_book('calendar')

        if opt == 'month':
            filtered = [p for p in sorted_list if p.dob.month == int(key)]
        elif opt == 'last':
            filtered = [p for p in sorted_list if p.last.startswith(key)]
        elif opt == 'first':
            filtered = [p for p in sorted_list if p.first.startswith(key)]

        return filtered

    def display_book(self, in_list):
        '''Print formatted book'''
        if len(in_list) == 0:
            print('Empty book.')
            return 0
    
        for p in in_list:
            name_str = p.get_full_name()
            dob_str  = p.dob.strftime('%Y-%m-%d')
            line     = '{:>25}   {}   {:2}'.format(name_str, dob_str, p.age)
            print(line)


class Person:
    def __init__(self, first, last, dob):
        self.first = first
        self.last  = last
        self.dob   = datetime.fromisoformat(dob)
        self.age   = self.get_age()

    def get_age(self):
        '''Determine and set person's age'''
        today       = date.today()
        one_or_zero = ((today.month, today.day) < (self.dob.month, self.dob.day))
        year_diff   = today.year - self.dob.year
        return year_diff - one_or_zero

    def get_full_name(self):
        '''Get and return person's full name'''
        full_name = '{} {}'.format(self.first, self.last)
        return full_name.title()

    def to_dict(self):
        d = {'first': self.first,
             'last' : self.last,
             'dob'  : self.dob.strftime('%Y-%m-%d'),
             'age'  : self.age}
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
    book = BirthdayBook(args.file)

    if args.sort:
        sorted_entries = book.sort_book(args.sort)
        book.display_book(sorted_entries)

    if args.append:
        book.add_entry(*args.append)
    elif args.remove:
        response = input('Are you sure you want to remove someone? (y/n)\t')
        if response == 'y':
            book.remove_entry(*args.remove)
            
    if args.month:
        filtered_list = book.filter_book('month', args.month)
        book.display_book(filtered_list)
    elif args.last:
        filtered_list = book.filter_book('last', args.last.lower())
        book.display_book(filtered_list)
    elif args.first:
        filtered_list = book.filter_book('first', args.first.lower())
        book.display_book(filtered_list)