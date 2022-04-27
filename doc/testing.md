# Testing document
[Test coverage report](https://codecov.io/gh/lukxsx/2048-ai)

## What is tested
- Game logic
- How well the algorithms are performing

## Unit tests
Unit tests are used to test the game logic of 2048 in the game.c file. They
mainly test the array processing functions. Unit tests can be run with 
```make check```

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
$ ./2048 -c 100
   Test results (100 runs)

Mode    Avg      Min      Max
──────────────────────────────
rand    577      104      1268
simp    1825     140      6752
mmax    9101     1804     22680
```

As we can see, the minimax algorithm performs best.

## Minimax testing
I have done separate tests for the minimax algorithm to test its ability to make wise moves.
Each test consists of a starting point and a goal the array should be changed to. The test
is performed by running the minimax move on the array and comparing it to the goal array.
Because the game relies heavily to the randomization, there is a possibility that it doesn't
make the best move every time.

These tests can be run with ```make mmaxtest```.

### Example output
```
=========================================================================
                        test 1: "should move left"
=========================================================================

          Initial state                               Goal
╔═══════╦═══════╦═══════╦═══════╗       ╔═══════╦═══════╦═══════╦═══════╗
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║   2   ║   2   ║   2   ║   2   ║       ║   4   ║   4   ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║       ║       ║       ║  -->  ║       ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║   4   ║       ║       ║       ║   4   ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║   4   ║       ║       ║       ║   4   ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╚═══════╩═══════╩═══════╩═══════╝       ╚═══════╩═══════╩═══════╩═══════╝
           Rating: 2                              Rating: 4

  --> Success

=========================================================================
                        test 2: "should move up"
=========================================================================

          Initial state                               Goal
╔═══════╦═══════╦═══════╦═══════╗       ╔═══════╦═══════╦═══════╦═══════╗
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║   4   ║   16  ║   64  ║   4   ║       ║   8   ║   16  ║   64  ║   8   ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║   4   ║   2   ║       ║       ║  -->  ║       ║   2   ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║       ║       ║   4   ║       ║       ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╠═══════╬═══════╬═══════╬═══════╣       ╠═══════╬═══════╬═══════╬═══════╣
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
║       ║       ║       ║       ║       ║       ║       ║       ║       ║
╚═══════╩═══════╩═══════╩═══════╝       ╚═══════╩═══════╩═══════╩═══════╝
           Rating: 14                              Rating: 19

  --> Success

********************
Passed 2 / 2 tests
