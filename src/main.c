#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "player.h"
#include "random_ai.h"
#include "text_ui.h"

void compare(int n) {
    int *rand_scores = calloc(n, sizeof(int));
    int *simp_scores = calloc(n, sizeof(int));
    size_t rand_sum = 0;
    size_t simple_sum = 0;
    int rand_min = INT_MAX;
    int simp_min = INT_MAX;
    int rand_max = 0;
    int simp_max = 0;

    // Test with random input
    for (int i = 0; i < n; i++) {
        rand_scores[i] = random_ai_play(0, 0);
        rand_sum += rand_scores[i];
        if (rand_scores[i] < rand_min)
            rand_min = rand_scores[i];
        if (rand_scores[i] > rand_max)
            rand_max = rand_scores[i];
    }

    // Test with simple AI
    for (int i = 0; i < n; i++) {
        simp_scores[i] = random_ai_play(0, 1);
        simple_sum += simp_scores[i];
        if (simp_scores[i] < simp_min)
            simp_min = simp_scores[i];
        if (simp_scores[i] > simp_max)
            simp_max = simp_scores[i];
    }

    // Calculate averages
    int rand_avg = rand_sum / n;
    int simp_avg = simple_sum / n;

    // Print data
    printf("   Test results (%d runs)\n", n);
    printf("\n");
    printf("Mode    Avg      Min      Max\n");
    printf("──────────────────────────────\n");
    printf("rand    %-5d    %-5d    %-5d\n", rand_avg, rand_min, rand_max);
    printf("simp    %-5d    %-5d    %-5d\n", simp_avg, simp_min, simp_max);
}

int main(int argc, char **argv) {
    // Process the command line options
    int opt, ai_mode = 0, delay = 0, rand = 1, comp = 0;
    while ((opt = getopt(argc, argv, "uc:asrt:h")) != -1) {
        switch (opt) {
        case 'a':
            ai_mode = 1;
            break;
        case 'h':
            printusage(argv[0]);
            exit(EXIT_SUCCESS);
        case 's':
            ai_mode = 2;
            break;
        case 'r':
            ai_mode = 2;
            rand = 0;
            break;
        case 't':
            delay = atoi(optarg);
            break;
        case 'c':
            comp = atoi(optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            printusage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (comp) {
        compare(comp);
        exit(EXIT_SUCCESS);
    }

    if (ai_mode == 1) { // start in AI mode
        printf("AI mode enabled\n");

    } else if (ai_mode == 2) {
        random_ai_play(delay, rand);
    } else {
        play(); // play the game normally
    }

    exit(EXIT_SUCCESS);
}
