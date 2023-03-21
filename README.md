Divvy Bike Ride Analyzer
========================

This C++ project analyzes Divvy bike ride data, providing insights into ride statistics, user types, and ride patterns.

Table of Contents
-----------------

- [Divvy Bike Ride Analyzer](#divvy-bike-ride-analyzer)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Getting Started](#getting-started)
  - [Usage](#usage)

Features
--------

1.  Read and clean the data from a selected data file
2.  Display overall trip information
3.  Display the percentage of members vs. casual riders
4.  Display weekday vs. weekend usage
5.  Find the closest Divvy station

Getting Started
---------------

Clone the repository to your local machine:

bash

```bash
git clone https://github.com/lumirth/divvy.git
```

> ⚠️ **NOTE:** The `data/all_divvy_rides_september.csv` has been compressed due to its size. Be sure to extract the file before running the program.

To compile the project, navigate to the project directory and run:

bash

```bash
g++ -o divvy_analyzer main.cpp --std=c++11
```

Usage
-----

Execute the compiled binary:

bash

```bash
./divvy_analyzer
```

Follow the on-screen prompts to select a menu option and analyze the data.
