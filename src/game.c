#include <stdlib.h>
#include "game.h"
#include "common.h"


// Allocate a 4x4 array and set everything to 0.
// Returns NULL in case of memory allocation error.
int** init_game_array() {
	int **game_array = calloc(4, sizeof(int *));
	if (game_array == NULL) {
		return NULL;
	}
	
	for (int i = 0; i < 4; i++) {
		game_array[i] = calloc(4, sizeof(int));
		if (game_array[i] == NULL) {
			for (int j = 0; j < 4; j++) {
				free(game_array[j]);
			}
			return NULL;
		}
	}
	
	return game_array;
}


// Frees the allocated memory of the game array
void free_game_array(int **game_array) {
	for (int i = 0; i < 4; i++) {
		free(game_array[i]);
	}
	free(game_array);
}


// Initializes a new game. Returns a new game_state_t
game_state_t* new_game() {
	game_state_t *game = malloc(sizeof(game_state_t));
	game->game_array = init_game_array();
	if (game->game_array == NULL) {
		error_exit("Failed to allocate the game array\n");
	}
	game->score = 0;
	game->moves = 0;
}


// Stops and frees the current game
void end_game(game_state_t *game) {
	free_game_array(game->game_array);
	free(game);
}
