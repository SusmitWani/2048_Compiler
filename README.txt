Readme file for the Compiler Constructions Course Assignment conducted in the second semester of the academic year 2020-2021.

Author: Susmit Wani
ID: 2018A7PS0116G
Date of submission: 16/04/2021

The following files are included in the tar.gz folder.
1. parser.y
2. lexer.l
3. helper_functions.cpp
4. helper2.cpp
5. helper_functions.h
6. makefile
7. assignmentspecs.pdf
8. README.txt

The codes have been tested on Linux kernel 5.11.13.arch1-1 and are working perfectly fine without any errors.

List of possible moves:
1. <Operation> <Direction>.
2. ASSIGN <value> to <x>, <y>.
3. VAR <varname> IS <x>, <y>.
4. VALUE IN <x>, <y>.

<Operation> can be ADD, SUBTRACT, MULTIPLY< DIVIDE.

A little implementational detail:
	In the SUBTRACT operation, there was a discussion on what the meaning of 'tile is obliterated' was. There were two common interpretations.

1. 4 2 2 4  ->  4 0 4 0
2. 4 2 2 4  ->  4 4 0 0


The primary implementation in my code is the first one. However if one wants to use the second implementation, they can use the 'make game2' command in the terminal.

Running 'make' will by default run the first implementation which 'oliterates' the 0 tile obtained from subtraction in the next move and obtains 4 0 4 0 from 4 2 2 4 on running 'SUBTRACT LEFT.'

Meanwhile, running 'make game2' will run the second implementation which 'obliterates' the 0 tile in the same move and obtains 4 4 0 0 from 4 2 2 4 on running 'SUBTRACT LEFT.'

Other details and conventions of the code are:
1. The board is to be treated as a 2D array where index of top left corner is to be considered as (1,1) and bottom right corner is (4,4).
2. Pressing Ctrl+D or typing 'EXIT' will exit the code.
