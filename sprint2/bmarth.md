# Sprint 2

Brandon Marth (bmarth) 

Group: ChessWebsite

### What I planned to do
- Improve the look of the pieces
    * #28 [issue](https://github.com/utk-cs340-fall22/Chess/issues/28)
- Make a function to convert the frontend board to a fen string.
    * #29 [issue](https://github.com/utk-cs340-fall22/Chess/issues/29)
- Used WebAssembly to convert a backend function to test that it works 
    * #30 [issue](https://github.com/utk-cs340-fall22/Chess/issues/30)
- Create turns in the board.
    * #31 [issue](https://github.com/utk-cs340-fall22/Chess/issues/31)

### What I did not do
- I was able to finish all my issues.

### What problems I encountered
- Piece look improvement
    * CSS classes are not case-sensitive and I did not know this.
    * Because we use fen strings I need the pieces' class names to be like "P" for a white pawn and "p" for a black pawn
    * This meant the CSS just used whatever came last for all the pawns making all pawns either black or white.
    * It was easy to fix by renaming the black pieces "B_p", but was annoying to figure out why it was not working.
- Fen.js
    * Mostly went smoothly until I needed to check for en passant
    * En passant has to be able to remove elements so I thought an array would be better than a string.
    * When adding a string "A5" to the array it would make the array[0] = "A" and array[1] = 0.
    * This was not what I was expecting but would mean I read two indexes at a time and increment twice.
    * Then I found out Javascript arrays add commas between elements to make 
    array[0] = "A", array[1] = ",", array[2] = 0, array[3] = "E", array[4] = ",", array[5] = 4
    if I pushed E4.
    * So now to avoid commas I increment i threes times for each loop, and add current element + current element + 2
    to the fen string.
- WebAssembly
    * I only had one problem that was strange to figure out.
    * WebAssembly would throw a compile error when I tried to bind the "chessGame" class
    * Only would compile when binding a constructor for the class even though the class had no actual constructor.

### Issues I worked on
- Improved the look of the chess pieces by using pngs as background images for all the pieces.
    * #28 [issue](https://github.com/utk-cs340-fall22/Chess/issues/28)
- Created a fen.js that converts the current state of the frontend board into a fen string that can be used by the backend.
    * #29 [issue](https://github.com/utk-cs340-fall22/Chess/issues/29)
- Used WebAssembly to convert playTurn in game.cpp into useable Javascript in chess.js. This correctly printed out the possible moves in the current state of the board.
    * #30 [issue](https://github.com/utk-cs340-fall22/Chess/issues/30)
- Created turns in the board. White goes first and only white can move, then only black, and so on.
    * #31 [issue](https://github.com/utk-cs340-fall22/Chess/issues/31)

### Files I worked on
- Chess/webassembly/Makefile
- Chess/ChessWebsite/static/(All the pngs)
- Chess/ChessWebsite/static/board.html
- Chess/ChessWebsite/static/board.js
- Chess/ChessWebsite/static/board.css
- Chess/ChessWebsite/static/fen.js
- Chess/ChessWebsite/static/chess.js (WebAssembly convert did not write the code)
- Chess/src/board.cpp

### What I accomplished
Improved the look of the pieces by using pngs as background images in CSS. Added turns with a simple if else statement. Added a function that creates a fen string needed to communicate to the back end in a separate .js file called fen. I also had two create two new functions in board.js to help know when a piece is an en passant target or when castling is available. Some other changes had to be made throughout board.js to correctly update or reset the half and full turn clock also needed for the fen string. Used WebAssembly to convert the Game class from game.cpp into useable Javascript. The function playTurn in the Game class prints out possible moves from the current fen string. This function correctly printed out the possible moves when called in board.html from both the starting position and the updating fen string the front end generates.