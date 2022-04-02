# Testing document
## (Test coverage report)[https://codecov.io/gh/lukxsx/2048-ai]

## What is tested
- Game logic
- How well algorithms are performing

## Unit tests
Unit tests are used to test the game logic of 2048 in the game.c file. They
mainly test the array processing functions.

## Comparison testing
There is a command line option ```-c``` that compares the different algorithms.
It runs all algorithms n times and calculates the average, minimum and
maximum scores of each algorithm.

Three algorithms are compared: randomization
(play the game with randomized input), simple algorithm (compare simulated runs
to all four directions and choose the one with best final score) and AI using
minimax algorithm.

### Example output

```
$ ./2048 -c 1000

   Test results (1000 runs)

Mode    Avg      Min      Max
──────────────────────────────
rand    450      176      1052 
simp    1625     288      5216
```
