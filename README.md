# ChessWebsite
![ChessWebsite](chessWebsiteGraphic.png)

## Contributors
* Jared Dixon [jdixon34-cs340](https://github.com/jdixon34-cs340)
* Brandon Marth [Brandon-Marth](https://github.com/Brandon-Marth)
* Justin McKnight [JMcknight75](https://github.com/JMcknight75)
* Devin Munsey [Dev5ter](https://github.com/Dev5ter)
* Jake Shoffner [Jxk0be](https://github.com/Jxk0be)

## About ChessWebsite
ChessWebsite is a chess web application that enables the user to learn the basics of chess and improve their game over time by playing against our custom chess engine.

## Installation
Before we begin, **download the latest version of [Node.js](https://nodejs.org/en/)** from their website. This is needed to install dependencies and run the application.

First, find a location on your system where you want to install the application. Then, **clone the repository** by running the following command:
```
$ git clone https://github.com/utk-cs340-fall22/Chess.git
```
Next, traverse through the cloned repository and enter the **ChessWebsite** directory:
```
$ cd Chess/Chesswebsite
```
From here, **install all the dependencies** for this project by running:
```
$ npm install
```
You have installed the application and are all set! 

## How to Run

To play, in the **ChessWebsite** directory, just run this command:
```
$ npm run dev
```
This will **create a local server** and output the address to use in your browser to access the website.
```
> Local:   http://localhost:xxxx/ (Where xxxx is just some port)
```

When done using the application, **kill the server** with:
```
$ <CTRL + C>
```

## How to Play
#### 1. Select Color
After every refresh of the page or return to the Play page, you will need to **select a color to play as**.

#### 2. Select a Piece to Move
**Click once** to *select piece* (indicated by a highlight around the piece), **click again** to *deselect* piece, or **click one of your other pieces** to *select that piece instead*.

#### 3. Move Piece or Take an Opposing Piece
After selecting your piece, the next step is to **click on a valid square** to move to **or** an **opposing piece** to take.

Since you can only make valid moves, it is best you understand the movement of each type of piece on the board. In case you are brand new, we have a **How To Play** page just for this.

#### 4. Pawn Promotion/Castling
For pawn promotion, you will be **prompted with a UI** that shows all pieces you can promote to. Just **click which piece you would like to promote to**.

When castling, **select the king** and **click the square** where the **king would move to** if you were to castle.

#### 5. Invalid Moves/Checkmate/Stalemate and Playing Again
You will be **prompted with an alert** that informs you of *invalid moves, checkmates, and stalemates*. When the game ends with a *stalemate or checkmate*, you only need to **refresh the page to play again**.

## License
[LICENSE](LICENSE)