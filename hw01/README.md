# Computer Programming II homework 1

## Author

- 我是資工系 116 級的吳振榮，學號是 41247012S。

## Overview

台師大資工程式設計(一)第四次作業，共 5+1 道題目。

## Build and Run

Run `make` to compile my code.

```shell
$ make
```

After compiling the program, you can execute hw0301 code by entering `./hw0101` in the terminal, and the remaining programs follow the same pattern.

```shell
$ ./hw0101
$ ./hw0102
$ ./hw0103
$ ./hw0104
$ ./hw0105
```

## homework description

### hw0101

README

- mystrchr: Locates the first occurrence of a character in a string.
- mystrrchr: Locates the last occurrence of a character in a string.
- mystrspn: Calculates the length of the initial segment of a string consisting of only characters that are present in another specified string.
- mystrcspn: Calculates the length of the initial segment of a string consisting of only characters not present in another specified string.
- mystrpbrk: Searches a string for any of a set of specified characters.
- mystrstr: Locates the first occurrence of a substring within another string.
- mystrtok: Breaks a string into a sequence of tokens based on a specified delimiter.

### hw0102

The mycal.h file for performing arithmetic calculations on custom numerical expressions. The main function provided is calculate, which evaluates an expression and returns the result in a specified base. Additionally, there are helper functions such as convert2base10 for converting numbers from a custom base to base 10, and valid for validating the format of the input expression.

### hw0103

The mychain.h file for computing the chain rule of derivatives for polynomials. The main function provided is chain_rule, which computes the derivative of the composition of two polynomials (pFy and pFx) and stores the result in pResult.

### hw0104

The mymaze.h file for finding the minimum path through a maze represented as a grid of rooms with doors. The main function provided is find_min_path, which computes the minimum path through the maze using depth-first search (DFS) algorithm.

### hw0105

This program is a simple implementation of a taiko game. It reads input from stdin, interprets the commands, and generates taiko chart data in a JSON format, and output with stdout.

- START: Marks the beginning of a new drum chart.
- END: Marks the end of a drum chart.
- MEASURE: Specifies the time signature of the drum chart.
- BPMCHANGE: Specifies a change in BPM (Beats Per Minute).

## Something to notify TAs
