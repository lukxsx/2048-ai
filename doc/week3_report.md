# Week 3
## 1.4.2022
The basic gameplay works now. Moving to all directions works. Added a flag to
detect if anything is changed (to prevent generating more tiles while going to
one direction).

I quickly made a stupid alternative "AI" implementation. It simulates the game
by making four copies of it, and running each of them to the endwith randomized
input, each beginning with different directions. It then finds out which has the
best score, and then chooses the next move based on the direction that got the
best simulated score.

The command line option ```-r``` enables this randomized AI mode. Using the
```-t``` option with integer value, a delay can be added (in milliseconds).

Added a code formatting script using clang-format. It keeps the code quality and
style constant. It can be run with ```make format```. Note that you need to have
clang installed in order to use it.

The next day I'm planning to read about minimax algorighms and start trying to
implement it on my game.

Time: 4h

## 2.4.2022
