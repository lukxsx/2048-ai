#ifndef GAME_H
#define GAME_H


// A struct to hold the current game state and variables
typedef struct {
	int **game_array;
	int score;
	int moves;
} game_state_t;

int** init_game_array();
void free_game_array(int **game_array);
game_state_t* new_game();
void end_game(game_state_t *game);

#endif
