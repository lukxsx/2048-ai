# Project specification

## Information for university
- Bachelor’s in computer science (CS)
- Known programming languages: C, C++, Java, Python
- Documentation language: English

## Project info
- Implementation of the 2048 game and an AI bot to play it automatically
- Using minimax algorithm for solving the game
- Also implementing two additional modes: randimizer AI mode and mode that
plays the game with randomized input for comparing the performance of minimax
- Compare the results of different modes
- Create a game client with options for user play or AI play
- Programming language: C
  - Unit tests using [Check](https://libcheck.github.io/check/), it should be already installed on university Linux systems, at least on Melkki
  - Test coverage using Codecov (online), coverage data created using gcov on GitHub Actions
- Expected time complexity: O(b^m) and space complexity: O(bm) (b = number of moves, m = maximum depth)

## References
- https://en.wikipedia.org/wiki/Minimax
- https://cis.temple.edu/~vasilis/Courses/CIS603/Lectures/l7.html
- https://stackoverflow.com/questions/22342854/what-is-the-optimal-algorithm-for-the-game-2048
- https://towardsdatascience.com/playing-2048-with-minimax-algorithm-1-d214b136bffb
