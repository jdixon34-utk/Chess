function fen(){
 
    let fen = "";

    let tab = document.getElementById("chessboard");
    var hold = tab.children[64];
    turn = hold.classList.item(0);
    cas = hold.classList.item(2);
    half = hold.classList.item(3);
    full = hold.classList.item(4) - 51;
    //console.log("T " + tur.classList.item(1));

    let count = tab.childElementCount;

    console.log("hi " + tab + " " + count + tab.children[0]);

    // iterate over all child nodes
    let space = 0;
    for(let i = 0; i < 64; i++){

        if(tab.children[i].children[0] === undefined){
            space++;
        }else{
            if(space !== 0){
                fen += space;
            }
            space = 0;
            fen += tab.children[i].children[0].classList.item(1);
        }

        if((((i + 1) % 8) === 0) && (i !== 63)){
            if(space !== 0){
                fen += space;
            }
            fen += '/';
            space = 0;
            console.log(i);
        }
    }

    fen += ' ';

    //Whose turn is it
    //b = black | white = w
    //Don't have this in front end yet
   
    let t = (turn === "white-piece") ? "w" : "b";
    
    fen += t + ' ';

    //Next you say what castling is available
    //q = castle queenside possible
    //k = castle kingside
    //Can be either KQkq or Qk- or -- or etc
    fen += cas + ' ';

    //Next you do en passant targets
    //you give it in terms of squares like e3.
    //This is different then how squares are named so will
    //Need to convert that either here or where they are made.

    //fen += pas + ' ';

    //Next is how many moves both players have made since the last pawn advance or piece capture
    //Global variable I assume, given as 99 or some other number
    //Game ends if draw if this is 100

    fen += half + ' ';
    //fen += " "

    //Last field is the number of completed turns in the game.
    //This number is incremented by one every time Black moves.
    //Global variable, is just a number

    fen += full + ' ';

    return fen;
}