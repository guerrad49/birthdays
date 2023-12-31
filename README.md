## Usage

This script allows the user to create and maintain a database of birthdays. The database is kept as a local binary file. This repo contains the file **test** as an example.

***

## Flags

1. #### SORT

    This flag sorts and displays the database by either one of the options: *age*, *last* (i.e. last name), or *calendar*.
    > ./birthdays.py test -s calendar

2. #### CHANGES

    This group allows the user to update the database.

	a. **APPEND**
	This flag requires three arguments: *first_name*, *last_name*, *date-of-birth*.
	> ./birthdays.py test -a john smith 1998-02-30

	b. **REMOVE**
	This flag requires two arguments: *first_name*, *last_name*.
	> ./birthdays.py test -r john smith

3. #### FILTERS

	This group allows the user to filter and display sections of the database.

	a. **MONTH**
	This flag requires one argument: *month_number*.
	> ./birthdays.py test -m 2

	b. **FIRST**
	This flag requires one argument: *first_name_letter*.
	> ./birthdays.py test -f d

	c. **LAST**
	This flag requires one argument: *last_name_letter*.
	> ./birthdays.py test -l g