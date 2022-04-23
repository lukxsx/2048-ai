#ifndef AI_H
#define AI_H

typedef struct {
    int score;
    direction dir;
} move_t;

typedef struct {
    int i;
    int j;
    int tile;
} minmove_t;

int ai_play(int delay, int print);

int rate(int **arr);

move_t maximize(int **arr, int a, int b, int depth);

move_t minimize(int **arr, int a, int b, int depth);

int *available_moves_max(int **arr);

int is_terminal(int **arr, int min);

direction int_to_dir(int i);

direction get_best_move(int **arr);

#endif
