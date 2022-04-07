#include "game.h"
#include "text_ui.h"

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
