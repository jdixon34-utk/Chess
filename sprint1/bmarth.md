# Sprint 1

Brandon Marth (bmarth) 

Group: ChessWebsite

### What I planned to do
- Setup and learned webassembly, then made a webassembly makefile.
    * #2 [issue](https://github.com/utk-cs340-fall22/Chess/issues/2)
- Created a chess board using JavaScript
    * #3 [issue](https://github.com/utk-cs340-fall22/Chess/issues/3)
- Created chess pieces on the board you can move around
    * #4 [issue](https://github.com/utk-cs340-fall22/Chess/issues/4)

### What I did not do
- I was able to finish all my issues.

### What problems I encountered
- Webassembly 
    * One of the core parts of our project is passing a string back and forth from the backend to the frontend
    * This did not work when I was testing, and eventually I found out web assembly can only use ints and floats not strings.
    * Many of the results when you look up this issue are years old and are complicated solutions.
    * Eventually I found out newer versions of web assembly can support strings if you include a different header and add a function at the bottom of the cpp file.

### Issues I worked on
- Setup and learned webassembly, then made a webassembly makefile.
    * #2 [issue](https://github.com/utk-cs340-fall22/Chess/issues/2)
- Created a chess board using JavaScript
    * #3 [issue](https://github.com/utk-cs340-fall22/Chess/issues/3)
- Created chess pieces on the board you can move around
    * #4 [issue](https://github.com/utk-cs340-fall22/Chess/issues/4)

### Files I worked on
- Chess/webassembly/Makefile
- Chess/webassembly/webassembly_ins
- Chess/ChessWebsite/src/components/board.html
- Chess/ChessWebsite/src/components/board.js
- Chess/ChessWebsite/src/components/board.css

### What I accomplished
I installed and tested web assembly. I created some C++ and C files testing different things compiling them in different ways and running the functions as outported Javascript. Passing strings between c++ and Javascript was the biggest headache, but by using EMSCRIPTEN_BINDINGS you can easily use any C++ function as Javascript. I also made a Makefile that will compile our C++ files, right now since I have not added the include or bindings in these C++ files the resulting Javascript and wasm files from compilation do nothing. I also created a chessboard. Basically, it makes a board and then creates squares that or added to the board. These squares are either given the class 'white' or 'black', and the CSS colors them in at the end. The finished product is a black and white chessboard. Next, I added pieces to the chess board once again using classes to give them labels like 'pawn', 'king', 'knight', etc. Created two functions that allow the pieces to move on the board. The first function moveStart checks if the user is selected a piece for the first time, if their move is invalid, if they are unselecting a piece, or if the move is valid. If the move is valid the function move is called and the piece is moved across the board.
