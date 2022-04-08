#define _GNU_SOURCE

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "text_ui.h"

typedef struct {
    direction dir;
    int score;
} move_t;

typedef struct {
    int x;
    int y;
} position;


move_t maximize(game_state_t *game, int a, int b, int depth);
move_t minimize(game_state_t *game, int a, int b, int depth);



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

int *available_moves_max(game_state_t *game) {
    int *av = calloc(4, sizeof(int));
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

position *available_moves_min(game_state_t *game) {
    position *pos = calloc(16, sizeof(position));
    int **free_tiles = get_free_tiles(game->game_array);
    int poscount = 0;
    
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (free_tiles[j][i] == 1) {
                position p;
                p.x = i;
                p.y = j;
                pos[poscount] = p;
                poscount++;
            }
        }
    }
    free(free_tiles);
    return pos;
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

direction int_to_dir(int i) {
    switch (i) {
        case 0:
        return LEFT;
        case 1:
        return RIGHT;
        case 2:
        return UP;
        case 3:
        return DOWN;
    }
    return LEFT;
}


move_t minimize(game_state_t *game, int a, int b, int depth) {
    printf("MINIZIME\n");
    usleep(1000*100);
    direction worst_move = LEFT;
    int worst_score = INT_MAX;
    
    if (depth == 0 || is_terminal(game, 1)) {
        move_t r;
        r.score = rate(game);
        r.dir = NONE;
        return r;
    }
    
    depth--;
    
    position *pos = available_moves_min(game);
    for (int i = 0; i < 16; i++) {
        position p = pos[i];
        game_state_t *temp = new_game();
        create_tile(temp, p.x, p.y, 2);
        move_t max = maximize(temp, a, b, depth);
        if (max.score < worst_score) {
            worst_score = max.score;
            worst_move = NONE;
        }
        
        if (worst_score >= a) break;
        
        if (worst_score < b) {
            b = worst_score;
            
        }        
        end_game(temp);
    }
    
    free(pos);
    move_t m;
    m.score = worst_score;
    m.dir = worst_move;
    return m;
}

move_t maximize(game_state_t *game, int a, int b, int depth) {
    printf("MAXIMIZE\n");
    usleep(1000*100);
    direction best_move = LEFT;
    int best_score = -1;
    
    if (depth == 0 || is_terminal(game, 0)) {
        move_t r;
        r.score = rate(game);
        r.dir = NONE;
        return r;
    }
    
    depth--;
    
    int *maxmoves = available_moves_max(game);
    for (int i = 0; i < 4; i++) {
        if (maxmoves[i] != 0) {
            game_state_t *temp = copy_game(game);
            move(temp, int_to_dir(i));
            move_t min = minimize(temp, a, b, depth);
            
            if (min.score > best_score) {
                best_score = min.score;
                best_move = int_to_dir(i);
            }
            
            if (best_score >= b) break;
            
            if (best_score > a) {
                a = best_score;
            }
            end_game(temp);
        }
        
    }
    free(maxmoves);
    
    move_t m;
    m.score = best_score;
    m.dir = best_move;
    return m;
}




direction get_best_move(game_state_t *game) {
    move_t best = maximize(game, -1, INT_MAX, 5);
    
    return best.dir;
}

int ai_play(int delay) {
    int score = 0;
    game_state_t *ai_game = new_game();
    create_random_tile(ai_game);
    create_random_tile(ai_game);
    while(!is_array_full(ai_game)) {
        move(ai_game, get_best_move(ai_game));
        usleep(delay * 1000);
        print_array(ai_game);
    }
    
    score = ai_game->score;
    end_game(ai_game);
    return score;
}
