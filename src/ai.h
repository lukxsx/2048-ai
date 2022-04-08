#ifndef AI_H
#define AI_H

int ai_play(int delay);

int rate(game_state_t *game);

move_t maximize(game_state_t *game, int a, int b, int depth);

move_t minimize(game_state_t *game, int a, int b, int depth);

int *available_moves_max(game_state_t *game);

position *available_moves_min(game_state_t *game);

int is_terminal(game_state_t *game, int min);

direction int_to_dir(int i);

direction get_best_move(game_state_t *game);

#endif
