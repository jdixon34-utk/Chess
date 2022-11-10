# Sprint 3
Justin McKnight, JMcknight75, Chess Website

### What you planned to do
*undoPromotionMove
*getMaterialCount
*evaluatePosition

### What you did not do
*evaluation function checking for weak squares

### What problems you encountered
*evaluation function needed constant optimization

### Issues you worked on
[#72](https://github.com/utk-cs340-fall22/Chess/issues/72) undoPromotionMove
[#73](https://github.com/utk-cs340-fall22/Chess/issues/73) getMaterialCount
[#38](https://github.com/utk-cs340-fall22/Chess/issues/74) evaluatePosition

### Files you worked on
board.cpp
board.h


### What you accomplished
I wrote a function to reset bitboards to as they were before a promotion move to be able to generate all possible move.
I then wrote a function that gets the material count of a given side to be used in the evaluation function, then
wrote the function that evaluates a given position to be used in the search process.
