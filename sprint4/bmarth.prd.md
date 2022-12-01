# Product Requirements

Brandon Marth (bmarth) 

Product: ChessWebsite

### Background
- Our product is a website that allows the player to play chess against a difficult engine. Some players can not find another player to play against in real life. There is an opportunity to attract these users to play a single-player game against our engine. The engine is easier than the hardest engines out there but is harder than most and can beat some veteran players. This middle ground is the perfect bot for somewhat new players to challenge themselves against. The website would also have a page describing the rules of chess for new users. The engine could also be used without our website and could be used on other frontends.

### Project Overview
- Build a playable chess game where you can play against a chess engine.
The engine will be C++ that will make all the decisions using bitboards and bit arethmetic to increase performance.
The front end will be a svelte frame-work so that the player can simply open a browser and got to the domain
Front end board and pieces will be made from JavaScript
This engine could be sold for customers who already have the front-end and then use the engine to make it a single player experience

### Features
1. **Move pieces only according to chess rules** As a chess player, if I am going to play chess online I still want the rules to be the same as over the board chess.
2. **Be able to pick what color to play** As a chess player, when I play chess sometimes I want to play white pieces and sometimes I want to play black pieces.
3. **Have a engine to play against** As a chess player with no one to play against, I would like to able to play alone against a engine.
4. **Have page on the website talking about the rules of chess** As a new player to chess, tt would be great if there was somewhere on the website I could read the rules of chess.
5. **Pawn promotion** As a long term thinking player, I want to be able to choose what piece a pawn turns into when it promotes.
6. **Tie by various possibilities** As a fair player, the game should tie by turn timers, stalemate positions, and insuffencent materials.
7. **Win by checkmate** As a gamer, I want to win by putting my oppoent in a position they can't get out of.
8. **En passant** As a seasoned chess player, I want to be able to perform the greatest chess move of all time the en passant.

## Technologies to be used
Describe any tools and technologies to be used in the project. Include the languages, third-party libraries, and tools that will be used.

We will use C++ to create the engine the player will play against. Svelte, html, and css will be used to make the website the user will acess the board on. JavaScript is used to create the chessboard and chesspieces that the user will interact with on the website. Webassembly is used to convert the C++ backend into JavaScript that can be used in the frontend chessboard.