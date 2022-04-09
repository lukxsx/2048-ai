/*
================================================================================
This file contains the game logic of the 2048 game.
Creating game, ending game, allocating arrays and moving and combining tiles
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "text_ui.h"

/*
================================================================================
Allocate a 4x4 array and set everything to 0.
Returns NULL in case of memory allocation error.
================================================================================
*/
int **init_game_array() {
    int **game_array;
    game_array = calloc(4, sizeof(int *));
    if (!game_array) {
        return NULL;
    }

    for (int j = 0; j < 4; j++) {
        game_array[j] = calloc(4, sizeof(int));
        if (!game_array[j]) {
            for (int i = 0; i < j; i++) {
                free(game_array[i]);
            }
            free(game_array);
            return NULL;
        }
    }
    return game_array;
}

/*
================================================================================
Frees the allocated memory of the game array
================================================================================
*/
void free_game_array(int **game_array) {
    for (int i = 0; i < 4; i++) {
        free(game_array[i]);
    }
    free(game_array);
}

/*
================================================================================
Initializes a new game. Returns a new game_state_t
================================================================================
*/
game_state_t *new_game() {
    game_state_t *game = malloc(sizeof(game_state_t));
    game->game_array = init_game_array();
    if (game->game_array == NULL) {
        error_exit("Failed to allocate the game array\n");
    }
    game->score = 0;
    game->moves = 0;
    return game;
}

/*
================================================================================
Makes a copy of a game array
================================================================================
*/
int **copy_game_array(int **old) {
    int **new = init_game_array();

    for (int i = 0; i < 4; i++) {
        new[i] =
            memcpy(new[i], old[i], (4 * sizeof(int)));
    }
    return new;
}

/*
================================================================================
Makes a copy of the given game_state_t and returns a pointer to the copy
================================================================================
*/
game_state_t *copy_game(game_state_t *old) {
    game_state_t *new = malloc(sizeof(game_state_t));
    new->score = old->score;
    new->moves = old->moves;

    new->game_array = copy_game_array(old->game_array);
    
    return new;
}

/*
================================================================================
Frees the current game
================================================================================
*/
void end_game(game_state_t *game) {
    free_game_array(game->game_array);
    free(game);
}

/*
================================================================================
Returns true if the whole array is full (and the game is over)
================================================================================
*/
int is_array_full(int **arr) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (arr[j][i] == 0)
                return 0;
        }
    }
    return 1;
}

int **get_free_tiles(int **game_array) {
    int **ga = init_game_array();
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (game_array[j][i] == 0)
                ga[j][i] = 1;
        }
    }
    return ga;
}

/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(int **game_array, int x, int y) {
    if (game_array[y][x] != 0) {
        return 0;
    } else
        return 1;
}


/*
================================================================================
Creates a new tile in specific coordinates (no checking)
================================================================================
*/
void create_tile(game_state_t *game, int x, int y, int value) {
    game->game_array[y][x] = value;
}

/*
================================================================================
Creates a new tile in random (empty) coordinates
================================================================================
*/
void create_random_tile(game_state_t *game) {
    // Create 2 with probability of 75%, 4 with probability of 25%
    int prob = (rand() & 1) | (rand() & 1);
    int value = prob ? 2 : 4;
    int rx, ry;

    // Trying random coordinates until an empty tile is found
    for (;;) {
        rx = rand() % 4;
        ry = rand() % 4;
        if (is_tile_empty(game->game_array, rx, ry)) {
            break;
        }
    }

    create_tile(game, rx, ry, value);
}

/*
================================================================================
Combines the same numbers in an array. Also updates the score and sets the
modification flag if something is changed.
================================================================================
*/
int combine(int *a, int n) {
    int score = 0;
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            if (a[i] == a[i + 1] && a[i] != 0) {
                a[i] = a[i] * 2;
                score += a[i];
                a[i + 1] = 0;
            }
        }
    }
    return score;
}

/*
================================================================================
Helper function that moves all tiles to the left. Updates the modification flag
if something is changed.
================================================================================
*/
void move_all_left(int *a, int n) {
    int last = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            continue;
        }
        if (a[i] != 0) {
            a[last] = a[i];
            if (i != last) {
                a[i] = 0;
            }
            last++;
        }
    }
}

