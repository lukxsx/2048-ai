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
Makes a copy of the given game_state_t and returns a pointer to the copy
================================================================================
*/
game_state_t *copy_game(game_state_t *old) {
    game_state_t *new = malloc(sizeof(game_state_t));
    new->score = old->score;
    new->moves = old->moves;

    new->game_array = init_game_array();
    for (int i = 0; i < 4; i++) {
        new->game_array[i] =
            memcpy(new->game_array[i], old->game_array[i], (4 * sizeof(int)));
    }
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
int is_array_full(game_state_t *game) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (game->game_array[j][i] == 0)
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
void combine(int *a, int n, game_state_t *game, int *modflag) {
    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            if (a[i] == a[i + 1] && a[i] != 0) {
                a[i] = a[i] * 2;
                game->score += a[i];
                *modflag = 1;
                a[i + 1] = 0;
            }
        }
    }
}

/*
================================================================================
Helper function that moves all tiles to the left. Updates the modification flag
if something is changed.
================================================================================
*/
void move_all_left(int *a, int n, int *modflag) {
    int last = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            continue;
        }
        if (a[i] != 0) {
            a[last] = a[i];
            if (i != last) {
                a[i] = 0;
                *modflag = 1;
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
*/
void move_array(int *array, game_state_t *game, int *modflag) {
    move_all_left(array, 4, modflag);
    combine(array, 4, game, modflag);
    move_all_left(array, 4, modflag);
}

int can_move(game_state_t *game, direction dir) {
    game_state_t *temp = copy_game(game);
    int can = move(temp, dir);
    end_game(temp);
    if (can) {
        return 1;
    } else {
        return 0;
    }
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


direction which_direction(game_state_t *current, game_state_t *compare) {
    direction d = LEFT;
    if (can_move(current, LEFT)) {
        game_state_t *temp = copy_game(current);
        move(temp, LEFT);
        if (compare_game(compare, temp)) d = LEFT;
        end_game(temp);
        return d;
    }
    if (can_move(current, RIGHT)) {
        game_state_t *temp = copy_game(current);
        move(temp, RIGHT);
        if (compare_game(compare, temp)) d = RIGHT;
        end_game(temp);
        return d;
    }
    if (can_move(current, UP)) {
        game_state_t *temp = copy_game(current);
        move(temp, UP);
        if (compare_game(compare, temp)) d = UP;
        end_game(temp);
        return d;
    }
    
    return DOWN;
}

/*
================================================================================
This function moves the tiles to specified direction.
Using a modification flag that is set if something is changed in the array.
Only add a new tile and process move if a change has happened.
================================================================================
*/
int move(game_state_t *game, direction dir) {
    int modflag = 0;
    int *flag = &modflag;

    if (dir == LEFT) {
        for (int i = 0; i < 4; i++) {
            move_array(game->game_array[i], game, flag);
        }
    } else if (dir == RIGHT) {
        for (int i = 0; i < 4; i++) {
            int *arr = game->game_array[i];
            reverse_array(arr, 4);
            move_array(arr, game, flag);
            reverse_array(arr, 4);
        }
    } else if (dir == UP) {
        for (int i = 0; i < 4; i++) {
            int temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = game->game_array[j][i];
            }
            move_array(temp, game, flag);
            for (int j = 0; j < 4; j++) {
                game->game_array[j][i] = temp[j];
            }
        }
    } else if (dir == DOWN) {
        for (int i = 0; i < 4; i++) {
            int temp[4];
            for (int j = 0; j < 4; j++) {
                temp[j] = game->game_array[j][i];
            }
            reverse_array(temp, 4);
            move_array(temp, game, flag);
            reverse_array(temp, 4);
            for (int j = 0; j < 4; j++) {
                game->game_array[j][i] = temp[j];
            }
        }
    }

    if (modflag) {
        create_random_tile(game);
        game->moves++;
        return 1;
    }
    return 0;
    // print_array(game);
}
