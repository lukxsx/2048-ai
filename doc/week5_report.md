# Week 5
## 21.4.2022
I fixed a memory leak in the minimax algorithm. There were copies of arrays that
were not freed properly. I also changed move_t typedef to include the direction
instead of an array. Now it's much faster to get the direction without comparing
arrays.

Time: 3h

## 22.4.2022
I added a silent mode to the AI modes so they won't print the output while
running. This is used in the comparasion mode. It runs much faster now because
the game board is not printed to the screen every time.

Time: 1-2h

## 23.4.2022
I changed the function copy_array() to just copy the contents of the old array
to the new array. Previously this function allocated and returned a pointer to a
new array with the contents copied. I used this to reduce the mallocs needed in
the minimax algorithm. Now the same allocation is used when going through all
possible moves for max or min.

I changed the whole structure of the game array. It used to be an array of
int-pointers that each pointed to int arrays. This was a bad option in terms of
cache efficiency. I changed the program so that the entire game board is stored
in a single 16-element array. The game board is stored there row by row. The
performance of the minimax AI increased by 50-80% (benchmarks will be released
later).

The disadvantage is that [][] syntax cannot be used for indexing anymore. I made
an inline helper function that calculates the correct index in the table with
the formula y*4+x.

Now the table can be allocated from the stack instead of needing millions of
malloc calls as in the previous version.

I changed the type of the game array from int to unsigned int, because there
cannot be negative numbers in the game table.

Time: 6h
