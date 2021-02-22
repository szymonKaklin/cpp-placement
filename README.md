# Completed placement test

Included in this repo are the completed placement test files:

```bash
├── api_task
│   └── ampify_parser.py
├── CMakeLists.txt
├── compiled
│   └── calculator
├── README.md
├── source
│   └── main.cpp
└── .gitignore
```
## C++ Calculator

The C++ calculator task was built using CMake, with Xcode as the IDE.

The completed source code for the C++ task is found under `./source/main.cpp`.
The compiled unix executable can be found under `./compiled/calculator` 

A CMakeLists.txt file is included. If cmake is installed, running: `cmake -B build -G "<Generator name>"` from the root directory will build the project.

### Additions and Improvements

+ Division was added
	+ division by 0 gives a warning
+ Fixed problems
	+ fixed the implemnetation of std::abs
	+ improved std::stod functionality so that inputs like '2abc' are no longer valid
	+ added a try catch for std::invalid_argument so that the program does not quit on invalid input allowing the user to continue input
+ Added functionality for negative numbers
	+ inputs like `-3*-20` are now valid and evalute correctly
	+ a negative number must have a minus sign directly in front of it (no whitespace)
+ `pi` was added as a constant
	+ std::setprecision(7) was added to output `pi * 5` to five decimal places

As asked in the task, the following examples are computed correctly:
```
10 * 4
25.3 + 18.6
3-5.6
pi * 5 (to five decimal places)
```
The commit history details the changes made to the original `main.cpp` file.

## Web API Parsing

The web API parsing task was completed using Python. The completed script is found in the `api_task` folder.
The only module required is the `requests` module. This can be installed from the terminal using:

`python -m pip install requests`

The script can be run (from the `./api_task` directory) with the command:

`python ampify_parser.py`

This will request data from https://api.ampifymusic.com/packs, and parse the data into a python dictionary with key value pairs of unique genres for keys, and with lists of names of all packs in that genre for values.

The script will then print out a list of all unique genres, followed by a list of all packs in the genre 'hip-hop'.