#ifndef GAME_H
#define GAME_H


// A struct to hold the current game state and variables
typedef struct {
	int **game_array;
	int score;
	int moves;
} game_state_t;


typedef enum movement {
	LEFT,
	RIGHT,
	UP,
	DOWN
} direction;


/*
================================================================================
Allocate a 4x4 array and set everything to 0.
Returns NULL in case of memory allocation error.
================================================================================
*/
int** init_game_array();


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
game_state_t* new_game();


/*
================================================================================
Makes a copy of the given game_state_t and returns a pointer to the copy
================================================================================
*/
game_state_t* copy_game(game_state_t *old);


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
int is_array_full(game_state_t *game);


/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(int **game_array, int x, int y);


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
void combine(int* a, int n, game_state_t *game);


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
work in progress..
================================================================================
*/
void move(game_state_t *game, direction dir);




#endif
