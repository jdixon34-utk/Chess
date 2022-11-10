# Sprint 3
Jared Dixon, jdixon34-cs340, Chess

### What I planned to do
* Write function to generate a FEN string from our board representation [Issue #56](https://github.com/utk-cs340-fall22/Chess/issues/56)
* Write the search function [Issue #63](https://github.com/utk-cs340-fall22/Chess/issues/63)
* Combine everything together to communicate with frontend in the demo [Issue #66](https://github.com/utk-cs340-fall22/Chess/issues/66)

### What I did not do
* I would have liked to do some more testing

### What problems I encountered
* Just a few bugs with the move search and some other functions

### Issues you worked on
* [Issue #56](https://github.com/utk-cs340-fall22/Chess/issues/56)
* [Issue #63](https://github.com/utk-cs340-fall22/Chess/issues/63)
* [Issue #66](https://github.com/utk-cs340-fall22/Chess/issues/66)

### Files you worked on
* Pretty much everything in the src folder

### What you accomplished
In this sprint I created the a function to generate a FEN string to return to the frontend and the main move search function which is currently 
set to a depth of 4.This means that we currently have a working engine, albeit, a pretty bad one. I think that we can push to depth 6 or 8 with 
alpha-beta pruning and then implement some things like an opening book, king safety, and endgame strategy to vastly improve the engine.
