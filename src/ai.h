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

int ai_play(int delay, int print);

int rate(unsigned int *arr);

move_t maximize(unsigned int *arr, int a, int b, int depth);

move_t minimize(unsigned int *arr, int a, int b, int depth);

int *available_moves_max(unsigned int *arr);

int is_terminal(unsigned int *arr, int min);

direction get_best_move(unsigned int *arr);

#endif
