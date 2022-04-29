# 2048-ai
[![codecov](https://codecov.io/gh/lukxsx/2048-ai/branch/master/graph/badge.svg?token=DK89Q0ETWI)](https://codecov.io/gh/lukxsx/2048-ai)
![build](https://github.com/lukxsx/2048-ai/actions/workflows/build_and_test.yml/badge.svg)

Data structures and algorithms project: Making an implementation of the 2048 game, as well as an AI bot to play it
automatically using the minimax algorithm.

## Links
- [Project specification](doc/spec.md)
- [Test coverage report](https://codecov.io/gh/lukxsx/2048-ai)
- [Implementation document](doc/implementation.md)
- [Testing document](doc/testing.md)
- [Week 1 report](doc/week1_report.md)
- [Week 2 report](doc/week2_report.md)
- [Week 3 report](doc/week3_report.md)
- [Week 4 report](doc/week4_report.md)
- [Week 5 report](doc/week5_report.md)
- [Week 6 report](doc/week6_report.md)

## Building
### Prerequisites
You need a C compiler (GCC for example), Make and Check. (Some university's computer should have these already installed, at least on melkki).
For example, in Arch Linux, ```pacman -S base-devel check``` and in Ubuntu/Debian based distros ```apt install build-essential check```.

**Optional**: In order to generate a HTML coverage report, ```gcovr``` is needed. Otherwise you can use Codecov
(link at the top of the page).

### Compiling
Run the command
```
make
```
Now the program can be run with ```./2048```.

### Tests
The unit tests can be run with
```
make check
```
Tests for the minimax algorithm can be run with
```
make mmaxtest
```

### Code auto formatting
The code can be formatted with clang-format to ensure the constant code style.
Note that clang and python must be installed to use this function.
```
make format
```

### Coverage HTML report
Note that ```gcovr``` must be installed
```
make coverage-html
```

## Usage
### Configuration
The program supports few command line options. If no options are given, the game will start in "normal" mode (the player controls the game)
```
-a            Play with minimax AI
-s            Use randomizer AI
-r            Play the game with randomized input
-t [value]    Delay in milliseconds
-c [runs]     Run in comparison mode
-h            Show this information
```
### Gameplay
The game can be played with ```W, A, S and D``` keys.
