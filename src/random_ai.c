/*
================================================================================
This file has code for a very stupid "AI"
1. At every turn, make 4 additional copies of the game.
2. Play each of them one turn in different directions (LEFT, RIGHT, UP and DOWN)
3. Play each of these games with randomized input until they are full
4. Compare the four games, and check which one has the best score
5. Choose the next move for game based on which direction ended up getting
   the best score
================================================================================
*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "text_ui.h"

void play_random(game_state_t *game) {
    while (!is_array_full(game)) {
        int dir = rand() % 4;
        if (dir == 0)
            move(game, LEFT);
        if (dir == 1)
            move(game, RIGHT);
        if (dir == 2)
            move(game, UP);
        if (dir == 3)
            move(game, DOWN);
    }
}

int max(int a, int b) { return a >= b ? a : b; }

void random_ai_play(int delay) {
    game_state_t *bgame = new_game();

    create_random_tile(bgame);
    create_random_tile(bgame);
    print_array(bgame);

    while (!is_array_full(bgame)) {
        // Make 4 identical copies of the game
        game_state_t *left = copy_game(bgame);
        game_state_t *right = copy_game(bgame);
        game_state_t *up = copy_game(bgame);
        game_state_t *down = copy_game(bgame);

        // Advance each of these games to different directions
        move(left, LEFT);
        move(right, RIGHT);
        move(up, UP);
        move(down, DOWN);

        // Play every copy to the end with randomized input
        play_random(left);
        play_random(right);
        play_random(up);
        play_random(down);

        // Determine which score is the best and advance the main game with
        // that direction
        int maxscore =
            max(max(left->score, right->score), max(up->score, down->score));
        if (left->score == maxscore) {
            move(bgame, LEFT);
        } else if (right->score == maxscore) {
            move(bgame, RIGHT);
        } else if (up->score == maxscore) {
            move(bgame, UP);
        } else {
            move(bgame, DOWN);
        }

        print_array(bgame);

        // Cleanup the copies
        end_game(left);
        end_game(right);
        end_game(up);
        end_game(down);

        if (delay)
            usleep(1000 * delay);
    }
    end_game(bgame);
}
