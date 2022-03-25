#include <check.h>
#include <stdlib.h>
#include <stdio.h>

#include "../src/game.h"
#include "../src/text_ui.h"

START_TEST(test_array_is_created) {
	// Checks that a game array is created and the input is stored
	// correctly
	int **ga = NULL;
	ga = init_game_array();
	ck_assert_ptr_ne(ga, NULL);
	ga[1][1] = 2;
	ck_assert_int_eq(ga[1][1], 2);
	free_game_array(ga);
}
END_TEST


START_TEST(test_new_game_is_created) {
	// Check that the new game_state_t is successfully created
	// and the game_array is allocated inside it too
	game_state_t *game = NULL;
	game = new_game();
	ck_assert_ptr_ne(game, NULL);
	ck_assert_ptr_ne(game->game_array, NULL);

	end_game(game);
}
END_TEST


START_TEST(test_tile_empty) {
	// Create a tile in a position 1,1 and test if the is_tile_empty()
	// returns correctly
	int **ga = NULL;
	ga = init_game_array();
	ga[1][2] = 2;
	ck_assert_int_eq(is_tile_empty(ga, 2, 1), 0);
	ck_assert_int_eq(is_tile_empty(ga, 0, 0), 1);
	free_game_array(ga);
}
END_TEST


START_TEST(test_array_full) {
	// Test that is_array_full returns correctly when array is full
	game_state_t *game = NULL;
	game = new_game();
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			game->game_array[j][i] = 2;	// fill the array
		}
	}
	ck_assert_int_eq(is_array_full(game), 1);
	end_game(game);
}
END_TEST


START_TEST(test_array_not_full) {
	// Test that is_array_full returns correctly when array is not full
	game_state_t *game = NULL;
	game = new_game();
	ck_assert_int_eq(is_array_full(game), 0);
	end_game(game);
}
END_TEST


START_TEST(test_random_tile_is_generated) {
	// Test that when calling create_random_tile, it will be created
	// somewhere
	game_state_t *game = new_game();
	create_random_tile(game);
	ck_assert_int_eq(is_array_full(game), 0);
	end_game(game);
}
END_TEST


/*
================================================================================
Tests if copy_game() works and the copy has the same tiles in it's game array
================================================================================
*/
START_TEST(test_copy_game) {
	game_state_t *old = new_game();
	old->game_array[1][3] = 2; // set value for tile
	old->game_array[1][1] = 4;
    game_state_t *new = copy_game(old); // make a copy
    
    ck_assert_int_eq(old->game_array[1][3], new->game_array[1][3]);
    ck_assert_int_eq(old->game_array[1][1], new->game_array[1][1]);
    
    end_game(old);
    end_game(new);
}
END_TEST

Suite * game_suite(void) {
	Suite *s;
	TCase *tc_core;
	s = suite_create("game");
	tc_core = tcase_create("Game logic");
	tcase_add_test(tc_core, test_array_is_created);
	tcase_add_test(tc_core, test_new_game_is_created);
	tcase_add_test(tc_core, test_tile_empty);
	tcase_add_test(tc_core, test_array_full);
	tcase_add_test(tc_core, test_array_not_full);
	tcase_add_test(tc_core, test_random_tile_is_generated);
	tcase_add_test(tc_core, test_copy_game);
	suite_add_tcase(s, tc_core);
	return s;


}


int main() {
	int number_failed;
	Suite *s;
	SRunner *sr;
	s = game_suite();
	sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

