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
