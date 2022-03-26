/*
--------------------------------------------------------------------------------
This file contains the game logic of the 2048 game.
Creating game, ending game, allocating arrays and moving and combining tiles
--------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "game.h"
#include "text_ui.h"


/*
================================================================================
Allocate a 4x4 array and set everything to 0.
Returns NULL in case of memory allocation error.
================================================================================
*/
int** init_game_array() {
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
game_state_t* new_game() {
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
game_state_t* copy_game(game_state_t *old) {
    game_state_t *new = malloc(sizeof(game_state_t));
    new->score = old->score;
    new->moves = old->moves;

    new->game_array = init_game_array();
    for (int i = 0; i < 4; i++) {
        new->game_array[i] = memcpy(new->game_array[i], old->game_array[i],
            (4 * sizeof(int)));
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
            if (game->game_array[j][i] == 0) return 0;
        }
    }
    return 1;
}


/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(int **game_array, int x, int y) {
    if (game_array[y][x] != 0) {
        return 0;
    }
    else return 1;
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
    for ( ; ; ) {
        rx = rand() % 4;
        ry = rand() % 4;
        if (is_tile_empty(game->game_array, rx, ry)) {
            break;
        }
    }

    game->game_array[ry][rx] = value;
}


/*
================================================================================
Combines the same numbers in an array. Also updates the score.
================================================================================
*/
void combine(int* a, int n, game_state_t *game) {
    for (int i = 0; i < n; i++) {
        if (i < n-1) {
            if (a[i] == a[i+1] && a[i] != 0) {
                a[i] = a[i] * 2;
                game->score += a[i];
                a[i+1] = 0;
            }
        }
    }
}


/*
================================================================================
Helper function that moves all tiles to the left.
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
This function moves the tiles to specified direction. Only left is implemented
so far.
================================================================================
*/
void move(game_state_t *game, direction dir){
    if (dir == LEFT) {
        for (int i = 0; i < 4; i++) {
            printf("moving to left\n");
            move_all_left(game->game_array[i], 4);
            combine(game->game_array[i], 4, game);
            move_all_left(game->game_array[i], 4);
        }
    }
    print_array(game);
}
