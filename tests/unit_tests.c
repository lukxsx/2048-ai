#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/game.h"
#include "../src/text_ui.h"

const int ARR_PADDING = 0;

// Check that the new game_state_t is successfully created
// and the game_array is allocated inside it too
START_TEST(test_new_game_is_created) {
    game_state_t *game = NULL;
    game = new_game();
    ck_assert_ptr_ne(game, NULL);
    
    free(game);
}
END_TEST

// Create a tile in a position 1,1 and test if the is_tile_empty()
// returns correctly
START_TEST(test_tile_empty) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 2, 0, 0,
                            0, 0, 0, 0};

    ck_assert_int_eq(is_tile_empty(arr, 2, 1), 0);
    ck_assert_int_eq(is_tile_empty(arr, 1, 1), 1);
}
END_TEST

// Test that is_array_full returns correctly when array is full
START_TEST(test_array_full) {
    unsigned int arr[16] = {8, 8, 8, 8,
                            8, 8, 8, 8,
                            8, 8, 8, 8,
                            8, 8, 8, 8};    
    ck_assert_int_eq(is_array_full(arr), 1);
}
END_TEST

// Test that is_array_full returns correctly when array is not full
START_TEST(test_array_not_full) {
    unsigned int arr[16] = {0, 2, 0, 0,
                            0, 0, 2, 0,
                            0, 2, 0, 0,
                            0, 0, 0, 0};
    
    ck_assert_int_eq(is_array_full(arr), 0);
}
END_TEST

// Test that when calling create_random_tile, it will be created
// somewhere
START_TEST(test_random_tile_is_generated) {
    game_state_t *game = new_game();
    create_random_tile(game);
    ck_assert_int_eq(is_array_full(game->game_array), 0);
    free(game);
}
END_TEST


START_TEST(test_combine1) {
    unsigned int arr[4] = {2, 2, 0, 0};
    combine(arr);

    ck_assert_int_eq(arr[0], 4);
}
END_TEST

START_TEST(test_combine2) {
    unsigned int arr[4] = {2, 2, 2, 2};
    unsigned int score = combine(arr);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 4);
    ck_assert_int_eq(arr[3], 0);
    ck_assert_int_eq(score, 8);
}
END_TEST

START_TEST(test_move_left1) {
    unsigned int arr[4] = {0, 2, 0, 4};
    move_all_left(arr);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left2) {
    unsigned int arr[4] = {2, 0, 0, 8};
    move_all_left(arr);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 8);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_left3) {
    unsigned int arr[4] = {0, 0, 0, 2};
    move_all_left(arr);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_reverse_array) {
    unsigned int arr[4] = {1, 2, 3, 4};
    reverse_array(arr);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 3);
    ck_assert_int_eq(arr[2], 2);
    ck_assert_int_eq(arr[3], 1);
}
END_TEST

START_TEST(test_move_array1) {
    unsigned int arr[4] = {2, 2, 2, 2};
    move_array(arr);

    ck_assert_int_eq(arr[0], 4);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_array2) {
    unsigned int arr[4] = {8, 0, 0, 8};
    move_array(arr);

    ck_assert_int_eq(arr[0], 16);
    ck_assert_int_eq(arr[1], 0);
    ck_assert_int_eq(arr[2], 0);
    ck_assert_int_eq(arr[3], 0);
}
END_TEST

START_TEST(test_move_array3) {
    unsigned int arr[4] = {2, 4, 2, 4};
    move_array(arr);

    ck_assert_int_eq(arr[0], 2);
    ck_assert_int_eq(arr[1], 4);
    ck_assert_int_eq(arr[2], 2);
    ck_assert_int_eq(arr[3], 4);
}
END_TEST

START_TEST(test_get_free_tiles) {
    unsigned int arr[16] = { 0 };
    int fr[16] = { 0 };
    create_tile(arr, 0, 0, 2);
    create_tile(arr, 2, 3, 2);
    get_free_tiles(arr, fr);
    ck_assert_int_eq(fr[5], 1);
    ck_assert_int_eq(fr[0], 0);
}
END_TEST

START_TEST(test_can_move_left1) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            2, 0, 0, 0,
                            2, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, LEFT), 0);
}
END_TEST

START_TEST(test_can_move_left2) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 2, 0,
                            0, 0, 2, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, LEFT), 1);
}
END_TEST

START_TEST(test_can_move_left3) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 2, 2,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, LEFT), 1);
}
END_TEST

START_TEST(test_can_move_left4) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            2, 4, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, LEFT), 0);
}
END_TEST

START_TEST(test_can_move_right1) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 0, 2,
                            0, 0, 0, 2,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, RIGHT), 0);
}
END_TEST

START_TEST(test_can_move_right2) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            2, 0, 0, 0,
                            2, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, RIGHT), 1);
}
END_TEST

START_TEST(test_can_move_right3) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 2, 2,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, RIGHT), 1);
}
END_TEST

START_TEST(test_can_move_right4) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 2, 4,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, RIGHT), 0);
}
END_TEST

START_TEST(test_can_move_up1) {
    unsigned int arr[16] = {2, 0, 0, 0,
                            2, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, UP), 1);
}
END_TEST

START_TEST(test_can_move_up2) {
    unsigned int arr[16] = {2, 0, 0, 0,
                            4, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, UP), 0);
}
END_TEST

START_TEST(test_can_move_up3) {
    unsigned int arr[16] = {0, 0, 2, 2,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, UP), 0);
}
END_TEST

START_TEST(test_can_move_up4) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 2, 4,
                            0, 0, 0, 0,
                            0, 0, 0, 0};
                            
    ck_assert_int_eq(can_move(arr, UP), 1);
}
END_TEST

START_TEST(test_can_move_down1) {
    unsigned int arr[16] = {2, 0, 0, 0,
                            2, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};

    ck_assert_int_eq(can_move(arr, DOWN), 1);
}
END_TEST

START_TEST(test_can_move_down2) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 0, 0,
                            2, 0, 0, 0,
                            4, 0, 0, 0};

    ck_assert_int_eq(can_move(arr, DOWN), 0);
}
END_TEST

START_TEST(test_can_move_down3) {
    unsigned int arr[16] = {0, 2, 2, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0};

    ck_assert_int_eq(can_move(arr, DOWN), 1);
}
END_TEST

START_TEST(test_can_move_down4) {
    unsigned int arr[16] = {0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 0, 0,
                            0, 0, 2, 4};

    ck_assert_int_eq(can_move(arr, DOWN), 0);
}
END_TEST

/* Test running code */

Suite *array_create_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("array creation and copying");
    tc_core = tcase_create("Game and array modification");
    tcase_add_test(tc_core, test_new_game_is_created);

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
    suite_add_tcase(s, tc_core);
    return s;
}

Suite *array_canmove_suite(void) {
    Suite *s;
    TCase *tc_core;
    s = suite_create("array move rule checking");
    tc_core = tcase_create("array move rule checking");

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
    Suite *s_canmove;
    SRunner *sr;
    s_arr = array_create_suite();
    s_mod = array_modify_suite();
    s_canmove = array_canmove_suite();
    sr = srunner_create(s_arr);
    srunner_add_suite(sr, s_mod);
    srunner_add_suite(sr, s_canmove);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
