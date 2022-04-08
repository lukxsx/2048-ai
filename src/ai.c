#include "game.h"
#include "text_ui.h"

int *available_moves_max(game_state_t *game) {
    static int av[4] = {0, 0, 0, 0};
    if (can_move(game, LEFT))
        av[0] = 1;
    if (can_move(game, RIGHT))
        av[1] = 1;
    if (can_move(game, UP))
        av[2] = 1;
    if (can_move(game, DOWN))
        av[3] = 1;
    return av;
}

int **available_moves_min(game_state_t *game) {
    return get_free_tiles(game->game_array);
}

int is_terminal(game_state_t *game, int min) {
    if (!min) {
        if (can_move(game, LEFT))
            return 0;
        if (can_move(game, RIGHT))
            return 0;
        if (can_move(game, UP))
            return 0;
        if (can_move(game, DOWN))
            return 0;
        return 1;
    } else {
        return is_array_full(game);
    }
}

int maximize(game_state_t *game) { return 0; }

int minimize(game_state_t *game) { return 0; }

int rate(game_state_t *game) {
    int count = 0, sum = 0;

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            int tile = game->game_array[j][i];
            sum += tile;
            if (tile)
                count++;
        }
    }

    return sum / count;
}

int ai_play(int delay) {
    int score = 0;

    return score;
}
