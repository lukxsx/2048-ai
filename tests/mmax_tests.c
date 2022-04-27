// clang-format off
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/game.h"
#include "../src/ai.h"
#include "../src/text_ui.h"
//clang-format on

int test_count = 0;

// checks if arrays are equal
int arr_equal(unsigned int *a, unsigned int *b) {
    for (int i = 0; i < 16; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

// prints two arrays and compares them
// update test count
int print_test_scene(char *text, unsigned int *init, unsigned int *res,
                     unsigned int *goal) {
    printf("==================================================================="
           "======\n");
    printf("                        test %d: \"%s\"\n", test_count + 1, text);
    printf("==================================================================="
           "======\n\n");
    printf("          Initial state                               Goal\n");
    print_two_arrays(init, goal);
    printf("           Rating: %d                              Rating: %d\n",
           rate(init), rate(goal));
    test_count++;
    if (arr_equal(res, goal)) {
        printf("\n  --> Success\n\n");
        return 1;
    } else {
        printf("\n  --> Failed! Should be:\n");
        print_only_array(goal);
        printf("    rating: %d\n", rate(goal));
        printf("\n");
        return 0;
    }
}

/* template for making tests

    unsigned int arr[16] =  { 0, 0, 0, 0,
                              0, 0, 0, 0,
                              0, 0, 0, 0,
                              0, 0, 0, 0 };

*/

int run_test(char *text, unsigned int *arr, unsigned int *goal) {
    unsigned int original[16];
    memcpy(original, arr, 16 * sizeof(unsigned int));

    move(arr, get_best_move(arr));
    return print_test_scene(text, original, arr, goal);
}

// tests start from here
// clang-format off
int ai_test1() {
    unsigned int orig[16] = { 2, 2, 2, 2,
                              0, 0, 0, 0,
                              0, 4, 0, 0,
                              0, 4, 0, 0 };
                              
    unsigned int goal[16] = { 4, 4, 0, 0,
                              0, 0, 0, 0,
                              4, 0, 0, 0,
                              4, 0, 0, 0 };
                        
    
    return run_test("should move left", orig, goal);
}

int ai_test2() {
    unsigned int orig[16] = { 4, 16, 64, 4,
                              4, 2, 0, 0,
                              0, 0, 0, 4,
                              0, 0, 0, 0 };
                              
    unsigned int goal[16] = { 8, 16, 64, 8,
                              0, 2, 0, 0,
                              0, 0, 0, 0,
                              0, 0, 0, 0 };
                        
    
    return run_test("should move up", orig, goal);
}

// clang-format on

int main(void) {
    // set random seed
    struct timespec t;
    timespec_get(&t, TIME_UTC);
    srand(t.tv_nsec);

    int pass = 0;
    pass += ai_test1();
    pass += ai_test2();

    printf("********************\nPassed %d / %d tests\n", pass, test_count);
}
