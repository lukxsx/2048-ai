#ifndef TEXT_UI_H
#define TEXT_UI_H

void printusage(char *program_name);
void error_exit(char *msg);
void print_top(int x_size);
void print_middle_walls(int x_size);
void print_row_lines(int x_size);
void print_array(game_state_t *game);

#endif
