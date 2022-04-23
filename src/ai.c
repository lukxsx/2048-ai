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
        if (tile)
            count++;
    }

    return sum / count;
}

/*
================================================================================
Return all moves in a list that max can make (list index maps to direction)
1 = can move, 0 = cannot move
================================================================================
*/
int *available_moves_max(unsigned int *arr) {
    int *av = calloc(4, sizeof(int));
    if (can_move(arr, LEFT))
        av[0] = 1;
    if (can_move(arr, RIGHT))
        av[1] = 1;
    if (can_move(arr, UP))
        av[2] = 1;
    if (can_move(arr, DOWN))
        av[3] = 1;
    return av;
}

/*
================================================================================
Lists all moves that min can make as minmove_t structs (defined in ai.h)
Max 32 items. Tile value will be 0 if the move cannot be made.
================================================================================
*/
minmove_t *available_moves_min(unsigned int *arr) {
    minmove_t *moves = calloc(32, sizeof(minmove_t));
    int *free_tiles = calloc(16, sizeof(int));
    get_free_tiles(arr, free_tiles);
    int lsize = 0;
    for (int i = 0; i < 16; i++) {
        if (free_tiles[i] == 1) {
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
    move_t this;
    this.score = -1;
    this.dir = UP;

    if (depth == 0 || is_terminal(arr, 0)) {
        this.score = rate(arr);
        return this;
    }

    depth--; // Reduce depth by one

    unsigned int temp[16]; // = calloc(16, sizeof(unsigned int));

    for (int i = 0; i < 4; i++) { // Go over all available moves for max
        if (can_move(arr, (direction)i)) {

            // Make a copy of the input array
            memcpy(temp, arr, 16 * sizeof(unsigned int));

            // int temp_free = 0;

            // Try each move and run minimize on it
            // printf("MAX: Trying to move to %d\n", i);
            move(temp, (direction)i);

            move_t min = minimize(temp, a, b, depth);
            // printf("Min rate: %d\n", min.score);
            if (min.score > this.score) {
                this.dir = (direction)i;
                // Now we can free temp array and array returned by minimize
                // free_game_array(temp);
                // temp_free = 1;

                // Replace the score with the better score
                this.score = min.score;
            }

            if (this.score >= b) {
                // if (!temp_free) {
                //     free_game_array(temp);
                //     temp_free = 1;
                // }
                break;
            }
            if (this.score > a)
                a = this.score;

            // if (!temp_free) {
            //     free_game_array(temp);
            //     temp_free = 1;
            // }
        }
    }
    // free(temp);
    return this;
}

/*
================================================================================
Min function of the minimax algorithm
================================================================================
*/
move_t minimize(unsigned int *arr, int a, int b, int depth) {
    move_t this;
    this.score = INT_MAX;
    this.dir = RIGHT;

    if (depth == 0 || is_terminal(arr, 1)) {
        this.score = rate(arr);
        return this;
    }

    depth--;

    unsigned int temp[16]; // = calloc(16, sizeof(unsigned int));
    minmove_t *mm_list = available_moves_min(arr); // Possible moves for min

    for (int i = 0; i < 32; i++) { // Go over all available moves for min
        minmove_t mm = mm_list[i]; // Helper variable for list access

        if (!mm.tile)
            continue; // skip empty list items

        // Make a copy of the input array
        memcpy(temp, arr, 16 * sizeof(unsigned int));

        // Create a tile and run maximize
        create_tile_index(temp, mm.index, mm.tile);
        move_t max = maximize(temp, a, b, depth);

        if (max.score < this.score) {

            // Now we can free temp array and array returned by maximize
            // free_game_array(temp);
            // temp_free = 1;

            // Replace this score with score returned by maximize
            this.score = max.score;
        }

        if (this.score <= a) {
            // if (!temp_free) {
            //     free_game_array(temp);
            //     temp_free = 1;
            // }
            break;
        }

        if (this.score < b) {
            b = this.score;
        }

        // if (!temp_free) {
        //     free_game_array(temp);
        //     temp_free = 1;
        // }
    }
    // free(temp);
    free(mm_list); // Free minimize move list
    return this;
}

/*
================================================================================
Runs the minimax algorithm and returns the best move it determines
================================================================================
*/
direction get_best_move(unsigned int *arr) {
    move_t m = maximize(arr, -1, INT_MAX, 5);
    return m.dir;
}

int ai_play(int delay, int print) {
    int score = 0;
    srand(time(NULL)); // Set random seed

    game_state_t *ai_game = new_game();
    create_random_tile(ai_game);
    create_random_tile(ai_game);
    if (print) {
        print_array(ai_game);
    }
    while (!is_terminal(ai_game->game_array, 0)) {
        move_game(ai_game, get_best_move(ai_game->game_array));
        if (print)
            print_array(ai_game); // only print the array if specified
        usleep(1000 * delay);
    }
    score = ai_game->score;
    end_game(ai_game);
    return score;
}
