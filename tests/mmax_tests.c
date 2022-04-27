#include <string.h>
#include <stdio.h>

#include "../src/game.h"
#include "../src/ai.h"
#include "../src/text_ui.h"

int arr_equal(unsigned int *a, unsigned int *b) {
    for (int i = 0; i < 16; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

void print_arr(unsigned int *arr) {
    for (int j = 0; j < 4; j++) {
        printf("    ");
        for (int i = 0; i < 4; i++) {
            printf("%d ", arr[idx(j, i)]);
        }
        printf("\n");
    }
    printf("    rating: %d\n", rate(arr));
}

int print_test_scene(char *text, unsigned int *init, unsigned int *res,
        unsigned int *goal) {
    printf("==============================\n");
    printf("    test \"%s\"\n", text);
    printf("==============================\n");
    printf("  Initial state:\n");
    print_only_array(init);
    printf("\n  Test result:\n");
    print_only_array(res);
    if (arr_equal(res, goal)) {
        printf("\n  --> Success\n\n");
        return 1;
    } else {
        printf("\n  --> Failed! Should be:\n");
        print_only_array(goal);
        printf("\n");
        return 0;
    }
    
}

/* template
 
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
    unsigned int orig[16] = { 0, 0, 0, 2,
                              4, 4, 0, 2,
                              0, 0, 0, 2,
                              0, 0, 0, 2 };
                              
    unsigned int goal[16] = { 4, 4, 0, 4,
                              0, 0, 0, 4,
                              0, 0, 0, 0,
                              0, 0, 0, 0 };
                        
    
    return run_test("should move up", orig, goal);
}


int main(void) {
    int pass = 0;
    int ntests = 2;
    pass += ai_test1();
    pass += ai_test2();
    
    printf("Passed %d / %d tests\n", pass, ntests);
}
