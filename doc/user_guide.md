# User guide
This application has four different modes: player mode, minimax AI, randomized AI and randomized input.
You can switch between the modes using command line arguments.

## Player mode
No command line arguments needed. Just run ```./2048``` and play the game with W, A, S and D keys.
Your job is to move the tiles in the game board. When there are two tiles with the same number,
they can be combined. The game is over when the whole game board is full and you cannot move anymore.

## Minimax AI
You can run the minimax AI with ```-a``` option. Additional options are ```-t [milliseconds]``` and
```-d [depth]``` which can be used to add delay to the game and specify the depth of the minimax AI.
The depth is 5 by default and delay is 0.

## Randomizer AI
This is a "AI" that simulates the game using randomized input and chooses the direction which ends up
getting the best score. It can be run with ```-s``` option and ```-t [milliseconds]``` can be used to
add delay.

## Randomized input
The command line option ```-r``` enables this mode. In this mode the game is played by completely random
input. The delay option can be used with this too.

## Comparasion mode
This mode compares the three different modes. This mode can be run with ```-c [runs]``` option. The amount
of runs needs to be specified.
