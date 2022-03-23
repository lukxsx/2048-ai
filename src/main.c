#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "game.h"
#include "text_ui.h"


int main(int argc, char **argv) {
	// Process the command line options
	int opt, ai_mode = 0;
	while ((opt = getopt(argc, argv, "uah")) != -1) {
		switch (opt) {
			case 'a':
				ai_mode = 1;
				break;
			case 'h':
				printusage(argv[0]);
				exit(EXIT_SUCCESS);
			case '?':
				printf("Unknown option: %c\n", optopt);
				printusage(argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	
	if (ai_mode) {
		printf("AI mode enabled\n");
		
	}
	
	
	
	exit(EXIT_SUCCESS);
}
