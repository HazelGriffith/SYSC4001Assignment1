# SYSC4001Assignment1
A linux based program written in C that multiplies two hardcoded 4x4 matrices by creating multiple processes that solve different parts of the problem concurrently.

The source code files are provided though must still be compiled on a linux system. 

The MMULT1 program requires no input and outputs the matrix Q

The MMULT2 program does require a single integer as input through the argv char array that is input when the program is run by typing it 
after the program name to be executed. For example: "./MMULT2 4" would make the program run with 4 processes, whereas "./MMULT2 2" would make
the program run with only 2 processes.
