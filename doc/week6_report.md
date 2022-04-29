# Week 6
## 24.4.2022
I started making a testing system to test the minimax algorithm. The tests first
determine the initial state and then the desired result. The test runs the
move with the minimax algorithm, after which the result obtained is compared
with the desired result.

Time. 2h

## 26.4.2022
Continued the work on the mmax tests

Time: 1h

## 27.4.2022
I noticed that most of the moves made by the minimax's maximize function are to
the left. This is because when the algorithm goes through possible moves, it
goes through them in this order: left, right, up, and down. Example: If the
first move to the left gets a grade of 4 and then a move up gets 4 too, the move
will still be made to left. This is because the move is only replaced if it has
better score.

I tried to fix the problem so that if the algorithm gets the same good score
from multiple moves, it randomly selects a move from among those.

But in my tests, it turned out that this gave worse results. With the old
method, the average score was about 8500 and with the new method it's only about
5000. I made a separate setting for the new method if you want to use it.

I added a feature to show the highest tile number when playing the game.

In addition to these, I refactored the code and improved the comments. I also
improved the documents.

Time: 5h

## 29.4.2022
I added more unit tests, the coverage is now 100%. I also added more tests for
the minimax algorithm. I added a GitHub Actions CI workflow for building the
program and running tests (unit tests and mmax tests).

Added local test coverage report generation using gcovr. This can be run with
```make coverage-html``` and the generated file will be ```coverage.html```.

Time: 3h

