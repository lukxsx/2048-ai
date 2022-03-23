#include <check.h>
#include <stdlib.h>

#include "../src/game.h"
#include "../src/text_ui.h"

START_TEST(test_array_is_created) {
	int **ga = NULL;
	ga = init_game_array();
	ck_assert_ptr_ne(ga, NULL);
	ga[1][1] = 2;
	ck_assert_int_eq(ga[1][1], 2);
	free_game_array(ga);
}
END_TEST


Suite * game_suite(void) {
	Suite *s;
	TCase *tc_core;
	s = suite_create("game");
	tc_core = tcase_create("Core");
	tcase_add_test(tc_core, test_array_is_created);
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

