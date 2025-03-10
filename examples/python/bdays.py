#!/usr/bin/env python3

import string
import argparse
import pickle

from pyBirthdays import Person, Book

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
    bb   = Book()

    # with open('data', 'rb') as f:
    #     data = pickle.load(f)
    
    # for p in data:
    #     bb.append(p)
    # bb.load_from_file(args.file)

    if args.sort:
        bb.sort(args.sort)
        bb.display()

    if args.append:
        p = Person(*args.append)
        bb.append(p)
        # bb.update(args.file)
    elif args.remove:
        bb.remove(*args.remove)
        # bb.update(args.file)
    
    if args.month:
        filteredBook = bb.filter('month', args.month)
        bb.display(filteredBook)
    elif args.last:
        filteredBook = bb.filter('last', args.last)
        bb.display(filteredBook)
    elif args.first:
        filteredBook = bb.filter('first', args.first)
        bb.display(filteredBook)