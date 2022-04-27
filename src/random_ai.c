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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "text_ui.h"

/*
================================================================================
Returns a random direction
================================================================================
*/
direction get_random_direction() {
    int dir = rand() % 4;
    if (dir == 0)
        return LEFT;
    if (dir == 1)
        return RIGHT;
    if (dir == 2)
        return UP;
    if (dir == 3)
        return DOWN;
    return LEFT; // default
}

/*
================================================================================
Play the game with randomized input. If boolean end is specified, play until the
end.
================================================================================
*/
void play_random(game_state_t *game, int end) {

    if (end) { // play to the end
        while (!is_array_full(game->game_array))
            move_game(game, get_random_direction());
    } else { // play just one round
        move_game(game, get_random_direction());
    }
}

/*
================================================================================
Move in desired direction. But if cannot move, choose some other direction
================================================================================
*/
void move_if_can(game_state_t *game, direction dir) {
    if (move_game(game, dir)) { // check if can move?
        return;
    } else { // if not, try random directions until can
        for (;;)
            if (move_game(game, get_random_direction())) {
                return;
            }
    }
}

// Function to calculate the maximum value
int max(int a, int b) { return a >= b ? a : b; }

/*
================================================================================
Decide the next direction based on the score of randomized play
================================================================================
*/
void decide_move(game_state_t *bgame, game_state_t *l, game_state_t *r,
                 game_state_t *u, game_state_t *d) {
    // determine the maximum score
    int maxscore = max(max(l->score, r->score), max(u->score, d->score));

    // choose the best direction based on the score, and try to move the game
    if (l->score == maxscore) {
        move_if_can(bgame, LEFT);
    } else if (r->score == maxscore) {
        move_if_can(bgame, RIGHT);
    } else if (u->score == maxscore) {
        move_if_can(bgame, UP);
    } else {
        move_if_can(bgame, DOWN);
    }
}

/*
================================================================================
Play the game with simple AI or just play the game to the end with randomized
input. Returns the score of the game.
================================================================================
*/
int random_ai_play(int delay, int ai, int print) {
    // Set random seed
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    srand(t.tv_nsec);

    int score = 0;

    game_state_t *bgame = new_game();

    create_random_tile(bgame->game_array);
    create_random_tile(bgame->game_array);
    if (print)
        print_array(bgame);

    // If AI boolean is not set, just play the game randomly without the "AI"
    if (!ai) {
        while (!is_array_full(bgame->game_array)) {
            play_random(bgame, 0);
            if (print)
                print_array(bgame);
            usleep(delay * 1000);
        }
        score = bgame->score;
        free(bgame);
        return score;
    }

    // Play the game with AI until the end
    while (!is_array_full(bgame->game_array)) {
        // Make 4 identical copies of the game
        game_state_t *left = calloc(1, sizeof(game_state_t));
        game_state_t *right = calloc(1, sizeof(game_state_t));
        game_state_t *up = calloc(1, sizeof(game_state_t));
        game_state_t *down = calloc(1, sizeof(game_state_t));
        left = memcpy(left, bgame, sizeof(game_state_t));
        right = memcpy(right, bgame, sizeof(game_state_t));
        up = memcpy(up, bgame, sizeof(game_state_t));
        down = memcpy(down, bgame, sizeof(game_state_t));

        // Advance each of these games to different directions
        move_game(left, LEFT);
        move_game(right, RIGHT);
        move_game(up, UP);
        move_game(down, DOWN);

        // Play every copy to the end with randomized input
        play_random(left, 1);
        play_random(right, 1);
        play_random(up, 1);
        play_random(down, 1);

        // Determine which score is the best and advance the main game with
        // that direction
        decide_move(bgame, left, right, up, down);

        if (print)
            print_array(bgame);

        // Cleanup the copies
        free(left);
        free(right);
        free(up);
        free(down);

        if (delay)
            usleep(1000 * delay); // add delay
    }
    score = bgame->score;
    free(bgame);
    return score;
}
