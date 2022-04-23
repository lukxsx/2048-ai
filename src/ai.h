#ifndef AI_H
#define AI_H

typedef struct {
    int score;
    direction dir;
} move_t;

typedef struct {
    int index;
    int tile;
} minmove_t;

unsigned int ai_play(int delay, int print);

int rate(unsigned int *arr);

minmove_t *available_moves_min(unsigned int *arr);

move_t maximize(unsigned int *arr, int a, int b, int depth);

move_t minimize(unsigned int *arr, int a, int b, int depth);

int is_terminal(unsigned int *arr, int min);

#endif
