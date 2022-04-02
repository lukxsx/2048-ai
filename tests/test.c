#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/game.h"
#include "../src/text_ui.h"

// Checks that a game array is created and the input is stored
// correctly
START_TEST(test_array_is_created) {
    int **ga = NULL;
    ga = init_game_array();
    ck_assert_ptr_ne(ga, NULL);
    ga[1][1] = 2;
    ck_assert_int_eq(ga[1][1], 2);
    free_game_array(ga);
}
END_TEST

// Check that the new game_state_t is successfully created
// and the game_array is allocated inside it too
START_TEST(test_new_game_is_created) {
    game_state_t *game = NULL;
    game = new_game();
    ck_assert_ptr_ne(game, NULL);
    ck_assert_ptr_ne(game->game_array, NULL);

    end_game(game);
}
END_TEST

// Create a tile in a position 1,1 and test if the is_tile_empty()
// returns correctly
START_TEST(test_tile_empty) {
    int **ga = NULL;
    ga = init_game_array();
    ga[1][2] = 2;
    ck_assert_int_eq(is_tile_empty(ga, 2, 1), 0);
    ck_assert_int_eq(is_tile_empty(ga, 0, 0), 1);
    free_game_array(ga);
}
END_TEST

// Test that is_array_full returns correctly when array is full
START_TEST(test_array_full) {
    game_state_t *game = NULL;
    game = new_game();
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            game->game_array[j][i] = 2; // fill the array
        }
    }
    ck_assert_int_eq(is_array_full(game), 1);
    end_game(game);
}
END_TEST

// Test that is_array_full returns correctly when array is not full
START_TEST(test_array_not_full) {
    game_state_t *game = NULL;
    game = new_game();
    ck_assert_int_eq(is_array_full(game), 0);
    end_game(game);
}
END_TEST

// Test that when calling create_random_tile, it will be created
// somewhere
START_TEST(test_random_tile_is_generated) {
    game_state_t *game = new_game();
    create_random_tile(game);
    ck_assert_int_eq(is_array_full(game), 0);
    end_game(game);
}
END_TEST

// Tests if copy_game() works and the copy has the same tiles in it's game array
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

START_TEST(test_combine1) {
    game_state_t *game = new_game();
    int arr[4] = {2, 2, 0, 0};
    int modflag = 0;
    int *flag = &modflag;

    combine(arr, 4, game, flag);

    ck_assert_int_eq(arr[0], 4);
    end_game(game);
}
END_TEST

START_TEST(test_combine2) {
    game_state_t *game = new_game();
    int arr[4] = {2, 2, 2, 2};
    int modflag = 0;
    int *flag = &modflag;

    combine(arr, 4, game, flag);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 4);
    ck_assert_int_eq(arr[3], 0);

    end_game(game);
}
END_TEST

START_TEST(test_move_left1) {
    int arr[4] = {0, 2, 0, 4};
    int modflag = 0;
    int *flag = &modflag;

    move_all_left(arr, 4, flag);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left2) {
    int arr[4] = {2, 0, 0, 8};
    int modflag = 0;
    int *flag = &modflag;

    move_all_left(arr, 4, flag);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 8);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left3) {
    int arr[4] = {0, 0, 0, 2};
    int modflag = 0;
    int *flag = &modflag;

    move_all_left(arr, 4, flag);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_reverse_array) {
    int arr[4] = {1, 2, 3, 4};
    reverse_array(arr, 4);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 3);
    ck_assert_int_eq(arr[2], 2);
    ck_assert_int_eq(arr[3], 1);
}
END_TEST

START_TEST(test_move_array1) {
    game_state_t *game = new_game();
    int arr[4] = {2, 2, 2, 2};
    int modflag = 0;
    int *flag = &modflag;

    move_array(arr, game, flag);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);

    end_game(game);
}
END_TEST

START_TEST(test_move_array2) {
    game_state_t *game = new_game();
    int arr[4] = {8, 0, 0, 8};
    int modflag = 0;
    int *flag = &modflag;

    move_array(arr, game, flag);

    ck_assert_int_eq(arr[0], 16);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);

    end_game(game);
}
END_TEST

START_TEST(test_move_array3) {
    game_state_t *game = new_game();
    int arr[4] = {2, 4, 2, 4};
    int modflag = 0;
    int *flag = &modflag;

    move_array(arr, game, flag);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 2);
    ck_assert_int_eq(arr[3], 4);

    end_game(game);
}
END_TEST

Suite *game_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("game logic checks");
    tc_core = tcase_create("Game and array modification");
    tcase_add_test(tc_core, test_array_is_created);
    tcase_add_test(tc_core, test_new_game_is_created);
    tcase_add_test(tc_core, test_tile_empty);
    tcase_add_test(tc_core, test_array_full);
    tcase_add_test(tc_core, test_array_not_full);
    tcase_add_test(tc_core, test_random_tile_is_generated);
    tcase_add_test(tc_core, test_copy_game);
    tcase_add_test(tc_core, test_combine1);
    tcase_add_test(tc_core, test_combine2);
    tcase_add_test(tc_core, test_move_left1);
    tcase_add_test(tc_core, test_move_left2);
    tcase_add_test(tc_core, test_move_left3);
    tcase_add_test(tc_core, test_reverse_array);
    tcase_add_test(tc_core, test_move_array1);
    tcase_add_test(tc_core, test_move_array2);
    tcase_add_test(tc_core, test_move_array3);
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
