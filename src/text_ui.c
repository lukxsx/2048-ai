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
    fprintf(stderr, "Simple command line 2048 clone. Can be played with WASD"
                    " keys.\n");
    fprintf(stderr, "Usage: %s [options]\n", program_name);
    fprintf(stderr, "Available options:\n");
    fprintf(stderr, "    -a            Play with minimax AI\n");
    fprintf(stderr, "    -d [value]    Set minimax depth (default is 5)\n");
    fprintf(stderr, "    -s            Play with randomizer AI\n");
    fprintf(stderr, "    -r            Play with randomized input\n");
    fprintf(stderr, "    -t [value]    Delay in milliseconds\n");
    fprintf(stderr, "    -c [runs]     Run in comparison mode\n");
    fprintf(stderr, "    -h            Show this information\n");
}

/*
================================================================================
Print the error message to stderr and exit the application
================================================================================
*/
void error_exit(char *msg) {
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

/*
================================================================================
The following are helper functions to print different parts of the game board
================================================================================
*/
void print_top() {
    printf("╔═══════");
    for (int i = 0; i < 3; i++) {
        printf("╦═══════");
    }
    printf("╗\n");
}

void print_top2() {
    printf("╔═══════");
    for (int i = 0; i < 3; i++) {
        printf("╦═══════");
    }
    printf("╗       ");
    printf("╔═══════");
    for (int i = 0; i < 3; i++) {
        printf("╦═══════");
    }
    printf("╗\n");
}

void print_middle_walls() {
    printf("║       ");
    for (int i = 0; i < 3; i++) {
        printf("║       ");
    }
    printf("║\n");
}

void print_middle_walls2() {
    printf("║       ");
    for (int i = 0; i < 3; i++) {
        printf("║       ");
    }
    printf("║       ");

    printf("║       ");
    for (int i = 0; i < 3; i++) {
        printf("║       ");
    }
    printf("║\n");
}

void print_row_lines() {
    printf("╠═══════");
    for (int i = 0; i < 3; i++) {
        printf("╬═══════");
    }
    printf("╣\n");
}

void print_row_lines2() {
    printf("╠═══════");
    for (int i = 0; i < 3; i++) {
        printf("╬═══════");
    }
    printf("╣       ");

    printf("╠═══════");
    for (int i = 0; i < 3; i++) {
        printf("╬═══════");
    }
    printf("╣\n");
}

void print_only_array(unsigned int *arr) {
    print_top();
    for (int j = 0; j < 4; j++) {
        print_middle_walls();
        for (int i = 0; i < 4; i++) {
            int num = arr[idx(j, i)];
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

        print_middle_walls();
        if (j < 4 - 1) {
            print_row_lines();
        }
    }
    printf("╚═══════");
    for (int i = 0; i < 3; i++) {
        printf("╩═══════");
    }
    printf("╝\n");
}

void print_two_arrays(unsigned int *a, unsigned int *b) {
    print_top2();
    for (int j = 0; j < 4; j++) {
        print_middle_walls2();
        for (int i = 0; i < 4; i++) {
            int num = a[idx(j, i)];
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
        if (j != 1) {
            printf("║       ");
        } else {
            printf("║  -->  ");
        }

        for (int i = 0; i < 4; i++) {
            int num = b[idx(j, i)];
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

        print_middle_walls2();
        if (j < 4 - 1) {
            print_row_lines2();
        }
    }
    printf("╚═══════");
    for (int i = 0; i < 3; i++) {
        printf("╩═══════");
    }
    printf("╝       ");
    printf("╚═══════");
    for (int i = 0; i < 3; i++) {
        printf("╩═══════");
    }
    printf("╝\n");
}

/*
================================================================================
This prints the game board
================================================================================
*/
void print_array(game_state_t *game) {
    printf("SCORE: %d   MOVES: %d   BEST: %d\n", game->score, game->moves,
           game->best_tile);
    print_only_array(game->game_array);
}
