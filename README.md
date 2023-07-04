## Usage

The birthday database is maintained in a json file.


## Flags

1. #### SORT

This flag sorts the database by either one of the options: *age*, *last*, or *calendar*.

  Example:

  > ./birthdays.py test.json -s calendar

2. #### CHANGES

This group of flags allows the user to add/remove an entry from the database. The only difference is that adding an entry requires date-of-birth as well.

  Examples:

  > ./birthdays.py test.json -a john smith 2000-01-30

  > ./birthdays.py test.json -r john smith

3. #### FILTERS

This group of flags allows the user to filter and display sections of the database.

  Examples:
  
  > ./birthdays.py test.json -m 2

  > ./birthdays.py test.json -l s

  > ./birthdays.py test.json -f d