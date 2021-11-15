CS 344 Assignment 3 - Multi-threaded Producer Consumer Pipeline
Created by Nicole Yarbrough

This project was created to solve the prompt provided for assignment 4 in the Oregon State 
University Operating Systems I course.

To compile the code, unzip all files and run the command "make". If you would like to delete
the executable, use the command "make clean"

This program takes input from the user, replaces substrings of "++" with "^", then prints strings 
of length 80 characters to the screen.

To use a file as input, enter "./line_processor < [inputfile]" to the command line, replicating
[inputfile] with the input file of your choice. To send the printed text to an output file, enter
"./line_processor > [outputfile]" to the command line, replacing [outputfile] with the name of 
the file you would like the output to be saved to. Additionally, you can combine the two processes
to utilize both an input and output file. "./line_processor < [inputfile] > [outputfile]"