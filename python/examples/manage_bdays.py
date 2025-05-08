#!/usr/bin/env python3

import pickle
import argparse
from datetime import date

import pyBirthdays
import pdb

#=======================================================================

def load_from_file(file: str) -> pyBirthdays.Book:
    try:
        with open(file, 'rb') as f:
            data = pickle.load(f)
    except:
        print("Could not read file. Creating empty Book.")
        return pyBirthdays.Book()
    else:
        return pyBirthdays.Book(data)
    
def update(file: str, bb: pyBirthdays.Book) -> None:
    # Note: Book itself cannot be pickled
    ppl = list(bb)
    with open(file, 'wb') as f:
        pickle.dump(ppl, f)

def parse_args():
    p = argparse.ArgumentParser()

    p.add_argument('file', help='local pickle file holding database')
    
    p.add_argument('-s', '--sort', 
        nargs='?', 
        const='calendar', 
        choices=['age','last','calendar'], 
        default=None, 
        help='sort birthdays in specified manner'
    )

    changes = p.add_mutually_exclusive_group()
    changes.add_argument('-a', '--append', nargs=3,
        help='append person to database: <first> <last> <dob>')
    changes.add_argument('-r', '--remove', nargs=3,
        help='remove person from database: <first> <last> <dob>')

    filters = p.add_mutually_exclusive_group()
    filters.add_argument('-m', '--month', type=int,
        help='filter birthdays by given month number e.g. 2, 10')
    filters.add_argument('-f', '--first',
        help='filter entries who\'s first name begins with given letter')
    filters.add_argument('-l', '--last',
        help='filter entries who\'s last name begins with given letter')
    
    args = p.parse_args()
        
    return args

#=======================================================================

if __name__ == '__main__':
    args = parse_args()
    bb   = load_from_file(args.file)

    # Changes.
    if args.append:
        p = pyBirthdays.Person(
            args.append[0], 
            args.append[1], 
            [int(x) for x in args.append[2].split('-')]
            )
        bb.append(p)
        update(args.file, bb)
        show = False
    elif args.remove:
        p = pyBirthdays.Person(
            args.remove[0], 
            args.remove[1], 
            [int(x) for x in args.remove[2].split('-')]
            )
        bb.remove(p)
        update(args.file, bb)
        show = False
    else:
        # All other options will display the book.
        tdy = date.today()
        bb.set_ages_as_of([tdy.year, tdy.month, tdy.day])
        show = True

    # Filters.
    if args.month is not None:
        bb.filter(pyBirthdays.FILTER_MONTH, args.month)
    elif args.last:
        bb.filter(pyBirthdays.FILTER_LASTNAME, args.last)
    elif args.first:
        bb.filter(pyBirthdays.FILTER_FIRSTNAME, args.first)

    # Sorting.
    if args.sort is not None:
        if args.sort == 'calendar':
            bb.sort(pyBirthdays.SORT_CALENDAR)
        elif args.sort == 'last':
            bb.sort(pyBirthdays.SORT_LASTNAME)
        elif args.sort == 'age':
            bb.sort(pyBirthdays.SORT_AGE)

    # Display the book.
    if show:
        bb.display()
