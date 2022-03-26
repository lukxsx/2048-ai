# 2048-ai
[![codecov](https://codecov.io/gh/lukxsx/2048-ai/branch/master/graph/badge.svg?token=DK89Q0ETWI)](https://codecov.io/gh/lukxsx/2048-ai)

Data structures and algorithms project: Making an implementation of the 2048 game, as well as an AI bot to play it
automatically using the minimax algorithm.

## Links
- [Project specification](doc/spec.md)
- [Week 1 report](doc/week1_report.md)
- [Week 2 report](doc/week2_report.md)
- [Test coverage report](https://codecov.io/gh/lukxsx/2048-ai)

## Building
### Prerequisites
You need GCC (or any C compiler), Make and Check. (Some university's computer should have these already installed, at least on melkki)

### Compiling
Run the command
```
make
```
Now the program can be run with ```./2048```.

### Tests
The tests can be run with
```
make check
```

## Usage
### Configuration
The program supports few command line options. If no options are given, the game will start in "normal" mode (the player controls the game)
```
-a    Start in AI mode
-t    Add delay in the AI mode
-h    Show help
```
### Gameplay
The game can be played with ```W, A, S and D``` keys.
