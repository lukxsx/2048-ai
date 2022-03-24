CC = gcc
CFLAGS = -O2 -std=c99 -pedantic -Wall -Werror
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

codecov:
	$(CC) -ftest-coverage -fprofile-arcs -O0 -o test tests/test.c $(filter-out src/main.c, $(wildcard src/*.c)) $(CHECK_FLAGS)

clean:
	rm -f 2048 $(OBJ_LIST) test *.gcda *.gcno *.gcov
