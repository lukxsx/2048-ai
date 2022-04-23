#define _GNU_SOURCE

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "game.h"

#include "ai.h"
#include "text_ui.h"

move_t maximize(unsigned int *arr, int a, int b, int depth);
move_t minimize(unsigned int *arr, int a, int b, int depth);

/*
================================================================================
Rate game array state
Returns good score if there are a small amount of large tiles
and bad score if there are many small tiles
================================================================================
*/
int rate(unsigned int *arr) {
    int count = 0;
    unsigned int sum = 0;

    for (int i = 0; i < 16; i++) {
        unsigned int tile = arr[i];
        sum += tile;
        if (tile) {
            count++;
        }
    }

    return sum / count;
}

/*
================================================================================
Lists all moves that min can make as minmove_t structs (defined in ai.h)
Max 32 items. Tile value will be 0 if the move cannot be made.
================================================================================
*/
minmove_t *available_moves_min(unsigned int *arr) {
    minmove_t *moves = calloc(32, sizeof(minmove_t)); // allocate space for
    int *free_tiles = calloc(16, sizeof(int));        // the move list and
    get_free_tiles(arr, free_tiles);                  // the return list
    int lsize = 0;
    for (int i = 0; i < 16; i++) {
        if (free_tiles[i] == 1) { // add both 4 and 2 variants to the list
            minmove_t m2;
            m2.index = i;
            m2.tile = 2;
            moves[lsize] = m2;
            lsize++;
            minmove_t m4;
            m4.index = i;
            m4.tile = 4;
            moves[lsize] = m4;
            lsize++;
        }
    }

    free(free_tiles);
    return moves;
}

/*
================================================================================
Returns true if the game is in a terminal state. The side is chosen with the min
variable. For max the game is over if no move can be made. For min the game is
over if no tiles can be placed.
================================================================================
*/
int is_terminal(unsigned int *arr, int min) {
    if (!min) {
        if (can_move(arr, LEFT))
            return 0;
        if (can_move(arr, RIGHT))
            return 0;
        if (can_move(arr, UP))
            return 0;
        if (can_move(arr, DOWN))
            return 0;
        return 1;
    } else {
        return is_array_full(arr);
    }
}

/*
================================================================================
Max function of the minimax algorithm
================================================================================
*/
move_t maximize(unsigned int *arr, int a, int b, int depth) {
    // initialize the return move_t struct
    move_t this;
    this.score = -1;
    this.dir = UP;

    // stop the recursion if we are on the lowest level
    if (depth == 0 || is_terminal(arr, 0)) {
        this.score = rate(arr);
        return this;
    }

    depth--; // reduce depth by one

    unsigned int temp[16]; // temp array for trying different moves

    // go over all available moves for max and run minimize on them
    for (int i = 0; i < 4; i++) {
        if (can_move(arr, (direction)i)) {

            // copy the input array to temp array
            memcpy(temp, arr, 16 * sizeof(unsigned int));

            move(temp, (direction)i);                 // try moving
            move_t min = minimize(temp, a, b, depth); // call minimize

            if (min.score > this.score) {
                // replace the current direction and score if the returned
                // values are better
                this.dir = (direction)i;
                this.score = min.score;
            }

            // these two checks are for alpha–beta pruning
            if (this.score >= b) {
                break;
            }

            if (this.score > a) {
                a = this.score;
            }
        }
    }

    return this;
}

/*
================================================================================
Min function of the minimax algorithm
================================================================================
*/
move_t minimize(unsigned int *arr, int a, int b, int depth) {
    // initialize the return move_t struct
    move_t this;
    this.score = INT_MAX;
    this.dir = RIGHT;

    // stop the recursion if we are on the lowest level
    if (depth == 0 || is_terminal(arr, 1)) {
        this.score = rate(arr);
        return this;
    }

    depth--; // reduce depth by one

    unsigned int temp[16]; // temp array for trying different moves

    // get a list of all possible moves for min
    minmove_t *mm_list = available_moves_min(arr);

    // go over all available moves for min and run maximize on them
    for (int i = 0; i < 32; i++) {
        minmove_t mm = mm_list[i]; // helper variable for list access

        if (!mm.tile)
            continue; // skip empty list items

        // copy the input array to temp array
        memcpy(temp, arr, 16 * sizeof(unsigned int));

        // create a new tile and run maximize
        create_tile_index(temp, mm.index, mm.tile);
        move_t max = maximize(temp, a, b, depth);

        // replace the current score if the returned score is worse
        // we don't set the direction here because it's only needed by the
        // maximizer function
        if (max.score < this.score) {
            this.score = max.score;
        }

        // these two checks are for alpha–beta pruning
        if (this.score <= a) {
            break;
        }

        if (this.score < b) {
            b = this.score;
        }
    }

    free(mm_list); // free the minimize move list
    return this;
}

direction get_best_move(unsigned int *arr) {
    // get the best move with the minimnax algo
    move_t best_move = maximize(arr, -1, INT_MAX, 5);
    return best_move.dir;
}

unsigned int ai_play(int delay, int print) {
    unsigned int score = 0;
    // set random seed
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    srand(t.tv_nsec);

    // create a new game and two initial tiles
    game_state_t *ai_game = new_game();
    create_random_tile(ai_game);
    create_random_tile(ai_game);

    if (print) {
        print_array(ai_game); // don't print the game array if quiet mode
    }

    // AI game loop
    while (!is_terminal(ai_game->game_array, 0)) {
        

        move_game(ai_game, get_best_move(ai_game->game_array)); // move the array
        if (print) {
            print_array(ai_game); // print array if not in quiet mode
        }

        usleep(1000 * delay); // add delay if specified
    }

    score = ai_game->score; // save the score from the game before freeing
    free(ai_game);

    return score;
}
