#include <stdio.h>
#include <stdlib.h>


// Prints the error message to stderr and exits with failure.
void error_exit(char *msg) {
	fprintf(stderr, "%s", msg);
	exit(EXIT_FAILURE);
}