/*
================================================================================
Reverses one-dimensional array of n length
================================================================================
*/
void reverse_array(int *array, int n) {
    int temp[4];

    for (int i = 0; i < n; i++) {
        temp[n - 1 - i] = array[i];
    }
    for (int i = 0; i < n; i++) {
        array[i] = temp[i];
    }
}

/*
================================================================================
This function performs the actions to move the array.
First move everything to left side, then run the combination algorithm and then
move everything to left side again.
================================================================================
*/
int move_array(int *array) {
    int score = 0;
    move_all_left(array, 4);
    score = combine(array, 4);
    move_all_left(array, 4);
    return score;
}

/*
================================================================================
Functions to check if an array can be moved to different directions
================================================================================
*/
int can_move_left(int **arr) {
    for (int j = 0; j < 4; j++) {
        int x = -1;
        for (int i = 3; i > -1; i--) {
            if (arr[j][i] != 0) {
                x = i;
                break;
            }
        }
        if (x > -1) {
            for (int i = x; i > 0; i--) {
                if (!(arr[j][i-1]) || arr[j][i] == arr[j][i-1]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int can_move_right(int **arr) {
    for (int j = 0; j < 4; j++) {
        int x = -1;
        
        for (int u = 0; u < 4; u++) {
        }
        for (int i = 0; i < 4; i++) {
            if (arr[j][i] != 0) {
                x = i;
                break;
            }
        }
        if (x > -1) {
            for (int i = x; i < 3; i++) {
                if (!(arr[j][i+1]) || arr[j][i] == arr[j][i+1]) return 1;
            }
        }
    }
    return 0;
}

int can_move_down(int **arr) {
    for (int i = 0; i < 4; i++) {
        int x = -1;
        for (int j = 0; j < 4; j++) {
            if (arr[j][i] != 0) {
                x = j;
                break;
            }
        }
        if (x > -1) {
            for (int j = x; j < 3; j++) {
                if (!(arr[j+1][i]) || arr[j][i] == arr[j+1][i]) return 1;
            }
        }
    }
    return 0;
}


int can_move_up(int **arr) {
    for (int i = 0; i < 4; i++) {
        for (int u = 0; u < 4; u++) {
        }
        int x = -1;
        for (int j = 3; j > -1; j--) {
            if (arr[j][i] != 0) {
                x = j;
                break;
            }
        }
        if (x > -1) {
            for (int j = x; j > 0; j--) {
                if (!(arr[j-1][i]) || arr[j][i] == arr[j-1][i]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

/*
================================================================================
Check if an array can be moved to specific direction
================================================================================
*/
int can_move(int **arr, direction dir) {
    if (dir == LEFT) return can_move_left(arr);
    if (dir == RIGHT) return can_move_right(arr);
    if (dir == UP) return can_move_up(arr);
    if (dir == DOWN) return can_move_down(arr);
    return 0;
}

// return 1 if equals
int compare_game(game_state_t *a, game_state_t *b) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (a->game_array[j][i] != b->game_array[j][i])
                return 0;
        }
    }
    return 1;
    
}




/*
================================================================================
This function moves the tiles to specified direction without any checks.
Returns the score.
================================================================================
*/
int move(int **game, direction dir) {
    int score = 0;

    if (dir == LEFT) {
        for (int i = 0; i < 4; i++) {
            score += move_array(game[i]);
        }
    } else if (dir == RIGHT) {
        for (int i = 0; i < 4; i++) {
            int *arr = game[i];
            reverse_array(arr, 4);
            score += move_array(arr);
            reverse_array(arr, 4);
        }
    } else if (dir == UP) {
            for (int i = 0; i < 4; i++) {
            int temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = game[j][i];
            }
            score += move_array(temp);
            for (int j = 0; j < 4; j++) {
                game[j][i] = temp[j];
            }
        }
    } else if (dir == DOWN) {
        for (int i = 0; i < 4; i++) {
            int temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = game[j][i];
            }
            reverse_array(temp, 4);
            score += move_array(temp);
            reverse_array(temp, 4);
            for (int j = 0; j < 4; j++) {
                game[j][i] = temp[j];
            }
        }
    }
    
        
    return score;
}


/*
================================================================================
Move array in game_state while checking if the move can be made. Return 1 if
move has made, otherwise 0.
================================================================================
*/
int move_game(game_state_t *game, direction dir) {
    if (can_move(game->game_array, dir)) {
        game->score += move(game->game_array, dir);
        game->moves++;
        create_random_tile(game);
        return 1;
    }
    return 0;
}
