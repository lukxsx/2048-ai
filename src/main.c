#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "player.h"
#include "random_ai.h"
#include "text_ui.h"

int main(int argc, char **argv) {
    // Process the command line options
    int opt, ai_mode = 0, delay = 0;
    while ((opt = getopt(argc, argv, "uart:h")) != -1) {
        switch (opt) {
        case 'a':
            ai_mode = 1;
            break;
        case 'h':
            printusage(argv[0]);
            exit(EXIT_SUCCESS);
        case 'r':
            ai_mode = 2;
            break;
        case 't':
            delay = atoi(optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            printusage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (ai_mode == 1) { // start in AI mode
        printf("AI mode enabled\n");

    } else if (ai_mode == 2) {
        random_ai_play(delay);
    } else {
        play(); // play the game normally
    }

    exit(EXIT_SUCCESS);
}
