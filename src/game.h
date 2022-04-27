#ifndef GAME_H
#define GAME_H

/*
================================================================================
A struct to hold the game board and game state variables
================================================================================
*/
typedef struct {
    unsigned int game_array[16];
    unsigned int score;
    unsigned int moves;
    unsigned int best_tile;
} game_state_t;

/*
================================================================================
Enum for all 4 directions and to map them to ints
================================================================================
*/
typedef enum { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NONE = 4 } direction;

/*
================================================================================
Converts the X and Y coordinates to integers between 0-15 for easier access
to the game array. Use inline for better efficiency
================================================================================
*/
static inline int idx(int y, int x) { return (4 * y) + x; }

/*
================================================================================
Initializes a new game. Returns a new game_state_t
================================================================================
*/
game_state_t *new_game();

/*
================================================================================
Returns true if the whole array is full (and the game is over)
================================================================================
*/
int is_array_full(unsigned int *arr);

/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(unsigned int *arr, int y, int x);

/*
================================================================================
Creates a new tile in specific coordinates or index (no checking)
================================================================================
*/
void create_tile(unsigned int *arr, int y, int x, int value);
void create_tile_index(unsigned int *arr, int index, int value);

/*
================================================================================
Creates a new tile in random empty coordinates
================================================================================
*/
void create_random_tile(unsigned int *arr);

/*
================================================================================
Combines the same numbers in an array. Returns the score
================================================================================
*/
unsigned int combine(unsigned int *arr);

/*
================================================================================
Helper function that moves all tiles to the left
================================================================================
*/
void move_all_left(unsigned int *arr);

/*
================================================================================
Reverse arrays
================================================================================
*/
void reverse_array(unsigned int *arr);

/*
================================================================================
This function performs the actions to move the array.
First move everything to left side, then run the combination algorithm and then
move everything to left side again. The score is taken from the combine
function.
================================================================================
*/
unsigned int move_array(unsigned int *arr);

/*
================================================================================
This function moves the tiles to specified direction without any checks.
Returns the score.
================================================================================
*/
unsigned int move(unsigned int *arr, direction dir);

/*
================================================================================
Move array in game_state while checking if the move can be made. Return 1 if
move has made, otherwise 0.
================================================================================
*/
int move_game(game_state_t *game, direction dir);

/*
================================================================================
Checks if array can be moved
================================================================================
*/
int can_move(unsigned int *arr, direction dir);

/*
================================================================================
Writes a list of free tiles to ret pointer
================================================================================
*/
void get_free_tiles(unsigned int *arr, int *ret);

#endif
