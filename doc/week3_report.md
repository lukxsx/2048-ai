# Week 3
## 1.4.2022
The basic gameplay works now. Moving to all directions works. Added a flag to
detect if anything is changed (to prevent generating more tiles while going to
one direction).

I quickly made a simple alternative "AI" implementation. It simulates the game
by making four copies of it, and running each of them to the endwith randomized
input, each beginning with different directions. It then finds out which has the
best score, and then chooses the next move based on the direction that got the
best simulated score.

The command line option ```-s``` enables this randomized AI mode. Using the
```-t``` option with integer value, a delay can be added (in milliseconds).

Added a code formatting script using clang-format. It keeps the code quality and
style constant. It can be run with ```make format```. Note that you need to have
clang installed in order to use it.

The next day I'm planning to read about minimax algorighms and start trying to
implement it on my game.

Time: 4h

## 2.4.2022
Fixed a bug in the simple AI mode (it was missing the randomizer seed).
Added mode where the game is played with randomized input. This can be activated
with ```-r``` option. Fixed some bugs and did some refactoring on some parts.

Added comparison mode that runs all modes n times and displays the average,
minimum and maximum scores of the runs. This can be used to compare the
different AI modes to the randomized input. This mode can be started with
```-c``` option with the number of runs, for example ```-c 1000``` will run
all modes 1000 times and compare the results.

Started reading about minimax algorithm and started implementing it.

I started writing the testing document and added more test for game.c file.

Time: 4h

Next week I will continue working on the minimax algorithm.
