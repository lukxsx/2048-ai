// clang-format off
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "ai.h"
#include "player.h"
#include "random_ai.h"
#include "text_ui.h"
//clang-format on

/*
================================================================================
Runs comparasion on the three algorithms: random input, randomized AI and
minimax AI
================================================================================
*/
void compare(int n, int mmax_depth) {
    int *rand_scores = calloc(n, sizeof(int));
    int *simp_scores = calloc(n, sizeof(int));
    int *mmax_scores = calloc(n, sizeof(int));
    size_t rand_sum = 0;
    size_t simp_sum = 0;
    size_t mmax_sum = 0;
    int rand_min = INT_MAX;
    int simp_min = INT_MAX;
    int mmax_min = INT_MAX;
    int rand_max = 0;
    int simp_max = 0;
    int mmax_max = 0;

    // Test with random input
    for (int i = 0; i < n; i++) {
        rand_scores[i] = random_ai_play(0, 0, 0);
        rand_sum += rand_scores[i];
        if (rand_scores[i] < rand_min)
            rand_min = rand_scores[i];
        if (rand_scores[i] > rand_max)
            rand_max = rand_scores[i];
    }

    // Test with simple AI
    for (int i = 0; i < n; i++) {
        simp_scores[i] = random_ai_play(0, 1, 0);
        simp_sum += simp_scores[i];
        if (simp_scores[i] < simp_min)
            simp_min = simp_scores[i];
        if (simp_scores[i] > simp_max)
            simp_max = simp_scores[i];
    }

    // Test with minimax AI
    for (int i = 0; i < n; i++) {
        mmax_scores[i] = ai_play(0, 0, mmax_depth);
        mmax_sum += mmax_scores[i];
        if (mmax_scores[i] < mmax_min)
            mmax_min = mmax_scores[i];
        if (mmax_scores[i] > mmax_max)
            mmax_max = mmax_scores[i];
    }

    // Calculate averages
    int rand_avg = rand_sum / n;
    int simp_avg = simp_sum / n;
    int mmax_avg = mmax_sum / n;

    // Print data
    printf("   Test results (%d runs)\n", n);
    printf("\n");
    printf("Mode    Avg      Min      Max\n");
    printf("??????????????????????????????????????????????????????????????????????????????????????????\n");
    printf("rand    %-5d    %-5d    %-5d\n", rand_avg, rand_min, rand_max);
    printf("simp    %-5d    %-5d    %-5d\n", simp_avg, simp_min, simp_max);
    printf("mmax    %-5d    %-5d    %-5d\n", mmax_avg, mmax_min, mmax_max);

    free(rand_scores);
    free(simp_scores);
    free(mmax_scores);
}

int main(int argc, char **argv) {
    // Process the command line options
    int opt;
    int ai_mode = 0;
    int delay = 0;
    int rand = 1;
    int comp = 0;
    int mmax_depth = 5;
    int print_out = 1;

    while ((opt = getopt(argc, argv, "c:d:asrt:h")) != -1) {
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
        case 'd':
            mmax_depth = atoi(optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            printusage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    if (mmax_depth < 1) {
        mmax_depth = 1;
    }

    if (comp) {
        compare(comp, mmax_depth);
        exit(EXIT_SUCCESS);
    }

    if (ai_mode == 1) { // start in AI mode
        ai_play(delay, print_out, mmax_depth);

    } else if (ai_mode == 2) {
        random_ai_play(delay, rand, print_out);
    } else {
        play(); // play the game normally
    }

    exit(EXIT_SUCCESS);
}
