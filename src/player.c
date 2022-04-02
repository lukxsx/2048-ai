/*
================================================================================
Functions for playing the game in the terminal. Keyboard input, game loop
================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "game.h"
#include "text_ui.h"

void play() {
    // Set random seed
    srand(time(NULL));

    // Change terminal mode to not to echo input
    static struct termios old_terminal, new_terminal;
    tcgetattr(STDIN_FILENO, &old_terminal);
    new_terminal = old_terminal;
    new_terminal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_terminal);

    // Create the game
    game_state_t *game = new_game();

    // Create two initial tiles
    create_random_tile(game);
    create_random_tile(game);
    print_array(game);

    // Main game loop
    for (;;) {
        // End the game if the array is full
        if (is_array_full(game))
            break;

        // Process input
        char key = getchar();
        switch (key) {
        case 'w':
            move(game, UP);
            break;
        case 'a':
            move(game, LEFT);
            break;
        case 's':
            move(game, DOWN);
            break;
        case 'd':
            move(game, RIGHT);
            break;
        default:
            break;
        }
        print_array(game);
    }

    // Cleanup
    end_game(game);

    // Return terminal back to the previous state
    tcsetattr(STDIN_FILENO, TCSANOW, &old_terminal);
}
