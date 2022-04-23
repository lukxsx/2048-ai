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
	$(CC) -O0 -o test tests/test.c $(filter-out src/main.c, $(wildcard src/*.c)) $(CHECK_FLAGS)
	@./test

debug:
	$(CC) -O2 -Wall -Werror -std=c99 -pedantic -g -o 2048 src/main.c src/game.c src/player.c src/text_ui.c src/random_ai.c src/ai.c
	

codecov:
	$(CC) -ftest-coverage -fprofile-arcs -O0 -o test tests/test.c $(filter-out src/main.c, $(wildcard src/*.c)) $(CHECK_FLAGS)

format:
	@python format.py	

clean:
	rm -f 2048 $(OBJ_LIST) test *.gcda *.gcno *.gcov
