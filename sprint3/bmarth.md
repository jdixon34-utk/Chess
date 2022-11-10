# Sprint 2

Brandon Marth (bmarth) 

Group: ChessWebsite

### What I planned to do
- Create a front-end to read in a fenstring and set the board.
    * #53 [issue](https://github.com/utk-cs340-fall22/Chess/issues/53)
- Create a function to flip a board.
    * #54 [issue](https://github.com/utk-cs340-fall22/Chess/issues/54)
- Have the player choose what color to play
    * #55 [issue](https://github.com/utk-cs340-fall22/Chess/issues/55)
- Have the front-end check if a user move is valid
    * #57 [issue](https://github.com/utk-cs340-fall22/Chess/issues/57)

### What I did not do
- I was able to finish all my issues.

### What problems I encountered
- Fenstring read in function
    * Minor bugs when testing the function but nothing major
- Function to flip the board.
    * Creating the function was not difficult.
    * Other aspects of the board rely on reading the board in a cetrain order, such as black first then white.
    * A non flipped board has black at index 0 and a flipped board has white at index 0.
    * Had to add some checks to pervious code to make it work correctly when flipped.
- Have the player choose what color to play
    * Didn't get to work on this issue.
    * The backend engine did not send a move until Thursday morning.
    * Did not want to lock the user into only being able to only move one piece color if we weren't getting a engine move.
- Front-end check if the user move is valid
    * Did not add en passant, castling, and due to lack of time

### Issues I worked on
- Create a front-end to read in a fenstring and set the board.
    * #53 [issue](https://github.com/utk-cs340-fall22/Chess/issues/53))
- Create a function to flip a board.
    * #54 [issue](https://github.com/utk-cs340-fall22/Chess/issues/54)
- Have the front-end check if a user move is valid
    * #57 [issue](https://github.com/utk-cs340-fall22/Chess/issues/57)

### Files I worked on
- Chess/webassembly/Makefile
- Chess/ChessWebsite/static/board.html
- Chess/ChessWebsite/static/board.js
- Chess/ChessWebsite/static/fen.js
- Chess/ChessWebsite/static/chess.js (WebAssembly convert did not write the code)

### What I accomplished
Created a fenin function that sets the board according to the fenstring. Added a flip board function that allows the user to flip the board perspective. Previously any piece could be moved anywhere on the board. Now all the pieces can only be moved on their according to the rules of chess. With the exception of en passant and castling. Tested the fenin function with the web assembly converted backend engine, and it worked.