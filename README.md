
***

# Introduction

Hello, and welcome to my Advent of Code 2023 solution repository!

The goal of this repo is to write efficient solutions to solve
each day's puzzle in C.

***

# Repository Structure

There are serveral directories used by this project,
which follow a pretty standard C project structure:
- `bin` : Any compiled binary files used to run the program. Git doesn't track empty directories,
 so you will need to create this when cloning the project.
- `include` : Any header files used by the runner and solutions.
- `input` : The input files used to test a solution.
- `src` : The source code for the project.
    - `src/puzzles` : The source code for solving each individual puzzle.
    - `src/util` : The source code for utility functions shared across the project. 
    - `src/aoc.c` : The main driver code to run each day's solution.

***

# Solutions

Each day's solution is named to be something associated with the problem 
description instead of the numbered day. Here's a list of each puzzle solution
mapped to the day it's the solution to:
- `test` : This is just a "Hello, World!" program for testing purposes.
- `trebuchet` : This is the solution to day 1.
- `cubes` : This is the solution to day 2.
- `gears` : This is the solution to day 3.

***

# Using this Repository

If you want to run any of the solutions, just clone the repository,
compile the project, and run it:
```
    mkdir bin  
    make PUZZLE=<puzzle identifier>
    bin/runner <path to input file>  
```
***
