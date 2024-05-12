### Birthdays

Birthdays is a module for creating and updating a database of people and their birthdays. To use, simply:

```
>>> import birthdays
```

To see extended details and examples:
```
>>> help(birthdays)
```

For practice, the user has access to the pickle file `tests/sample_data`.

***

### Testing:

Examples for running tests from the command line:
```
$ python3 -m unittest tests/person_test.py
$ python3 -m unittest -v tests/book_test.py
$ python3 -m unittest -v tests/person_test.py tests/book_test.py
```

For more details, see the [unit testing framework](https://docs.python.org/3/library/unittest.html).

Note: `book_test.py` makes use of `sample_data`.

***

### Command Line

`main.py` gives the user the option to use the birthdays module from the command line. To see details:

```
$ ./main.py -h
```

The user is required to pass the path:
1. to existing local database OR
2. where new database will be created.

For the following examples, we'll use the path to our sample database.

##### Flag Examples

1. <u>Sorting</u>

    This flag sorts and displays the database by either one of the options: *age*, *last* (i.e. last name), or *calendar*.
    ```$ ./main.py tests/sample_data -s calendar```

2. <u>Changing</u>

    This group allows the user to update the database.

	a. **append**
	This flag requires three arguments: *first_name*, *last_name*, *date-of-birth*.
	```$ ./main.py tests/sample_data -a john smith 1998-02-30```
	Warning: *date-of-birth* should have *yyyy-mm-dd* format.

	b. **remove**
	This flag requires two arguments: *first_name*, *last_name*.
	```$ ./main.py tests/sample_data -r john smith```

3. <u>Filtering</u>

	This group allows the user to filter and display sections of the database.

	a. **month**
	This flag requires one argument: *month_number*.
	```$ ./main.py tests/sample_data -m 2```

	b. **first**
	This flag requires one argument: *first_name_letter*.
	```$ ./main.py tests/sample_data -f d```

	c. **last**
	This flag requires one argument: *last_name_letter*.
	```$ ./main.py tests/sample_data -l g```