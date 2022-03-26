/*
================================================================================
This file contains the functions that print the game array to the screen
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>

#include "game.h"


/*
================================================================================
Print the help (-h option or with unknown option
================================================================================
*/
void printusage(char *program_name) {
    fprintf(stderr, "Simple command line 2048 clone. Can be played with WASD keys.\n");
    fprintf(stderr, "Usage: %s [options]\n", program_name);
    fprintf(stderr, "Available options:\n");
    fprintf(stderr, "    -a    Let AI play the game\n");
    fprintf(stderr, "    -h    Show this information\n");
}


/*
================================================================================
Print the error message to stderr and exit the application
================================================================================
*/void error_exit(char *msg) {
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}


/*
================================================================================
The following are helper functions to print different parts of the game board
================================================================================
*/
void print_top(int x_size) {
    printf("╔═══════");
    for (int i = 0; i < x_size-1; i++) {
        printf("╦═══════");
    }
    printf("╗\n");
}


void print_middle_walls(int x_size) {
    printf("║       ");
        for (int i = 0; i < x_size-1; i++) {
            printf("║       ");
        }
        printf("║\n");
}


void print_row_lines(int x_size) {
    printf("╠═══════");
    for (int i = 0; i < x_size-1; i++) {
        printf("╬═══════");
    }
    printf("╣\n");
}


/*
================================================================================
This prints the game board
================================================================================
*/
void print_array(game_state_t *game) {
    printf("SCORE: %d   MOVES: %d\n", game->score, game->moves);
    print_top(4);
    for (int j = 0; j < 4; j++) {
        print_middle_walls(4);

        for (int i = 0; i < 4; i++) {
            int num = game->game_array[j][i];
            if (num == 0) {
                printf("║       ");
            } else if (num >= 1000) {
                printf("║ %d  ", num);
            } else if (num >= 100 && num < 1000) {
                printf("║  %d  ", num);
            } else if (num >= 10 && num < 100) {
                printf("║   %d  ", num);
            } else {
                printf("║   %d   ", num);
            }

        }
        printf("║\n");

        print_middle_walls(4);
        if (j < 4 - 1) {
            print_row_lines(4);
        }
    }
    printf("╚═══════");
    for (int i = 0; i < 4-1; i++) {
        printf("╩═══════");
    }
    printf("╝\n");
}
