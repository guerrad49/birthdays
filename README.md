## Usage

The birthday database is maintained in a json file.


## Flags

1. #### SORT

  This flag sorts and displays the database by either one of the options: *age*, *last* (i.e. last name), or *calendar*.

  > ./birthdays.py test.json -s calendar

2. #### CHANGES

This group allows the user to update the database.

  a. **APPEND**

  This flag requires three arguments: *first_name*, *last_name*, *date-of-birth*.

  > ./birthdays.py test.json -a john smith 2000-01-30

  b. **REMOVE**
  
  This flag requires two arguments: *first_name*, *last_name*.
  
  > ./birthdays.py test.json -r john smith

3. #### FILTERS

This group allows the user to filter and display sections of the database.

  Examples:
  
  > ./birthdays.py test.json -m 2

  > ./birthdays.py test.json -l s

  > ./birthdays.py test.json -f d