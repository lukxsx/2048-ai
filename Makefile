CC = gcc
CFLAGS = -O2 -std=c11 -pedantic -Wall -Werror
CHECK_FLAGS := $(shell bash check_flags.sh)

SRC_DIR     = ./src
SRC_LIST = $(wildcard $(SRC_DIR)/*.c)
OBJ_LIST = $(SRC_LIST:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: all clean

all: 2048

2048: $(OBJ_LIST)
	$(CC) $(CFLAGS) $(OBJ_LIST) -o 2048

check:
	$(CC) -O0 -o unittest tests/unit_tests.c $(filter-out src/main.c, $(wildcard src/*.c)) $(CHECK_FLAGS)
	@./unittest

mmaxtest:
	$(CC) -Wall -Werror -o mmax tests/mmax_tests.c $(filter-out src/main.c, $(wildcard src/*.c))
	@./mmax

codecov:
	$(CC) -ftest-coverage -coverage -g -fprofile-arcs -O0 -o unittest tests/unit_tests.c $(filter-out src/main.c, $(wildcard src/*.c)) $(CHECK_FLAGS)

coverage-html: codecov
	@./unittest
	gcovr --html-details coverage.html

format:
	@python format.py	

clean:
	rm -f 2048 $(OBJ_LIST) unittest mmax *.gcda *.gcno *.gcov coverage.*
