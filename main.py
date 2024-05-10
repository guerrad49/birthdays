#!/usr/bin/env python3

import pdb
import string
import argparse

from classes import BirthdayBook


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
        sortedBook = bb.sort_book(args.sort)
        bb.display_book(sortedBook)

    if args.append:
        bb.add_entry(*args.append)
    elif args.remove:
        response = input('Are you sure you want to remove someone? (y/n)\t')
        if response == 'y':
            bb.remove_entry(*args.remove)
            
    if args.month:
        filteredBook = bb.filter_book('month', args.month)
        bb.display_book(filteredBook)
    elif args.last:
        filteredBook = bb.filter_book('last', args.last)
        bb.display_book(filteredBook)
    elif args.first:
        filteredBook = bb.filter_book('first', args.first)
        bb.display_book(filteredBook)