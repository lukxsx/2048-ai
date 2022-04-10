# Implementation
This is a command line implementation of the 2048 game and AI that can be used
to play it automatically.

## About game
2048 is a simple game with 4x4 sized board. Numbered tiles are automatically
generated on the board (one at every
move) and when they collide, they will combine and the number on the tile is
doubled. The numbers start from 2 and 4 and every new tile added will be either
2 or 4. The game can be considered "completed" when tile 2048 is reached.
However the game can be continued as long as possible achieving even higher
numbers.

## Features
My implementation has 4 different modes for running the game.
### Player mode
The default mode (not using any command line arguments). The game can be played
normally by the player with WASD keys.

### Randomized mode
The game is played by randomized input (simulates randomly pressing WASD keys)

### Simple/randomizer AI
This mode simulates the game with randomized input and chooses the move that has
the largest score.

### Minimax AI
This mode uses the minimax algorithm to find the most optimal moves to play the
game.

## How the game code works
### Game state struct
The most used piece of code in this application is probably the struct typedef
called ```game_state_t```. It contains the game board, score and the amount of
moves.

### Game management
#### New game
When a new game is started (gamemode doesn't matter), the function
```new_game()``` is used. It will allocate a new ```game_state_t``` struct
and initialize it's values. It calls ```init_game_array()``` which allocates
and returns a new game board (2-dimensional array, stored in memory as an array
of int pointers (columns) each pointing to the corresponding row.

#### Ending game
The game is stopped with ```end_game(game_state_t *game)``` which frees the
two-dimensional array (free cannot be used on it as is, because it would only
free the columns array pointer and leave row arrays in place) ̣

#### Copying games
The functions ```copy_game(game_state_t *old)``` and
```copy_game_array(int **old)``` are used by randomizer AI and minimax AI to
make copies of the current game for simulation purposes. They will allocate and
initialize new games and copy the contents of the old games to them.

### Tiles
#### Creating tiles
New tiles to the game board can be created with
```create_random_tile(game_state_t *game)```. It adds a 2 or 4 to the board to a
randomized (free) coordinates. The tile will be 2 with 75% probability and 4
with 25% probability.

```create_tile(int **arr, int x, int y, int value)``` is used to generate a tile
to a speficic spot. Create_random_tile uses it internally but it is also used by
the minimax AI for simulation.

#### Moving tiles
The tiles on the game board are moved with the ```move_game(game_state_t)```
function which calls the internal ```move(int **game_array)``` function.

All internal moving functions work on 1-dimensional arrays. The game board is
processed as single rows and columns by the processing functions.

Moving process has three parts: 1) check if we can move to the direction using
```can_move(int **arr, direction dir)``` 2) move all tiles of each row or column
to the left side of the array using ```move_all_left(int *arr)``` 3) run the
```combine(int *arr)``` on all subarrays (it will combine the matching tiles
and returns the score increase). 4) Move all left again, because otherwise the
array is not in the right order after combine function.

#### Checking functions
There are many checking functions in the game.c to make sure the game is played
according to the rules. For example, ```can_move()``` and ```is_array_full()```.

## Minimax
### How it works
In minimax algorithm, there are two sides: maximizer and minimizer. Maximizer
aims for highest results and minimizer aims for lowest results. When they are
used in games, they can be thought as opponents.

2048 is a single player game so naturally maximizer is the player who moves the
tiles and minimizer is the computer that places the new tiles.

### Implementation
I have two functions, maximize and minimize. They both take game board array,
alpha, beta and depth as input and return move_t struct typedefs.

My maximizer and minimizer uses the ```rate(int **arr)``` function to return
a score of each game state. The score will be high if there are few large-value
tiles and low if there are many low-value tiles.

Maximizer function generates a list of possible moves that the player can take
in the current game state. It will go through all the possible moves and run
minimizer on them. It checks the ratings returned by minimizer and
compares them to the current rating.

Minimizer works similarly, but goes through all possible spots where the
computer can put a random 2 or 4 tile. It tries to keep the rating as low as
possible.

Both functions are called by each other many times until the depth reaches 0.
Then both functions start returning and the maximizer function can now find out
what is the best performing move.

## Source code files
### main.c
This file has the code which processes command line arguments and handles
starting the correct game mode. It also has code to run comparasion mode of the
different gamemodes.

### game.c and game.h
These files contains the functions and structs for running the 2048 game.
Functions for processing and moving the arrays. These are used from all the
different game modes.

### text_ui.c and text_ui.h
Contains functions for printing the game board to the screen

### player.c and player.h
Contains code for player mode. Changing the terminal mode and getting input
from keyboard.

### random_ai.c and random_ai.h
Functions for running the randomizer mode and randomizer AI

### ai.c and ai.h
Functions and structs of the minimax AI

## Important structs and enums
### game_state_t
Contains the state of the current game (game board, score, amount of moves)

### direction
Enum that maps the directions LEFT, RIGHT, UP and DOWN to ints.

### move_t
It is a struct used to pass data between the max and min functions of the
minimax algorithm

### minmove_t
Struct which contains the coordinates and the value of the tile. Used when
returning the all possible moves the min can make in minimax algorithm.

## Comparison
My application includes a comparasion mode that runs all of the game modes n
times and shows the differences between average, maximum and minimum scores.

## Results
tba

## What could be improved
tba

## Sources
- [https://en.wikipedia.org/wiki/Minimax](https://en.wikipedia.org/wiki/Minimax)
- [https://stackoverflow.com/questions/22342854/what-is-the-optimal-algorithm-for-the-game-2048](https://stackoverflow.com/questions/22342854/what-is-the-optimal-algorithm-for-the-game-2048)
- [https://towardsdatascience.com/playing-2048-with-minimax-algorithm-1-d214b136bffb](https://towardsdatascience.com/playing-2048-with-minimax-algorithm-1-d214b136bffb)

