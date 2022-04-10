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
    ck_assert_int_eq(is_array_full(game->game_array), 1);
    end_game(game);
}
END_TEST

// Test that is_array_full returns correctly when array is not full
START_TEST(test_array_not_full) {
    game_state_t *game = NULL;
    game = new_game();
    ck_assert_int_eq(is_array_full(game->game_array), 0);
    end_game(game);
}
END_TEST

// Test that when calling create_random_tile, it will be created
// somewhere
START_TEST(test_random_tile_is_generated) {
    game_state_t *game = new_game();
    create_random_tile(game);
    ck_assert_int_eq(is_array_full(game->game_array), 0);
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
    int arr[4] = {2, 2, 0, 0};
    combine(arr, 4);

    ck_assert_int_eq(arr[0], 4);
}
END_TEST

START_TEST(test_combine2) {
    int arr[4] = {2, 2, 2, 2};
    combine(arr, 4);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 4);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left1) {
    int arr[4] = {0, 2, 0, 4};
    move_all_left(arr, 4);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left2) {
    int arr[4] = {2, 0, 0, 8};
    move_all_left(arr, 4);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 8);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left3) {
    int arr[4] = {0, 0, 0, 2};
    move_all_left(arr, 4);

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
    int arr[4] = {2, 2, 2, 2};
    move_array(arr);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_array2) {
    int arr[4] = {8, 0, 0, 8};
    move_array(arr);

    ck_assert_int_eq(arr[0], 16);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_array3) {
    int arr[4] = {2, 4, 2, 4};
    move_array(arr);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 2);
    ck_assert_int_eq(arr[3], 4);
}
END_TEST

START_TEST(test_get_free_tiles) {
    int **arr = init_game_array();
    create_tile(arr, 0, 0, 2);
    create_tile(arr, 2, 3, 2);
    int **fr = get_free_tiles(arr);
    ck_assert_int_eq(fr[1][1], 1);
    ck_assert_int_eq(fr[0][0], 0);
    free_game_array(fr);
    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_left1) {
    int **arr = init_game_array();

    arr[1][0] = 2;
    arr[2][0] = 2;

    ck_assert_int_eq(can_move(arr, LEFT), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_left2) {
    int **arr = init_game_array();

    arr[1][2] = 2;
    arr[2][2] = 2;

    ck_assert_int_eq(can_move(arr, LEFT), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_left3) {
    int **arr = init_game_array();

    arr[1][2] = 2;
    arr[1][3] = 2;

    ck_assert_int_eq(can_move(arr, LEFT), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_left4) {
    int **arr = init_game_array();

    arr[1][0] = 2;
    arr[1][1] = 4;

    ck_assert_int_eq(can_move(arr, LEFT), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_right1) {
    int **arr = init_game_array();

    arr[1][3] = 2;
    arr[2][3] = 2;

    ck_assert_int_eq(can_move(arr, RIGHT), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_right2) {
    int **arr = init_game_array();

    arr[1][0] = 2;
    arr[2][0] = 2;

    ck_assert_int_eq(can_move(arr, RIGHT), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_right3) {
    int **arr = init_game_array();

    arr[1][2] = 2;
    arr[1][3] = 2;

    ck_assert_int_eq(can_move(arr, RIGHT), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_right4) {
    int **arr = init_game_array();

    arr[1][2] = 2;
    arr[1][3] = 4;

    ck_assert_int_eq(can_move(arr, RIGHT), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_up1) {
    int **arr = init_game_array();

    arr[0][0] = 2;
    arr[1][0] = 2;

    ck_assert_int_eq(can_move(arr, UP), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_up2) {
    int **arr = init_game_array();

    arr[0][0] = 2;
    arr[1][0] = 4;

    ck_assert_int_eq(can_move(arr, UP), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_up3) {
    int **arr = init_game_array();

    arr[0][2] = 2;
    arr[0][3] = 2;

    ck_assert_int_eq(can_move(arr, UP), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_up4) {
    int **arr = init_game_array();

    arr[1][2] = 2;
    arr[1][3] = 4;

    ck_assert_int_eq(can_move(arr, UP), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_down1) {
    int **arr = init_game_array();

    arr[0][0] = 2;
    arr[1][0] = 2;

    ck_assert_int_eq(can_move(arr, DOWN), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_down2) {
    int **arr = init_game_array();

    arr[2][0] = 2;
    arr[3][0] = 4;

    ck_assert_int_eq(can_move(arr, DOWN), 0);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_down3) {
    int **arr = init_game_array();

    arr[0][1] = 2;
    arr[0][2] = 2;

    ck_assert_int_eq(can_move(arr, DOWN), 1);

    free_game_array(arr);
}
END_TEST

START_TEST(test_can_move_down4) {
    int **arr = init_game_array();

    arr[3][2] = 2;
    arr[3][3] = 4;

    ck_assert_int_eq(can_move(arr, DOWN), 0);

    free_game_array(arr);
}
END_TEST

/* Test running code */

Suite *array_create_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("array creation and copying");
    tc_core = tcase_create("Game and array modification");
    tcase_add_test(tc_core, test_array_is_created);
    tcase_add_test(tc_core, test_new_game_is_created);
    tcase_add_test(tc_core, test_copy_game);

    suite_add_tcase(s, tc_core);
    return s;
}

Suite *array_modify_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("array moving and processing");
    tc_core = tcase_create("array moving and processing");
    tcase_add_test(tc_core, test_tile_empty);
    tcase_add_test(tc_core, test_array_full);
    tcase_add_test(tc_core, test_array_not_full);
    tcase_add_test(tc_core, test_random_tile_is_generated);
    tcase_add_test(tc_core, test_combine1);
    tcase_add_test(tc_core, test_combine2);
    tcase_add_test(tc_core, test_move_left1);
    tcase_add_test(tc_core, test_move_left2);
    tcase_add_test(tc_core, test_move_left3);
    tcase_add_test(tc_core, test_reverse_array);
    tcase_add_test(tc_core, test_move_array1);
    tcase_add_test(tc_core, test_move_array2);
    tcase_add_test(tc_core, test_move_array3);
    tcase_add_test(tc_core, test_get_free_tiles);

    tcase_add_test(tc_core, test_can_move_left1);
    tcase_add_test(tc_core, test_can_move_left2);
    tcase_add_test(tc_core, test_can_move_left3);
    tcase_add_test(tc_core, test_can_move_left4);

    tcase_add_test(tc_core, test_can_move_right1);
    tcase_add_test(tc_core, test_can_move_right2);
    tcase_add_test(tc_core, test_can_move_right3);
    tcase_add_test(tc_core, test_can_move_right4);

    tcase_add_test(tc_core, test_can_move_up1);
    tcase_add_test(tc_core, test_can_move_up2);
    tcase_add_test(tc_core, test_can_move_up3);
    tcase_add_test(tc_core, test_can_move_up4);

    tcase_add_test(tc_core, test_can_move_down1);
    tcase_add_test(tc_core, test_can_move_down2);
    tcase_add_test(tc_core, test_can_move_down3);
    tcase_add_test(tc_core, test_can_move_down4);
    suite_add_tcase(s, tc_core);
    return s;
}

int main() {
    int number_failed;
    Suite *s_arr;
    Suite *s_mod;
    SRunner *sr;
    s_arr = array_create_suite();
    s_mod = array_modify_suite();
    sr = srunner_create(s_arr);
    srunner_add_suite(sr, s_mod);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
