#ifndef GAME_H
#define GAME_H

// A struct to hold the current game state and variables
typedef struct {
    unsigned int game_array[16];
    unsigned int score;
    unsigned int moves;
} game_state_t;

typedef enum movement { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3 } direction;

/*
================================================================================
Allocate a 4x4 array and set everything to 0.
Returns NULL in case of memory allocation error.
================================================================================
*/
//int **init_game_array();

/*
================================================================================
Frees the allocated memory of the game array
================================================================================
*/
//void free_game_array(int **game_array);

inline int idx(int y, int x) {
    return (y * 4) + x;
}

/*
================================================================================
Initializes a new game. Returns a new game_state_t
================================================================================
*/
game_state_t *new_game();

/*
================================================================================
Makes a copy of a game array
================================================================================
*/
void copy_game_array(unsigned int *new, unsigned int *old);

/*
================================================================================
Makes a copy of the given game_state_t and returns a pointer to the copy
================================================================================
*/
game_state_t *copy_game(game_state_t *old);

/*
================================================================================
Frees the current game
================================================================================
*/
void end_game(game_state_t *game);

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
Creates a new tile in specific coordinates (no checking)
================================================================================
*/
void create_tile(unsigned int *arr, int y, int x, int value);

/*
================================================================================
Creates a new tile in random (empty) coordinates
================================================================================
*/
void create_random_tile(game_state_t *game);

/*
================================================================================
Combines the same numbers in an array. Also updates the score.
================================================================================
*/
int combine(unsigned int *arr);

/*
================================================================================
Helper function that moves all tiles to the left.
================================================================================
*/
void move_all_left(unsigned int *arr);

/*
================================================================================
Reverses one-dimensional array of n length
================================================================================
*/
void reverse_array(unsigned int *arr);

/*
================================================================================
This function performs the actions to move the array.
First move everything to left side, then run the combination algorithm and then
move everything to left side again.
*/
int move_array(unsigned int *arr);

/*
================================================================================
Move array in a specific direction
================================================================================
*/
int move(unsigned int *arr, direction dir);

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

void get_free_tiles(unsigned int *arr, unsigned int *ret);

#endif
