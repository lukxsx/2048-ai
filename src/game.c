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
Initializes a new game. Returns a new game_state_t
================================================================================
*/

game_state_t *new_game() {
    game_state_t *game = malloc(sizeof(game_state_t));
    memset(game->game_array, 0, 16 * sizeof(unsigned int));
    game->score = 0;
    game->moves = 0;
    return game;
}

/*
================================================================================
Makes a copy of a game array
================================================================================
*/
void copy_game_array(unsigned int *new, unsigned int *old) {
    new = memcpy(new, old, 16 * sizeof(unsigned int));
}


/*
================================================================================
Returns true if the whole array is full (and the game is over)
================================================================================
*/
int is_array_full(unsigned int *arr) {

    /*
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (arr[j][i] == 0)
                return 0;
        }
    }*/

    for (int i = 0; i < 16; i++) {
        if (arr[i] == 0) {
            return 0;
        }
    }

    return 1;
}

void get_free_tiles(unsigned int *arr, int *ret) {
    for (int i = 0; i < 16; i++) {
        if (arr[i] == 0)
            ret[i] = 1;
    }

    /*
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (game_array[j][i] == 0)
                ga[j][i] = 1;
        }
    }
    return ga;
    */
}

/*
================================================================================
Returns true if a tile on the array is empty
================================================================================
*/
int is_tile_empty(unsigned int *arr, int y, int x) {
    if (arr[idx(y, x)] != 0) {
        return 0;
    }
    return 1;
}

/*
================================================================================
Creates a new tile in specific coordinates (no checking)
================================================================================
*/
void create_tile(unsigned int *arr, int y, int x, int value) {
    arr[idx(y, x)] = value;
}

/*
================================================================================
Creates a new tile in index
================================================================================
*/
void create_tile_index(unsigned int *arr, int index, int value) {
    arr[index] = value;
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
    int ry, rx;

    // Trying random coordinates until an empty tile is found
    for (;;) {
        ry = rand() % 4;
        rx = rand() % 4;
        if (is_tile_empty(game->game_array, ry, rx)) {
            break;
        }
    }

    create_tile(game->game_array, ry, rx, value);
}

/*
================================================================================
Combines the same numbers in an array. Also updates the score and sets the
modification flag if something is changed.
================================================================================
*/
unsigned int combine(unsigned int *arr) {
    unsigned int score = 0;
    for (int i = 0; i < 4; i++) {
        if (i < 3) {
            if (arr[i] == arr[i + 1] && arr[i] != 0) {
                arr[i] = arr[i] * 2;
                score += arr[i];
                arr[i + 1] = 0;
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
void move_all_left(unsigned int *arr) {
    int last = 0;
    for (int i = 0; i < 4; i++) {
        if (arr[i] == 0) {
            continue;
        }
        if (arr[i] != 0) {
            arr[last] = arr[i];
            if (i != last) {
                arr[i] = 0;
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
void reverse_array(unsigned int *arr) {
    int temp[4];

    for (int i = 0; i < 4; i++) {
        temp[3 - i] = arr[i];
    }
    for (int i = 0; i < 4; i++) {
        arr[i] = temp[i];
    }
}

/*
================================================================================
This function performs the actions to move the array.
First move everything to left side, then run the combination algorithm and then
move everything to left side again.
================================================================================
*/
unsigned int move_array(unsigned int *arr) {
    unsigned int score = 0;
    move_all_left(arr);
    score = combine(arr);
    move_all_left(arr);
    return score;
}

/*
================================================================================
Functions to check if an array can be moved to different directions
================================================================================
*/
int can_move_left(unsigned int *arr) {
    for (int j = 0; j < 4; j++) {
        int x = -1;
        for (int i = 3; i > -1; i--) {
            if (arr[idx(j, i)] != 0) {
                x = i;
                break;
            }
        }
        if (x > -1) {
            for (int i = x; i > 0; i--) {
                if (!(arr[idx(j, i - 1)]) ||
                    arr[idx(j, i)] == arr[idx(j, i - 1)]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int can_move_right(unsigned int *arr) {
    for (int j = 0; j < 4; j++) {
        int x = -1;

        for (int u = 0; u < 4; u++) {
        }
        for (int i = 0; i < 4; i++) {
            if (arr[idx(j, i)] != 0) {
                x = i;
                break;
            }
        }
        if (x > -1) {
            for (int i = x; i < 3; i++) {
                if (!(arr[idx(j, i + 1)]) ||
                    arr[idx(j, i)] == arr[idx(j, i + 1)])
                    return 1;
            }
        }
    }
    return 0;
}

int can_move_down(unsigned int *arr) {
    for (int i = 0; i < 4; i++) {
        int x = -1;
        for (int j = 0; j < 4; j++) {
            if (arr[idx(j, i)] != 0) {
                x = j;
                break;
            }
        }
        if (x > -1) {
            for (int j = x; j < 3; j++) {
                if (!(arr[idx(j + 1, i)]) ||
                    arr[idx(j, i)] == arr[idx(j + 1, i)])
                    return 1;
            }
        }
    }
    return 0;
}

int can_move_up(unsigned int *arr) {
    for (int i = 0; i < 4; i++) {
        for (int u = 0; u < 4; u++) {
        }
        int x = -1;
        for (int j = 3; j > -1; j--) {
            if (arr[idx(j, i)] != 0) {
                x = j;
                break;
            }
        }
        if (x > -1) {
            for (int j = x; j > 0; j--) {
                if (!(arr[idx(j - 1, i)]) ||
                    arr[idx(j, i)] == arr[idx(j - 1, i)]) {
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
int can_move(unsigned int *arr, direction dir) {
    if (dir == LEFT)
        return can_move_left(arr);
    if (dir == RIGHT)
        return can_move_right(arr);
    if (dir == UP)
        return can_move_up(arr);
    if (dir == DOWN)
        return can_move_down(arr);
    return 0;
}

/*
================================================================================
This function moves the tiles to specified direction without any checks.
Returns the score.
================================================================================
*/
unsigned int move(unsigned int *arr, direction dir) {
    unsigned int score = 0;

    if (dir == LEFT) {
        for (int i = 0; i < 16; i += 4) {
            score += move_array(arr + i);
        }
    } else if (dir == RIGHT) {
        for (int i = 0; i < 16; i += 4) {
            unsigned int temp[4];
            memcpy(temp, (arr + i), 4 * sizeof(unsigned int));
            reverse_array(temp);
            score += move_array(temp);
            reverse_array(temp);
            memcpy((arr + i), temp, 4 * sizeof(unsigned int));
        }
    } else if (dir == UP) {
        unsigned int temp[4];

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[j] = arr[idx(j, i)];
            }
            score += move_array(temp);
            for (int j = 0; j < 4; j++) {
                arr[idx(j, i)] = temp[j];
            }
        }
    } else if (dir == DOWN) {
        unsigned int temp[4];

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[j] = arr[idx(j, i)];
            }
            reverse_array(temp);
            score += move_array(temp);
            reverse_array(temp);
            for (int j = 0; j < 4; j++) {
                arr[idx(j, i)] = temp[j];
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
