# 01-HWC-LFU-cache

**Authors**:
- Zagorodnyuk Vladislav
- Kirkicha Andrey

## Introduction
This project is the implementation of Least Frequently Used cache algorithm in C++.

**The task was**:
- Implement any cache algorithm of suggested ones (ARC, 2Q, LFU, LIRS)
- Test it
- Implement perfect cache algorithm
- Compare the perfect cache with the one we implemented

All points were done.

## Project desription
Project contains **folders**:
- ``Include``
- ``Object``
- ``Source``
- ``Test``

### Include folder
Contains header files that include implementations of both cache algorithms.

### Object folder
Created for *.o files. After linking all object files will be removed.

### Source folder
Contains source file ``cache.cpp`` to test LFU cache algorithm in console and compare it with perfect cache.

**To use this option**:
- Run ``make`` in folder ``./Source/``
- Executable file ``cache`` will appear there
- Run ``cache``

Input and output are realized by ``stdin`` and ``stdout``.

**Input**:
- Size of cache
- Number of elemennts
- Elements themselves

```bash
2 6 1 2 1 2 1 2
```

**Output**:
- Number of hits for LFU cache
- Number of hits for perfect cache

```bash
LFU     cache: 4
Perfect cache: 4
```

### Test folder
Contains source file ``test.cpp`` to make tests of LFU cache algorithm in .txt file.

Input file: "test_data.txt"

**To use this option**:
- Fill file ``test_data.txt`` in folder ``./Test/`` with test data according to instruction below
- Run ``make`` in folder ``./Test/``
- Executable file ``test`` will appear there
- Run ``test``

**Input for each test**:
- Size of cache
- Number of elements
- Elements themselves
- Right answer for LFU cache (number of hits)

```bash
2 6 1 2 1 2 1 2
4

2 6 1 2 1 2 1 2
4

1 0
0

1 4 1 2 3 4
0

0 0
0

5 5 5 5 5 5 5
4

3 7 1 2 3 2 3 4 2
3

0 5 1 2 3 2 1
0

1 9 1 234 -324 -324 33 28 3 3 29
2

```

**Output**:
- Result of each test (success / error - expected - recieved)
- Total result

```bash
TEST #1 >>> SUCCESS

TEST #2 >>> SUCCESS

TEST #3 >>> SUCCESS

TEST #4 >>> SUCCESS

TEST #5 >>> SUCCESS

TEST #6 >>> SUCCESS

TEST #7 >>> SUCCESS

TEST #8 >>> SUCCESS

========================================================= 

CORRECT TESTS: 8 / 8
```