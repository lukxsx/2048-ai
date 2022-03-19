# Week 1

This week I started the project. I spent a lot of time choosing the topic.
I decided to make a 2048 game and an automatic AI bot for it using the
minimax algorithm. I’ve done a 2048 clone (without any AI) with C before,
so I think this project might succeed, too.

I read some articles about minmax algorithms, many people have made 2048 AIs
with it before. It seems to be one of most powerful algorithms for 2048.

At first I thought about making the project with Java. But I remembered
how annoying gradle and maven are, so I started thinking about
alternative solutions.

I decided to try to make it with C because I have been using it a lot
lately. I spent time researching different test libraries and messing
with build systems. From the unit testing libraries, I tried Check and CUnit.

I tried to make a test project using Check unit tests and gcov to create
test coverage data. By using GitHub Actions, I can generate an online
test coverage report to Codecov that automatically updates on every
commit. It worked pretty well in my opinion, so I decided to go with C
and use simple self-written makefile instead of Autotools.

I asked the instructor about using C and apparently it is okay, the only
problem is that instructors of this course cannot help with the testing.

I learned a bit about minimax algorithm I also learned the basics of
setting up a project with Check and how to generate test coverage
information on Codecov using GitHub Actions.

Next step is starting to write the game itself. I have done it previously
but I'm going to make it from scratch (and make it better than the last one).
After the game is done, I can start working on the algorithm.

Hours: 4-5
