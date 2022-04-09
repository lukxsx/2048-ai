#ifndef GAME_H
#define GAME_H

// A struct to hold the current game state and variables
typedef struct {
    int **game_array;
    int score;
    int moves;
} game_state_t;


typedef enum movement { LEFT, RIGHT, UP, DOWN, NONE } direction;

/*
================================================================================
Allocate a 4x4 array and set everything to 0.
Returns NULL in case of memory allocation error.
================================================================================
*/
int **init_game_array();

/*
================================================================================
Frees the allocated memory of the game array
================================================================================
*/
void free_game_array(int **game_array);

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
int **copy_game_array(int **old);

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
int is_array_full(int **arr);

/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(int **game_array, int x, int y);

/*
================================================================================
Creates a new tile in specific coordinates (no checking)
================================================================================
*/
void create_tile(game_state_t *game, int x, int y, int value);

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
int combine(int *a, int n);

/*
================================================================================
Helper function that moves all tiles to the left.
================================================================================
*/
void move_all_left(int *a, int n);

/*
================================================================================
Reverses one-dimensional array of n length
================================================================================
*/
void reverse_array(int *array, int n);

/*
================================================================================
This function performs the actions to move the array.
First move everything to left side, then run the combination algorithm and then
move everything to left side again.
*/
int move_array(int *array);

/*
================================================================================
Move array in a specific direction
================================================================================
*/
int move(int **game, direction dir);

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
int can_move(int **arr, direction dir);

int **get_free_tiles(int **game_array);

int compare_game(game_state_t *a, game_state_t *b);

#endif
