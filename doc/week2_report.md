# Week 2

## 23.3.2022

Added functions for game board/array creation and freeing, game state
struct and utility functions. Added also code for printing the game
array. Added command line option parsing (for enabling AI mode)

Time: 2h


## 24.3.2022
Added functions to get user input and to actually play the game. The
functionality that moves the tiles is still missing. Added more tests

Time: 3h


## 25.3.2022
Added helper functions for moving the tiles. Combination function and function
that moves all tiles in an array to left. Improved commenting styles. I added
some tests for the functions in the game.c.

I spent about 40 minutes trying to debug a weird bug. The solution was very
simple. I had forgotten to set a return value for a function. I have now
added -Wall and -Werror CFLAGS to the makefile. Now I should be able to get
information about possible errors more easily.

Time: 3h


## 26.3.2022
Moving the array to left works now, other directions still need work. I also
improved the comments and other documentation of the project.

Time: 1-2h

Next week I'm planning to finish the game mechanics and start working on the AI
side. I'm also planning to expand the testing.
