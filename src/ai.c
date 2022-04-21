#define _GNU_SOURCE

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game.h"

#include "ai.h"
#include "text_ui.h"

int mss[4] = {0};

move_t maximize(int **arr, int a, int b, int depth);
move_t minimize(int **arr, int a, int b, int depth);

/*
================================================================================
Rate game array state
Returns good score if there are a small amount of large tiles
and bad score if there are many small tiles
================================================================================
*/
int rate(int **arr) {
    int count = 0, sum = 0;

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            int tile = arr[j][i];
            sum += tile;
            if (tile)
                count++;
        }
    }

    return sum / count;
}

/*
================================================================================
Return all moves in a list that max can make (list index maps to direction)
1 = can move, 0 = cannot move
================================================================================
*/
int *available_moves_max(int **arr) {
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
minmove_t *available_moves_min(int **arr) {
    minmove_t *moves = calloc(32, sizeof(minmove_t));
    int **free_tiles = get_free_tiles(arr);
    int lsize = 0;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (free_tiles[j][i] == 1) {
                minmove_t m2;
                m2.i = i;
                m2.j = j;
                m2.tile = 2;
                moves[lsize] = m2;
                lsize++;
                minmove_t m4;
                m4.i = i;
                m4.j = j;
                m4.tile = 4;
                moves[lsize] = m4;
                lsize++;
            }
        }
    }

    free_game_array(free_tiles);
    return moves;
}

/*
================================================================================
Returns true if the game is in a terminal state. The side is chosen with the min
variable. For max the game is over if no move can be made. For min the game is
over if no tiles can be placed.
================================================================================
*/
int is_terminal(int **arr, int min) {
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
move_t maximize(int **arr, int a, int b, int depth) {
    move_t this;
    this.arr = NULL;
    this.score = -1;
    this.dir = RIGHT;

    if (depth == 0 || is_terminal(arr, 0)) {
        this.score = rate(arr);
        return this;
    }

    depth--; // Reduce depth by one

    int *max_move_list = available_moves_max(arr); // List of possible moves

    for (int i = 0; i < 4; i++) { // Go over all available moves for max
        if (max_move_list[i] == 1) {

            // Make a copy of the input array
            int **temp = copy_game_array(arr);

            // Try each move and run minimize on it
            // printf("MAX: Trying to move to %d\n", i);
            move(temp, (direction)i);
            move_t min = minimize(temp, a, b, depth);
            // printf("Min rate: %d\n", min.score);
            if (min.score > this.score) {
                // Set this arr as temp, free existing array if any
                if (this.arr != NULL) {
                    free_game_array(this.arr);
                }
                this.arr = copy_game_array(temp);
                this.dir = (direction)i;

                // Now we can free temp array and array returned by minimize
                free_game_array(temp);
                if (min.arr != NULL)
                    free_game_array(min.arr);

                // Replace the score with the better score
                this.score = min.score;
            }

            if (this.score >= b)
                break;
            if (this.score > a)
                a = this.score;
        }
    }
    free(max_move_list); // Free the move list after use

    return this;
}

/*
================================================================================
Min function of the minimax algorithm
================================================================================
*/
move_t minimize(int **arr, int a, int b, int depth) {
    move_t this;
    this.arr = NULL;
    this.score = INT_MAX;
    this.dir = RIGHT;

    if (depth == 0 || is_terminal(arr, 1)) {
        this.score = rate(arr);
        return this;
    }

    depth--;

    minmove_t *mm_list = available_moves_min(arr); // Possible moves for min
    for (int i = 0; i < 32; i++) { // Go over all available moves for min

        minmove_t mm = mm_list[i]; // Helper variable for list access
        if (!mm.tile)
            continue; // skip empty list items

        // Make a copy of the input array
        int **temp = copy_game_array(arr);

        // Create a tile and run maximize
        create_tile(temp, mm.i, mm.j, mm.tile);
        move_t max = maximize(temp, a, b, depth);

        if (max.score < this.score) {
            // Set this arr as temp, free existing array if any
            if (this.arr != NULL)
                free_game_array(this.arr);
            this.arr = copy_game_array(temp);

            // Now we can free temp array and array returned by maximize
            free_game_array(temp);
            if (max.arr != NULL)
                free_game_array(max.arr);

            // Replace this score with score returned by maximize
            this.score = max.score;
        }

        if (this.score <= a)
            break;
        if (this.score < b)
            b = this.score;
    }

    free(mm_list); // Free minimize move list

    return this;
}

/*
================================================================================
Runs the minimax algorithm and returns the best move it determines
================================================================================
*/
direction get_best_move(int **arr) {
    move_t m = maximize(arr, -1, INT_MAX, 5);

    // direction best = which_direction(arr, m.arr);
    direction best = m.dir;
    printf("BEST: %d\n", best);
    mss[(int)best]++;
    free_game_array(m.arr);
    return best;
}

int ai_play(int delay) {
    int score = 0;
    srand(time(NULL)); // Set random seed

    game_state_t *ai_game = new_game();
    create_random_tile(ai_game);
    create_random_tile(ai_game);
    print_array(ai_game);
    while (!is_terminal(ai_game->game_array, 0)) {
        move_game(ai_game, get_best_move(ai_game->game_array));
        print_array(ai_game);
        usleep(1000 * delay);
    }
    score = ai_game->score;
    end_game(ai_game);
    printf("LEFT: %d RIGHT: %d UP: %d DOWN %d\n", mss[0], mss[1], mss[2],
           mss[3]);
    return score;
}
